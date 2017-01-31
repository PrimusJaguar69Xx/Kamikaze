#include "Default_Level.h"

void Default_Level::Load(SDL_Renderer* render) {
	nObjects = 0;
	soliderFrame = 0;
	solider_effectsFrame = 0;
	TargetFrame = 0;
	nSprite = 0;
	renderer = render;

	hitObjectEffect = new Effect("Resources/hit_object.png", render, 3, 64);
	hitSpriteEffect = new Effect("Resources/blood.png", render, 4, 64);

	boxes = new Object("Resources/boxes.png", render, 400, 200);
	boxes->CreateCustomHitbox(0, 0, 155, 190);
	objects[nObjects] = boxes->GetHitbox();
	nObjects++;

	solider = new Sprite(render);
	solider->InitSprite("Resources/solider_spritesheet.png");
	solider->CreateSpriteSheet(192, 192, 6, 6);
	solider->SetCenter(90, 130);
	solider->CreateCustomHitbox(60, 96, 60, 78);
	solider->ChangePos(90, 400, 400);
	solider->SetSpriteN(0);
	solider->UpdateHitbox();
	sprites[nSprite] = solider->GetHitbox();
	nSprite++;

	crosshair = new Crosshair("Resources/Crosshair.png", render, 200, solider->GetXPointer(), solider->GetYPointer(), solider->GetRotPointer(), solider->GetCenter());

	Target = new Sprite(render);
	Target->InitSprite("Resources/solider_spritesheet.png");
	Target->CreateSpriteSheet(192, 192, 6, 6);
	Target->SetCenter(90, 130);
	Target->CreateCustomHitbox(60, 96, 60, 78);
	Target->ChangePos(270, 800, 500);
	Target->SetState(0, 1);
	Target->SetSpriteN(1);
	Target->UpdateHitbox();
	sprites[nSprite] = Target->GetHitbox();
	nSprite++;

	solider_effects = new Sprite(render);
	solider_effects->InitSprite("Resources/solider_fire.png");
	solider_effects->CreateSpriteSheet(192, 192, 1, 4);
	solider_effects->SetCenter(90, 130);
	solider_effects->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX, solider->GetPos().spriteY);
	solider_effects->SetState(1, 0);

	LastKeyStates = SDL_GetKeyboardState(NULL);


	background = new MapTiles(render, "Resources/Tiles.png");
	background->InitTiles(48, 3, 3);
	background->LoadMap(40, 23, "Resources/map.map", false);

	walls = new MapTiles(render, "Resources/walls.png");
	walls->InitTiles(96, 3, 3);
	walls->LoadMap(20, 11, "Resources/objects.map", true);

	for (int i = 0; i < walls->GetNTilesOnMap(); i++) {
		objects[nObjects] = walls->GetIHitbox(i);
		nObjects++;
	}
}
void Default_Level::Unload() {

}
void Default_Level::Update() {

	solider->UpdateHitbox();
	Target->UpdateHitbox();

	sprites[0] = solider->GetHitbox();
	sprites[1] = Target->GetHitbox();

	if (solider->GetPos().spriteRot < 0) solider->ChangePos(solider->GetPos().spriteRot + 360, solider->GetPos().spriteX, solider->GetPos().spriteY);
	if (solider->GetPos().spriteRot > 360) solider->ChangePos(solider->GetPos().spriteRot - 360, solider->GetPos().spriteX, solider->GetPos().spriteY);

	const Uint8* KeyStates = SDL_GetKeyboardState(NULL);

	if (KeyStates[SDL_SCANCODE_Q]) {
		solider->ChangePos(solider->GetPos().spriteRot - SPRITE_ROT_VEL, solider->GetPos().spriteX, solider->GetPos().spriteY);
	}
	if (KeyStates[SDL_SCANCODE_E]) {
		solider->ChangePos(solider->GetPos().spriteRot + SPRITE_ROT_VEL, solider->GetPos().spriteX, solider->GetPos().spriteY);
	}

	if (!KeyStates[SDL_SCANCODE_W] && !KeyStates[SDL_SCANCODE_S] && !KeyStates[SDL_SCANCODE_A] && !KeyStates[SDL_SCANCODE_D]) {
		soliderFrame = 0; 
		solider->SetState(0, 1);
	}
	
	if (KeyStates[SDL_SCANCODE_W]) {
		solider->SetState(1, 4);
		
		soliderFrame++;
		

		double xDir = cos((solider->GetPos().spriteRot - 90) * 0.0174533);
		double yDir = sin((solider->GetPos().spriteRot - 90) * 0.0174533);

		double xMov = xDir * SPRITE_VEL;
		double yMov = yDir * SPRITE_VEL;




		if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(sprites, true, nSprite, xMov, yMov)) 
			solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		else printf("collided\n");
	}

	else if (KeyStates[SDL_SCANCODE_S]) {
		solider->SetState(2, 4);
		
		soliderFrame++;
		double xDir = cos((solider->GetPos().spriteRot-90) * 0.0174533);
		double yDir = sin((solider->GetPos().spriteRot-90) * 0.0174533);

		double xMov = xDir * SPRITE_VEL * -1;
		double yMov = yDir * SPRITE_VEL * -1;

		if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(sprites, true, nSprite, xMov, yMov))
			solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		else printf("collided\n");
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
			soliderFrame++;
		}
		else {
			soliderFrame++;
		}

		double xDir = cos((solider->GetPos().spriteRot) * 0.0174533);
		double yDir = sin((solider->GetPos().spriteRot) * 0.0174533);

		double xMov = xDir * SPRITE_VEL * -1;
		double yMov = yDir * SPRITE_VEL * -1;

		if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(sprites, true, nSprite, xMov, yMov))
			solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		else printf("collided\n");
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
			soliderFrame++;
		}
		else {
			soliderFrame++;
		}

		double xDir = cos((solider->GetPos().spriteRot) * 0.0174533);
		double yDir = sin((solider->GetPos().spriteRot) * 0.0174533);

		double xMov = xDir * SPRITE_VEL;
		double yMov = yDir * SPRITE_VEL;

		if (!solider->CheckCollision(objects, false, nObjects, xMov, yMov) && !solider->CheckCollision(sprites, true, nSprite, xMov, yMov))
			solider->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX + xMov, solider->GetPos().spriteY + yMov);
		else printf("collided\n");
	}

	if (KeyStates[SDL_SCANCODE_SPACE]) {
		if (solider_effects->GetState().aniN != 0) {
			solider_effects->SetState(0, 4);
			hitInfo info = solider->CheckLineOfFire(Target->GetHitbox(), objects, nObjects, 102, 54);
			if (info.Object == HITOBJECT_SPRITE) {
				XYRot temp;
				temp.spriteX = info.pointOfImpact.x + cos((info.angle - 90) * 0.0174533) * (Target->getAnimation(Target->GetState().aniN).sprites[0].w / 2);
				temp.spriteY = info.pointOfImpact.y + sin((info.angle - 90) * 0.0174533) * (Target->getAnimation(Target->GetState().aniN).sprites[0].h / 2);
				temp.spriteRot = info.angle;
				hitSpriteEffect->NewEffect(temp);
				Target->SetState(5, 6);
				printf("target hit");
			}
			else if (info.Object == HITOBJECT_OBSTACLE) {
				printf("hit: \nx: %d, %d\n\n", info.pointOfImpact.x, info.pointOfImpact.y);
				XYRot temp;
				temp.spriteX = info.pointOfImpact.x;
				temp.spriteY = info.pointOfImpact.y;
				temp.spriteRot = info.angle;
				hitObjectEffect->NewEffect(temp);
			}
			solider_effects->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX, solider->GetPos().spriteY);
		}
	}

	if (solider_effects->GetState().aniN == 0) {
		solider_effectsFrame++;
	}
	
	solider_effects->ChangePos(solider->GetPos().spriteRot, solider->GetPos().spriteX, solider->GetPos().spriteY);

	LastKeyStates = KeyStates;


	if ((TargetFrame / 24 < Target->GetState().nFrames-1) && (Target->GetState().aniN == 5)) TargetFrame++;
	if (soliderFrame / SPRITE_UPDATERATE >= solider->GetState().nFrames) soliderFrame = 0;
	if (solider_effectsFrame / SPRITE_EFFECT_UPDATERATE > 4) {
		solider_effectsFrame = 0;
		solider_effects->SetState(1, 0);
	}

	for (int i = 0; i < hitObjectEffect->GetNEffect(); i++) {
		hitObjectEffect->NextFrame(i);
	}

	for (int i = 0; i < hitSpriteEffect->GetNEffect(); i++) {
		hitSpriteEffect->NextFrame(i);
	}

	crosshair->UpdatePos();
}
void Default_Level::Render() {

	background->renderTiles();
	solider->RenderSprite(soliderFrame, SPRITE_UPDATERATE);
	if (solider_effects->GetState().aniN == 0) {
		solider_effects->GetTexture()->RenderTexture(solider_effects->GetPos().spriteX, solider_effects->GetPos().spriteY, &solider_effects->getAnimation(solider_effects->GetState().aniN).sprites[solider_effectsFrame / SPRITE_EFFECT_UPDATERATE], solider_effects->GetPos().spriteRot, solider_effects->GetCenter(), SDL_FLIP_NONE);
	}
	if (Target->GetState().aniN < 6) {
		Target->GetTexture()->RenderTexture(Target->GetPos().spriteX, Target->GetPos().spriteY, &Target->getAnimation(Target->GetState().aniN).sprites[TargetFrame / 24], Target->GetPos().spriteRot, Target->GetCenter(), SDL_FLIP_NONE);
	}
	boxes->RenderObject();
	walls->renderTiles();

	hitSpriteEffect->RenderEffects(renderer);
	hitObjectEffect->RenderEffects(renderer);


//	crosshair->Render();

//	SDL_RenderDrawRects(renderer, objects, nObjects);

}