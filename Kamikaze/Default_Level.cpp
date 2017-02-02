#include "Default_Level.h"

void Default_Level::Load(SDL_Renderer* render) {
	nObjects = 0;
//	nSprite = 0;
	renderer = render;
	spriteList.reserve(sizeof(Sprite) * 4);

	SDL_Color color = {255, 255, 255};
	timer = new Timer(120, "Resources/Pixeled.ttf", 864+16+2, 50+16+8, 102, 160, 28, color, render);

	hitObjectEffect = new Effect("Resources/hit_object.png", render, 3, 64);
	hitSpriteEffect = new Effect("Resources/blood.png", render, 4, 64);

	boxes = new Object("Resources/boxes.png", render, 400, 200);
	boxes->CreateCustomHitbox(0, 0, 155, 190);
	objects[nObjects] = boxes->GetHitbox();
	nObjects++;

	boxes2 = new Object("Resources/boxes.png", render, 1300, 200);
	boxes2->CreateCustomHitbox(0, 0, 155, 190);
	objects[nObjects] = boxes2->GetHitbox();
	nObjects++;

	boxes3 = new Object("Resources/boxes.png", render, 1250, 800);
	boxes3->CreateCustomHitbox(0, 0, 155, 190);
	objects[nObjects] = boxes3->GetHitbox();
	nObjects++;

	barrel = new Object("Resources/barrel.png", render, 1370, 360);
	objects[nObjects] = barrel->GetHitbox();
	nObjects++;

	barrel2 = new Object("Resources/barrel.png", render, 590, 150);
	objects[nObjects] = barrel2->GetHitbox();
	nObjects++;

	solider = new Sprite(render, SPRITE_UPDATERATE);
	solider->InitSprite("Resources/solider_spritesheet.png");
	solider->CreateSpriteSheet(192, 192, 6, 6);
	solider->SetCenter(90, 130);
	solider->CreateCustomHitbox(60, 96, 60, 78);
	solider->ChangePos(90, 180, 720);
	solider->SetSpriteN(0);
	solider->UpdateHitbox();
//	sprites[nSprite] = solider->GetHitbox();
	spriteList.push_back(solider);
//	nSprite++;

	crosshair = new Crosshair("Resources/Crosshair.png", render, 200, solider->GetXPointer(), solider->GetYPointer(), solider->GetRotPointer(), solider->GetCenter());

	solider2 = new Sprite(render, SPRITE_UPDATERATE);
	solider2->InitSprite("Resources/solider_spritesheet.png");
	solider2->CreateSpriteSheet(192, 192, 6, 6);
	solider2->SetCenter(90, 130);
	solider2->CreateCustomHitbox(60, 96, 60, 78);
	solider2->ChangePos(270, 1630, 200);
	solider2->SetState(0, 1);
	solider2->SetSpriteN(1);
	solider2->UpdateHitbox();
//	sprites[nSprite] = Target->GetHitbox();
	spriteList.push_back(solider2);
//	nSprite++;

	solider_effects = new Sprite(render, SPRITE_EFFECT_UPDATERATE);
	solider_effects->InitSprite("Resources/solider_fire.png");
	solider_effects->CreateSpriteSheet(192, 192, 1, 4);
	solider_effects->SetCenter(90, 130);
	solider_effects->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX, solider->GetPos().spriteY);
	solider_effects->SetState(1, 0);

	solider2_effects = new Sprite(render, SPRITE_EFFECT_UPDATERATE);
	solider2_effects->InitSprite("Resources/solider_fire.png");
	solider2_effects->CreateSpriteSheet(192, 192, 1, 4);
	solider2_effects->SetCenter(90, 130);
	solider2_effects->ChangePos(solider2->GetPos().spriteRot, solider2->GetPos().spriteX, solider2->GetPos().spriteY);
	solider2_effects->SetState(1, 0);

	LastKeyStates = SDL_GetKeyboardState(NULL);


	background = new MapTiles(render, "Resources/Tiles.png");
	background->InitTiles(96, 3, 4);
	background->LoadMap(20, 11, "Resources/map.map", false);

	walls = new MapTiles(render, "Resources/walls.png");
	walls->InitTiles(96, 4, 3);
	walls->LoadMap(20, 11, "Resources/objects.map", true);

	for (int i = 0; i < walls->GetNTilesOnMap(); i++) {
		objects[nObjects] = walls->GetIHitbox(i);
		nObjects++;
	}

	solider->SetFrame(0);
	solider_effects->SetFrame(0);
	solider2->SetFrame(0);
	solider2_effects->SetFrame(0);

	timer->StartTimer();
}
void Default_Level::Unload() {

}
void Default_Level::Update() {

	const Uint8* KeyStates = SDL_GetKeyboardState(NULL);

	//PLAYER 1
	//PLAYER 1
	//PLAYER 1

	if (solider->GetState().aniN != 5) {

		if (solider->GetPos().spriteRot < 0) solider->ChangePos(solider->GetPos().spriteRot + 360, solider->GetPos().spriteX, solider->GetPos().spriteY);
		if (solider->GetPos().spriteRot > 360) solider->ChangePos(solider->GetPos().spriteRot - 360, solider->GetPos().spriteX, solider->GetPos().spriteY);

		if (KeyStates[SDL_SCANCODE_Q]) {
			solider->ChangePos(solider->GetPos().spriteRot - SPRITE_ROT_VEL, solider->GetPos().spriteX, solider->GetPos().spriteY);
		}
		if (KeyStates[SDL_SCANCODE_E]) {
			solider->ChangePos(solider->GetPos().spriteRot + SPRITE_ROT_VEL, solider->GetPos().spriteX, solider->GetPos().spriteY);
		}

		if (!KeyStates[SDL_SCANCODE_W] && !KeyStates[SDL_SCANCODE_S] && !KeyStates[SDL_SCANCODE_A] && !KeyStates[SDL_SCANCODE_D]) {
			solider->SetFrame(0);
			solider->SetState(0, 1);
		}

		if (KeyStates[SDL_SCANCODE_W]) {
			solider->SetState(1, 4);

			solider->NextFrame(true);


			double xDir = cos((solider->GetPos().spriteRot - 90) * 0.0174533);
			double yDir = sin((solider->GetPos().spriteRot - 90) * 0.0174533);

			double xMov = xDir * SPRITE_VEL;
			double yMov = yDir * SPRITE_VEL;




			if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		}

		else if (KeyStates[SDL_SCANCODE_S]) {
			solider->SetState(2, 4);

			solider->NextFrame(true);
			double xDir = cos((solider->GetPos().spriteRot - 90) * 0.0174533);
			double yDir = sin((solider->GetPos().spriteRot - 90) * 0.0174533);

			double xMov = xDir * SPRITE_VEL * -1;
			double yMov = yDir * SPRITE_VEL * -1;

			if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		}

		if (KeyStates[SDL_SCANCODE_A]) {

			if (KeyStates[SDL_SCANCODE_W]) {
				solider->SetState(1, 4);
			}
			else if (KeyStates[SDL_SCANCODE_S]) {
				solider->SetState(2, 4);
			}
			else if (!(KeyStates[SDL_SCANCODE_S]) && !(KeyStates[SDL_SCANCODE_W])) {
				solider->SetState(4, 3);
				solider->NextFrame(true);
			}
			else {
				solider->NextFrame(true);
			}

			double xDir = cos((solider->GetPos().spriteRot) * 0.0174533);
			double yDir = sin((solider->GetPos().spriteRot) * 0.0174533);

			double xMov = xDir * SPRITE_VEL * -1;
			double yMov = yDir * SPRITE_VEL * -1;

			if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		}

		else if (KeyStates[SDL_SCANCODE_D]) {
			if (KeyStates[SDL_SCANCODE_W]) {
				solider->SetState(1, 4);
			}
			else if (KeyStates[SDL_SCANCODE_S]) {
				solider->SetState(2, 4);
			}
			else if (!(KeyStates[SDL_SCANCODE_S]) && !(KeyStates[SDL_SCANCODE_W])) {
				solider->SetState(3, 3);
				solider->NextFrame(true);
			}
			else {
				solider->NextFrame(true);
			}

			double xDir = cos((solider->GetPos().spriteRot) * 0.0174533);
			double yDir = sin((solider->GetPos().spriteRot) * 0.0174533);

			double xMov = xDir * SPRITE_VEL;
			double yMov = yDir * SPRITE_VEL;

			if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		}

		if (KeyStates[SDL_SCANCODE_SPACE]) {
			if (solider_effects->GetState().aniN != 0) {
				solider_effects->SetState(0, 4);
				hitInfo info = solider->CheckLineOfFire(spriteList, objects, nObjects, 102, 54);
				if (info.Object == HITOBJECT_SPRITE) {
					XYRot temp;
					temp.spriteX = info.pointOfImpact.x + cos((info.angle - 90) * 0.0174533) * (solider->getAnimation(solider->GetState().aniN).sprites[0].w / 2);
					temp.spriteY = info.pointOfImpact.y + sin((info.angle - 90) * 0.0174533) * (solider->getAnimation(solider->GetState().aniN).sprites[0].h / 2);
					temp.spriteRot = info.angle;
					hitSpriteEffect->NewEffect(temp);
					spriteList[info.nObject]->SetState(5, 6);
					spriteList[info.nObject]->CreateCustomHitbox(0, 0, 0, 0);
				}
				else if (info.Object == HITOBJECT_OBSTACLE) {
					printf("hit: \nx: %d, %d\n\n", info.pointOfImpact.x, info.pointOfImpact.y);
					XYRot temp;
					temp.spriteX = info.pointOfImpact.x;
					temp.spriteY = info.pointOfImpact.y;
					temp.spriteRot = info.angle;
					hitObjectEffect->NewEffect(temp);
				}
			}
		}

	}





	//PLAYER 2
	//PLAYER 2
	//PLAYER 2

	if (solider2->GetState().aniN != 5) {

		if (solider2->GetPos().spriteRot < 0) solider2->ChangePos(solider2->GetPos().spriteRot + 360, solider2->GetPos().spriteX, solider2->GetPos().spriteY);
		if (solider2->GetPos().spriteRot > 360) solider2->ChangePos(solider2->GetPos().spriteRot - 360, solider2->GetPos().spriteX, solider2->GetPos().spriteY);


		if (KeyStates[SDL_SCANCODE_COMMA]) {
			solider2->ChangePos(solider2->GetPos().spriteRot - SPRITE_ROT_VEL, solider2->GetPos().spriteX, solider2->GetPos().spriteY);
		}
		if (KeyStates[SDL_SCANCODE_SLASH]) {
			solider2->ChangePos(solider2->GetPos().spriteRot + SPRITE_ROT_VEL, solider2->GetPos().spriteX, solider2->GetPos().spriteY);
		}

		if (!KeyStates[SDL_SCANCODE_UP] && !KeyStates[SDL_SCANCODE_DOWN] && !KeyStates[SDL_SCANCODE_LEFT] && !KeyStates[SDL_SCANCODE_RIGHT]) {
			solider2->SetFrame(0);
			solider2->SetState(0, 1);
		}

		if (KeyStates[SDL_SCANCODE_UP]) {
			solider2->SetState(1, 4);

			solider2->NextFrame(true);


			double xDir = cos((solider2->GetPos().spriteRot - 90) * 0.0174533);
			double yDir = sin((solider2->GetPos().spriteRot - 90) * 0.0174533);

			double xMov = xDir * SPRITE_VEL;
			double yMov = yDir * SPRITE_VEL;



			if (!solider2->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider2->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider2->ChangePos(solider2->GetPos().spriteRot, solider2->GetPos().spriteX + xMov, solider2->GetPos().spriteY + yMov);
		}

		else if (KeyStates[SDL_SCANCODE_DOWN]) {
			solider2->SetState(2, 4);

			solider2->NextFrame(true);
			double xDir = cos((solider2->GetPos().spriteRot - 90) * 0.0174533);
			double yDir = sin((solider2->GetPos().spriteRot - 90) * 0.0174533);

			double xMov = xDir * SPRITE_VEL * -1;
			double yMov = yDir * SPRITE_VEL * -1;

			if (!solider2->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider2->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider2->ChangePos(solider2->GetPos().spriteRot, solider2->GetPos().spriteX + xMov, solider2->GetPos().spriteY + yMov);
		}

		if (KeyStates[SDL_SCANCODE_LEFT]) {

			if (KeyStates[SDL_SCANCODE_UP]) {
				solider2->SetState(1, 4);
			}
			else if (KeyStates[SDL_SCANCODE_DOWN]) {
				solider2->SetState(2, 4);
			}
			else if (!(KeyStates[SDL_SCANCODE_DOWN]) && !(KeyStates[SDL_SCANCODE_UP])) {
				solider2->SetState(4, 3);
				solider2->NextFrame(true);
			}
			else {
				solider2->NextFrame(true);
			}

			double xDir = cos((solider2->GetPos().spriteRot) * 0.0174533);
			double yDir = sin((solider2->GetPos().spriteRot) * 0.0174533);

			double xMov = xDir * SPRITE_VEL * -1;
			double yMov = yDir * SPRITE_VEL * -1;

			if (!solider2->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider2->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider2->ChangePos(solider2->GetPos().spriteRot, solider2->GetPos().spriteX + xMov, solider2->GetPos().spriteY + yMov);
		}

		else if (KeyStates[SDL_SCANCODE_RIGHT]) {
			if (KeyStates[SDL_SCANCODE_UP]) {
				solider2->SetState(1, 4);
			}
			else if (KeyStates[SDL_SCANCODE_DOWN]) {
				solider2->SetState(2, 4);
			}
			else if (!(KeyStates[SDL_SCANCODE_DOWN]) && !(KeyStates[SDL_SCANCODE_UP])) {
				solider2->SetState(3, 3);
				solider2->NextFrame(true);
			}
			else {
				solider2->NextFrame(true);
			}

			double xDir = cos((solider2->GetPos().spriteRot) * 0.0174533);
			double yDir = sin((solider2->GetPos().spriteRot) * 0.0174533);

			double xMov = xDir * SPRITE_VEL;
			double yMov = yDir * SPRITE_VEL;

			if (!solider2->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider2->CheckCollision(spriteList, true, spriteList.size(), xMov, yMov))
				solider2->ChangePos(solider2->GetPos().spriteRot, solider2->GetPos().spriteX + xMov, solider2->GetPos().spriteY + yMov);
		}

		if (KeyStates[SDL_SCANCODE_PERIOD]) {
			if (solider2_effects->GetState().aniN != 0) {
				solider2_effects->SetState(0, 4);
				hitInfo info = solider2->CheckLineOfFire(spriteList, objects, nObjects, 102, 54);
				if (info.Object == HITOBJECT_SPRITE) {
					XYRot temp;
					temp.spriteX = info.pointOfImpact.x + cos((info.angle - 90) * 0.0174533) * (solider2->getAnimation(solider->GetState().aniN).sprites[0].w / 2);
					temp.spriteY = info.pointOfImpact.y + sin((info.angle - 90) * 0.0174533) * (solider2->getAnimation(solider2->GetState().aniN).sprites[0].h / 2);
					temp.spriteRot = info.angle;
					hitSpriteEffect->NewEffect(temp);
					spriteList[info.nObject]->SetState(5, 6);
					spriteList[info.nObject]->CreateCustomHitbox(0, 0, 0, 0);
				}
				else if (info.Object == HITOBJECT_OBSTACLE) {
					printf("hit: \nx: %d, %d\n\n", info.pointOfImpact.x, info.pointOfImpact.y);
					XYRot temp;
					temp.spriteX = info.pointOfImpact.x;
					temp.spriteY = info.pointOfImpact.y;
					temp.spriteRot = info.angle;
					hitObjectEffect->NewEffect(temp);
				}
			}
		}

	}

	if ((KeyStates[SDL_SCANCODE_T]) && ((solider->GetState().aniN == 5) || (solider2->GetState().aniN == 5))) {
		solider->ChangePos(90, 180, 720);
		solider->SetState(0, 1);
		solider->SetFrame(0);
		solider->CreateCustomHitbox(60, 96, 60, 78);

		solider2->ChangePos(270, 1630, 200);
		solider2->SetState(0, 1);
		solider2->SetFrame(0);
		solider2->CreateCustomHitbox(60, 96, 60, 78);
	}

	solider->UpdateHitbox();
	solider2->UpdateHitbox();


	if (solider_effects->GetState().aniN == 0) {
		solider_effects->NextFrame(false);
	}


	if (solider2_effects->GetState().aniN == 0) {
		solider2_effects->NextFrame(false);
	}

	LastKeyStates = KeyStates;


//	if ((solider2->GetFrame() / solider2->GetUpdateRate() < solider2->GetState().nFrames-1) && (solider2->GetState().aniN == 5)) solider2->NextFrame(true);
	
	if (solider2_effects->GetFrame() / SPRITE_EFFECT_UPDATERATE > 4) {
		solider2_effects->SetFrame(0);
		solider2_effects->SetState(1, 0);
	}
	
	if (solider_effects->GetFrame() / SPRITE_EFFECT_UPDATERATE > 4) {
		solider_effects->SetFrame(0);
		solider_effects->SetState(1, 0);
	}

	for (int i = 0; i < hitObjectEffect->GetNEffect(); i++) {
		hitObjectEffect->NextFrame(i);
	}

	for (int i = 0; i < hitSpriteEffect->GetNEffect(); i++) {
		hitSpriteEffect->NextFrame(i);
	}

	solider2_effects->ChangePos(solider2->GetPos().spriteRot, solider2->GetPos().spriteX, solider2->GetPos().spriteY);
	solider_effects->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX, solider->GetPos().spriteY);

	crosshair->UpdatePos();

	if ((solider->GetState().aniN == 5) && ((solider->GetFrame()+1) / solider->GetUpdateRate() < solider->GetState().nFrames)) {
		solider->NextFrame(false);
	}

	if ((solider2->GetState().aniN == 5) && ((solider2->GetFrame()+1) / solider2->GetUpdateRate() < solider2->GetState().nFrames)) {
		solider2->NextFrame(false);
	}
}
void Default_Level::Render() {
	
	background->renderTiles();

//	spriteList[0]->RenderSprite();
//	spriteList[1]->RenderSprite();


	for (int i = 0; i < spriteList.size(); i++) {
		if (spriteList[i]->GetState().aniN == 5) {
			spriteList[i]->RenderSprite();
		}
	}

	for (int i = 0; i < spriteList.size(); i++) {
		if (spriteList[i]->GetState().aniN != 5) {
			spriteList[i]->RenderSprite();
		}
	}
	
	if (solider_effects->GetState().aniN == 0) {
		solider_effects->RenderSprite();
	}

	if (solider2_effects->GetState().aniN == 0) {
		solider2_effects->RenderSprite();
	}

	boxes->RenderObject();
	boxes2->RenderObject();
	boxes3->RenderObject();

	barrel->RenderObject();
	barrel2->RenderObject();

	walls->renderTiles();

	hitSpriteEffect->RenderEffects(renderer);
	hitObjectEffect->RenderEffects(renderer);

//	SDL_RenderDrawRects(renderer, objects, nObjects);

}