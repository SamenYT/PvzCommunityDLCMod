#include "Board.h"
#include "Plant.h"
#include "Zombie.h"
#include "GridItem.h"
#include "Cutscene.h"
#include "Projectile.h"
#include "../LawnApp.h"
#include "../Resources.h"
#include "../GameConstants.h"
#include "../Sexy.TodLib/TodFoley.h"
#include "../Sexy.TodLib/TodDebug.h"
#include "../Sexy.TodLib/Reanimator.h"
#include "../Sexy.TodLib/Attachment.h"
#include "../Sexy.TodLib/TodFoley.h"
#include "../Sexy.TodLib/TodCommon.h"
#include "../Sexy.TodLib/TodParticle.h"

ProjectileDefinition gProjectileDefinition[] = {  //0x69F1C0
	{ ProjectileType::PROJECTILE_PEA,            0,  20  },
	{ ProjectileType::PROJECTILE_SNOWPEA,        0,  20  },
	{ ProjectileType::PROJECTILE_CABBAGE,        0,  40  },
	{ ProjectileType::PROJECTILE_MELON,          0,  80  },
	{ ProjectileType::PROJECTILE_PUFF,           0,  20  },
	{ ProjectileType::PROJECTILE_WINTERMELON,    0,  80  },
	{ ProjectileType::PROJECTILE_FIREBALL,       0,  40  },
	{ ProjectileType::PROJECTILE_PLASMABALL,     0,  60  },
	{ ProjectileType::PROJECTILE_ICEQUEEN,       0,  20  },
	{ ProjectileType::PROJECTILE_ELECTRIC,       0,  80  },
	{ ProjectileType::PROJECTILE_STAR,           0,  20  },
	{ ProjectileType::PROJECTILE_SEASTAR,        0,  20  },
	{ ProjectileType::PROJECTILE_SPIKE,          0,  20  },
	{ ProjectileType::PROJECTILE_BASKETBALL,     0,  75  },
	{ ProjectileType::PROJECTILE_KERNEL,         0,  20  },
	{ ProjectileType::PROJECTILE_COBBIG,         0,  300 },
	{ ProjectileType::PROJECTILE_BUTTER,         0,  40  },
	{ ProjectileType::PROJECTILE_ZOMBIE_PEA,     0,  20  },
	{ ProjectileType::PROJECTILE_PEPPER,         0,  60  },	
	{ ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA, 0,  20  },
	{ ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA,0,  40  },
	{ ProjectileType::PROJECTILE_ARROW,			 0,  80  },
	{ ProjectileType::PROJECTILE_BEE,			 0,  20  },
	{ ProjectileType::PROJECTILE_SHOOTING_STAR,	 0,  40  }
};

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
	AttachmentDie(mAttachmentID);
}

//0x46C730
void Projectile::ProjectileInitialize(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType)
{
	int aGridX = mBoard->PixelToGridXKeepOnBoard(theX, theY);
	mProjectileType = theProjectileType;
	mPosX = theX;
	mPosY = theY;
	mPosZ = 0.0f;
	mVelX = 0.0f;
	mVelY = 0.0f;
	mVelZ = 0.0f;
	mAccZ = 0.0f;
	mShadowY = mBoard->GridToPixelY(aGridX, theRow) + 67.0f;
	mHitTorchwoodGridX = -1;
	mMotionType = ProjectileMotion::MOTION_STRAIGHT;
	mFrame = 0;
	mNumFrames = 1;
	mRow = theRow;
	mCobTargetX = 0.0f;
	mDamageRangeFlags = 0;
	mDead = false;
	mAttachmentID = AttachmentID::ATTACHMENTID_NULL;
	mCobTargetRow = 0;
	mTargetZombieID = ZombieID::ZOMBIEID_NULL;
	mOnHighGround = mBoard->mGridSquareType[aGridX][theRow] == GridSquareType::GRIDSQUARE_HIGH_GROUND;
	if (mBoard->StageHasRoof())
	{
		mShadowY -= 12.0f;
	}
	mRenderOrder = theRenderOrder;
	mRotation = 0.0f;
	mRotationSpeed = 0.0f;
	mWidth = 40;
	mHeight = 40;
	mProjectileAge = 0;
	mClickBackoffCounter = 0;
	mAnimTicksPerFrame = 0;
	mProjOrder = 0.0f;
	mRadius = 0.0f;
	mExpAm = 0.0f;
	mleft = false;

	if (mProjectileType == ProjectileType::PROJECTILE_CABBAGE || mProjectileType == ProjectileType::PROJECTILE_BUTTER)
	{
		mRotation = -7 * PI / 25;  // DEG_TO_RAD(-50.4f);
		mRotationSpeed = RandRangeFloat(-0.08f, -0.02f);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_MELON || mProjectileType == ProjectileType::PROJECTILE_WINTERMELON)
	{
		mRotation = -2 * PI / 5;  // DEG_TO_RAD(-72.0f);
		mRotationSpeed = RandRangeFloat(-0.08f, -0.02f);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_KERNEL)
	{
		mRotation = 0.0f;
		mRotationSpeed = RandRangeFloat(-0.2f, -0.08f);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA)
	{
		TodParticleSystem* aParticle = mApp->AddTodParticle(mPosX + 8.0f, mPosY + 13.0f, 400000, ParticleEffect::PARTICLE_SNOWPEA_TRAIL);
		AttachParticle(mAttachmentID, aParticle, 8.0f, 13.0f);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN)
	{
		TodParticleSystem* aParticle = mApp->AddTodParticle(mPosX + 8.0f, mPosY + 13.0f, 400000, ParticleEffect::PARTICLE_SNOWPEA_TRAIL);
		AttachParticle(mAttachmentID, aParticle, 8.0f, 13.0f);

		aParticle = mApp->AddTodParticle(mPosX + 8.0f, mPosY + 13.0f, 400000, ParticleEffect::PARTICLE_SNOWPEA_TRAIL);
		AttachParticle(mAttachmentID, aParticle, 8.0f, 13.0f);

		aParticle = mApp->AddTodParticle(mPosX + 8.0f, mPosY + 13.0f, 400000, ParticleEffect::PARTICLE_SNOWPEA_TRAIL);
		AttachParticle(mAttachmentID, aParticle, 8.0f, 13.0f);

	}
	else if (mProjectileType == PROJECTILE_SHOOTING_STAR)
	{
		float aOffsetX = 0;
		float aOffsetY = 0;
		Reanimation* aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_PROJECTILE_SHOOTINGSTAR);
		/*if (mBackwards)
		{
			aFirePeaReanim->OverrideScale(-1.0f, 1.0f);
			aOffsetX += 80.0f;
		}*/

		aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
		aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
		aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
		AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA)
	{
		//TOD_ASSERT();
		//TodParticleSystem* aParticle = mApp->AddTodParticle(mPosX + 8.0f, mPosY + 13.0f, 400000, ParticleEffect::PARTICLE_SNOWPEA_TRAIL);
		//AttachParticle(mAttachmentID, aParticle, 8.0f, 13.0f);
		//aParticle->OverrideColor(nullptr, Color(255, 0, 0, 255));
		float aOffsetX = -25.0f; //turn into firepea animation
		float aOffsetY = -25.0f;
		Reanimation* aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_FIRE_PEA);
		if (mMotionType == ProjectileMotion::MOTION_BACKWARDS || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA)
		{
			aFirePeaReanim->OverrideScale(-1.0f, 1.0f);
			aOffsetX += 80.0f;
		}

		aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
		aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
		aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
		AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY);

		aFirePeaReanim->mIsAttachment = true;
		aFirePeaReanimID = mApp->ReanimationGetID(aFirePeaReanim);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PLASMABALL)
	{
		float aOffsetX = -25.0f; //turn into plasmapea animation
		float aOffsetY = -25.0f;
		Reanimation* aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_PLASMA_PEA);
		if (mMotionType == ProjectileMotion::MOTION_BACKWARDS)
		{
			aFirePeaReanim->OverrideScale(-1.0f, 1.0f);
			aOffsetX += 80.0f;
		}

		aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
		aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
		aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
		AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_BEE)
	{
		int randomNumber = Sexy::Rand(2);
		if (randomNumber == 1) mApp->PlayFoley(FOLEY_BEE1);
		else mApp->PlayFoley(FOLEY_BEE2);

		float aOffsetX = -25.0f; //turn into plasmapea animation
		float aOffsetY = 25.0f;
		Reanimation* aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_BEE);

		aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
		aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
		aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
		AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY);
		aFirePeaReanim->mIsAttachment = true;
		aFirePeaReanimID = mApp->ReanimationGetID(aFirePeaReanim);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PEPPER)
	{
		float aOffsetX = -25.0f; //turn into pepper animation
		float aOffsetY = -25.0f;
		Reanimation* aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_PEPPERBALL);
		if (mMotionType == ProjectileMotion::MOTION_BACKWARDS)
		{
			aFirePeaReanim->OverrideScale(-1.0f, 1.0f);
			aOffsetX += 80.0f;
		}

		aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
		aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
		aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
		AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY);
		aFirePeaReanim->mIsAttachment = true;
		aFirePeaReanimID = mApp->ReanimationGetID(aFirePeaReanim);
		
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ELECTRIC)
	{
		float aOffsetX = -25.0f; //turn into electric animation
		float aOffsetY = -25.0f;
		Reanimation* aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ELECTRIC_PEA);
		if (mMotionType == ProjectileMotion::MOTION_BACKWARDS)
		{
			aFirePeaReanim->OverrideScale(-1.0f, 1.0f);
			aOffsetX += 80.0f;
		} 

		aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
		aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
		aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
		AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY);
	} 
	else if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		mWidth = IMAGE_REANIM_COBCANNON_COB->GetWidth();
		mHeight = IMAGE_REANIM_COBCANNON_COB->GetHeight();
		mRotation = PI / 2;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PUFF)
	{
		TodParticleSystem* aParticle = mApp->AddTodParticle(mPosX + 13.0f, mPosY + 13.0f, 400000, ParticleEffect::PARTICLE_PUFFSHROOM_TRAIL);
		AttachParticle(mAttachmentID, aParticle, 13.0f, 13.0f);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_BASKETBALL)
	{
		mRotation = RandRangeFloat(0.0f, 2 * PI);
		mRotationSpeed = RandRangeFloat(0.05f, 0.1f);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_STAR || mProjectileType == ProjectileType::PROJECTILE_SEASTAR)
	{
		mShadowY += 15.0f;
		mRotationSpeed = RandRangeFloat(0.05f, 0.1f);
		if (Rand(2) == 0)
		{
			mRotationSpeed = -mRotationSpeed;
		}
	}

	mAnimCounter = 0;
	mX = (int)mPosX;
	mY = (int)mPosY;
}

//0x46CAA0
Plant* Projectile::FindCollisionTargetPlant()
{
	Rect aProjectileRect = GetProjectileRect();

	Plant* aPlant = nullptr;
	while (mBoard->IteratePlants(aPlant))
	{
		if (aPlant->mRow != mRow)
			continue;

		if (mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA)
		{
			if (aPlant->mSeedType == SeedType::SEED_PUFFSHROOM ||
				aPlant->mSeedType == SeedType::SEED_REVERSE_PUFFSHROOM ||
			    aPlant->mSeedType == SeedType::SEED_PULTSHROOM ||
				aPlant->mSeedType == SeedType::SEED_SUNSHROOM ||
				aPlant->mSeedType == SeedType::SEED_POTATOMINE ||
				aPlant->mSeedType == SeedType::SEED_SPIKEWEED ||
				aPlant->mSeedType == SeedType::SEED_SPIKEROCK ||
				aPlant->mSeedType == SeedType::SEED_THORNMOSS ||
				aPlant->mSeedType == SeedType::SEED_LILYPAD)  // 僵尸豌豆不能击中低矮植物
				continue;
		}

		Rect aPlantRect = aPlant->GetPlantRect();
		if (GetRectOverlap(aProjectileRect, aPlantRect) > 8)
		{
			if (mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA)
			{
				return mBoard->GetTopPlantAt(aPlant->mPlantCol, aPlant->mRow, PlantPriority::TOPPLANT_EATING_ORDER);
			}
			else
			{
				return mBoard->GetTopPlantAt(aPlant->mPlantCol, aPlant->mRow, PlantPriority::TOPPLANT_CATAPULT_ORDER);
			}
		}
	}

	return nullptr;
}

//0x46CC30
bool Projectile::PeaAboutToHitTorchwood()
{
	if (mMotionType != ProjectileMotion::MOTION_STRAIGHT)
		return false;

	if (mProjectileType != ProjectileType::PROJECTILE_PEA && mProjectileType != ProjectileType::PROJECTILE_SNOWPEA && mProjectileType != ProjectileType::PROJECTILE_FIREBALL
		&& mProjectileType != ProjectileType::PROJECTILE_PLASMABALL)
		return false;

	Plant* aPlant = nullptr;
	while (mBoard->IteratePlants(aPlant))
	{
		if ((aPlant->mSeedType == SeedType::SEED_TORCHWOOD || aPlant->mSeedType == SeedType::SEED_FLAMEWOOD) 
			&& aPlant->mRow == mRow && !aPlant->NotOnGround() && mHitTorchwoodGridX != aPlant->mPlantCol)
		{
			Rect aPlantAttackRect = aPlant->GetPlantAttackRect(PlantWeapon::WEAPON_PRIMARY);
			Rect aProjectileRect = GetProjectileRect();
			aProjectileRect.mX += 40;

			if (GetRectOverlap(aPlantAttackRect, aProjectileRect) > 10)
			{
				return true;
			}
		}
	}

	return false;
}

//0x46CD40
Zombie* Projectile::FindCollisionTarget()
{
	if (PeaAboutToHitTorchwood())  // “卡火炬”的原理，这段代码在两版内测版中均不存在
		return nullptr;

	Rect aProjectileRect = GetProjectileRect();
	Zombie* aBestZombie = nullptr;
	int aMinX = 0;

	Zombie* aZombie = nullptr;
	while (mBoard->IterateZombies(aZombie))
	{
		if ((aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mRow == mRow) && aZombie->EffectedByDamage((unsigned int)mDamageRangeFlags))
		{
			if (aZombie->mZombiePhase == ZombiePhase::PHASE_SNORKEL_WALKING_IN_POOL && mPosZ >= 45.0f)
			{
				continue;
			}

			if (mProjectileType == ProjectileType::PROJECTILE_STAR && mProjectileAge < 25 && mVelX >= 0.0f && aZombie->mZombieType == ZombieType::ZOMBIE_DIGGER)
			{
				continue;
			}

			Rect aZombieRect = aZombie->GetZombieRect();
			if (GetRectOverlap(aProjectileRect, aZombieRect) > 0)
			{
				if (aBestZombie == nullptr || aZombie->mX < aMinX)
				{
					aBestZombie = aZombie;
					aMinX = aZombie->mX;
				}
			}
		}
	}

	return aBestZombie;
}

GridItem* Projectile::FindCollisionTargetGridItem()
{
	Rect aProjectileRect = GetProjectileRect();
	GridItem* aBestGridItem = nullptr;
	int aMinX = 0;

	GridItem* aGridItem = nullptr;
	while (mBoard->IterateGridItems(aGridItem))
	{
		if (aGridItem->mGridY == mRow)
		{
			Rect aGridItemRect = aGridItem->GetGridItemRect();
			if (GetRectOverlap(aProjectileRect, aGridItemRect) > 0)
			{
				if (aBestGridItem == nullptr || aGridItem->mGridX * 80.0f < aMinX)
				{
					aBestGridItem = aGridItem;
					aMinX = aGridItem->mGridX * 80.0f;
				}
				aBestGridItem = aGridItem;
			}
		}
	}

	//if (aBestGridItem != nullptr) mApp->PlayFoley(FOLEY_SCREAM);

	return aBestGridItem;
}

//0x46CE80
void Projectile::CheckForCollision()
{
	if (mMotionType == ProjectileMotion::MOTION_PUFF && mProjectileAge >= 75)
	{
		Die();
		return;
	}

	if (mPosX > WIDE_BOARD_WIDTH || mPosX + mWidth < 0.0f)
	{
		Die();
		return;
	}

	if (mMotionType == ProjectileMotion::MOTION_HOMING)
	{
		Zombie* aZombie = mBoard->ZombieTryToGet(mTargetZombieID);
		if (aZombie && aZombie->EffectedByDamage((unsigned int)mDamageRangeFlags))
		{
			Rect aProjectileRect = GetProjectileRect();
			Rect aZombieRect = aZombie->GetZombieRect();
			if (GetRectOverlap(aProjectileRect, aZombieRect) >= 0 && mPosY > aZombieRect.mY&& mPosY < aZombieRect.mY + aZombieRect.mHeight)
			{
				DoImpact(aZombie);
			}
		}
		return;
	}

	if ((mProjectileType == ProjectileType::PROJECTILE_STAR || mProjectileType == ProjectileType::PROJECTILE_SEASTAR) && (mPosY > 600.0f || mPosY < 0.0f))
	{
		Die();
		return;
	}

	if ((mProjectileType == ProjectileType::PROJECTILE_PEA || mProjectileType == ProjectileType::PROJECTILE_STAR || mProjectileType == ProjectileType::PROJECTILE_SEASTAR) && mShadowY - mPosY > 90.0f)
	{
		return;
	}

	if (mMotionType == ProjectileMotion::MOTION_FLOAT_OVER)
	{
		return;
	}

	if (mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA)
	{
		Plant* aPlant = FindCollisionTargetPlant();
		if (aPlant && !aPlant->mHypnotized)
		{
			const ProjectileDefinition& aProjectileDef = GetProjectileDef();
			aPlant->mPlantHealth -= aProjectileDef.mDamage;
			aPlant->mEatenFlashCountdown = max(aPlant->mEatenFlashCountdown, 25);
			
			if (mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA)
			{
				if ((!aPlant->IsFirePlant() && !aPlant->IsFrozenPlant()) && aPlant->mChilledCounter == 0 && !mBoard->FindFirePlant(aPlant->mPlantCol, aPlant->mRow)) mApp->PlayFoley(FoleyType::FOLEY_FROZEN);
				aPlant->FreezePlant();
				mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
				mApp->AddTodParticle(mPosX - 3.0f, mPosY + 17.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_SNOWPEA_SPLAT);
			}
			else if (mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA)
			{
				if ((!aPlant->IsFirePlant() && !aPlant->IsFrozenPlant()) && aPlant->mChilledCounter == 0 && !mBoard->FindFirePlant(aPlant->mPlantCol, aPlant->mRow)) mApp->PlayFoley(FoleyType::FOLEY_IGNITE);
				Reanimation* aFireReanim = mApp->AddReanimation(mPosX - 5.0f, mPosY + 0.0f, mRenderOrder + 1, ReanimationType::REANIM_JALAPENO_FIRE);
				aFireReanim->mAnimTime = 0.25f;
				aFireReanim->mAnimRate = 24.0f;
				aFireReanim->OverrideScale(0.7f, 0.4f);
				aPlant->mChilledCounter = 0;
			}
			else if (mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR)
			{
				Reanimation* aFireReanim = mApp->AddReanimation(mPosX, mPosY - 23.0f + 337, mRenderOrder + 1, ReanimationType::REANIM_JALAPENO_FIRE);
				aFireReanim->mAnimTime = 0.25f;
				aFireReanim->mAnimRate = 24.0f;
				aFireReanim->OverrideScale(0.7f, 0.4f);
			}
			else
			{
				mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
				mApp->AddTodParticle(mPosX - 3.0f, mPosY + 17.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_PEA_SPLAT);
			}
			
			Die();
		}
		return;
	}

	Zombie* aZombie = FindCollisionTarget();
	if (aZombie)
	{
		if (aZombie->mOnHighGround && CantHitHighGround())
		{
			return;
		}

		DoImpact(aZombie);
	}
	GridItem* aGridItem = FindCollisionTargetGridItem();
	if (aGridItem)
	{
		DoImpactGridItem(aGridItem);
		//DoImpact(aZombie);
	}
	Plant* aPlant = FindCollisionTargetPlant();
	if (aPlant)
	{
		if (aPlant->mSeedType == SEED_GRAVE || aPlant->mHypnotized)
		{
			DoImpactPlant(aPlant);
		}
	}
}

void Projectile::DoImpactPlant(Plant* thePlant)
{
	const ProjectileDefinition& aProjectileDef = GetProjectileDef();
	thePlant->mPlantHealth -= aProjectileDef.mDamage;
	thePlant->mEatenFlashCountdown = max(thePlant->mEatenFlashCountdown, 25);

	if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL)
	{
		if ((!thePlant->IsFirePlant() && !thePlant->IsFrozenPlant()) && thePlant->mChilledCounter == 0 && !mBoard->FindFirePlant(thePlant->mPlantCol, thePlant->mRow)) 
		mApp->PlayFoley(FoleyType::FOLEY_IGNITE);
		ReanimationType aReanimType = REANIM_JALAPENO_FIRE;
		if (mProjectileType == ProjectileType::PROJECTILE_PLASMABALL) aReanimType = REANIM_PLASMA_FIRE;
		Reanimation* aFireReanim = mApp->AddReanimation(mPosX - 5.0f, mPosY + 0.0f, mRenderOrder + 1, aReanimType);
		aFireReanim->mAnimTime = 0.25f;
		aFireReanim->mAnimRate = 24.0f;
		aFireReanim->OverrideScale(0.7f, 0.4f);
		//if (mProjectileType == ProjectileType::PROJECTILE_PLASMABALL) aFireReanim->mColorOverride = Color(0, 255, 255, 255);
		thePlant->mChilledCounter = 0;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ELECTRIC)
	{
		int aRand = Rand(2);
		if (aRand == 0)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC);
		else if (aRand == 1)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC2);
		else  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC3);
		mApp->AddTodParticle(mPosX - 3.0f, mPosY + 17.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_PEA_SPLAT);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA)
	{
		if (thePlant->mSeedType != SEED_GRAVE)
		{
			if ((!thePlant->IsFirePlant() && !thePlant->IsFrozenPlant()) && thePlant->mChilledCounter == 0 && !mBoard->FindFirePlant(thePlant->mPlantCol, thePlant->mRow)) mApp->PlayFoley(FoleyType::FOLEY_FROZEN);
			thePlant->FreezePlant();
		}
		mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
		mApp->AddTodParticle(mPosX - 3.0f, mPosY + 17.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_SNOWPEA_SPLAT);
	}
	else
	{
		mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
		mApp->AddTodParticle(mPosX - 3.0f, mPosY + 17.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_PEA_SPLAT);
	}

	Die();
}

//0x46D090
bool Projectile::CantHitHighGround()
{
	if (mMotionType == ProjectileMotion::MOTION_BACKWARDS || mProjectileType == PROJECTILE_SHOOTING_STAR || mMotionType == ProjectileMotion::MOTION_HOMING)
		return false;

	return (
		mProjectileType == ProjectileType::PROJECTILE_PEA ||
		mProjectileType == ProjectileType::PROJECTILE_SNOWPEA ||
		mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN ||
		//mProjectileType == ProjectileType::PROJECTILE_ELECTRIC ||
		mProjectileType == ProjectileType::PROJECTILE_STAR ||
		mProjectileType == ProjectileType::PROJECTILE_SEASTAR ||
		mProjectileType == ProjectileType::PROJECTILE_PUFF ||
		mProjectileType == ProjectileType::PROJECTILE_FIREBALL ||
		mProjectileType == ProjectileType::PROJECTILE_PLASMABALL
		) && !mOnHighGround;
}

//0x46D0D0
void Projectile::CheckForHighGround()
{
	if (mProjectileType == PROJECTILE_SHOOTING_STAR)
		return;

	float aShadowDelta = mShadowY - mPosY;

	if (mProjectileType == ProjectileType::PROJECTILE_PEA ||
		mProjectileType == ProjectileType::PROJECTILE_SNOWPEA ||
		mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN ||
		//mProjectileType == ProjectileType::PROJECTILE_ELECTRIC ||
		mProjectileType == ProjectileType::PROJECTILE_FIREBALL ||
		mProjectileType == ProjectileType::PROJECTILE_PLASMABALL ||
		mProjectileType == ProjectileType::PROJECTILE_SPIKE ||
		mProjectileType == ProjectileType::PROJECTILE_ARROW ||
		mProjectileType == ProjectileType::PROJECTILE_BEE ||
		mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		if (aShadowDelta < 28.0f)
		{
			DoImpact(nullptr);
			return;
		}
	}

	if (mProjectileType == ProjectileType::PROJECTILE_PUFF && aShadowDelta < 0.0f)
	{
		DoImpact(nullptr);
		return;
	}

	if ((mProjectileType == ProjectileType::PROJECTILE_STAR || mProjectileType == ProjectileType::PROJECTILE_SEASTAR) && aShadowDelta < 23.0f)
	{
		DoImpact(nullptr);
		return;
	}

	if (CantHitHighGround())
	{
		int aGridX = mBoard->PixelToGridXKeepOnBoard(mPosX + 30, mPosY);
		if (mBoard->mGridSquareType[aGridX][mRow] == GridSquareType::GRIDSQUARE_HIGH_GROUND)
		{
			DoImpact(nullptr);
		}
	}
}

//0x46D1F0
bool Projectile::IsSplashDamage(Zombie* theZombie)
{
	if (mProjectileType && theZombie && theZombie->IsFireResistant() && mProjectileType != ProjectileType::PROJECTILE_SHOOTING_STAR)
		return false;

	return 
		mProjectileType == ProjectileType::PROJECTILE_MELON || 
		mProjectileType == ProjectileType::PROJECTILE_PEPPER ||
		mProjectileType == ProjectileType::PROJECTILE_WINTERMELON || 
		mProjectileType == ProjectileType::PROJECTILE_FIREBALL ||
		mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR ||
		mProjectileType == ProjectileType::PROJECTILE_ELECTRIC ||
		mProjectileType == ProjectileType::PROJECTILE_PLASMABALL;
}

//0x46D230
unsigned int Projectile::GetDamageFlags(Zombie* theZombie)
{
	unsigned int aDamageFlags = 0U;

	if (IsSplashDamage(theZombie))
	{
		SetBit(aDamageFlags, (int)DamageFlags::DAMAGE_HITS_SHIELD_AND_BODY, true);
		if (mProjectileType == PROJECTILE_PEPPER) theZombie->RemoveColdEffects();
	}
	else if (mMotionType == ProjectileMotion::MOTION_LOBBED || mMotionType == ProjectileMotion::MOTION_BACKWARDS)
	{
		SetBit(aDamageFlags, (int)DamageFlags::DAMAGE_BYPASSES_SHIELD, true);
	}
	else if (mMotionType == ProjectileMotion::MOTION_STAR && mVelX < 0.0f)
	{
		SetBit(aDamageFlags, (int)DamageFlags::DAMAGE_BYPASSES_SHIELD, true);
	}

	if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA || mProjectileType == ProjectileType::PROJECTILE_WINTERMELON)
	{
		SetBit(aDamageFlags, (int)DamageFlags::DAMAGE_FREEZE, true);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN)
	{
		//SetBit(aDamageFlags, (int)DamageFlags::DAMAGE_FREEZE, true);
		if (theZombie->mShieldType != ShieldType::SHIELDTYPE_DOOR && theZombie->mShieldType != ShieldType::SHIELDTYPE_LADDER && theZombie->mShieldType != ShieldType::SHIELDTYPE_TRASHCAN && theZombie->mShieldType != ShieldType::SHIELDTYPE_NEWSPAPER)
		{
			if (theZombie->CanBeChilled())
			{
				theZombie->HitIceTrap();
				theZombie->mIceTrapCounter = 50;
			}
			else theZombie->ApplyChill(theZombie);
		}
	}
	/*else if (mProjectileType == ProjectileType::PROJECTILE_SEASTAR)
	{
		theZombie->mHypnoCounter = 50;
	}*/
	else if (mProjectileType == ProjectileType::PROJECTILE_ELECTRIC) //teleport 
	{
		int aRand = Rand(2);
		if (aRand == 0)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC);
		else if (aRand == 1)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC2);
		else  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC3);
		SetBit(aDamageFlags, (int)DamageFlags::DAMAGE_HITS_SHIELD_AND_BODY, true);
		//if (!theZombie->mHasHead) theZombie->ApplyBurn();
		//float aShootAngleX = cos(DEG_TO_RAD(30.0f)) * 3.33f;
		//loat aShootAngleY = sin(DEG_TO_RAD(30.0f)) * 3.33f;
		/*for (int i = 0; i < 8; i++)
		{
			Projectile* aProjectile = mBoard->AddProjectile(mX + 25, mY + 25, mRenderOrder - 1, mRow, ProjectileType::PROJECTILE_ELECTRIC);
			//aProjectile->mDamageRangeFlags = 1;
			aProjectile->mMotionType = ProjectileMotion::MOTION_STAR;

			switch (i)
			{
			case 0:     aProjectile->mVelX = -3.33f  /4;        aProjectile->mVelY = 0.0f / 4;              break;
			case 1:     aProjectile->mVelX = 0.0f / 4;          aProjectile->mVelY = 3.33f / 4;             break;
			case 2:     aProjectile->mVelX = 0.0f / 4;          aProjectile->mVelY = -3.33f / 4;            break;
			case 3:     aProjectile->mVelX = 3.33f / 4;		    aProjectile->mVelY = 0.0f / 4;		        break;
			case 4:     aProjectile->mVelX = -2.355f / 4;		aProjectile->mVelY = -2.355f / 4;			break;
			case 5:     aProjectile->mVelX = -2.355f / 4;       aProjectile->mVelY = 2.355f / 4;            break;
			case 6:     aProjectile->mVelX = 2.355f / 4;        aProjectile->mVelY = 2.355f / 4;            break;
			case 7:     aProjectile->mVelX = 2.355f / 4;        aProjectile->mVelY = -2.355f / 4;           break;
			default:    TOD_ASSERT();																	    break;
			}
		} */
		
	}

	return aDamageFlags;
}

//0x46D2B0
bool Projectile::IsZombieHitBySplash(Zombie* theZombie)
{
	Rect aProjectileRect = GetProjectileRect();
	if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_ELECTRIC || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR)
	{
		aProjectileRect.mWidth = 100;
	}

	int aRowDeviation = theZombie->mRow - mRow;
	Rect aZombieRect = theZombie->GetZombieRect();
	if (theZombie->IsFireResistant() && (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_ELECTRIC || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR))
	{
		return false;
	}

	if (theZombie->mZombieType == ZombieType::ZOMBIE_BOSS)
	{
		aRowDeviation = 0;
	}
	if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_ELECTRIC)
	{
		if (aRowDeviation != 0)
		{
			return false;
		}
	}
	else if (aRowDeviation > 1 || aRowDeviation < -1)
	{
		return false;
	}

	return theZombie->EffectedByDamage((unsigned int)mDamageRangeFlags) && GetRectOverlap(aProjectileRect, aZombieRect) >= 0;
}

//0x46D390
void Projectile::DoSplashDamage(Zombie* theZombie)
{
	const ProjectileDefinition& aProjectileDef = GetProjectileDef();

	int aZombiesGetSplashed = 0;
	Zombie* aZombie = nullptr;
	while (mBoard->IterateZombies(aZombie))
	{
		if (aZombie != theZombie && IsZombieHitBySplash(aZombie))
		{
			aZombiesGetSplashed++;
		}
	}

	int aOriginalDamage = aProjectileDef.mDamage;
	int aSplashDamage = aProjectileDef.mDamage / 3;
	int aMaxSplashDamageAmount = aSplashDamage * 7;
	if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_ELECTRIC || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR)
	{
		aMaxSplashDamageAmount = aOriginalDamage;
	}
	int aSplashDamageAmount = aSplashDamage * aZombiesGetSplashed;
	if (aSplashDamageAmount > aMaxSplashDamageAmount)
	{
		//aSplashDamage *= aMaxSplashDamageAmount / aSplashDamage;
		aSplashDamage = aOriginalDamage * aMaxSplashDamageAmount / (aSplashDamageAmount * 3);
		aSplashDamage = max(aSplashDamage, 1);
	}

	aZombie = nullptr;
	while (mBoard->IterateZombies(aZombie))
	{
		if (IsZombieHitBySplash(aZombie))
		{
			unsigned int aDamageFlags = GetDamageFlags(aZombie);
			if (aZombie == theZombie)
			{
				aZombie->TakeDamage(aOriginalDamage, aDamageFlags);
			}
			else
			{
				aZombie->TakeDamage(aSplashDamage, aDamageFlags);
			}
		}
	}
}

//0x46D490
void Projectile::UpdateLobMotion()
{
	if (mProjectileType == ProjectileType::PROJECTILE_COBBIG && mPosZ < -700.0f)
	{
		mVelZ = 8.0f;
		mRow = mCobTargetRow;
		mPosX = mCobTargetX;
		int aCobTargetCol = mBoard->PixelToGridXKeepOnBoard(mCobTargetX, 0);
		mPosY = mBoard->GridToPixelY(aCobTargetCol, mCobTargetRow);
		mShadowY = mPosY + 67.0f;
		mRotation = -PI / 2;
	}

	mVelZ += mAccZ;
	if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HIGH_GRAVITY && mProjectileType != PROJECTILE_ELECTRIC)
	{
		mVelZ += mAccZ;
	}
	mPosX += mVelX;
	mPosY += mVelY;
	mPosZ += mVelZ;

	bool isRising = mVelZ < 0.0f;
	if (isRising && (mProjectileType == ProjectileType::PROJECTILE_BASKETBALL || mProjectileType == ProjectileType::PROJECTILE_COBBIG))
	{
		return;
	}
	if (mProjectileAge > 20)
	{
		if (isRising)
		{
			return;
		}

		float aMinCollisionZ = 0.0f;
		if (mProjectileType == ProjectileType::PROJECTILE_BUTTER)
		{
			aMinCollisionZ = -32.0f;
		}
		else if (mProjectileType == ProjectileType::PROJECTILE_BASKETBALL)
		{
			aMinCollisionZ = 60.0f;
		}
		else if (mProjectileType == ProjectileType::PROJECTILE_MELON || mProjectileType == ProjectileType::PROJECTILE_WINTERMELON || mProjectileType == ProjectileType::PROJECTILE_PEPPER)
		{
			aMinCollisionZ = -35.0f;
		}
		else if (mProjectileType == ProjectileType::PROJECTILE_CABBAGE || mProjectileType == ProjectileType::PROJECTILE_KERNEL)
		{
			aMinCollisionZ = -30.0f;
		}
		else if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
		{
			aMinCollisionZ = -60.0f;
		}
		if (mBoard->mPlantRow[mRow] == PlantRowType::PLANTROW_POOL)
		{
			aMinCollisionZ += 40.0f;
		}

		if (mProjectileType == PROJECTILE_SHOOTING_STAR) {
			aMinCollisionZ += 307;
		}

		if (mPosZ <= aMinCollisionZ)
		{
			return;
		}

	
	}

	Plant* aPlant = nullptr;
	Plant* bPlant = nullptr;
	Zombie* aZombie = nullptr;
	GridItem* aGridItem = nullptr;
	if (mProjectileType == ProjectileType::PROJECTILE_BASKETBALL || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA ||
		mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA)
	{
		aPlant = FindCollisionTargetPlant();
	}
	else
	{
		/*Plant* bPlant = FindCollisionTargetPlant();
		Zombie* bZombie = FindCollisionTarget();

		if (bPlant && !bZombie)
		{
			if (bPlant->mSeedType == SEED_GRAVE && mProjectileAge > 100)
			{
				aPlant = FindCollisionTargetPlant();
			}
		}
		else aZombie = FindCollisionTarget();*/
		aZombie = FindCollisionTarget();
		if (aZombie == nullptr)
		{
			aGridItem = FindCollisionTargetGridItem();
			bPlant = FindCollisionTargetPlant();
		}
		
	}

	float aGroundZ = 80.0f;
	if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		aGroundZ = -40.0f;
	}
	if (aGridItem)
	{
		if (aGridItem->mGridY == mRow)
		{
			aGroundZ = -20.0f;
		}
	}
	bool hitGround = mPosZ > aGroundZ;
	if (aZombie == nullptr && aPlant == nullptr && !hitGround)
	{
		return;
	}
	//if (aGridItem == nullptr)
	{
		//return;
	}

	if (aPlant)
	{
		Plant* aUmbrellaPlant = mBoard->FindUmbrellaPlant(aPlant->mPlantCol, aPlant->mRow);
		if (aUmbrellaPlant)
		{
			if (aUmbrellaPlant->mState == PlantState::STATE_UMBRELLA_REFLECTING)
			{
				mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
				int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_TOP, 0, 1);
				mApp->AddTodParticle(mPosX + 20.0f, mPosY + 20.0f, aRenderPosition, ParticleEffect::PARTICLE_UMBRELLA_REFLECT);
				Die();
			}
			else if (aUmbrellaPlant->mState != PlantState::STATE_UMBRELLA_TRIGGERED)
			{
				mApp->PlayFoley(FoleyType::FOLEY_UMBRELLA);
				aUmbrellaPlant->DoSpecial();
			}
		}
		else
		{
			aPlant->mPlantHealth -= GetProjectileDef().mDamage;
			aPlant->mEatenFlashCountdown = max(aPlant->mEatenFlashCountdown, 25);
			mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
			Die();
		}
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		mBoard->KillAllZombiesInRadius(mRow, mPosX + 80, mPosY + 40, 115, 1, true, mDamageRangeFlags, 0, 1800, false);
		DoImpact(nullptr);
	}
	else if (aGridItem)
	{
		DoImpactGridItem(aGridItem);
	}
	else if (bPlant)
	{
		if (bPlant->mSeedType == SEED_GRAVE || bPlant->mHypnotized)
		{
			DoImpactPlant(bPlant);
		}
	}
	else
	{
		DoImpact(aZombie);
	}
}

//0x46D890
void Projectile::UpdateNormalMotion()
{
	if (mMotionType == ProjectileMotion::MOTION_BACKWARDS)
	{
		mPosX -= 3.33f;
	}
	else if (mMotionType == ProjectileMotion::MOTION_HOMING)
	{
		Zombie* aZombie = mBoard->ZombieTryToGet(mTargetZombieID);
		if (aZombie && aZombie->EffectedByDamage((unsigned int)mDamageRangeFlags))
		{
			Rect aZombieRect = aZombie->GetZombieRect();
			SexyVector2 aTargetCenter(aZombie->ZombieTargetLeadX(0.0f), aZombieRect.mY + aZombieRect.mHeight / 2);
			SexyVector2 aProjectileCenter(mPosX + mWidth / 2, mPosY + mHeight / 2);
			SexyVector2 aToTarget = (aTargetCenter - aProjectileCenter).Normalize();
			SexyVector2 aMotion(mVelX, mVelY);

			aMotion += aToTarget * (0.001f * mProjectileAge);
			aMotion = aMotion.Normalize();
			aMotion *= 2.0f;

			mVelX = aMotion.x;
			mVelY = aMotion.y;
			mRotation = -atan2(mVelY, mVelX);
		}

		mPosY += mVelY;
		mPosX += mVelX;
		mShadowY += mVelY;
		mRow = mBoard->PixelToGridYKeepOnBoard(mPosX, mPosY);
	}
	else if (mMotionType == ProjectileMotion::MOTION_STAR)
	{
		mPosY += mVelY;
		mPosX += mVelX;
		mShadowY += mVelY;

		if (mVelY != 0.0f)
		{
			mRow = mBoard->PixelToGridYKeepOnBoard(mPosX, mPosY);
		}
	}
	else if (mMotionType == ProjectileMotion::MOTION_BEE)
	{
		if (mProjectileAge < 60)
		{
			mPosY -= 0.5f;
		}
		mPosX += 3.33f;
	}
	else if (mMotionType == ProjectileMotion::MOTION_FLOAT_OVER)
	{
		if (mVelZ < 0.0f)
		{
			mVelZ += 0.002f;
			mVelZ = min(mVelZ, 0.0f);
			mPosY += mVelZ;
			mRotation = 0.3f - 0.7f * mVelZ * PI * 0.25f;
		}
		mPosX += 0.4f;
	}
	else if (mMotionType == ProjectileMotion::MOTION_BEE_BACKWARDS)
	{
		if (mProjectileAge < 60)
		{
			mPosY -= 0.5f;
		}
		mPosX -= 3.33f;
	}
	else if (mMotionType == ProjectileMotion::MOTION_THREEPEATER)
	{
		mPosX += 3.33f;
		mPosY += mVelY;
		mVelY *= 0.97f;
		mShadowY += mVelY;
	}
	else if (mMotionType == ProjectileMotion::MOTION_THREEPEATER_BACKWARDS)
	{
		mPosX -= 3.33f;
		mPosY += mVelY;
		mVelY *= 0.97f;
		mShadowY += mVelY;
	}
	else
	{
		mPosX += 3.33f;
	}

	if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HIGH_GRAVITY && mProjectileType != PROJECTILE_ELECTRIC)
	{
		if (mMotionType == ProjectileMotion::MOTION_FLOAT_OVER)
		{
			mVelZ += 0.004f;
		}
		else
		{
			mVelZ += 0.2f;
		}

		mPosY += mVelZ;
	}

	CheckForCollision();
	CheckForHighGround();
}

//0x46DC70
void Projectile::UpdateMotion()
{
	if (mMotionType == ProjectileMotion::MOTION_STAR && mProjectileType == PROJECTILE_SPIKE)
	{
		int num = 8;

		mVelX = mRadius * cos(mExpAm + mProjOrder/8 * PI*2);
		mVelY = mRadius * sin(mExpAm + mProjOrder/8 * PI*2);

		if (mleft)
		{
			mRadius -= 0.02f;
			mExpAm -= 0.01f;
		}
		else
		{
			mRadius += 0.02f;
			mExpAm += 0.01f;
		}

		mRotation = -atan2(mVelY, mVelX);

		if (mPosY < 0 || mPosY > 600) Die();
	}

	if (mAnimTicksPerFrame > 0)
	{
		mAnimCounter = (mAnimCounter + 1) % (mNumFrames * mAnimTicksPerFrame);
		mFrame = mAnimCounter / mAnimTicksPerFrame;
	}

	int aOldRow = mRow;
	float aOldY = mBoard->GetPosYBasedOnRow(mPosX, mRow);
	if (mMotionType == ProjectileMotion::MOTION_LOBBED)
	{
		UpdateLobMotion();
	}
	else
	{
		UpdateNormalMotion();
	}

	float aSlopeHeightChange = mBoard->GetPosYBasedOnRow(mPosX, aOldRow) - aOldY;
//#ifdef DO_FIX_BUGS
	if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		aSlopeHeightChange = 0.0f;  // 修复“上界之风”
	}
//#endif
	if (mMotionType == ProjectileMotion::MOTION_FLOAT_OVER)
	{
		mPosY += aSlopeHeightChange;
	}
	if (mMotionType == ProjectileMotion::MOTION_LOBBED)
	{
		mPosY += aSlopeHeightChange;
		mPosZ -= aSlopeHeightChange;
	}

	if (mProjectileType == PROJECTILE_SHOOTING_STAR)
		mShadowY = mPosY + 337;

	mShadowY += aSlopeHeightChange;
	mX = (int)mPosX;
	mY = (int)(mPosY + mPosZ);
}

//0x46DD30
void Projectile::PlayImpactSound(Zombie* theZombie)
{
	bool aPlayHelmSound = true;
	bool aPlaySplatSound = true;
	if (mProjectileType == ProjectileType::PROJECTILE_KERNEL)
	{
		mApp->PlayFoley(FoleyType::FOLEY_KERNEL_SPLAT);
		aPlayHelmSound = false;
		aPlaySplatSound = false;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_BUTTER)
	{
		mApp->PlayFoley(FoleyType::FOLEY_BUTTER);
		aPlaySplatSound = false;
	}
	else if ((mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR) && IsSplashDamage(theZombie))
	{
		mApp->PlayFoley(FoleyType::FOLEY_IGNITE);
		aPlayHelmSound = false;
		aPlaySplatSound = false;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_MELON || mProjectileType == ProjectileType::PROJECTILE_WINTERMELON)
	{
		mApp->PlayFoley(FoleyType::FOLEY_MELONIMPACT);
		aPlaySplatSound = false;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PEPPER)
	{
		mApp->PlayFoley(FoleyType::FOLEY_IGNITE);
		aPlaySplatSound = false;
	}
	

	if (aPlayHelmSound && theZombie)
	{
		if (theZombie->mHelmType == HELMTYPE_PAIL || theZombie->mHelmType == HELMTYPE_GLADIANTUAR || theZombie->mHelmType == HELMTYPE_PAIL_GIGA)
		{
			mApp->PlayFoley(FoleyType::FOLEY_SHIELD_HIT);
			aPlaySplatSound = false;
		}
		else if (theZombie->mHelmType == HELMTYPE_TRAFFIC_CONE || theZombie->mHelmType == HELMTYPE_DIGGER || theZombie->mHelmType == HELMTYPE_FOOTBALL || theZombie->mHelmType == HELMTYPE_GIGA_FOOTBALL)
		{
			mApp->PlayFoley(FoleyType::FOLEY_PLASTIC_HIT);
		}
		else if (theZombie->mHelmType == HELMTYPE_ICE)
		{
			mApp->PlayFoley(FoleyType::FOLEY_ICE);
		}
	}

	if (aPlaySplatSound)
	{
		if (theZombie && theZombie->mZombieType == ZombieType::ZOMBIE_RAVEN) mApp->PlayFoley(FOLEY_CROW_DEATH);
		mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
	}
}

void Projectile::DoImpactGridItem(GridItem* theGridItem)
{
	if (mProjectileType == PROJECTILE_ELECTRIC)
	{
		if (mGridItem != theGridItem)
		{
			int aRand = Rand(2);
			if (aRand == 0)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC);
			else if (aRand == 1)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC2);
			else  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC3);
			theGridItem->mJustGotShotCounter = 25;
			theGridItem->mHealth -= GetProjectileDef().mDamage;
			mGridItem = theGridItem;
		}
		return;
	}

	if (theGridItem->mGridItemType == GRIDITEM_WOOD_LOG)
	{
		bool aPlaySplatSound = true;
		if (mProjectileType == ProjectileType::PROJECTILE_KERNEL)
		{
			mApp->PlayFoley(FoleyType::FOLEY_KERNEL_SPLAT);
			aPlaySplatSound = false;
		}
		else if (mProjectileType == ProjectileType::PROJECTILE_BUTTER)
		{
			mApp->PlayFoley(FoleyType::FOLEY_BUTTER);
			aPlaySplatSound = false;
		}
		else if ((mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR))
		{
			mApp->PlayFoley(FoleyType::FOLEY_IGNITE);
			aPlaySplatSound = false;
		}
		else if (mProjectileType == ProjectileType::PROJECTILE_MELON || mProjectileType == ProjectileType::PROJECTILE_WINTERMELON)
		{
			mApp->PlayFoley(FoleyType::FOLEY_MELONIMPACT);
			aPlaySplatSound = false;
		}
		else if (mProjectileType == ProjectileType::PROJECTILE_PEPPER)
		{
			mApp->PlayFoley(FoleyType::FOLEY_IGNITE);
			aPlaySplatSound = false;
		}

		if (aPlaySplatSound)
		{
			mApp->PlayFoley(FoleyType::FOLEY_PLASTIC_HIT);
		}
	}

	//ParticleEffect aEffect = ParticleEffect::PARTICLE_PEA_SPLAT;
	//mApp->PlayFoley(FOLEY_SPLAT);
	theGridItem->mJustGotShotCounter = 25;
	theGridItem->mHealth -= GetProjectileDef().mDamage;
	/*if (mProjectileType == ProjectileType::PROJECTILE_PEA)
	{
		aEffect = ParticleEffect::PARTICLE_PEA_SPLAT;
	}
	if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA)
	{
		aEffect = ParticleEffect::PARTICLE_SNOWPEA_SPLAT;
	}
	if (mProjectileType == ProjectileType::PROJECTILE_STAR)
	{
		aEffect = ParticleEffect::PARTICLE_STAR_SPLAT;
	}
	if (mProjectileType == ProjectileType::PROJECTILE_SEASTAR)
	{
		aEffect = ParticleEffect::PARTICLE_STAR_SPLAT;
	}
	if (mProjectileType == ProjectileType::PROJECTILE_PUFF)
	{
		aEffect = ParticleEffect::PARTICLE_PUFF_SPLAT;
	}
	if (mProjectileType == ProjectileType::PROJECTILE_CABBAGE)
	{
		aEffect = ParticleEffect::PARTICLE_CABBAGE_SPLAT;
	}
	if (mProjectileType == ProjectileType::PROJECTILE_BUTTER)
	{
		aEffect = ParticleEffect::PARTICLE_BUTTER_SPLAT;
	}
	mApp->AddTodParticle((theGridItem->mGridX + 1) * 80.0f, mY + 20.0f, mRenderOrder + 1, aEffect);*/
	DoImpact(nullptr, true);
	Die();
}

//0x46E000
void Projectile::DoImpact(Zombie* theZombie, bool isSilent)
{
	if (theZombie)
	{
		bool aIsBushSquare =
			mBoard->GetBushAt(mBoard->PixelToGridX(theZombie->mX + 75, theZombie->mY), mRow) &&
			mBoard->GetBushAt(mBoard->PixelToGridX(theZombie->mX + 45, mY), theZombie->mRow) &&
			mX < 680;
		if (aIsBushSquare && mProjectileType != PROJECTILE_BEE && mProjectileType != PROJECTILE_ARROW)
		{
			return;
		}
	}

	if (mProjectileType == PROJECTILE_ELECTRIC)
	{
		if (mZombie != theZombie)
		{
			int aRand = Rand(2);
			if (aRand == 0)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC);
			else if (aRand == 1)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC2);
			else  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC3);
			if (theZombie)
			{
				unsigned int aDamageFlags = GetDamageFlags(theZombie);
				theZombie->TakeDamage(GetProjectileDef().mDamage, aDamageFlags);				

				Zombie* aZombie = nullptr;
				while (mBoard->IterateZombies(aZombie))
				{
					if ((theZombie->mRow == aZombie->mRow - 1 || theZombie->mRow == aZombie->mRow + 1) && (aZombie->mPosX >= theZombie->mPosX - 80 && aZombie->mPosX <= theZombie->mPosX + 80) &&
						!aZombie->mMindControlled)
						if (aZombie->IsFlying()) aZombie->TakeFlyingDamage(20, aDamageFlags);
						else aZombie->TakeDamage(10, aDamageFlags);
				}

				mZombie = theZombie;
			}		
		}
		return;
	}
	if (!isSilent)
	{
		PlayImpactSound(theZombie);
	}
	if (theZombie && theZombie->mZombieType == ZOMBIE_TARGET)
	{
		theZombie->PlayZombieReanim("anim_hit", REANIM_PLAY_ONCE_AND_HOLD, 20, 16.0f);
	}

	if (theZombie && ((mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_PEPPER) &&
		theZombie->mHelmType == HelmType::HELMTYPE_ICE))
	{
		unsigned int aDamageFlags = GetDamageFlags(theZombie);
		theZombie->TakeDamage(GetProjectileDef().mDamage * 2, aDamageFlags);
	}
	if (theZombie && ((mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_PEPPER) &&
		(theZombie->mHelmType == HelmType::HELMTYPE_TRAFFIC_CONE && theZombie->mZombieType == ZOMBIE_GIGA_CONEHEAD)))
	{
		unsigned int aDamageFlags = GetDamageFlags(theZombie);
		theZombie->TakeDamage(GetProjectileDef().mDamage / 2, aDamageFlags);
	}
	else if (IsSplashDamage(theZombie))
	{
		if ((mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_PEPPER || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR) && theZombie)
		{
			theZombie->RemoveColdEffects();
		}

		DoSplashDamage(theZombie);
	}
	else if (theZombie && mProjectileType == ProjectileType::PROJECTILE_ARROW)
	{
		int amplifier = 1;
		if (Sexy::Rand(4) == 0)
		{
			amplifier = 2;
			mApp->AddTodParticle(mPosX + 40.0f, mPosY + 40.0f, RENDER_LAYER_ABOVE_UI, ParticleEffect::PARTICLE_POW);
			mApp->PlaySample(SOUND_BONK);
		}
		unsigned int aDamageFlags = GetDamageFlags(theZombie);
		theZombie->TakeDamage(GetProjectileDef().mDamage * amplifier, aDamageFlags);
	}
	else if (theZombie)
	{
		unsigned int aDamageFlags = GetDamageFlags(theZombie);
		theZombie->TakeDamage(GetProjectileDef().mDamage, aDamageFlags);
	}

	float aLastPosX = mPosX - mVelX;
	float aLastPosY = mPosY + mPosZ - mVelY - mVelZ;
	ParticleEffect aEffect = ParticleEffect::PARTICLE_NONE;
	float aSplatPosX = mPosX + 12.0f;
	float aSplatPosY = mPosY + 12.0f;
	if (mProjectileType == ProjectileType::PROJECTILE_MELON)
	{
		mApp->AddTodParticle(aLastPosX + 30.0f, aLastPosY + 30.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_MELONSPLASH);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_WINTERMELON)
	{
		mApp->AddTodParticle(aLastPosX + 30.0f, aLastPosY + 30.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_WINTERMELON);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		int aRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_GROUND, mCobTargetRow, 2);
		mApp->AddTodParticle(mPosX + 80.0f, mPosY + 40.0f, aRenderOrder, ParticleEffect::PARTICLE_BLASTMARK);
		mApp->AddTodParticle(mPosX + 80.0f, mPosY + 40.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_POPCORNSPLASH);
		mApp->PlaySample(SOUND_DOOMSHROOM);
		mBoard->ShakeBoard(3, -4);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PEA)
	{ 
		aSplatPosX -= 15.0f;
		aEffect = ParticleEffect::PARTICLE_PEA_SPLAT;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA || mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN)
	{
		aSplatPosX -= 15.0f;
		aEffect = ParticleEffect::PARTICLE_SNOWPEA_SPLAT;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_PEPPER || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR)
	{
		if (IsSplashDamage(theZombie))
		{
			ReanimationType aReanimType = REANIM_JALAPENO_FIRE;
			if (mProjectileType == ProjectileType::PROJECTILE_PLASMABALL) aReanimType = REANIM_PLASMA_FIRE;
			Reanimation* aFireReanim = mApp->AddReanimation(mPosX + 38.0f, mPosY - 20.0f, mRenderOrder + 1, aReanimType);
			aFireReanim->mAnimTime = 0.25f;
			aFireReanim->mAnimRate = 24.0f;
			aFireReanim->OverrideScale(0.7f, 0.4f);
			//if (mProjectileType == ProjectileType::PROJECTILE_PLASMABALL) aFireReanim->mColorOverride = Color(0, 255, 255, 255);
		}
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_STAR)
	{
		aEffect = ParticleEffect::PARTICLE_STAR_SPLAT;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SEASTAR)
	{
		aEffect = ParticleEffect::PARTICLE_STAR_SPLAT;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PUFF)
	{
		aSplatPosX -= 20.0f;
		aEffect = ParticleEffect::PARTICLE_PUFF_SPLAT;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_CABBAGE)
	{
		aSplatPosX = aLastPosX - 38.0f;
		aSplatPosY = aLastPosY + 23.0f;
		aEffect = ParticleEffect::PARTICLE_CABBAGE_SPLAT;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_BUTTER)
	{
		aSplatPosX = aLastPosX - 20.0f;
		aSplatPosY = aLastPosY + 63.0f;
		aEffect = ParticleEffect::PARTICLE_BUTTER_SPLAT;

		if (theZombie)
		{
			theZombie->ApplyButter();
		}
	}

	if (aEffect != ParticleEffect::PARTICLE_NONE)
	{
		if (theZombie)
		{
			float aPosX = aSplatPosX + 52.0f - theZombie->mX;
			float aPosY = aSplatPosY - theZombie->mY;
			if (theZombie->mZombiePhase == ZombiePhase::PHASE_SNORKEL_WALKING_IN_POOL || theZombie->mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_IN_POOL)
			{
				aPosY += 60.0f;
			}
			if (mMotionType == ProjectileMotion::MOTION_BACKWARDS)
			{
				aPosX -= 80.0f;
			}
			else if (mPosX > theZombie->mX + 40 && mMotionType != ProjectileMotion::MOTION_LOBBED)
			{
				aPosX -= 60.0f;
			}

			aPosY = ClampFloat(aPosY, 20.0f, 100.0f);
			theZombie->AddAttachedParticle(aPosX, aPosY, aEffect);
		}
		else
		{
			mApp->AddTodParticle(aSplatPosX, aSplatPosY, mRenderOrder + 1, aEffect);
		}
	}

	Die();
}

//0x46E460
void Projectile::Update()
{
	mProjectileAge++;
	if (mApp->mGameScene != GameScenes::SCENE_PLAYING && !mBoard->mCutScene->ShouldRunUpsellBoard())
		return;
	if (mProjectileType == ProjectileType::PROJECTILE_REED_ZAP)
	{
		if (mProjectileAge > 50)
			Die();
		return;
	}
	int aTime = 20;
	if (mProjectileType == ProjectileType::PROJECTILE_PEA || 
		mProjectileType == ProjectileType::PROJECTILE_SNOWPEA || 
		mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN ||
		mProjectileType == ProjectileType::PROJECTILE_ELECTRIC ||
		mProjectileType == ProjectileType::PROJECTILE_CABBAGE || 
		mProjectileType == ProjectileType::PROJECTILE_MELON || 
		mProjectileType == ProjectileType::PROJECTILE_PEPPER ||
		mProjectileType == ProjectileType::PROJECTILE_WINTERMELON || 
		mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR || 
		mProjectileType == ProjectileType::PROJECTILE_KERNEL || 
		mProjectileType == ProjectileType::PROJECTILE_BUTTER || 
		mProjectileType == ProjectileType::PROJECTILE_COBBIG || 
		mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA || 
		mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA ||
		mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA ||
		mProjectileType == ProjectileType::PROJECTILE_ARROW ||
		mProjectileType == ProjectileType::PROJECTILE_SPIKE)
	{
		aTime = 0;
	}
	if (mProjectileAge > aTime)
	{
		mRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PROJECTILE, mRow, 0);
	}

	if (mClickBackoffCounter > 0)
	{
		mClickBackoffCounter--;
	}
	mRotation += mRotationSpeed;

	UpdateMotion();
	AttachmentUpdateAndMove(mAttachmentID, mPosX, mPosY + mPosZ);
	RotatePepper();
	RotateBee();
	
	if (mProjectileType == PROJECTILE_ELECTRIC && mBoard->StageHasRoof() && mPosX > 300 && mPosX < 450) mPosY -= 1;
}

void Projectile::RotatePepper()
{
	if (mProjectileType == ProjectileType::PROJECTILE_PEPPER)
	{
		//Reanimation* aBodyReanim = mApp->ReanimationTryToGet(aFirePeaReanimID);
		//TodScaleRotateTransformMatrix(aBodyReanim->mOverlayMatrix, 0, 0, atan2f(mVelZ - mVelY, mVelX), 1.0f, 1.0f);
		Reanimation* aBodyReanim = mApp->ReanimationTryToGet(aFirePeaReanimID);
		float direction = (float)atan2((double)mVelZ - mVelY, (double)mVelX);
		aBodyReanim->mOverlayMatrix.m10 = sin(direction);
		aBodyReanim->mOverlayMatrix.m01 = -sin(direction);//

		aBodyReanim->mOverlayMatrix.m00 = cos(direction);//stetch l-r (24)
		aBodyReanim->mOverlayMatrix.m11 = cos(direction);//stretch u-d (34)

		float st1 = cos(direction);
		float st0 = sin(direction);
		float st2 = 1.0f;
		float value28 = 40.0f;//sorta like a anker 

		st2 = st1 - st2;
		st2 += st0;
		st2 *= value28;
		st2 = -st2;
		aBodyReanim->mOverlayMatrix.m12 = st2;
		aBodyReanim->mOverlayMatrix.m12 += mY - 20;

		st2 = 1.0f;
		st2 -= st1;
		st2 += st0;
		st2 *= value28;
		aBodyReanim->mOverlayMatrix.m02 = st2;
		aBodyReanim->mOverlayMatrix.m02 += mX - 20;

	}
}

void Projectile::RotateBee()
{
	if (mProjectileType == ProjectileType::PROJECTILE_BEE)
	{
		Reanimation* aBodyReanim = mApp->ReanimationTryToGet(aFirePeaReanimID);
		float direction = (float)atan2((double)mVelZ - mVelY, (double)mVelX);
		aBodyReanim->mOverlayMatrix.m10 = sin(direction);
		aBodyReanim->mOverlayMatrix.m01 = -sin(direction);//

		aBodyReanim->mOverlayMatrix.m00 = cos(direction);//stetch l-r (24)
		aBodyReanim->mOverlayMatrix.m11 = cos(direction);//stretch u-d (34)

		float st1 = cos(direction);
		float st0 = sin(direction);
		float st2 = 1.0f;
		float value28 = 40.0f;//sorta like a anker 

		st2 = st1 - st2;
		st2 += st0;
		st2 *= value28;
		st2 = -st2;
		aBodyReanim->mOverlayMatrix.m12 = st2;
		aBodyReanim->mOverlayMatrix.m12 += mY - 4;

		st2 = 1.0f;
		st2 -= st1;
		st2 += st0;
		st2 *= value28;
		aBodyReanim->mOverlayMatrix.m02 = st2;
		aBodyReanim->mOverlayMatrix.m02 += mX - 0;
	
		if (mVelX < 0) aBodyReanim->OverrideScale(-0.7f, 0.7f);
		else aBodyReanim->OverrideScale(0.7f, 0.7f);
	}
}

void Projectile::DrawReedZap(Graphics* g)
{
	g->SetColor(Color(255,255,255, TodAnimateCurve(0,50,mProjectileAge, 255, 0, CURVE_LINEAR)));
	g->SetColorizeImages(true);
	SexyMatrix3 aMatrix;
	aMatrix.LoadIdentity();
	TodScaleRotateTransformMatrix(aMatrix, 0, 0, mRotation, mRadius, 1.0f);
	//float aStretch = 
	//IMAGE_PROJECTILE_ZAP->mWidth
		//IMAGE_PROJECTILE_ZAP->mWidth
	//Center left of image aligns with mPos, Center right aligns with mPos + mWidth/Height

	g->DrawImageMatrix(IMAGE_PROJECTILE_ZAP, aMatrix);
	//g->DrawImage(IMAGE_PROJECTILE_ZAP, 0, 0);
	g->SetColorizeImages(false);
}

void Projectile::TransformZap()
{
	mRadius = sqrtf(mWidth * mWidth + mHeight * mHeight) / IMAGE_PROJECTILE_ZAP->mWidth;
	mRotation = atan2f(-mHeight,mWidth);
	mX += mWidth / 2;
	mY += mHeight / 2;
}

//0x46E540
void Projectile::Draw(Graphics* g)
{
	if (mProjectileType == ProjectileType::PROJECTILE_REED_ZAP)
	{
		DrawReedZap(g);
		return;
	}
	//g->SetColorizeImages(true);
	//g->SetColor(Color(255, 0, 0));
	const ProjectileDefinition& aProjectileDef = GetProjectileDef();

	Image* aImage;
	float aScale = 1.0f;
	float aY = 0.0f;

	if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		aImage = IMAGE_REANIM_COBCANNON_COB;
		aScale = 0.9f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA)
	{
		aImage = IMAGE_PROJECTILEPEA;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA)
	{
		aImage = IMAGE_PROJECTILESNOWPEA;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN)
	{
		aImage = IMAGE_PROJECTILEICEQUEEN;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ELECTRIC || mProjectileType == ProjectileType::PROJECTILE_PEPPER || mProjectileType == ProjectileType::PROJECTILE_SHOOTING_STAR)
	{
		aImage = nullptr;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA ||
			 mProjectileType == ProjectileType::PROJECTILE_BEE)
	{
		aImage = nullptr;
		//g->SetColorizeImages(true);
		//g->SetColor(Color(255, 0, 0));
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SPIKE)
	{
		if (mProjectileAge < 57 && mMotionType == MOTION_STAR) aImage = nullptr;
		else aImage = IMAGE_PROJECTILECACTUS;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ARROW)
	{
		aImage = IMAGE_OAK_ARROW;
		aScale = 0.8f;
		aY = 10.0f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_STAR)
	{
		aImage = IMAGE_PROJECTILE_STAR;
		//g->SetColorizeImages(true);
		//g->SetColor(Color(255, 0, 0));
		//aScale = 3.0f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SEASTAR)
	{
		aImage = IMAGE_PROJECTILE_SEASTAR;
		//aScale = 1.25f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PUFF)
	{
		aImage = IMAGE_PUFFSHROOM_PUFF1;
		aScale = TodAnimateCurveFloat(0, 30, mProjectileAge, 0.3f, 1.0f, TodCurves::CURVE_LINEAR);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_BASKETBALL)
	{
		aImage = IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL;
		aScale = 1.1f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_CABBAGE)
	{
		aImage = IMAGE_REANIM_CABBAGEPULT_CABBAGE;
		aScale = 1.0f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_KERNEL)
	{
		aImage = IMAGE_REANIM_CORNPULT_KERNAL;
		aScale = 0.95f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_BUTTER)
	{
		aImage = IMAGE_REANIM_CORNPULT_BUTTER;
		aScale = 0.8f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_MELON)
	{
		aImage = IMAGE_REANIM_MELONPULT_MELON;
		aScale = 1.0f;
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_WINTERMELON)
	{
		aImage = IMAGE_REANIM_WINTERMELON_PROJECTILE;
		aScale = 1.0f;
	}
	else
	{
		TOD_ASSERT();
	}

	bool aMirror = false;
	if (mMotionType == ProjectileMotion::MOTION_BEE_BACKWARDS || mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA)
	{
		aMirror = true;
	}

	if (aImage)
	{
		TOD_ASSERT(aProjectileDef.mImageRow < aImage->mNumRows);
		TOD_ASSERT(mFrame < aImage->mNumCols);

		int aCelWidth = aImage->GetCelWidth();
		int aCelHeight = aImage->GetCelHeight();
		Rect aSrcRect(aCelWidth * mFrame, aCelHeight * aProjectileDef.mImageRow, aCelWidth, aCelHeight);
		if (FloatApproxEqual(mRotation, 0.0f) && FloatApproxEqual(aScale, 1.0f))
		{
			Rect aDestRect(0, 0, aCelWidth, aCelHeight);
			g->DrawImageMirror(aImage, aDestRect, aSrcRect, aMirror);
		}
		else
		{
			float aOffsetX = mPosX + aCelWidth * 0.5f;
			float aOffsetY = mPosZ + mPosY + aCelHeight * 0.5f + aY;
			SexyTransform2D aTransform;
			TodScaleRotateTransformMatrix(aTransform, aOffsetX + mBoard->mX, aOffsetY + mBoard->mY, mRotation, aScale, aScale);
			TodBltMatrix(g, aImage, aTransform, g->mClipRect, Color::White, g->mDrawMode, aSrcRect);
		} 
	}

	if (mAttachmentID != AttachmentID::ATTACHMENTID_NULL)
	{
		Graphics theParticleGraphics(*g);
		MakeParentGraphicsFrame(&theParticleGraphics);
		AttachmentDraw(mAttachmentID, &theParticleGraphics, false);
	}
	g->SetColorizeImages(false);
}

//0x46E8C0
void Projectile::DrawShadow(Graphics* g)
{
	if (mProjectileType == ProjectileType::PROJECTILE_REED_ZAP) return;
	int aCelCol = 0;
	float aScale = 1.0f;
	float aStretch = 1.0f;
	float aOffsetX = mPosX - mX;
	float aOffsetY = mPosY - mY;

	int aGridX = mBoard->PixelToGridXKeepOnBoard(mX, mY);
	bool isHighGround = false;
	if (mBoard->mGridSquareType[aGridX][mRow] == GridSquareType::GRIDSQUARE_HIGH_GROUND)
	{
		isHighGround = true;
	}
	if (mOnHighGround && !isHighGround)
	{
		aOffsetY += HIGH_GROUND_HEIGHT;
	}
	else if (!mOnHighGround && isHighGround)
	{
		aOffsetY -= HIGH_GROUND_HEIGHT;
	}

	if (mBoard->StageIsNight())
	{
		aCelCol = 1;
	}

	switch (mProjectileType)
	{
	case ProjectileType::PROJECTILE_PEA:
	case ProjectileType::PROJECTILE_ZOMBIE_PEA:
	case ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA:
	case ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA:
		aOffsetX += 3.0f;
		break;

	case ProjectileType::PROJECTILE_SNOWPEA:
	case ProjectileType::PROJECTILE_ICEQUEEN:
	case ProjectileType::PROJECTILE_ELECTRIC:
		aOffsetX += -1.0f;
		aScale = 1.3f;
		
		break;

	case ProjectileType::PROJECTILE_STAR:
	case ProjectileType::PROJECTILE_SEASTAR:
		aOffsetX += 7.0f;
		break;

	case ProjectileType::PROJECTILE_CABBAGE:
	case ProjectileType::PROJECTILE_KERNEL:
	case ProjectileType::PROJECTILE_BUTTER:
	case ProjectileType::PROJECTILE_MELON:
	case ProjectileType::PROJECTILE_PEPPER:
	case ProjectileType::PROJECTILE_WINTERMELON:
	case ProjectileType::PROJECTILE_SHOOTING_STAR:
		aOffsetX += 3.0f;
		aOffsetY += 10.0f;
		aScale = 1.6f;
		break;

	case ProjectileType::PROJECTILE_PUFF:
		return;
		
	case ProjectileType::PROJECTILE_COBBIG:
		aScale = 1.0f;
		aStretch = 3.0f;
		aOffsetX += 57.0f;
		break;

	case ProjectileType::PROJECTILE_ARROW:
		aScale = 0.8f;
		aStretch = 3.0f;
		aOffsetX += 35.0f;
		break;

	case ProjectileType::PROJECTILE_FIREBALL:
	case ProjectileType::PROJECTILE_PLASMABALL:
	case ProjectileType::PROJECTILE_BEE:
		aScale = 1.4f;
		break;
	}

	if (mMotionType == ProjectileMotion::MOTION_LOBBED)
	{
		float aHeight = ClampFloat(-mPosZ, 0.0f, 200.0f);
		aScale *= 200.0f / (aHeight + 200.0f);

		if (mProjectileType == PROJECTILE_SHOOTING_STAR) {
			aScale = TodAnimateCurveFloatTime(0, 337, mPosZ, 0, aScale, CURVE_LINEAR);
		}
	}
	//g->SetColorizeImages(true);
	//g->SetColor(Color(255, 0, 0));


	if (!(mProjectileAge < 57 && mMotionType == MOTION_STAR)) // check if spike is behind KingCactus
	{
		TodDrawImageCelScaledF(g, IMAGE_PEA_SHADOWS, aOffsetX, (mShadowY - mPosY + aOffsetY), aCelCol, 0, aScale * aStretch, aScale);
	}
}

//0x46EB20
void Projectile::Die()
{
	mDead = true;

	if (mProjectileType == ProjectileType::PROJECTILE_PUFF || mProjectileType == ProjectileType::PROJECTILE_SNOWPEA || mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN)
	{
		AttachmentCrossFade(mAttachmentID, "FadeOut");
		AttachmentDetach(mAttachmentID);
	}
	else
	{
		AttachmentDie(mAttachmentID);
	}
}

//0x46EBC0
Rect Projectile::GetProjectileRect()
{
	if (mProjectileType == ProjectileType::PROJECTILE_PEA || 
		mProjectileType == ProjectileType::PROJECTILE_SNOWPEA ||
		mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN ||
		mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA ||
		mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA ||
		mProjectileType == ProjectileType::PROJECTILE_BEE ||
		mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_FLAMEPEA)
	{
		return Rect(mX - 15, mY, mWidth + 15, mHeight);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ELECTRIC)
	{
		return Rect(mX + 10, mY, 10, mHeight);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_COBBIG)
	{
		return Rect(mX + mWidth / 2 - 115, mY + mHeight / 2 - 115, 230, 230);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_MELON || mProjectileType == ProjectileType::PROJECTILE_WINTERMELON)
	{
		return Rect(mX + 20, mY, 60, mHeight);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_PEPPER)
	{
		return Rect(mX + 20, mY, 30, mHeight);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL || mProjectileType == ProjectileType::PROJECTILE_PLASMABALL)
	{
		return Rect(mX, mY, mWidth - 10, mHeight);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_SPIKE)
	{
		return Rect(mX - 25, mY, mWidth + 25, mHeight);
	}
	else if (mProjectileType == ProjectileType::PROJECTILE_ARROW)
	{
		return Rect(mX + 25, mY, mWidth + 25, mHeight);
	}
	else
	{
		return Rect(mX, mY, mWidth, mHeight);
	}
}

Reanimation* aFirePeaReanim;

void Projectile::ConvertToPlasmaball(int theGridX)
{
	if (mHitTorchwoodGridX == theGridX)
		return;

	//aFirePeaReanim->ReanimationDie();
	Reanimation* aBodyReanim = mApp->ReanimationTryToGet(aFirePeaReanimID);
	if (aBodyReanim) aBodyReanim->ReanimationDie();

	mProjectileType = ProjectileType::PROJECTILE_PLASMABALL;
	mHitTorchwoodGridX = theGridX;
	mApp->PlayFoley(FoleyType::FOLEY_FIREPEA);

	float aOffsetX = -25.0f;
	float aOffsetY = -25.0f;
	Reanimation* aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_PLASMA_PEA);
	if (mMotionType == ProjectileMotion::MOTION_BACKWARDS)
	{
		aFirePeaReanim->OverrideScale(-1.0f, 1.0f);
		aOffsetX += 80.0f;
	}

	aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
	aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
	aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
	AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY); 
}


//0x46ECB0
void Projectile::ConvertToFireball(int theGridX)
{
	if (mHitTorchwoodGridX == theGridX)
		return;

	mProjectileType = ProjectileType::PROJECTILE_FIREBALL;
	mHitTorchwoodGridX = theGridX;
	mApp->PlayFoley(FoleyType::FOLEY_FIREPEA);

	float aOffsetX = -25.0f;
	float aOffsetY = -25.0f;

	aFirePeaReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_FIRE_PEA);
	if (mMotionType == ProjectileMotion::MOTION_BACKWARDS)
	{
		aFirePeaReanim->OverrideScale(-1.0f, 1.0f);
		aOffsetX += 80.0f;
	}
	aFirePeaReanim->SetPosition(mPosX + aOffsetX, mPosY + aOffsetY);
	aFirePeaReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
	aFirePeaReanim->mAnimRate = RandRangeFloat(50.0f, 80.0f);
	AttachReanim(mAttachmentID, aFirePeaReanim, aOffsetX, aOffsetY);	

	aFirePeaReanim->mIsAttachment = true;
	aFirePeaReanimID = mApp->ReanimationGetID(aFirePeaReanim);
}

//0x46EE00
void Projectile::ConvertToPea(int theGridX)
{
	if (mHitTorchwoodGridX == theGridX)
		return;

	AttachmentDie(mAttachmentID);
	mProjectileType = ProjectileType::PROJECTILE_PEA;
	mHitTorchwoodGridX = theGridX;
	mApp->PlayFoley(FoleyType::FOLEY_THROW);
}

void Projectile::ConvertToSnowPea(int theGridX)
{
	if (mHitTorchwoodGridX == theGridX)
		return;

	AttachmentDie(mAttachmentID);
	mProjectileType = ProjectileType::PROJECTILE_SNOWPEA;
	mHitTorchwoodGridX = theGridX;
	mApp->PlayFoley(FoleyType::FOLEY_THROW);
}

ProjectileDefinition& Projectile::GetProjectileDef()
{
	ProjectileDefinition& aProjectileDef = gProjectileDefinition[(int)mProjectileType];
	TOD_ASSERT(aProjectileDef.mProjectileType == mProjectileType);

	return aProjectileDef;
}
