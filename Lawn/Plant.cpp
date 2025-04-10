#include "Coin.h"
#include "Plant.h"
#include "Board.h"
#include "Zombie.h"
#include "Cutscene.h"
#include "GridItem.h"
#include "ZenGarden.h"
#include "Challenge.h"
#include "Projectile.h"
#include "SeedPacket.h"
#include "../LawnApp.h"
#include "CursorObject.h"
#include "../GameConstants.h"
#include "System/PlayerInfo.h"
#include "System/ReanimationLawn.h"
#include "../Sexy.TodLib/TodFoley.h"
#include "../Sexy.TodLib/TodDebug.h"
#include "../Sexy.TodLib/Attachment.h"
#include "../Sexy.TodLib/Reanimator.h"
#include "../Sexy.TodLib/TodParticle.h"
#include "../Sexy.TodLib/EffectSystem.h"
#include "../Sexy.TodLib/TodStringFile.h"

PlantDefinition gPlantDefs[SeedType::NUM_SEED_TYPES] = {  //0x69F2B0
    { SeedType::SEED_PEASHOOTER,        nullptr, ReanimationType::REANIM_PEASHOOTER,      0,  100,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("PEASHOOTER") },
    { SeedType::SEED_SUNFLOWER,         nullptr, ReanimationType::REANIM_SUNFLOWER,       1,  50,     750,    PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("SUNFLOWER") },
    { SeedType::SEED_CHERRYBOMB,        nullptr, ReanimationType::REANIM_CHERRYBOMB,      3,  150,    5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("CHERRY_BOMB") },
    { SeedType::SEED_WALLNUT,           nullptr, ReanimationType::REANIM_WALLNUT,         2,  50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("WALL_NUT") },
    { SeedType::SEED_POTATOMINE,        nullptr, ReanimationType::REANIM_POTATOMINE,      37, 25,     3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("POTATO_MINE") },
    { SeedType::SEED_SNOWPEA,           nullptr, ReanimationType::REANIM_SNOWPEA,         4,  175,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("SNOW_PEA") },
    { SeedType::SEED_CHOMPER,           nullptr, ReanimationType::REANIM_CHOMPER,         31, 150,    750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("CHOMPER") },
    { SeedType::SEED_REPEATER,          nullptr, ReanimationType::REANIM_REPEATER,        5,  200,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("REPEATER") },
    { SeedType::SEED_PUFFSHROOM,        nullptr, ReanimationType::REANIM_PUFFSHROOM,      6,  0,      750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("PUFF_SHROOM") },
    { SeedType::SEED_SUNSHROOM,         nullptr, ReanimationType::REANIM_SUNSHROOM,       7,  25,     750,    PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("SUN_SHROOM") },
    { SeedType::SEED_FUMESHROOM,        nullptr, ReanimationType::REANIM_FUMESHROOM,      9,  75,     750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("FUME_SHROOM") },
    { SeedType::SEED_GRAVEBUSTER,       nullptr, ReanimationType::REANIM_GRAVE_BUSTER,    40, 75,     750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("GRAVE_BUSTER") },
    { SeedType::SEED_HYPNOSHROOM,       nullptr, ReanimationType::REANIM_HYPNOSHROOM,     10, 75,     3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("HYPNO_SHROOM") },
    { SeedType::SEED_SCAREDYSHROOM,     nullptr, ReanimationType::REANIM_SCRAREYSHROOM,   33, 25,     750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("SCAREDY_SHROOM") },
    { SeedType::SEED_ICESHROOM,         nullptr, ReanimationType::REANIM_ICESHROOM,       36, 75,     5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("ICE_SHROOM") },
    { SeedType::SEED_DOOMSHROOM,        nullptr, ReanimationType::REANIM_DOOMSHROOM,      20, 125,    5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("DOOM_SHROOM") },
    { SeedType::SEED_LILYPAD,           nullptr, ReanimationType::REANIM_LILYPAD,         19, 25,     750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("LILY_PAD") },
    { SeedType::SEED_SQUASH,            nullptr, ReanimationType::REANIM_SQUASH,          21, 50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("SQUASH") },
    { SeedType::SEED_THREEPEATER,       nullptr, ReanimationType::REANIM_THREEPEATER,     12, 325,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("THREEPEATER") },
    { SeedType::SEED_TANGLEKELP,        nullptr, ReanimationType::REANIM_TANGLEKELP,      17, 25,     3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("TANGLE_KELP") },
    { SeedType::SEED_JALAPENO,          nullptr, ReanimationType::REANIM_JALAPENO,        11, 125,    5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("JALAPENO") },
    { SeedType::SEED_SPIKEWEED,         nullptr, ReanimationType::REANIM_SPIKEWEED,       22, 100,    750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("SPIKEWEED") },
    { SeedType::SEED_TORCHWOOD,         nullptr, ReanimationType::REANIM_TORCHWOOD,       29, 175,    750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("TORCHWOOD") },
    { SeedType::SEED_TALLNUT,           nullptr, ReanimationType::REANIM_TALLNUT,         28, 125,    3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("TALL_NUT") },
    { SeedType::SEED_SEASHROOM,         nullptr, ReanimationType::REANIM_SEASHROOM,       39, 0,      3000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("SEA_SHROOM") },
    { SeedType::SEED_PLANTERN,          nullptr, ReanimationType::REANIM_PLANTERN,        38, 25,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("PLANTERN") },
    { SeedType::SEED_CACTUS,            nullptr, ReanimationType::REANIM_CACTUS,          15, 125,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("CACTUS") },
    { SeedType::SEED_BLOVER,            nullptr, ReanimationType::REANIM_BLOVER,          18, 100,    750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("BLOVER") },
    { SeedType::SEED_SPLITPEA,          nullptr, ReanimationType::REANIM_SPLITPEA,        32, 125,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("SPLIT_PEA") },
    { SeedType::SEED_STARFRUIT,         nullptr, ReanimationType::REANIM_STARFRUIT,       30, 125,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("STARFRUIT") },
    { SeedType::SEED_PUMPKINSHELL,      nullptr, ReanimationType::REANIM_PUMPKIN,         25, 125,    3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("PUMPKIN") },
    { SeedType::SEED_MAGNETSHROOM,      nullptr, ReanimationType::REANIM_MAGNETSHROOM,    35, 100,    750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("MAGNET_SHROOM") },
    { SeedType::SEED_CABBAGEPULT,       nullptr, ReanimationType::REANIM_CABBAGEPULT,     13, 100,    750,    PlantSubClass::SUBCLASS_SHOOTER,    300,    _S("CABBAGE_PULT") },
    { SeedType::SEED_FLOWERPOT,         nullptr, ReanimationType::REANIM_FLOWER_POT,      33, 25,     750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("FLOWER_POT") },
    { SeedType::SEED_KERNELPULT,        nullptr, ReanimationType::REANIM_KERNELPULT,      13, 100,    750,    PlantSubClass::SUBCLASS_SHOOTER,    300,    _S("KERNEL_PULT") },
    { SeedType::SEED_INSTANT_COFFEE,    nullptr, ReanimationType::REANIM_COFFEEBEAN,      33, 75,     750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("COFFEE_BEAN") },
    { SeedType::SEED_GARLIC,            nullptr, ReanimationType::REANIM_GARLIC,          8,  50,     750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("GARLIC") },
    { SeedType::SEED_UMBRELLA,          nullptr, ReanimationType::REANIM_UMBRELLALEAF,    23, 100,    750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("UMBRELLA_LEAF") },
    { SeedType::SEED_MARIGOLD,          nullptr, ReanimationType::REANIM_MARIGOLD,        24, 50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("MARIGOLD") },
    { SeedType::SEED_MELONPULT,         nullptr, ReanimationType::REANIM_MELONPULT,       14, 300,    750,    PlantSubClass::SUBCLASS_SHOOTER,    300,    _S("MELON_PULT") },

    { SeedType::SEED_PULTSHROOM,        nullptr, ReanimationType::REANIM_PULTSHROOM,      13, 0,      750,    PlantSubClass::SUBCLASS_SHOOTER,    300,    _S("PULT_SHROOM"),1 },
    { SeedType::SEED_LUMESHROOM,        nullptr, ReanimationType::REANIM_LUMESHROOM,      5,  50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("LUME_SHROOM"), 1 },
    { SeedType::SEED_MORTARSHROOM,      nullptr, ReanimationType::REANIM_MORTARSHROOM,    5,  75,     750,    PlantSubClass::SUBCLASS_SHOOTER,    600,    _S("MORTAR_SHROOM"),1 },
    { SeedType::SEED_BLOODORANGE,       nullptr, ReanimationType::REANIM_BLOODORANGE,     30, 50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     150,    _S("BLOOD_ORANGE"), 1 },
    { SeedType::SEED_REED,              nullptr, ReanimationType::REANIM_REED,            5,  125,    750,    PlantSubClass::SUBCLASS_SHOOTER,    200,    _S("LIGHTNING_REED"),1 },
    { SeedType::SEED_HURRIKALE,         nullptr, ReanimationType::REANIM_HURIKALE,        5,  100,    3000,   PlantSubClass::SUBCLASS_NORMAL,     150,    _S("HURRIKALE"),1 },  
    { SeedType::SEED_VOLTSHROOM,        nullptr, ReanimationType::REANIM_VOLTSHROOM,      5,  175,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("VOLT_SHROOM"),1},
    { SeedType::SEED_GHOSTPEPPER ,      nullptr, ReanimationType::REANIM_GHOSTPEPPER,     5,  75,     3000,   PlantSubClass::SUBCLASS_NORMAL,     450,    _S("GHOST_PEPPER"),1},

    { SeedType::SEED_BEE_SHOOTER,       nullptr, ReanimationType::REANIM_BEESHOOTER,      5,  100,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("BEESHOOTER"),1},
    { SeedType::SEED_CHARD_GUARD,       nullptr, ReanimationType::REANIM_CHARDGUARD,      5,  75,     3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("CHARD_GUARD"),1},
    { SeedType::SEED_BONKCHOY,          nullptr, ReanimationType::REANIM_BONKCHOY,        5,  150,    750,    PlantSubClass::SUBCLASS_NORMAL,     150,    _S("BONK_CHOY"),1},
    { SeedType::SEED_ALOEVERA,          nullptr, ReanimationType::REANIM_ALOE,            5,  50,     750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("ALOE_VERA"),1},
    { SeedType::SEED_OAK_ARCHER,        nullptr, ReanimationType::REANIM_OAKARCHER,       5,  175,    750,    PlantSubClass::SUBCLASS_SHOOTER,    450,    _S("OAK_ARCHER"),1},
    { SeedType::SEED_SHRINK,            nullptr, ReanimationType::REANIM_VIOLET,          5,  100,    5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("SHRINKING_VIOLET"),1},
    { SeedType::SEED_LEMON_NADE,        nullptr, ReanimationType::REANIM_LEMONADE,        5,  200,    5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("LEMON_NADE"),1},
    { SeedType::SEED_AMPLI_FLOWER,      nullptr, ReanimationType::REANIM_AMPLIFLOWER,     5,  125,    750,    PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("AMPLIFLOWER"),1},

    { SeedType::SEED_GATLINGPEA,        nullptr, ReanimationType::REANIM_GATLINGPEA,      5,  250,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("GATLING_PEA"),0 },
    { SeedType::SEED_TWINSUNFLOWER,     nullptr, ReanimationType::REANIM_TWIN_SUNFLOWER,  1,  150,    5000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("TWIN_SUNFLOWER"),0 },
    { SeedType::SEED_GLOOMSHROOM,       nullptr, ReanimationType::REANIM_GLOOMSHROOM,     27, 150,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    200,    _S("GLOOM_SHROOM"),0 },
    { SeedType::SEED_CATTAIL,           nullptr, ReanimationType::REANIM_CATTAIL,         27, 225,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("CATTAIL"),0 },
    { SeedType::SEED_WINTERMELON,       nullptr, ReanimationType::REANIM_WINTER_MELON,    27, 200,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    300,    _S("WINTER_MELON"),0 },
    { SeedType::SEED_GOLD_MAGNET,       nullptr, ReanimationType::REANIM_GOLD_MAGNET,     27, 50,     5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("GOLD_MAGNET"),0 },
    { SeedType::SEED_SPIKEROCK,         nullptr, ReanimationType::REANIM_SPIKEROCK,       27, 125,    5000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("SPIKEROCK"),0 },
    { SeedType::SEED_COBCANNON,         nullptr, ReanimationType::REANIM_COBCANNON,       16, 500,    5000,   PlantSubClass::SUBCLASS_NORMAL,     600,    _S("COB_CANNON"),0 },

    { SeedType::SEED_ICYFUME,           nullptr, ReanimationType::REANIM_ICYFUME,         5,  200,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("FROST_SHROOM"),1 },
    { SeedType::SEED_SUPERCHOMP,        nullptr, ReanimationType::REANIM_SUPERCHOMP,      5,  150,    5000,   PlantSubClass::SUBCLASS_NORMAL ,    150,    _S("DEVOURER"),1 },
    { SeedType::SEED_FLAMEWOOD,         nullptr, ReanimationType::REANIM_FLAMEWOOD,       5,  175,    5000,   PlantSubClass::SUBCLASS_NORMAL,     150,    _S("PLASMAWOOD"),1 },
    { SeedType::SEED_QUEENPEA,          nullptr, ReanimationType::REANIM_ICEQUEEN,        5,  225,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("ICE_QUEEN_PEA"),1 },
    { SeedType::SEED_VINENUT,           nullptr, ReanimationType::REANIM_VINENUT,         5,  100,    5000,   PlantSubClass::SUBCLASS_NORMAL,     150,    _S("VINE_NUT"),1 },
    { SeedType::SEED_THORNMOSS,         nullptr, ReanimationType::REANIM_THORNMOSS,       5,  50,     5000,   PlantSubClass::SUBCLASS_NORMAL ,    150,    _S("THORNMOSS"),1 },
    { SeedType::SEED_BRAVESHROOM,       nullptr, ReanimationType::REANIM_BRAVERYSHROOM,   5,  75,     5000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("BRAVERY_SHROOM"),1 },
    { SeedType::SEED_ECACTUS,           nullptr, ReanimationType::REANIM_CACTUSKING,      5,  250,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("KING_CACTUS"),1 },
    
    { SeedType::SEED_IMITATER,          nullptr, ReanimationType::REANIM_IMITATER,        33, 0,      750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("IMITATER"),0 },

    { SeedType::SEED_FLAMEPEA,          nullptr, ReanimationType::REANIM_FLAMEPEA,        5,  200,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("FIRE_PEASHOOTER"),2 },
    { SeedType::SEED_PEPPER,            nullptr, ReanimationType::REANIM_PEPPER,          13, 200,    750,    PlantSubClass::SUBCLASS_SHOOTER,    300,    _S("PEPPER_PULT"), 2 },
    { SeedType::SEED_PICKLEPEPPER,      nullptr, ReanimationType::REANIM_PICKLEPEPPER,    5,  125,    5000,   PlantSubClass::SUBCLASS_NORMAL,     150,    _S("PICKLED_PEPPER"),2 },
    { SeedType::SEED_FIRESHROOM,        nullptr, ReanimationType::REANIM_FIRESHROOM,      5,  75,     3000,   PlantSubClass::SUBCLASS_NORMAL,     150,    _S("FIRE_SHROOM"),2 },
    { SeedType::SEED_WATERPOT,          nullptr, ReanimationType::REANIM_FLOWER_POT,      33, 25,     750,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("WATER_POT"), 2 },
    { SeedType::SEED_PINKSTAR,          nullptr, ReanimationType::REANIM_PINKSTAR,        30, 175,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("SEASTAR"), 2 },
    { SeedType::SEED_CHILLYPEPPER,      nullptr, ReanimationType::REANIM_CHILLYPEPPER,    5,  100,    5000,   PlantSubClass::SUBCLASS_NORMAL,     150,    _S("CHILLYPEPPER"),2 },
    { SeedType::SEED_EPEA ,             nullptr, ReanimationType::REANIM_EPEA,            5,  300,    750,    PlantSubClass::SUBCLASS_SHOOTER,    450,    _S("ELECTRIC_PEA"),2 },

    { SeedType::SEED_PLASMAPEA,         nullptr, ReanimationType::REANIM_PLASMAPEA,       5,  100,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("PLASMAPEA"),2 },
    { SeedType::SEED_SHOOTINGSTAR,      nullptr, ReanimationType::REANIM_SHOOTINGSTAR,    30, 325,    5000,   PlantSubClass::SUBCLASS_SHOOTER,    450,    _S("SHOOTING_STAR"),2 },

    { SeedType::SEED_EXPLODE_O_NUT,     nullptr, ReanimationType::REANIM_EXPLODEONUT,     2,  0,      3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("EXPLODE_O_NUT"),-1 },
    { SeedType::SEED_GIANT_WALLNUT,     nullptr, ReanimationType::REANIM_WALLNUT,         2,  0,      3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("GIANT_WALLNUT"),-1 },
    { SeedType::SEED_SPROUT,            nullptr, ReanimationType::REANIM_ZENGARDEN_SPROUT,33, 0,      3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("SPROUT"),-1 },
    { SeedType::SEED_LEFTPEATER,        nullptr, ReanimationType::REANIM_REPEATER,        5,  200,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("REPEATER"),-1 },
    { SeedType::SEED_ICENUT,            nullptr, ReanimationType::REANIM_ICENUT,          2,  0,      3000,   PlantSubClass::SUBCLASS_NORMAL,     0,      _S("ICENUT"),-1 },

    { SeedType::SEED_VERSUS_NORMAL,          nullptr, ReanimationType::REANIM_ZOMBIE,               2,  25,     750,    PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("ZOMBIE"),0 },
    { SeedType::SEED_GRAVE,                  nullptr, ReanimationType::REANIM_GRAVE,                2,  50,     750,    PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("GRAVE"),0 },
    { SeedType::SEED_VERSUS_CONEHEAD,        nullptr, ReanimationType::REANIM_ZOMBIE,               2,  75,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("CONEHEAD_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_POLE,            nullptr, ReanimationType::REANIM_POLEVAULTER,          2,  75,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("POLE_VAULTING_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_BUCKET,          nullptr, ReanimationType::REANIM_ZOMBIE,               2,  100,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("BUCKETHEAD_ZOMBIE"),0 },

    { SeedType::SEED_VERSUS_NEWSPAPER,       nullptr, ReanimationType::REANIM_ZOMBIE_NEWSPAPER,     2,  50,     1500,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("NEWSPAPER_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_SCREENDOOR,      nullptr, ReanimationType::REANIM_ZOMBIE,               2,  100,    1500,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("SCREEN_DOOR_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_FOOTBALL,        nullptr, ReanimationType::REANIM_ZOMBIE_FOOTBALL,      2,  150,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("FOOTBALL_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_DANCER,          nullptr, ReanimationType::REANIM_DANCER,               2,  150,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("DANCING_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_FLAG,            nullptr, ReanimationType::REANIM_ZOMBIE,               2,  300,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("FLAG_ZOMBIE"),0 },

    { SeedType::SEED_VERSUS_ZOMBONI,         nullptr, ReanimationType::REANIM_ZOMBIE_ZAMBONI,       2,  150,    6000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("ZOMBONI"),0 },
    { SeedType::SEED_VERSUS_JACK,            nullptr, ReanimationType::REANIM_JACKINTHEBOX,         2,  50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("JACK_IN_THE_BOX_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_BALLOON,         nullptr, ReanimationType::REANIM_BALLOON,              2,  200,    6000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("BALLOON_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_DIGGER,          nullptr, ReanimationType::REANIM_DIGGER,               2,  100,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("DIGGER_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_POGO,            nullptr, ReanimationType::REANIM_POGO,                 2,  175,    6000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("POGO_ZOMBIE"),0 },

    { SeedType::SEED_VERSUS_BUNGEE,          nullptr, ReanimationType::REANIM_BUNGEE,               2,  125,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("BUNGEE_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_LADDER,          nullptr, ReanimationType::REANIM_LADDER,               2,  150,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("LADDER_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_CATAPULT,        nullptr, ReanimationType::REANIM_CATAPULT,             2,  150,    6000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("CATAPULT_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_GARGANTUAR,      nullptr, ReanimationType::REANIM_GARGANTUAR,           2,  225,    6000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("GARGANTUAR"),0 },
    { SeedType::SEED_VERSUS_TRASHCAN,        nullptr, ReanimationType::REANIM_ZOMBIE,               2,  50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("TRASHCAN_ZOMBIE"),0 },

    { SeedType::SEED_VERSUS_VAMPIRE,         nullptr, ReanimationType::REANIM_VAMPIRE,              2,  75,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("VAMPIRE"),0 },
    { SeedType::SEED_VERSUS_SCARECROW,       nullptr, ReanimationType::REANIM_SCARECROW,            2,  150,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("SCARECROW"),0 },
    { SeedType::SEED_VERSUS_FOOTBALL_GIGA,   nullptr, ReanimationType::REANIM_ZOMBIE_GIGA_FOOTBALL, 2,  300,    6000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("GIGA_FOOTBALL_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_GLADIANTUAR,     nullptr, ReanimationType::REANIM_GLADIANTUAR,          2,  300,    9000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("GLADIANTUAR"),0 },
    { SeedType::SEED_VERSUS_GARGANTUAR_GIGA, nullptr, ReanimationType::REANIM_GARGANTUAR,           2,  450,    12000,  PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("REDEYED_GARGANTUAR"),0 },

    { SeedType::SEED_VERSUS_IMP,             nullptr, ReanimationType::REANIM_IMP,                  2,  25,     750,    PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("IMP"),0 },
    { SeedType::SEED_VERSUS_SNORKEL,         nullptr, ReanimationType::REANIM_SNORKEL,              2,  50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("SNORKEL_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_DOLPHIN,         nullptr, ReanimationType::REANIM_ZOMBIE_DOLPHINRIDER,  2,  125,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("DOLPHIN_RIDER_ZOMBIE"),0 },
    { SeedType::SEED_VERSUS_BACKUP,          nullptr, ReanimationType::REANIM_BACKUP_DANCER,        2,  0,      3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("BACKUP_DANCER"),0 },
    { SeedType::SEED_VERSUS_ZOMBOSS,         nullptr, ReanimationType::REANIM_BOSS,                 2,  1000,   18000,  PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("BOSS"),0 },

    { SeedType::SEED_VERSUS_LEAFBLOWER,      nullptr, ReanimationType::REANIM_LEAFBLOWER,           2,  125,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("LEAFBLOWER"),1 },
    { SeedType::SEED_VERSUS_LUMBERJACK,      nullptr, ReanimationType::REANIM_LUMBERJACK,           2,  200,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("LUMBERJACK"),1 },
    { SeedType::SEED_VERSUS_FISHERMAN,       nullptr, ReanimationType::REANIM_FISHERMAN,            2,  50,     3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("FISHERMAN"),1 },
    { SeedType::SEED_VERSUS_HUNTER,          nullptr, ReanimationType::REANIM_HUNTER,               2,  150,    3000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("HUNTER"),1 },
    { SeedType::SEED_VERSUS_ICE,             nullptr, ReanimationType::REANIM_ICE_ZOMBIE,           2,  175,    6000,   PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("ICE"),1 },

    { SeedType::SEED_VERSUS_GLADIANTUAR_GIGA,nullptr, ReanimationType::REANIM_GLADIANTUAR,          2,  900,    18000,  PlantSubClass::SUBCLASS_NORMAL,     2500,   _S("GIGA_GLADIANTUAR"),2 },

    { SeedType::SEED_REVERSE_PEASHOOTER,     nullptr, ReanimationType::REANIM_PEASHOOTER,    0,   100,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("PEASHOOTER"),-1 },
    { SeedType::SEED_REVERSE_SNOWPEA,        nullptr, ReanimationType::REANIM_SNOWPEA,       4,   175,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("SNOW_PEA"),-1 },
    { SeedType::SEED_REVERSE_CHOMPER,        nullptr, ReanimationType::REANIM_CHOMPER,       31,  150,    750,    PlantSubClass::SUBCLASS_NORMAL,     150,    _S("CHOMPER"),-1 },
    { SeedType::SEED_REVERSE_PUFFSHROOM,     nullptr, ReanimationType::REANIM_PUFFSHROOM,    31,  0,      750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("CHOMPER"),-1 },
    { SeedType::SEED_REVERSE_FUMESHROOM,     nullptr, ReanimationType::REANIM_FUMESHROOM,    31,  75,     750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("CHOMPER"),-1 },
    { SeedType::SEED_REVERSE_CACTUS,         nullptr, ReanimationType::REANIM_CACTUS,        31,  100,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("CHOMPER"),-1 },
    { SeedType::SEED_REVERSE_STARFRUIT,      nullptr, ReanimationType::REANIM_STARFRUIT,     31,  550,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("CHOMPER"),-1 },
    { SeedType::SEED_REVERSE_THREEPEATER,    nullptr, ReanimationType::REANIM_THREEPEATER,   31,  325,    750,    PlantSubClass::SUBCLASS_SHOOTER,    150,    _S("THREEPEATER"),-1 },
    { SeedType::SEED_DUMMY,                  nullptr, ReanimationType::REANIM_DUMMY,         2,    50,   3000,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("DUMMY"),-1 },
    { SeedType::SEED_FLYING_GARLIC,          nullptr, ReanimationType::REANIM_AIRRAID_POT,        2,    50,   3000,    PlantSubClass::SUBCLASS_NORMAL,     0,      _S("DUMMY"),-1 },
};

//0x401B20
Plant::Plant()
{
}

//0x45DB60
void Plant::PlantInitialize(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType)
{
    mPlantCol = theGridX;
    mRow = theGridY;
    if (mBoard && !mIsPreview) // It should check if its valid because -1 will crash
    {
        mX = mBoard->GridToPixelX(theGridX, theGridY);
        mY = mBoard->GridToPixelY(theGridX, theGridY);
    }
    mAnimCounter = 0;
    mAnimPing = true;
    mFrame = 0;
    mShootingCounter = 0;
    mShakeOffsetX = 0.0f;
    mShakeOffsetY = 0.0f;
    mFrameLength = RandRangeInt(12, 18);
    mTargetX = -1;
    mTargetY = -1;
    mStartRow = mRow;
    mNumFrames = 5;
    mState = PlantState::STATE_NOTREADY;
    mDead = false;
    mSquished = false;
    mSeedType = theSeedType;
    mImitaterType = theImitaterType;
    mPlantHealth = 300;
    mDoSpecialCountdown = 0;
    mDisappearCountdown = 200;
    mStateCountdown = 0;
    mParticleID = ParticleSystemID::PARTICLESYSTEMID_NULL;
    mBodyReanimID = ReanimationID::REANIMATIONID_NULL;
    mHeadReanimID = ReanimationID::REANIMATIONID_NULL;
    mHeadReanimID2 = ReanimationID::REANIMATIONID_NULL;
    mHeadReanimID3 = ReanimationID::REANIMATIONID_NULL;
    mBlinkReanimID = ReanimationID::REANIMATIONID_NULL;
    mLightReanimID = ReanimationID::REANIMATIONID_NULL;
    mSleepingReanimID = ReanimationID::REANIMATIONID_NULL;
    mBlinkCountdown = 0;
    mRecentlyEatenCountdown = 0;
    mEatenFlashCountdown = 0;
    mBeghouledFlashCountdown = 0;
    mWidth = 80;
    mHeight = 80;
    memset(mMagnetItems, 0, sizeof(mMagnetItems));
    const PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
    mIsAsleep = false;
    mWakeUpCounter = 0;
    mOnBungeeState = PlantOnBungeeState::NOT_ON_BUNGEE;
    mPottedPlantIndex = -1;
    mLaunchRate = aPlantDef.mLaunchRate;
    mSubclass = aPlantDef.mSubClass;
    mRenderOrder = CalcRenderOrder();
    mSeaStarCycle = false;
    mChilledCounter = 0;
    mBoostCounter = 0;
    mToss = false;
    mMoveTimer = 0;
    mNextX = 0;
    mNextY = 0;
    XGrid = 0;
    YGrid = 0;
    XOrig = 0;
    YOrig = 0;
    BounceLimit = 0;
    mMushroomAge = 0;
    mShrinkCounter = 0;
    mStopAnimation = false;
    mIsBackwards = false;
    mChardGuardLeafs = 0;
    mApliflowerCounter = 0;
    mCycle = false;
    mMoveOffset = 0;
    mStunnedWeb = 0;
    mStunned = 0;
    mHypnotized = false;
    mSoundCounter = -1;
	mTriggered = false;
	mGhostAge = 0;
	mGhostFlash = 0;

    Reanimation* aBodyReanim = nullptr;
    if (aPlantDef.mReanimationType != ReanimationType::REANIM_NONE)
    {
        float aOffsetY = PlantDrawHeightOffset(mBoard, this, mSeedType, mPlantCol, mRow);
        ReanimationType aReanimationType;
        //if (aPlantDef.mReanimationType == REANIM_LEMONADE && !mApp->mPlayerInfo->mHardmodeIsOff) aReanimationType = SetUpCostumes(aPlantDef.mReanimationType);
        //else 
        aReanimationType = aPlantDef.mReanimationType;
        aBodyReanim = mApp->AddReanimation(0.0f, aOffsetY, mRenderOrder + 1, aReanimationType);
        aBodyReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
        aBodyReanim->mAnimRate = RandRangeFloat(10.0f, 15.0f);

        if (mSeedType == SEED_GRAVE && mBoard->mPlantRow[mRow] == PLANTROW_POOL)
        {
            if (aBodyReanim->TrackExists("anim_idle_water"))
                aBodyReanim->SetFramesForLayer("anim_idle_water");    
        }
        else if (mSeedType == SEED_GRAVE && (mBoard->mBackground == BACKGROUND_5_ROOF || mBoard->mBackground == BACKGROUND_6_BOSS))
        {
            if (aBodyReanim->TrackExists("anim_idle_roof"))
                aBodyReanim->SetFramesForLayer("anim_idle_roof");
        }
        else
        {
            if (aBodyReanim->TrackExists("anim_idle"))
                aBodyReanim->SetFramesForLayer("anim_idle");
        }

       /* if (mBoard && SEED_GRAVE && (mBoard->mBackground == BACKGROUND_5_ROOF || mBoard->mBackground == BACKGROUND_6_BOSS))
        {
            aBodyReanim->SetImageOverride("Stone_dirt", IMAGE_BLANK);
            ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("eye_glow_right");
            aTrackInstance->mShakeX -= 2;
            aTrackInstance->mShakeY -= 2;
            ReanimatorTrackInstance* aTrackInstance2 = aBodyReanim->GetTrackInstanceByName("eye_glow_left");
            aTrackInstance2->mShakeX -= 1;
            aTrackInstance2->mShakeY -= 2;
        }*/
        if (mBoard && mSeedType == SEED_GRAVE && (mBoard->mBackground == BACKGROUND_2_NIGHT || mBoard->mBackground == BACKGROUND_4_FOG))
        {
            aBodyReanim->SetImageOverride("Stone_dirt", IMAGE_GRAVESTONE_NIGHT_DIRT);
        }

        if (mBoard && mSeedType == SEED_MORTARSHROOM && ((mBoard->GetFlowerPotAt(mPlantCol, mRow) || (mBoard->mBackground != BACKGROUND_5_ROOF && mBoard->mBackground != BACKGROUND_6_BOSS))))
        {
            aBodyReanim->SetImageOverride("anim_body", IMAGE_REANIM_MORTAR_BODY_2);
        }

        if (mApp->IsWallnutBowlingLevel() && aBodyReanim->TrackExists("_ground"))
        {
            aBodyReanim->SetFramesForLayer("_ground");
            if (mSeedType == SeedType::SEED_WALLNUT || mSeedType == SeedType::SEED_EXPLODE_O_NUT || mSeedType == SeedType::SEED_DUMMY)
                aBodyReanim->mAnimRate = RandRangeFloat(12.0f, 18.0f);
            else if (mSeedType == SeedType::SEED_GIANT_WALLNUT)
                aBodyReanim->mAnimRate = RandRangeFloat(6.0f, 10.0f);
        }

        aBodyReanim->mIsAttachment = true;
        mBodyReanimID = mApp->ReanimationGetID(aBodyReanim);
        mBlinkCountdown = 400 + Sexy::Rand(400);
    }

    if (IsNocturnal(mSeedType) && mBoard && !mBoard->StageIsNight() && !mIsPreview) //Preview Plant dont sleep
        SetSleeping(true);

    if (mLaunchRate > 0)
    {
        if (MakesSun())
            mLaunchCounter = RandRangeInt(300, mLaunchRate / 2);
        else
            mLaunchCounter = RandRangeInt(0, mLaunchRate);
    }
    else
        mLaunchCounter = 0;

    switch (theSeedType)
    {
    case SeedType::SEED_FLYING_GARLIC:
    {
        Reanimation* aGarlic = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, ReanimationType::REANIM_GARLIC);
        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("Airraid_pottop");

        aGarlic->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 12.0f);
        mHeadReanimID = mApp->ReanimationGetID(aGarlic);
            //aGarlic->AttachToAnotherReanimation(aBodyReanim, "Airraid_pottop");
        aBodyReanim->AssignRenderGroupToPrefix("Pot_pumpkin", RENDER_GROUP_HIDDEN);
        AttachEffect* aAttachedGarlic = AttachReanim(aTrackInstance->mAttachmentID, aGarlic, -2.0f, -30.0f);
        UpdateReanim();
        aBodyReanim->Update();
    }
    case SeedType::SEED_TWINSUNFLOWER:
    case SeedType::SEED_SUNFLOWER:
    {
        TOD_ASSERT(aBodyReanim);
        if (IsInPlay() && mApp->IsIZombieLevel())
        {
            aBodyReanim->mAnimTime = 0.15f;
        }
        break;
    }
    case SeedType::SEED_BLOVER:
    case SeedType::SEED_HURRIKALE:
    {
        mDoSpecialCountdown = 50;

        if (IsInPlay())
        {
            aBodyReanim->SetFramesForLayer("anim_blow");
            aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
            aBodyReanim->mAnimRate = 20.0f;
        }
        else
        {
            aBodyReanim->SetFramesForLayer("anim_idle");
            aBodyReanim->mAnimRate = 10.0f;
        }

        break;
    }
    case SeedType::SEED_PINKSTAR:
        /*AttachEffect* aAttachEffect;
        ReanimatorTrackInstance* aTrackInstance;
        aTrackInstance = aBodyReanim->GetTrackInstanceByName("angelstarfruit_body");
        aBodyReanim->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
        aAttachEffect = AttachReanim(aTrackInstance->mAttachmentID, aBodyReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;
        TodScaleRotateTransformMatrix(aAttachEffect->mOffset, 37.0f, 0.0f, 0.2f, -0.8f, 0.8f); */
    break;
    case SeedType::SEED_PEASHOOTER:
    case SeedType::SEED_FLAMEPEA:
    case SeedType::SEED_QUEENPEA:
    case SeedType::SEED_PLASMAPEA:
    case SeedType::SEED_EPEA:
    case SeedType::SEED_SNOWPEA:
    case SeedType::SEED_REPEATER:
    case SeedType::SEED_LEFTPEATER:
    case SeedType::SEED_GATLINGPEA:
    case SeedType::SEED_BEE_SHOOTER:
    case SeedType::SEED_REVERSE_PEASHOOTER:
    case SeedType::SEED_REVERSE_SNOWPEA:
        if (aBodyReanim)
        {
            aBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
            Reanimation* aHeadReanim = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
            aHeadReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
            aHeadReanim->mAnimRate = aBodyReanim->mAnimRate;
            aHeadReanim->SetFramesForLayer("anim_head_idle");
            mHeadReanimID = mApp->ReanimationGetID(aHeadReanim);

            if (aBodyReanim->TrackExists("anim_stem"))
                aHeadReanim->AttachToAnotherReanimation(aBodyReanim, "anim_stem");
            else if (aBodyReanim->TrackExists("anim_idle"))
                aHeadReanim->AttachToAnotherReanimation(aBodyReanim, "anim_idle");
        }
        break;
    case SeedType::SEED_SPLITPEA:
    {
        TOD_ASSERT(aBodyReanim);

        aBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
        Reanimation* aHeadReanim1 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim1->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim1->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim1->SetFramesForLayer("anim_head_idle");
        aHeadReanim1->AttachToAnotherReanimation(aBodyReanim, "anim_idle");
        mHeadReanimID = mApp->ReanimationGetID(aHeadReanim1);

        Reanimation* aHeadReanim2 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim2->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim2->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim2->SetFramesForLayer("anim_splitpea_idle");
        aHeadReanim2->AttachToAnotherReanimation(aBodyReanim, "anim_idle");
        mHeadReanimID2 = mApp->ReanimationGetID(aHeadReanim2);

        break;
    }
    case SeedType::SEED_THREEPEATER:
    {
        TOD_ASSERT(aBodyReanim);

        aBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
        Reanimation* aHeadReanim1 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim1->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim1->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim1->SetFramesForLayer("anim_head_idle1");
        aHeadReanim1->AttachToAnotherReanimation(aBodyReanim, "anim_head1");
        mHeadReanimID = mApp->ReanimationGetID(aHeadReanim1);

        Reanimation* aHeadReanim2 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim2->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim2->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim2->SetFramesForLayer("anim_head_idle2");
        aHeadReanim2->AttachToAnotherReanimation(aBodyReanim, "anim_head2");
        mHeadReanimID2 = mApp->ReanimationGetID(aHeadReanim2);

        Reanimation* aHeadReanim3 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim3->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim3->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim3->SetFramesForLayer("anim_head_idle3");
        aHeadReanim3->AttachToAnotherReanimation(aBodyReanim, "anim_head3");
        mHeadReanimID3 = mApp->ReanimationGetID(aHeadReanim3);

        break;
    }
    case SeedType::SEED_REVERSE_THREEPEATER:
    {
        TOD_ASSERT(aBodyReanim);

        aBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
        Reanimation* aHeadReanim1 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim1->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim1->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim1->SetFramesForLayer("anim_head_idle1");
        aHeadReanim1->AttachToAnotherReanimation(aBodyReanim, "anim_head1");
        mHeadReanimID = mApp->ReanimationGetID(aHeadReanim1);

        Reanimation* aHeadReanim2 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim2->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim2->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim2->SetFramesForLayer("anim_head_idle2");
        aHeadReanim2->AttachToAnotherReanimation(aBodyReanim, "anim_head2");
        mHeadReanimID2 = mApp->ReanimationGetID(aHeadReanim2);

        Reanimation* aHeadReanim3 = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, aPlantDef.mReanimationType);
        aHeadReanim3->mLoopType = ReanimLoopType::REANIM_LOOP;
        aHeadReanim3->mAnimRate = aBodyReanim->mAnimRate;
        aHeadReanim3->SetFramesForLayer("anim_head_idle3");
        aHeadReanim3->AttachToAnotherReanimation(aBodyReanim, "anim_head3");
        mHeadReanimID3 = mApp->ReanimationGetID(aHeadReanim3);

        break;
    }
    case SeedType::SEED_SHOOTINGSTAR:
    {
        if (aBodyReanim)
        {
            Reanimation* aHeadReanim = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder, aPlantDef.mReanimationType);
            aHeadReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
            aHeadReanim->mAnimRate = 12;
            aHeadReanim->SetFramesForLayer("anim_spiral");
            //mBackbodyReanimID = mApp->ReanimationGetID(aHeadReanim);
            aHeadReanim->AttachToAnotherReanimation(aBodyReanim, "anim_idle");
        }
        break;
    }
    case SeedType::SEED_WALLNUT:
        mPlantHealth = 4000;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        break;
    case SeedType::SEED_DUMMY:
        mPlantHealth = 4000;
        break;
    case SeedType::SEED_PULTSHROOM:
        if (mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON) mLaunchRate /= 2;
        if (IsInPlay())
        {
            mX += Sexy::Rand(10) - 5;
            mY += Sexy::Rand(6) - 3;
        }
        break;
    case SeedType::SEED_CHARD_GUARD:
        mPlantHealth = 2000;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        mState = PlantState::STATE_READY;
        mChardGuardLeafs = 3;
        break;
    case SeedType::SEED_OAK_ARCHER:
        mState = PlantState::STATE_READY;
        break;
    case SeedType::SEED_GHOSTPEPPER:
        mState = PlantState::STATE_READY;
        break;
    case SeedType::SEED_FIRESHROOM:
        mPlantHealth = 4000;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        break;
    case SeedType::SEED_EXPLODE_O_NUT:
        mPlantHealth = 4000;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        //aBodyReanim->mColorOverride = Color(255, 64, 64);
        break;
    case SeedType::SEED_GRAVE:
        if (mApp->IsVersusLevel()) mPlantHealth = 360;
        TOD_ASSERT(aBodyReanim);
        if (mBoard->mBackground == BACKGROUND_5_ROOF || mBoard->mBackground == BACKGROUND_6_BOSS)
        {
            if (IsInPlay())
            {
                aBodyReanim->SetFramesForLayer("anim_fall_roof");
                aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
                mSoundCounter = 33;
            }
        }
        break;
    case SeedType::SEED_ICENUT:
        mPlantHealth = 2000;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        //aBodyReanim->mColorOverride = Color(100, 160, 255);
        //aBodyReanim->mColorOverride = Color(255, 64, 64);
        break;
    case SeedType::SEED_GIANT_WALLNUT:
        mPlantHealth = 6500;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        break;
    case SeedType::SEED_TALLNUT:
        mPlantHealth = 8000;
        mHeight = 80;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        break;
    case SeedType::SEED_VINENUT:
        mPlantHealth = 8000;
        mHeight = 80;
        mBlinkCountdown = 1000 + Sexy::Rand(1000);
        break;
    case SeedType::SEED_GARLIC:
        TOD_ASSERT(aBodyReanim);
        mPlantHealth = 400;
        aBodyReanim->SetTruncateDisappearingFrames();
        break;
    case SeedType::SEED_GOLD_MAGNET:
        TOD_ASSERT(aBodyReanim);
        aBodyReanim->SetTruncateDisappearingFrames();
        break;
    case SeedType::SEED_IMITATER:
        TOD_ASSERT(aBodyReanim);
        aBodyReanim->mAnimRate = RandRangeFloat(25.0f, 30.0f);
        mStateCountdown = 200;
        break;
    case SeedType::SEED_WATERPOT:
        TOD_ASSERT(aBodyReanim);
        aBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
        aBodyReanim->SetFramesForLayer("anim_water_idle");
        if (IsInPlay())
        {
            mState = PlantState::STATE_FLOWERPOT_INVULNERABLE;
            mStateCountdown = 100;
        }
        break;
    case SeedType::SEED_CHERRYBOMB:
    case SeedType::SEED_JALAPENO:
    case SeedType::SEED_PICKLEPEPPER:
    case SeedType::SEED_CHILLYPEPPER:
    case SeedType::SEED_BLOODORANGE:
    {
        TOD_ASSERT(aBodyReanim);

        if (IsInPlay())
        {
            mDoSpecialCountdown = 100;

            aBodyReanim->SetFramesForLayer("anim_explode");
            aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;

            mApp->PlayFoley(FoleyType::FOLEY_REVERSE_EXPLOSION);
        }

        break;
    }
    case SeedType::SEED_POTATOMINE:
    {
        TOD_ASSERT(aBodyReanim);

        aBodyReanim->mAnimRate = 12.0f;

        if (IsInPlay())
        {
            aBodyReanim->AssignRenderGroupToTrack("anim_glow", RENDER_GROUP_HIDDEN);
            mStateCountdown = 1200;
        }
        else
        {
            aBodyReanim->SetFramesForLayer("anim_armed");
            mState = PlantState::STATE_POTATO_ARMED;
        }

        break;
    }
    case SeedType::SEED_GRAVEBUSTER:
    {
        TOD_ASSERT(aBodyReanim);

        if (IsInPlay())
        {
            aBodyReanim->SetFramesForLayer("anim_land");
            aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;

            mState = PlantState::STATE_GRAVEBUSTER_LANDING;
            mApp->PlayFoley(FoleyType::FOLEY_GRAVEBUSTERCHOMP);
        }

        break;
    }
    case SeedType::SEED_SHRINK:
        if (!IsInPlay())
        {
            PlayBodyReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 0);
        }
        break;
    case SeedType::SEED_SUNSHROOM:
    {
        TOD_ASSERT(aBodyReanim);

        aBodyReanim->mFrameBasePose = 6;

        if (IsInPlay())
        {
            mX += Sexy::Rand(10) - 5;
            mY += Sexy::Rand(10) - 5;
        }
        else if (mIsAsleep)
            aBodyReanim->SetFramesForLayer("anim_bigsleep");
        else
            aBodyReanim->SetFramesForLayer("anim_bigidle");

        mState = PlantState::STATE_SUNSHROOM_SMALL;
        mStateCountdown = 12000;

        break;
    }
    case SeedType::SEED_PUFFSHROOM:
    case SeedType::SEED_REVERSE_PUFFSHROOM:
    case SeedType::SEED_SEASHROOM:
        if (IsInPlay())
        {
            mX += Sexy::Rand(10) - 5;
            mY += Sexy::Rand(6) - 3;
        }
        break;
    case SeedType::SEED_PUMPKINSHELL:
    {
        mPlantHealth = 4000;
        mWidth = 120;

        TOD_ASSERT(aBodyReanim);
        aBodyReanim->AssignRenderGroupToTrack("Pumpkin_back", 1);
        break;
    }
    case SeedType::SEED_CHOMPER:
    case SeedType::SEED_REVERSE_CHOMPER:
    case SeedType::SEED_AMPLI_FLOWER:
    case SeedType::SEED_BONKCHOY:
        mState = PlantState::STATE_READY;
        break;
    case SeedType::SEED_SUPERCHOMP:
        mState = PlantState::STATE_READY;
        break;
    case SeedType::SEED_PLANTERN:
    {
        mStateCountdown = 50;

        if (!IsOnBoard() || mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN)
        {
            AddAttachedParticle(mX + 40, mY + 40, (int)RenderLayer::RENDER_LAYER_FOG + 1, ParticleEffect::PARTICLE_LANTERN_SHINE);
        }
        if (IsInPlay())
        {
            mApp->PlaySample(Sexy::SOUND_PLANTERN);
        }
        
        break;
    }
    case SeedType::SEED_LUMESHROOM:
    {
        mMushroomAge = 1000;

        if ((!IsOnBoard() || mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN) && !mIsAsleep)
        {
            AddAttachedParticle(mX + 40, mY + 40, (int)RenderLayer::RENDER_LAYER_FOG + 1, ParticleEffect::PARTICLE_LANTERN_SHINE);
        }
        if (IsInPlay() && !mIsAsleep)
        {
            mApp->PlaySample(Sexy::SOUND_PLANTERN);
        }

        break;
    }
    case SeedType::SEED_TORCHWOOD:
    case SeedType::SEED_FLAMEWOOD:
        break;
    case SeedType::SEED_MARIGOLD:
        TOD_ASSERT(aBodyReanim);
        if (IsInPlay())
        {
            if (mApp->IsIZombieLevel())
                aBodyReanim->mAnimTime = 0.15f;
            else 
                aBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
        }
        break;
    case SeedType::SEED_CACTUS:
        mState = PlantState::STATE_CACTUS_LOW;
        break;
    case SeedType::SEED_INSTANT_COFFEE:
        mDoSpecialCountdown = 100;
        break;
    case SeedType::SEED_SCAREDYSHROOM:
        mState = PlantState::STATE_READY;
        break;
    case SeedType::SEED_BRAVESHROOM:
        mState = PlantState::STATE_READY;
        break;
    case SeedType::SEED_COBCANNON:
        if (IsInPlay())
        {
            mState = PlantState::STATE_COBCANNON_ARMING;
            mStateCountdown = 500;

            TOD_ASSERT(aBodyReanim);
            aBodyReanim->SetFramesForLayer("anim_unarmed_idle");
        }
        break;
    case SeedType::SEED_KERNELPULT:
        TOD_ASSERT(aBodyReanim);
        aBodyReanim->AssignRenderGroupToPrefix("Cornpult_butter", RENDER_GROUP_HIDDEN);
        break;
    case SeedType::SEED_MAGNETSHROOM:
        TOD_ASSERT(aBodyReanim);
        aBodyReanim->SetTruncateDisappearingFrames();
        break;
    case SeedType::SEED_SPIKEROCK:
        mPlantHealth = 450;
        TOD_ASSERT(aBodyReanim);
        break;
    case SeedType::SEED_SPROUT:
        break;
    case SeedType::SEED_FLOWERPOT:
        if (IsInPlay())
        {
            mState = PlantState::STATE_FLOWERPOT_INVULNERABLE;
            mStateCountdown = 100;
        }
        break;
    case SeedType::SEED_LILYPAD:
        if (IsInPlay())
        {
            mState = PlantState::STATE_LILYPAD_INVULNERABLE;
            mStateCountdown = 100;
        }
        break;
    case SeedType::SEED_TANGLEKELP:
        TOD_ASSERT(aBodyReanim);
        aBodyReanim->SetTruncateDisappearingFrames();
    }

    if ((mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BIG_TIME) &&
        (theSeedType == SeedType::SEED_WALLNUT || theSeedType == SeedType::SEED_SUNFLOWER || theSeedType == SeedType::SEED_MARIGOLD))
    {
        mPlantHealth *= 2;
    }
    mPlantMaxHealth = mPlantHealth;

    if (mIsPreview)
        return;
    //to prevent them from making our flowerpots static.

    if ((mSeedType != SeedType::SEED_FLOWERPOT && mSeedType != SeedType::SEED_WATERPOT) && IsOnBoard())
    {
        TOD_ASSERT(mBoard);
        Plant* aFlowerPot = mBoard->GetFlowerPotAt(mPlantCol, mRow);
        if (aFlowerPot)
            mApp->ReanimationGet(aFlowerPot->mBodyReanimID)->mAnimRate = 0.0f;
    }

    if (IsInPlay() && mSeedType == SEED_LEMON_NADE)
    {
        mDoSpecialCountdown = 100;
        XOrig = mPlantCol, YOrig = mRow;
        XGrid = mPlantCol, YGrid = mRow;

        aBodyReanim->SetFramesForLayer("anim_explode");
        aBodyReanim->mLoopType = ReanimLoopType::REANIM_LOOP;

        mApp->PlayFoley(FoleyType::FOLEY_REVERSE_EXPLOSION);
    }
}

//0x45E7C0
int Plant::CalcRenderOrder()
{
    PLANT_ORDER anOrder = PLANT_ORDER::PLANT_ORDER_NORMAL;
    RenderLayer aLayer = RenderLayer::RENDER_LAYER_PLANT;

    SeedType aSeedType = mSeedType;
    if (mSeedType == SeedType::SEED_IMITATER && mImitaterType != SeedType::SEED_NONE)
        aSeedType = mImitaterType;

    if (mApp->IsWallnutBowlingLevel())
    {
        aLayer = RenderLayer::RENDER_LAYER_PROJECTILE;
    }
    else if (aSeedType == SeedType::SEED_PUMPKINSHELL)
    {
        anOrder = PLANT_ORDER::PLANT_ORDER_PUMPKIN;
    }
    else if (IsFlying(aSeedType))
    {
        anOrder = PLANT_ORDER::PLANT_ORDER_FLYER;
    }
    else if (aSeedType == SeedType::SEED_FLOWERPOT || aSeedType == SeedType::SEED_WATERPOT || (aSeedType == SeedType::SEED_LILYPAD && mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN))
    {
        anOrder = PLANT_ORDER::PLANT_ORDER_LILYPAD;
    }

    return Board::MakeRenderOrder(aLayer, mRow, anOrder * 5 - mX + 800);
}

//0x45E860
void Plant::SetSleeping(bool theIsAsleep)
{
    if (mIsAsleep == theIsAsleep || NotOnGround())
        return;

    mIsAsleep = theIsAsleep;
    if (theIsAsleep)
    {
        float aPosX = mX + 50.0f;
        float aPosY = mY + 40.0f;
        if (mSeedType == SeedType::SEED_FUMESHROOM)
            aPosX += 12.0f;
        else if (mSeedType == SeedType::SEED_SCAREDYSHROOM || mSeedType == SeedType::SEED_BRAVESHROOM)
            aPosY -= 20.0f;
        else if (mSeedType == SeedType::SEED_GLOOMSHROOM)
            aPosY -= 12.0f;
        else if (mSeedType == SeedType::SEED_ICYFUME)
            aPosY += 12.0f;

        Reanimation* aSleepReanim = mApp->AddReanimation(aPosX, aPosY, mRenderOrder + 2, ReanimationType::REANIM_SLEEPING);
        aSleepReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
        aSleepReanim->mAnimRate = RandRangeFloat(6.0f, 8.0f);
        aSleepReanim->mAnimTime = RandRangeFloat(0.0f, 0.9f);
        mSleepingReanimID = mApp->ReanimationGetID(aSleepReanim);
    }
    else
    {
        mApp->RemoveReanimation(mSleepingReanimID);
        mSleepingReanimID = ReanimationID::REANIMATIONID_NULL;
    }

    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim == nullptr)
        return;

    if (theIsAsleep)
    {
        if (!IsInPlay() && mSeedType == SeedType::SEED_SUNSHROOM)
        {
            aBodyReanim->SetFramesForLayer("anim_bigsleep");
        }
        else if (aBodyReanim->TrackExists("anim_sleep"))
        {
            float aAnimTime = aBodyReanim->mAnimTime;
            aBodyReanim->StartBlend(20);
            aBodyReanim->SetFramesForLayer("anim_sleep");
            aBodyReanim->mAnimTime = aAnimTime;
        }
        else
        {
            aBodyReanim->mAnimRate = 1.0f;
        }

        EndBlink();
    }
    else
    {
        if (!IsInPlay() && mSeedType == SeedType::SEED_SUNSHROOM)
        {
            aBodyReanim->SetFramesForLayer("anim_bigidle");
        }
        else if (aBodyReanim->TrackExists("anim_idle"))
        {
            float aAnimTime = aBodyReanim->mAnimTime;
            aBodyReanim->StartBlend(20);
            aBodyReanim->SetFramesForLayer("anim_idle");
            aBodyReanim->mAnimTime = aAnimTime;
        }

        if (aBodyReanim->mAnimRate < 2.0f && IsInPlay())
            aBodyReanim->mAnimRate = RandRangeFloat(10.0f, 15.0f);
    }
}

//0x45EB10
int Plant::GetDamageRangeFlags(PlantWeapon thePlantWeapon)
{
    switch (mSeedType)
    {
    case SeedType::SEED_CACTUS:
        return thePlantWeapon == PlantWeapon::WEAPON_SECONDARY ? 1 : 2;
    case SeedType::SEED_REED:
        return 3;
    case SeedType::SEED_CHERRYBOMB:
    case SeedType::SEED_JALAPENO:
    case SeedType::SEED_PICKLEPEPPER:
    case SeedType::SEED_CHILLYPEPPER:
    case SeedType::SEED_COBCANNON:
    case SeedType::SEED_DOOMSHROOM:
    case SeedType::SEED_SHRINK:
    case SeedType::SEED_LEMON_NADE:
    case SeedType::SEED_BLOODORANGE:
        return 127;
    case SeedType::SEED_MELONPULT:
    case SeedType::SEED_PEPPER:
    case SeedType::SEED_CABBAGEPULT:
    case SeedType::SEED_KERNELPULT:
    case SeedType::SEED_WINTERMELON:
    case SeedType::SEED_PULTSHROOM:
    case SeedType::SEED_SHOOTINGSTAR:
    case SeedType::SEED_MORTARSHROOM:
        return 13;
    case SeedType::SEED_POTATOMINE:
        return 77;
    case SeedType::SEED_SQUASH:
        return 13;
    case SeedType::SEED_PUFFSHROOM:
    case SeedType::SEED_REVERSE_PUFFSHROOM:
    case SeedType::SEED_SEASHROOM:
    case SeedType::SEED_FUMESHROOM:
    case SeedType::SEED_ICYFUME:
    case SeedType::SEED_GLOOMSHROOM:
    case SeedType::SEED_CHOMPER:
    case SeedType::SEED_REVERSE_CHOMPER:
    case SeedType::SEED_BONKCHOY:
    case SeedType::SEED_SUPERCHOMP:
        return 9;
    case SeedType::SEED_ECACTUS:
    case SeedType::SEED_CATTAIL:
        return 11;
    case SeedType::SEED_TANGLEKELP:
        return 5;
    case SeedType::SEED_GIANT_WALLNUT:
        return 17;
    default:
        return 1;
    }
}

//0x45EBD0
bool Plant::IsOnHighGround()
{
    return mBoard && mBoard->mGridSquareType[mPlantCol][mRow] == GridSquareType::GRIDSQUARE_HIGH_GROUND;
}

//0x45EC00
void Plant::SpikeRockTakeDamage()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);

    SpikeweedAttack();

    mPlantHealth -= 50;
    if (mPlantHealth <= 300)
    {
        aBodyReanim->AssignRenderGroupToTrack("bigspike3", RENDER_GROUP_HIDDEN);
    }
    if (mPlantHealth <= 150)
    {
        aBodyReanim->AssignRenderGroupToTrack("bigspike2", RENDER_GROUP_HIDDEN);
    }
    if (mPlantHealth <= 0)
    {
        mApp->PlayFoley(FoleyType::FOLEY_SQUISH);
        Die();
    }
}

bool Plant::IsSpiky()
{
    return mSeedType == SeedType::SEED_SPIKEWEED || mSeedType == SeedType::SEED_SPIKEROCK || mSeedType == SeedType::SEED_THORNMOSS;
}

//0x45ED00
void Plant::DoRowAreaDamage(int theDamage, unsigned int theDamageFlags)
{
    bool canDamageTarget = true;
    Plant* aGrave = nullptr;
    Plant* aBestPlant = nullptr;
    while (mBoard->IteratePlants(aGrave))
    {
        if (aGrave->mSeedType == SEED_GRAVE && aGrave->mRow == mRow)
        {
            canDamageTarget = false;
        }
    }
    Plant* bGrave = nullptr;
    while (mBoard->IteratePlants(bGrave))
    {
        if (bGrave->mSeedType == SEED_GRAVE && bGrave->mRow == mRow && bGrave->mPlantCol > mPlantCol && bGrave->mPlantCol < mPlantCol + 5 && (mSeedType == SEED_FUMESHROOM || mSeedType == SEED_ICYFUME))
        {
            if (aBestPlant == nullptr)
            {
                aBestPlant = bGrave;
            }
            else if (bGrave->mPlantCol < aBestPlant->mPlantCol)
            {
                aBestPlant = bGrave;
            }
        }
    }
    if (aBestPlant)
    {
        aBestPlant->mPlantHealth -= 20;
        aBestPlant->mEatenFlashCountdown = 25;
        mApp->PlayFoley(FOLEY_SPLAT);
    }

    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
    Rect aAttackRect = GetPlantAttackRect(PlantWeapon::WEAPON_PRIMARY);

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {       
        int aDiffY = (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS) ? 0 : (aZombie->mRow - mRow);
        if (mSeedType == SeedType::SEED_GLOOMSHROOM)
        {
            if (aDiffY < -1 || aDiffY > 1)
                continue;
        }
        else if (aDiffY)
            continue;

        if (aZombie->mOnHighGround == IsOnHighGround() && aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            Rect aZombieRect = aZombie->GetZombieRect();
            if (GetRectOverlap(aAttackRect, aZombieRect) > 0)
            {
                int aDamage = theDamage;
                if ((aZombie->mZombieType == ZombieType::ZOMBIE_ZOMBONI || aZombie->mZombieType == ZombieType::ZOMBIE_CATAPULT) &&
                    (TestBit(theDamageFlags, DamageFlags::DAMAGE_SPIKE)))
                {
                    aDamage = 1800;

                    if (mSeedType == SeedType::SEED_SPIKEROCK)
                    {
                        SpikeRockTakeDamage();
                    }
                    else
                    {
                        Die();
                    }
                }
                if (aZombie->mZombieType != ZOMBIE_TARGET || canDamageTarget)
                {
                    aZombie->TakeDamage(aDamage, theDamageFlags);
                    if (mSeedType == SeedType::SEED_ICYFUME) aZombie->ApplyChill(true);
                    mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
                }
            }
        }
    }
}

//0x45EEA0
TodParticleSystem* Plant::AddAttachedParticle(int thePosX, int thePosY, int theRenderPosition, ParticleEffect theEffect)
{
    TodParticleSystem* aParticle = mApp->ParticleTryToGet(mParticleID);
    if (aParticle)
        aParticle->ParticleSystemDie();

    TodParticleSystem* aNewParticle = mApp->AddTodParticle(thePosX, thePosY, theRenderPosition, theEffect);
    if (aNewParticle)
        mParticleID = mApp->ParticleGetID(aNewParticle);

    //if (icy)aNewParticle->OverrideColor(nullptr, Color(0, 255, 255, 255));

    return aNewParticle;
}

//0x45EF10
bool Plant::FindTargetAndFire(int theRow, PlantWeapon thePlantWeapon)
{
    Zombie* aZombie = FindTargetZombie(theRow, thePlantWeapon);
    Plant* aPlant = FindTargetPlant(theRow, thePlantWeapon);
    GridItem* aGridItem = FindTargetGridItem(theRow);
    if (aZombie == nullptr && (aPlant == nullptr || (aPlant->mSeedType != SEED_GRAVE && !aPlant->mHypnotized)) && aGridItem == nullptr)
        return false;

    EndBlink();
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    Reanimation* aHeadReanim = mApp->ReanimationTryToGet(mHeadReanimID);
    if (mSeedType == SeedType::SEED_SPLITPEA && thePlantWeapon == PlantWeapon::WEAPON_SECONDARY)
    {
        Reanimation* aHeadReanim2 = mApp->ReanimationGet(mHeadReanimID2);
        aHeadReanim2->StartBlend(20);
        aHeadReanim2->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
        aHeadReanim2->mAnimRate = 35.0f;
        aHeadReanim2->SetFramesForLayer("anim_splitpea_shooting");
        mShootingCounter = 25;
    }
    else if (aHeadReanim && aHeadReanim->TrackExists("anim_shooting"))
    {
        aHeadReanim->StartBlend(20);
        aHeadReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
        aHeadReanim->mAnimRate = 35.0f;
        aHeadReanim->SetFramesForLayer("anim_shooting");

        mShootingCounter = 33;
        if (mSeedType == SeedType::SEED_REPEATER || mSeedType == SeedType::SEED_SPLITPEA || mSeedType == SeedType::SEED_LEFTPEATER)
        {
            aHeadReanim->mAnimRate = 45.0f;
            mShootingCounter = 26;
        }
        else if (mSeedType == SeedType::SEED_GATLINGPEA)
        {
            aHeadReanim->mAnimRate = 38.0f;
            mShootingCounter = 100;
        }
    }
    else if (mState == PlantState::STATE_CACTUS_HIGH)
    {
        PlayBodyReanim("anim_shootinghigh", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 35.0f);
        mShootingCounter = 23;
    }
    else if (mSeedType == SeedType::SEED_REED)
    {
        PlayBodyReanim("anim_attack", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 35.0f);
        mShootingCounter = 20;
        int aRand = Rand(2);
        if (aRand == 0)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC);
        else if (aRand == 1)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC2);
        else  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC3);
    }
    else if (mSeedType == SeedType::SEED_GLOOMSHROOM)
    {
        PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 14.0f);
        mShootingCounter = 200;
    }
    else if (mSeedType == SeedType::SEED_CATTAIL || mSeedType == SeedType::SEED_BEE_SHOOTER)
    {
        PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 30.0f);
        mShootingCounter = 50;
    }
    else if (aBodyReanim && aBodyReanim->TrackExists("anim_shooting"))
    {
        PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 35.0f);

        switch (mSeedType)
        {
        case SeedType::SEED_FUMESHROOM:     mShootingCounter = 50;  break;
        case SeedType::SEED_ICYFUME:        mShootingCounter = 50;  break;
        case SeedType::SEED_PUFFSHROOM:     mShootingCounter = 29;  break;
        case SeedType::SEED_REVERSE_PUFFSHROOM: mShootingCounter = 29;  break;
        case SeedType::SEED_PULTSHROOM:
        case SeedType::SEED_MORTARSHROOM:
        case SeedType::SEED_SCAREDYSHROOM:  mShootingCounter = 25;  break;
        case SeedType::SEED_BRAVESHROOM:    mShootingCounter = 25;  break;
        case SeedType::SEED_PEPPER:
        case SeedType::SEED_CABBAGEPULT:    mShootingCounter = 32;  break;
        case SeedType::SEED_MELONPULT:
        case SeedType::SEED_WINTERMELON:    mShootingCounter = 36;  break;
        case SeedType::SEED_KERNELPULT:
        {
            if (Sexy::Rand(4) == 0)
            {
                aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
                aBodyReanim->AssignRenderGroupToPrefix("Cornpult_butter", RENDER_GROUP_NORMAL);
                aBodyReanim->AssignRenderGroupToPrefix("Cornpult_kernal", RENDER_GROUP_HIDDEN);
                mState = PlantState::STATE_KERNELPULT_BUTTER;
            }

            mShootingCounter = 30;
            break;
        }
        case SeedType::SEED_CACTUS:         mShootingCounter = 35;  break;
        default:                            mShootingCounter = 29;  break;
        }
    }
    else

        Fire(aZombie, theRow, thePlantWeapon);

    return true;
}

//0x45F2A0
void Plant::LaunchThreepeater()
{
    int rowAbove = mRow - 1;
    int rowBelow = mRow + 1;

    PlantWeapon aPlantWeapon = PlantWeapon::WEAPON_PRIMARY;
    if (mSeedType == SEED_REVERSE_THREEPEATER) aPlantWeapon = PlantWeapon::WEAPON_SECONDARY;

    if ((FindTargetZombie(mRow, aPlantWeapon)) ||
        (mBoard->RowCanHaveZombies(rowAbove) && FindTargetZombie(rowAbove, aPlantWeapon)) ||
        (mBoard->RowCanHaveZombies(rowBelow) && FindTargetZombie(rowBelow, aPlantWeapon)))
    {
        Reanimation* aHeadReanim1 = mApp->ReanimationGet(mHeadReanimID);
        Reanimation* aHeadReanim2 = mApp->ReanimationGet(mHeadReanimID2);
        Reanimation* aHeadReanim3 = mApp->ReanimationGet(mHeadReanimID3);

        if (mBoard->RowCanHaveZombies(rowBelow))
        {
            aHeadReanim1->StartBlend(10);
            aHeadReanim1->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
            aHeadReanim1->mAnimRate = 20.0f;
            aHeadReanim1->SetFramesForLayer("anim_shooting1");
        }

        aHeadReanim2->StartBlend(10);
        aHeadReanim2->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
        aHeadReanim2->mAnimRate = 20.0f;
        aHeadReanim2->SetFramesForLayer("anim_shooting2");

        if (mBoard->RowCanHaveZombies(rowAbove))
        {
            aHeadReanim3->StartBlend(10);
            aHeadReanim3->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
            aHeadReanim3->mAnimRate = 20.0f;
            aHeadReanim3->SetFramesForLayer("anim_shooting3");
        }

        mShootingCounter = 35;
    }
}

bool Plant::FindReedTarget()
{
    int rowAbove = mRow - 1;
    int rowBelow = mRow + 1;

    if ((FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY)) ||
        (mBoard->RowCanHaveZombies(rowAbove) && FindTargetZombie(rowAbove, PlantWeapon::WEAPON_PRIMARY)) ||
        (mBoard->RowCanHaveZombies(rowBelow) && FindTargetZombie(rowBelow, PlantWeapon::WEAPON_PRIMARY)))
    {
        return true;
    }
    return false;
}

//0x45F470
bool Plant::FindStarFruitTarget()
{
    if (mRecentlyEatenCountdown > 0)
        return true;

    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
    int aCenterStarX = mX + 40;
    int aCenterStarY = mY + 40;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        Rect aZombieRect = aZombie->GetZombieRect();
        if (aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            if (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS && mPlantCol >= 5)
                return true;

            if (aZombie->mRow == mRow)
            {
                if (aZombieRect.mX + aZombieRect.mWidth < aCenterStarX)
                    return true;
            }
            else
            {
                if (aZombie->mZombieType == ZombieType::ZOMBIE_DIGGER)
                    aZombieRect.mX += 10;

                float aProjectileTime = Distance2D(aCenterStarX, aCenterStarY, aZombieRect.mX + aZombieRect.mWidth / 2, aZombieRect.mY + aZombieRect.mHeight / 2) / 3.33f;
                int aZombieHitX = aZombie->ZombieTargetLeadX(aProjectileTime) - aZombieRect.mWidth / 2;
                if ((aZombieHitX + aZombieRect.mWidth > aCenterStarX) && (aZombieHitX < aCenterStarX))
                    return true;

                int aCenterZombieX = aZombieHitX + aZombieRect.mWidth / 2;
                int aCenterZombieY = aZombieRect.mY + aZombieRect.mHeight / 2;
                float angle = RAD_TO_DEG(atan2(aCenterZombieY - aCenterStarY, aCenterZombieX - aCenterStarX));
                if (abs(aZombie->mRow - mRow) < 2)
                {
                    if ((angle > 20.0f && angle < 40.0f) || (angle < -25.0f && angle > -45.0f))
                        return true;
                }
                else
                {
                    if ((angle > 25.0f && angle < 35.0f) || (angle < -28.0f && angle > -38.0f))
                        return true;
                }
            }
        }
    }
    Plant* aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant))
    {
        if (aPlant->mSeedType == SEED_GRAVE)
        {
            Rect aPlantRect = aPlant->GetPlantRect();
            if (aPlant->mRow == mRow)
            {
                if (aPlantRect.mX + aPlantRect.mWidth < aCenterStarX)
                    return true;
            }
            else
            {
                float aProjectileTime = Distance2D(aCenterStarX, aCenterStarY, aPlantRect.mX + aPlantRect.mWidth / 2, aPlantRect.mY + aPlantRect.mHeight / 2) / 3.33f;
                int aPlantHitX = aPlant->PlantTargetLeadX(aProjectileTime) - aPlantRect.mWidth / 2;
                if ((aPlantHitX + aPlantRect.mWidth > aCenterStarX) && (aPlantHitX < aCenterStarX))
                    return true;

                int aCenterZombieX = aPlantHitX + aPlantRect.mWidth / 2;
                int aCenterZombieY = aPlantRect.mY + aPlantRect.mHeight / 2;
                float angle = RAD_TO_DEG(atan2(aCenterZombieY - aCenterStarY, aCenterZombieX - aCenterStarX));
                if (abs(aPlant->mRow - mRow) < 2)
                {
                    if ((angle > 15.0f && angle < 45.0f) || (angle < -20.0f && angle > -50.0f))
                        return true;
                }
                else
                {
                    if ((angle > 20.0f && angle < 40.0f) || (angle < -23.0f && angle > -43.0f))
                        return true;
                }
            }
        }
    }
    GridItem* aGriditem = nullptr;
    while (mBoard->IterateGridItems(aGriditem))
    {
        if (aGriditem->mGridItemType == GRIDITEM_WOOD_LOG)
            return true;
    }

    return false;
}

bool Plant::FindStarFruitTargetReverse()
{
    if (mRecentlyEatenCountdown > 0)
        return true;

    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
    int aCenterStarX = mX + 40;
    int aCenterStarY = mY + 40;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        Rect aZombieRect = aZombie->GetZombieRect();
        if (aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            if (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS && mPlantCol >= 5)
                return true;

            if (aZombie->mRow == mRow)
            {
                if (aZombieRect.mX + aZombieRect.mWidth < aCenterStarX)
                    return true;
            }
            else
            {
                if (aZombie->mZombieType == ZombieType::ZOMBIE_DIGGER)
                    aZombieRect.mX += 10;

                float aProjectileTime = Distance2D(aCenterStarX, aCenterStarY, aZombieRect.mX + aZombieRect.mWidth / 2, aZombieRect.mY + aZombieRect.mHeight / 2) / 3.33f;
                int aZombieHitX = aZombie->ZombieTargetLeadX(aProjectileTime) - aZombieRect.mWidth / 2;
                if ((aZombieHitX + aZombieRect.mWidth > aCenterStarX) && (aZombieHitX < aCenterStarX))
                    return true;

                int aCenterZombieX = aZombieHitX + aZombieRect.mWidth / 2;
                int aCenterZombieY = aZombieRect.mY + aZombieRect.mHeight / 2;
                float angle = RAD_TO_DEG(atan2(aCenterZombieY - aCenterStarY, aCenterZombieX - aCenterStarX));
                if (abs(aZombie->mRow - mRow) < 2)
                {
                    if ((angle > 135.0f && angle < 150.0f) || (angle < -140.0f && angle > -155.0f))
                        return true;
                }
                else
                {
                    if ((angle > 140.0f && angle < 150.0f) || (angle < (- 28.0f + 115.0f) && angle > (-38.0f + 115.0f)))
                        return true;
                }
            }
        }
    }

    return false;
}

bool Plant::FindSeaFruitTarget()
{
    if (mRecentlyEatenCountdown > 0)
        return true;

    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
    int aCenterStarX = mX + 40;
    int aCenterStarY = mY + 40;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        Rect aZombieRect = aZombie->GetZombieRect();
        if (aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            if (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS && mPlantCol >= 5)
                return true;

            if (aZombie->mRow == mRow)
            {
                if (aZombieRect.mX + aZombieRect.mWidth > aCenterStarX)
                    return true;
            }
            else
            {
                if (aZombie->mZombieType == ZombieType::ZOMBIE_DIGGER)
                    aZombieRect.mX += 10;

                float aProjectileTime = Distance2D(aCenterStarX, aCenterStarY, aZombieRect.mX + aZombieRect.mWidth / 2, aZombieRect.mY + aZombieRect.mHeight / 2) / 3.33f;
                int aZombieHitX = aZombie->ZombieTargetLeadX(aProjectileTime) - aZombieRect.mWidth / 2;
                /*if ((aZombieHitX + aZombieRect.mWidth > aCenterStarX) && (aZombieHitX < aCenterStarX))
                    return true; */

                int aCenterZombieX = aZombieHitX + aZombieRect.mWidth / 2;
                int aCenterZombieY = aZombieRect.mY + aZombieRect.mHeight / 2;
                float angle = RAD_TO_DEG(atan2(aCenterZombieY - aCenterStarY, aCenterZombieX - aCenterStarX));
                if (abs(aZombie->mRow - mRow) < 2)
                {
                    if ((angle > 40.0f && angle < 60.0f) || (angle < -45.0f && angle > -65.0f))
                        return true;
                    else if ((angle > 115.0f && angle < 135.0f) || (angle < -125.0f && angle > -145.0f))
                        return true;
                }
                else
                {
                    if ((angle > 50.0f && angle < 60.0f) || (angle < -53.0f && angle > -63.0f))
                        return true;
                    else if ((angle > 130.0f && angle < 140.0f) || (angle < -128.0f && angle > -138.0f))
                        return true;
                }
                
            }
        }
    }

    return false;
}

//0x45F6E0
void Plant::LaunchStarFruit()
{
    if (FindStarFruitTarget())
    {
        PlayBodyReanim("anim_shoot", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
        mShootingCounter = 40;
    }
}

void Plant::LaunchStarFruitReverse()
{
    if (FindStarFruitTargetReverse())
    {
        PlayBodyReanim("anim_shoot", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
        mShootingCounter = 40;
    }
}

void Plant::LaunchCactusKing()
{
    Zombie* aZombie = nullptr;
    if (mBoard->IterateZombies(aZombie))
    {
        mShootingCounter = 40;
    }
}

void Plant::LaunchSeaFruit()
{
    if (FindStarFruitTarget())
    {
        PlayBodyReanim("anim_shoot", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
        mShootingCounter = 40;
        mSeaStarCycle = false;
    }
    else if (FindSeaFruitTarget())
    {
        PlayBodyReanim("anim_rotate", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
        PlayBodyReanim("anim_shoot2", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
        mShootingCounter = 40;
        mSeaStarCycle = true;
    }
}

void Plant::LaunchReed()
{
    if (FindReedTarget())
    {
        PlayBodyReanim("anim_attack", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
        mShootingCounter = 30;
    }
}

void Plant::ReedFire()
{
    int aRand = Rand(2);
    if (aRand == 0)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC);
    else if (aRand == 1)  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC2);
    else  mApp->PlayFoley(FoleyType::FOLEY_ELECTRIC3);
    ElectricuteZombie();
}

void Plant::ElectricuteZombie()
{
    bool isZombie1 = true;
    bool isZombie2 = true;
    bool isZombie3 = true;

    Zombie* aZombie = nullptr;
    Zombie* smallest = nullptr;
    Zombie* smallest2 = nullptr;
    Zombie* smallest3 = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {     
        if ((mRow == aZombie->mRow || mRow == aZombie->mRow + 1 || mRow == aZombie->mRow - 1) && !aZombie->mMindControlled && 
            !aZombie->IsFlying() && aZombie->mZombiePhase != ZombiePhase::PHASE_DIGGER_TUNNELING && (aZombie->mZombieType != ZOMBIE_BOSS || (aZombie->mZombiePhase == ZombiePhase::PHASE_BOSS_HEAD_IDLE_BEFORE_SPIT || aZombie->mZombiePhase == ZombiePhase::PHASE_BOSS_HEAD_IDLE_AFTER_SPIT)))
        {         
            if (smallest == NULL) smallest = aZombie;
            if (smallest2 == NULL && smallest != aZombie) smallest2 = aZombie;
            if (smallest3 == NULL && smallest != aZombie && smallest2 != aZombie) smallest3 = aZombie;
            if (aZombie->mPosX < smallest->mPosX) smallest = aZombie;
            if ((aZombie->mPosX > smallest->mPosX) && smallest2)
            {
                if (aZombie->mPosX < smallest2->mPosX) smallest2 = aZombie;            
            }
            if (smallest2)
            {
                if ((aZombie->mPosX > smallest2->mPosX) && smallest3)
                {
                    if (aZombie->mPosX < smallest3->mPosX) smallest3 = aZombie;
                }
            }
        }
    }

    Plant* aPlant = nullptr;
    Plant* smallestGrave = nullptr;
    Plant* smallestGrave2 = nullptr;
    Plant* smallestGrave3 = nullptr;
    while (mBoard->IteratePlants(aPlant))
    {
        if ((mRow == aPlant->mRow || mRow == aPlant->mRow + 1 || mRow == aPlant->mRow - 1) && aPlant->mSeedType == SEED_GRAVE)
        {
            if (smallestGrave == NULL) smallestGrave = aPlant;
            if (smallestGrave2 == NULL && smallestGrave != aPlant) smallestGrave2 = aPlant;
            if (smallestGrave3 == NULL && smallestGrave != aPlant && smallestGrave2 != aPlant) smallestGrave3 = aPlant;
            if (aPlant->mPlantCol < smallestGrave->mPlantCol) smallestGrave = aPlant;
            if ((aPlant->mPlantCol > smallestGrave->mPlantCol) && smallestGrave2)
            {
                if (aPlant->mPlantCol < smallestGrave2->mPlantCol) smallestGrave2 = aPlant;
            }
            if (smallestGrave2)
            {
                if ((aPlant->mPlantCol > smallestGrave2->mPlantCol) && smallestGrave3)
                {
                    if (aPlant->mPlantCol < smallestGrave3->mPlantCol) smallestGrave3 = aPlant;
                }
            }
        }
    }

    if (smallestGrave)
    {
        if (smallestGrave->mX < smallest->mX)
        {
            smallestGrave->mPlantHealth -= 10;
            smallestGrave->mEatenFlashCountdown = 25;
        }
        else
        {
            smallest->DoElectroDamage(smallest);
        }
    }
    else
    {
        smallest->DoElectroDamage(smallest);
    }

    if (smallestGrave2)
    {     
        if (smallestGrave2->mX < smallest->mX)
        {
            smallestGrave2->mPlantHealth -= 10;
            smallestGrave->mEatenFlashCountdown = 25;
        }
        else
        {
            if (smallest2 && smallest2->mZombieType != ZOMBIE_TARGET) smallest2->DoElectroDamage(smallest2);
        }
    }
    else
    {
        if (smallest2 && smallest2->mZombieType != ZOMBIE_TARGET) smallest2->DoElectroDamage(smallest2);
    }

    if (smallestGrave3)
    {
        if (smallestGrave3->mX < smallest->mX)
        {
            smallestGrave3->mPlantHealth -= 10;
            smallestGrave->mEatenFlashCountdown = 25;
        }
        else
        {
            if (smallest3 && smallest3->mZombieType != ZOMBIE_TARGET) smallest3->DoElectroDamage(smallest3);
        }
    }
    else
    {
        if (smallest3 && smallest3->mZombieType != ZOMBIE_TARGET) smallest3->DoElectroDamage(smallest3);
    }

   
    if (smallest)
    {
        float x1 = mX + 80;
        float y1 = mY + 30;
        float x2 = smallest->mPosX + 80;
        float y2 = smallest->mPosY + 60;

        int i = 0;
        float steigung = 0;
        if (smallest) steigung = (y2 - y1) / (x2 - x1);
        float mB = y1 - (steigung * x1);
        float yCord;
        float xCord;
        float ySteps;
        float xSteps;
        int iterations = 20;
        while (i < iterations)
        {
            xSteps = 600 / iterations;
            ySteps = 800 / iterations;
            yCord = i * xSteps * steigung + mB;
            xCord = ySteps * i;
            
            ParticleEffect aParticle = ParticleEffect::PARTICLE_ELECTRIC;
            if (xCord < x2 && xCord > x1) mApp->AddTodParticle(xCord, yCord, mRenderOrder + 4, aParticle);
            i++;
        } 
    }
    else if (smallestGrave)
    {
        float x1 = mX + 80;
        float y1 = mY + 30;
        float x2 = smallestGrave->mX + 80;
        float y2 = smallestGrave->mY + 60;

        int i = 0;
        float steigung = 0;
        if (smallestGrave) steigung = (y2 - y1) / (x2 - x1);
        float mB = y1 - (steigung * x1);
        float yCord;
        float xCord;
        float ySteps;
        float xSteps;
        int iterations = 20;
        while (i < iterations)
        {
            xSteps = 600 / iterations;
            ySteps = 800 / iterations;
            yCord = i * xSteps * steigung + mB;
            xCord = ySteps * i;

            ParticleEffect aParticle = ParticleEffect::PARTICLE_ELECTRIC;
            if (xCord < x2 && xCord > x1) mApp->AddTodParticle(xCord, yCord, mRenderOrder + 4, aParticle);
            i++;
        }
    }
    
}

void Zombie::DoElectroDamage(Zombie* smallest)
{
    if (smallest)
    {
        if (smallest->mZombieType == ZombieType::ZOMBIE_NEWSPAPER || smallest->mZombieType == ZombieType::ZOMBIE_SCREENDOOR || smallest->mZombieType == ZombieType::ZOMBIE_TRASHCAN || smallest->mZombieType == ZombieType::ZOMBIE_LADDER) smallest->TakeBodyDamage(10, 18U);
        else if (smallest->mZombieType == ZombieType::ZOMBIE_RAVEN)
        {
            Reanimation* aBodyReanim = mApp->ReanimationTryToGet(smallest->mBodyReanimID);
            smallest->PlayZombieReanim("anim_shock", ReanimLoopType::REANIM_LOOP, 10, 15.0f);
            smallest->mVelX = 0;
            if (smallest->mCounterToDeath == 0) smallest->mCounterToDeath = 100;
        }
        else smallest->TakeDamage(10, 0U);
        //if (!smallest->mHasHead) smallest->ApplyBurn();
    }
}

//0x45F720
void Plant::StarFruitFire()
{
    mApp->PlayFoley(FoleyType::FOLEY_THROW);

    float aShootAngleX = cos(DEG_TO_RAD(30.0f)) * 3.33f;
    float aShootAngleY = sin(DEG_TO_RAD(30.0f)) * 3.33f;
    for (int i = 0; i < 5; i++)
    {
        ProjectileType starVariant;
        if (mSeedType == SEED_STARFRUIT) starVariant = PROJECTILE_STAR;
        else starVariant = PROJECTILE_SEASTAR;
        Projectile* aProjectile = mBoard->AddProjectile(mX + 25, mY + 25, mRenderOrder - 1, mRow, starVariant);
        aProjectile->mDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
        aProjectile->mMotionType = ProjectileMotion::MOTION_STAR;

        switch (i)
        {
        case 0:     aProjectile->mVelX = -3.33f;         aProjectile->mVelY = 0.0f;             break;
        case 1:     aProjectile->mVelX = 0.0f;          aProjectile->mVelY = 3.33f;             break;
        case 2:     aProjectile->mVelX = 0.0f;          aProjectile->mVelY = -3.33f;            break;
        case 3:     aProjectile->mVelX = aShootAngleX;  aProjectile->mVelY = aShootAngleY;      break;
        case 4:     aProjectile->mVelX = aShootAngleX;  aProjectile->mVelY = -aShootAngleY;     break;
        default:    TOD_ASSERT();                                                               break;
        }
    }
}

void Plant::StarFruitFireReverse()
{
    mApp->PlayFoley(FoleyType::FOLEY_THROW);

    float aShootAngleX = cos(DEG_TO_RAD(30.0f)) * 3.33f;
    float aShootAngleY = sin(DEG_TO_RAD(30.0f)) * 3.33f;
    for (int i = 0; i < 5; i++)
    {
        ProjectileType starVariant;
        starVariant = PROJECTILE_STAR;
        Projectile* aProjectile = mBoard->AddProjectile(mX + 25, mY + 25, mRenderOrder - 1, mRow, starVariant);
        aProjectile->mDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
        aProjectile->mMotionType = ProjectileMotion::MOTION_STAR;

        switch (i)
        {
        case 0:     aProjectile->mVelX = -3.33f;         aProjectile->mVelY = 0.0f;             break;
        case 1:     aProjectile->mVelX = 0.0f;          aProjectile->mVelY = 3.33f;             break;
        case 2:     aProjectile->mVelX = 0.0f;          aProjectile->mVelY = -3.33f;            break;
        case 3:     aProjectile->mVelX = -aShootAngleX;  aProjectile->mVelY = aShootAngleY;      break;
        case 4:     aProjectile->mVelX = -aShootAngleX;  aProjectile->mVelY = -aShootAngleY;     break;
        default:    TOD_ASSERT();                                                               break;
        }
    }
}

void Plant::KingCactusFire()
{
    mApp->PlayFoley(FoleyType::FOLEY_THROW);
    
    float aShootAngleX = cos(DEG_TO_RAD(30.0f)) * 3.33f;
    float aShootAngleY = sin(DEG_TO_RAD(30.0f)) * 3.33f;
    for (int i = 0; i < 8; i++)
    {
        ProjectileType starVariant;
        starVariant = PROJECTILE_SPIKE;
        Projectile* aProjectile = mBoard->AddProjectile(mX + 25, mY + 25, mRenderOrder - 1, mRow, starVariant);
        aProjectile->mDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
        aProjectile->mMotionType = ProjectileMotion::MOTION_STAR;
        
        //aProjectile->mVelY = sin(i * 2*PI / 8) * 4;
        //aProjectile->mVelX = cos(i * 2*PI / 8) * 4;

        aProjectile->mProjOrder = i;
        aProjectile->mleft = mCycle;
    }   
    mCycle = !mCycle;
}

void Plant::SeaStarFruitFire()
{
    mApp->PlayFoley(FoleyType::FOLEY_THROW);

    float aShootAngleX;
    float aShootAngleY;
    for (int i = 0; i < 5; i++)
    {
        aShootAngleX = cos(DEG_TO_RAD(60.0f)) * 3.33f;
        aShootAngleY = sin(DEG_TO_RAD(60.0f)) * 3.33f;
        Projectile* aProjectile = mBoard->AddProjectile(mX + 25, mY + 25, mRenderOrder - 1, mRow, ProjectileType::PROJECTILE_SEASTAR);
        aProjectile->mDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
        aProjectile->mMotionType = ProjectileMotion::MOTION_STAR;

        switch (i)
        {
        case 0:     aProjectile->mVelX = -2.355f;       aProjectile->mVelY = -2.355f;           break;
        case 1:     aProjectile->mVelX = -2.355f;       aProjectile->mVelY = 2.355f;            break;
        case 2:     aProjectile->mVelX = 3.33f;         aProjectile->mVelY = 0;                 break;
        case 3:     aProjectile->mVelX = aShootAngleX;  aProjectile->mVelY = aShootAngleY;      break;
        case 4:     aProjectile->mVelX = aShootAngleX;  aProjectile->mVelY = -aShootAngleY;     break;
        default:    TOD_ASSERT();                                                               break;
        }
    }    
    //mSeaStarCycle = !mSeaStarCycle;
}

//0x45F8A0
void Plant::UpdateShooter()
{
    mLaunchCounter--;
    if (mLaunchCounter <= 0)
    {
        mLaunchCounter = mLaunchRate - Sexy::Rand(15);

        if (mSeedType == SeedType::SEED_THREEPEATER)
        {
            LaunchThreepeater();
        }
        else if (mSeedType == SeedType::SEED_REVERSE_THREEPEATER)
        {
            LaunchThreepeater();
        }
        else if (mSeedType == SeedType::SEED_STARFRUIT)
        {
            LaunchStarFruit();
        }
        else if (mSeedType == SeedType::SEED_REVERSE_STARFRUIT)
        {
            LaunchStarFruitReverse();
        }
        else if (mSeedType == SeedType::SEED_SHOOTINGSTAR)
        {
            bool doAttack = false;
            for (int gridY = 0; gridY < MAX_GRID_SIZE_Y; gridY++) {
                Zombie* aZombie = FindTargetZombie(gridY, WEAPON_SECONDARY);
                if (aZombie) {
                    doAttack = true;
                    break;
                }
            }
            if (doAttack)
            {
                PlayBodyReanim("anim_shoot", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
                mShootingCounter = 40;
            }
        }
        else if (mSeedType == SeedType::SEED_ECACTUS)
        {
            LaunchCactusKing();
        }
        else if (mSeedType == SeedType::SEED_PINKSTAR)
        {
            LaunchSeaFruit();
        }
        /*else if (mSeedType == SeedType::SEED_REED)
        {
            LaunchReed();
        }*/
        else if (mSeedType == SeedType::SEED_SPLITPEA)
        {
            FindTargetAndFire(mRow, PlantWeapon::WEAPON_SECONDARY);
        }
        else if (mSeedType == SeedType::SEED_CACTUS)
        {
            if (mState == PlantState::STATE_CACTUS_HIGH)
            {
                FindTargetAndFire(mRow, PlantWeapon::WEAPON_PRIMARY);
            }
            else if (mState == PlantState::STATE_CACTUS_LOW)
            {
                FindTargetAndFire(mRow, PlantWeapon::WEAPON_SECONDARY);
            }
        }
        else
        {
            FindTargetAndFire(mRow, PlantWeapon::WEAPON_PRIMARY);
        }
    }

    if (mLaunchCounter == 50 && (mSeedType == SeedType::SEED_CATTAIL))
    {
        FindTargetAndFire(mRow, PlantWeapon::WEAPON_PRIMARY);
    }
    if (mLaunchCounter == 25)
    {
        if (mSeedType == SeedType::SEED_REPEATER || mSeedType == SeedType::SEED_LEFTPEATER)
        {
            FindTargetAndFire(mRow, PlantWeapon::WEAPON_PRIMARY);
        }
        else if (mSeedType == SeedType::SEED_SPLITPEA)
        {
            FindTargetAndFire(mRow, PlantWeapon::WEAPON_PRIMARY);
            FindTargetAndFire(mRow, PlantWeapon::WEAPON_SECONDARY);
        }
    }
}

//0x45F980
bool Plant::MakesSun()
{
    return mSeedType == SeedType::SEED_SUNFLOWER || mSeedType == SeedType::SEED_TWINSUNFLOWER || mSeedType == SeedType::SEED_SUNSHROOM || mSeedType == SeedType::SEED_GRAVE || mSeedType == SeedType::SEED_AMPLI_FLOWER;
}

//0x45F9A0
void Plant::UpdateProductionPlant()
{
    if (!IsInPlay() || mApp->IsIZombieLevel() || mApp->mGameMode == GameMode::GAMEMODE_UPSELL || mApp->mGameMode == GameMode::GAMEMODE_INTRO)
        return;

    if (mBoard->HasLevelAwardDropped())
        return;

    if (mSeedType == SeedType::SEED_MARIGOLD && mBoard->mCurrentWave == mBoard->mNumWaves)
    {
        if (mState != PlantState::STATE_MARIGOLD_ENDING)
        {
            mState = PlantState::STATE_MARIGOLD_ENDING;
            mStateCountdown = 6000;
        }
        else if (mStateCountdown <= 0)
            return;
    }

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND && mBoard->mChallenge->mChallengeState != ChallengeState::STATECHALLENGE_LAST_STAND_ONSLAUGHT)
        return;

    mLaunchCounter--;
    if (mLaunchCounter <= 100)
    {
        int aFlashCountdown = TodAnimateCurve(100, 0, mLaunchCounter, 0, 100, TodCurves::CURVE_LINEAR);
        mEatenFlashCountdown = max(mEatenFlashCountdown, aFlashCountdown);
    }

    if (mLaunchCounter <= 0)
    {
        mLaunchCounter = RandRangeInt(mLaunchRate - 150, mLaunchRate);
        mApp->PlayFoley(FoleyType::FOLEY_SPAWN_SUN);

        if (mSeedType == SeedType::SEED_SUNSHROOM)
        {
            if (mState == PlantState::STATE_SUNSHROOM_SMALL)
            {
                mBoard->AddCoin(mX, mY, CoinType::COIN_SMALLSUN, CoinMotion::COIN_MOTION_FROM_PLANT);
            }
            else
            {
                mBoard->AddCoin(mX, mY, CoinType::COIN_SUN, CoinMotion::COIN_MOTION_FROM_PLANT);
            }
        }
        else if (mSeedType == SeedType::SEED_SUNFLOWER)
        {
            mBoard->AddCoin(mX, mY, CoinType::COIN_SUN, CoinMotion::COIN_MOTION_FROM_PLANT);
        }
        else if (mSeedType == SeedType::SEED_AMPLI_FLOWER)
        {
            mApliflowerCounter = 700;
            PlayBodyReanim("anim_cheer", ReanimLoopType::REANIM_LOOP, 20, 0.0f);
            mState = PlantState::STATE_AMPLI_DANCING;
            TodParticleSystem* aPinataParticle = mApp->AddTodParticle(mX + 20.0f, mY + 40.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_ZOMBIE_PINATA);
        }
        else if (mSeedType == SeedType::SEED_GRAVE)
        {
            if (mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES)
                mBoard->AddCoin(mX, mY, CoinType::COIN_SUN, CoinMotion::COIN_MOTION_FROM_PLANT);
            else mBoard->AddCoin(mX, mY, CoinType::COIN_BRAIN, CoinMotion::COIN_MOTION_FROM_PLANT);
        }
        else if (mSeedType == SeedType::SEED_TWINSUNFLOWER)
        {
            mBoard->AddCoin(mX, mY, CoinType::COIN_SUN, CoinMotion::COIN_MOTION_FROM_PLANT);
            mBoard->AddCoin(mX, mY, CoinType::COIN_SUN, CoinMotion::COIN_MOTION_FROM_PLANT);
        }
        else if (mSeedType == SeedType::SEED_MARIGOLD)
        {
            mBoard->AddCoin(mX, mY, (Sexy::Rand(100) < 10) ? CoinType::COIN_GOLD : CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
        }

        if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BIG_TIME)
        {
            if (mSeedType == SeedType::SEED_SUNFLOWER)
            {
                mBoard->AddCoin(mX, mY, CoinType::COIN_SUN, CoinMotion::COIN_MOTION_FROM_PLANT);
            }
            else if (mSeedType == SeedType::SEED_MARIGOLD)
            {
                mBoard->AddCoin(mX, mY, CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
            }
        }
    }
}

//0x45FB70
void Plant::UpdateSunShroom()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_SUNSHROOM_SMALL)
    {
        if (mStateCountdown == 0)
        {
            PlayBodyReanim("anim_grow", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, 12.0f);
            mState = PlantState::STATE_SUNSHROOM_GROWING;
            mApp->PlayFoley(FoleyType::FOLEY_PLANTGROW);
        }

        UpdateProductionPlant();
    }
    else if (mState == PlantState::STATE_SUNSHROOM_GROWING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayBodyReanim("anim_bigidle", ReanimLoopType::REANIM_LOOP, 10, RandRangeFloat(12.0f, 15.0f));
            mState = PlantState::STATE_SUNSHROOM_BIG;
        }
    }
    else
    {
        UpdateProductionPlant();
    }
}

//0x45FC70
void Plant::UpdateGraveBuster()
{
    if (mState == PlantState::STATE_GRAVEBUSTER_LANDING)
    {
        if (mApp->ReanimationGet(mBodyReanimID)->mLoopCount > 0)
        {
            PlayBodyReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 10, 12.0f);
            //if (mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS) mStateCountdown = 500;
            //else 
            mStateCountdown = 400;
            mState = PlantState::STATE_GRAVEBUSTER_EATING;
            AddAttachedParticle(mX + 40, mY + 40, mRenderOrder + 4, ParticleEffect::PARTICLE_GRAVE_BUSTER);
        }
    }
    else if (mState == PlantState::STATE_GRAVEBUSTER_EATING && mStateCountdown == 0)
    {
        GridItem* aGraveStone = mBoard->GetGraveStoneAt(mPlantCol, mRow);
        if (aGraveStone)
        {
            aGraveStone->GridItemDie();
            mBoard->mGravesCleared++;
        }

        Plant* aPlant = nullptr;
        while (mBoard->IteratePlants(aPlant))
        {
            if (mPlantCol == aPlant->mPlantCol && mRow == aPlant->mRow && aPlant->mSeedType == SEED_GRAVE)
            {
                aPlant->Die();
            }
        }

        mApp->AddTodParticle(mX + 40, mY + 40, mRenderOrder + 4, ParticleEffect::PARTICLE_GRAVE_BUSTER_DIE);
        Die();
        if (!mApp->IsVersusLevel()) mBoard->DropLootPiece(mX + 40, mY, 12);
    }
}

//0x45FD90
void Plant::PlayBodyReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);

    if (theBlendTime > 0)
        aBodyReanim->StartBlend(theBlendTime);
    if (theAnimRate > 0.0f)
        aBodyReanim->mAnimRate = theAnimRate;

    aBodyReanim->mLoopType = theLoopType;
    aBodyReanim->mLoopCount = 0;
    aBodyReanim->SetFramesForLayer(theTrackName);
}

//0x45FE20
void Plant::UpdatePotato()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);

    if (mState == PlantState::STATE_NOTREADY)
    {
        if (mStateCountdown == 0)
        {
            mApp->AddTodParticle(mX + mWidth / 2, mY + mHeight / 2, mRenderOrder, ParticleEffect::PARTICLE_POTATO_MINE_RISE);
            PlayBodyReanim("anim_rise", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 18.0f);
            mState = PlantState::STATE_POTATO_RISING;
            mApp->PlayFoley(FoleyType::FOLEY_DIRT_RISE);
        }
    }
    else if (mState == PlantState::STATE_POTATO_RISING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            float aRate = RandRangeFloat(12.0f, 15.0f);
            PlayBodyReanim("anim_armed", ReanimLoopType::REANIM_LOOP, 0, aRate);

            Reanimation* aLightReanim = mApp->AddReanimation(0.0f, 0.0f, mRenderOrder + 2, GetPlantDefinition(mSeedType).mReanimationType);
            aLightReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
            aLightReanim->mAnimRate = aRate - 2.0f;
            aLightReanim->SetFramesForLayer("anim_glow");
            aLightReanim->mFrameCount = 10;
            aLightReanim->ShowOnlyTrack("anim_glow");
            aLightReanim->SetTruncateDisappearingFrames("anim_glow", false);
            mLightReanimID = mApp->ReanimationGetID(aLightReanim);
            aLightReanim->AttachToAnotherReanimation(aBodyReanim, "anim_light");

            mState = PlantState::STATE_POTATO_ARMED;
            mBlinkCountdown = 400 + Sexy::Rand(4000);
        }
    }
    else if (mState == PlantState::STATE_POTATO_ARMED)
    {
        if (FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY))
        {
            DoSpecial();
        }
        else
        {
            Reanimation* aLightReanim = mApp->ReanimationTryToGet(mLightReanimID);
            if (aLightReanim)
            {
                aLightReanim->mFrameCount = TodAnimateCurve(200, 50, DistanceToClosestZombie(), 10, 3, TodCurves::CURVE_LINEAR);
            }
        }
    }
}

//0x460060
void Plant::UpdateTanglekelp()
{
    if (mState != PlantState::STATE_TANGLEKELP_GRABBING)
    {
        Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
        if (aZombie && (aZombie->mZombieType == ZombieType::ZOMBIE_GARGANTUAR || aZombie->mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR || aZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR || 
            aZombie->mZombieType == ZombieType::ZOMBIE_GIGA_FOOTBALL || aZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR_GIGA))
        {
            mApp->PlayFoley(FoleyType::FOLEY_FLOOP);
            aZombie->TakeDamage(1800, 0U);
            Die();
        }
        else if (aZombie)
        {
            mApp->PlayFoley(FoleyType::FOLEY_FLOOP);
            mState = PlantState::STATE_TANGLEKELP_GRABBING;
            mStateCountdown = 100;
            aZombie->PoolSplash(false);

            float aVinesPosX = -13.0f;
            float aVinesPosY = 15.0f;
            if (aZombie->mZombieType == ZombieType::ZOMBIE_SNORKEL)
            {
                aVinesPosX = -43.0f;
                aVinesPosY = 55.0f;
            }
            if (aZombie->mZombiePhase == ZombiePhase::PHASE_DOLPHIN_RIDING)
            {
                aVinesPosX = -20.0f;
                aVinesPosY = 37.0f;
            }
            Reanimation* aGrabReanim = aZombie->AddAttachedReanim(aVinesPosX, aVinesPosY, ReanimationType::REANIM_TANGLEKELP);
            if (aGrabReanim)
            {
                aGrabReanim->SetFramesForLayer("anim_grab");
                aGrabReanim->mAnimRate = 24.0f;
                aGrabReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
            }

            mTargetZombieID = mBoard->ZombieGetID(aZombie);
        }
    } 
    else
    {
        if (mStateCountdown == 50)
        {
            Zombie* aZombie = mBoard->ZombieTryToGet(mTargetZombieID);
            if (aZombie)
            {
                aZombie->DragUnder();
                aZombie->PoolSplash(false);
            }
        }

        if (mStateCountdown == 20)
        {
            int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 0);
            Reanimation* aSplashReanim = mApp->AddReanimation(mX - 23, mY + 7, aRenderPosition, ReanimationType::REANIM_SPLASH);
            aSplashReanim->OverrideScale(1.3f, 1.3f);

            mApp->AddTodParticle(mX + 31, mY + 64, aRenderPosition, ParticleEffect::PARTICLE_PLANTING_POOL);
            mApp->PlayFoley(FoleyType::FOLEY_ZOMBIE_ENTERING_WATER);
        }

        if (mStateCountdown == 0)
        {
            Die();

            Zombie* aZombie = mBoard->ZombieTryToGet(mTargetZombieID);
            if (aZombie)
            {
                aZombie->DieWithLoot();
            } 
        } 
    } 
}

//0x460320
void Plant::SpikeweedAttack()
{
    TOD_ASSERT(IsSpiky());

    if (mState != PlantState::STATE_SPIKEWEED_ATTACKING)
    {
        PlayBodyReanim("anim_attack", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 18.0f);
        mApp->PlaySample(SOUND_THROW);
        
        mState = PlantState::STATE_SPIKEWEED_ATTACKING;
        mStateCountdown = 100;
    }
}

//0x460370
void Plant::UpdateSpikeweed()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_SPIKEWEED_ATTACKING)
    {
        if (mStateCountdown == 0)
        {
            mState = PlantState::STATE_NOTREADY;
        }
        else if (mSeedType == SeedType::SEED_SPIKEROCK)
        {
            if (mStateCountdown == 69 || mStateCountdown == 33)
            {
                DoRowAreaDamage(20, 33U);
            }
        }
        else if (mStateCountdown == 75)
        {
            DoRowAreaDamage(20, 33U);
        }

        if (aBodyReanim->mLoopCount > 0)
        {
            PlayIdleAnim(RandRangeFloat(12.0f, 15.0f));
        }
    }
    else if (FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY))
    {
        SpikeweedAttack();
    }
}

void Plant::UpdateThornmoss()
{
    Zombie* aZombie = nullptr;
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_SPIKEWEED_ATTACKING)
    {
        if (mStateCountdown == 0)
        {
            mState = PlantState::STATE_NOTREADY;
        }
        else if (mStateCountdown == 75)
        {
            DoRowAreaDamage(20, 33U);
        }
    }
    else if (FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY))
    {
        SpikeweedAttack();
    }
    while (mBoard->IterateZombies(aZombie))
    {
        if (aZombie->mRow == mRow && (aZombie->mZombieType != ZOMBIE_GLADIANTUAR && aZombie->mZombieType != ZOMBIE_GLADIANTUAR_GIGA && aZombie->mZombieType != ZOMBIE_GIGA_FOOTBALL && aZombie->mZombieType != ZOMBIE_BOSS && aZombie->mZombiePhase != PHASE_IMP_GETTING_THROWN && aZombie->mZombieType != ZOMBIE_ZOMBONI && aZombie->mZombieType != ZOMBIE_CATAPULT &&
            aZombie->mZombiePhase != PHASE_DIGGER_TUNNELING && aZombie->mZombiePhase != PHASE_BALLOON_FLYING && aZombie->mZombiePhase != PHASE_POGO_BOUNCING && aZombie->mZombiePhase != PHASE_POLEVAULTER_PRE_VAULT) && aZombie->mHasHead)
        {
            if (aZombie->mX > mX - 20.0f && aZombie->mX < mX - 10.0f && !aZombie->mHasBeenStunned)
            {
                aZombie->StunZombie();
                aZombie->mHasBeenStunned = true;
            }
            else if (aZombie->mX > mX - 200.0f && aZombie->mX < mX - 15.0f && !aZombie->mHasBeenStunned)
                aZombie->mPosX += 2;
            else if (aZombie->mX > mX - 15.0f && aZombie->mX < mX + 200.0f && !aZombie->mHasBeenStunned)
                aZombie->mPosX -= 2;
        }
    }
    if (aBodyReanim->mLoopCount > 0)
    {
        PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
        mState = PlantState::STATE_READY;
    }
}

//0x460420
void Plant::UpdateScaredyShroom()
{
    if (mShootingCounter > 0)
        return;

    bool aHasZombieNearby = false;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        Rect aZombieRect = aZombie->GetZombieRect();
        int aDiffY = (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS) ? 0 : (aZombie->mRow - mRow);
        if (!aZombie->mMindControlled && !aZombie->IsDeadOrDying() && aDiffY <= 1 && aDiffY >= -1 && GetCircleRectOverlap(mX, mY + 20.0f, 120, aZombieRect))
        {
            aHasZombieNearby = true;
            break;
        }
    }

    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_READY)
    {
        if (aHasZombieNearby)
        {
            mState = PlantState::STATE_SCAREDYSHROOM_LOWERING;
            PlayBodyReanim("anim_scared", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, 10.0f);
        }
    }
    else if (mState == PlantState::STATE_SCAREDYSHROOM_LOWERING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_SCAREDYSHROOM_SCARED;
            PlayBodyReanim("anim_scaredidle", ReanimLoopType::REANIM_LOOP, 10, 0.0f);
        }
    }
    else if (mState == PlantState::STATE_SCAREDYSHROOM_SCARED)
    {
        if (!aHasZombieNearby)
        {
            mState = PlantState::STATE_SCAREDYSHROOM_RAISING;

            float aAnimRate = RandRangeFloat(7.0f, 12.0f);
            PlayBodyReanim("anim_grow", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, aAnimRate);
        }
    }
    else if (mState == PlantState::STATE_SCAREDYSHROOM_RAISING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_READY;

            float aAnimRate = RandRangeFloat(10.0f, 15.0f);
            PlayIdleAnim(aAnimRate);
        }
    }

    if (mState != PlantState::STATE_READY)
    {
        mLaunchCounter = mLaunchRate;
    }
}

void Plant::UpdateBraveShroom()
{
    if (mShootingCounter > 0)
        return;

    bool aHasZombieNearby = false;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        Rect aZombieRect = aZombie->GetZombieRect();
        int aDiffY = (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS) ? 0 : (aZombie->mRow - mRow);
        if (!aZombie->mMindControlled && !aZombie->IsDeadOrDying() && aDiffY <= 1 && aDiffY >= -1 && GetCircleRectOverlap(mX, mY + 20.0f, 300, aZombieRect))
        {
            aHasZombieNearby = true;
            break;
        }
    }

    aZombie = nullptr;
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_READY)
    {
        if (!mBoard->IterateZombies(aZombie))
        {
            mState = PlantState::STATE_SCAREDYSHROOM_LOWERING;
            PlayBodyReanim("anim_scared", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, 10.0f);
        }
    }
    else if (mState == PlantState::STATE_SCAREDYSHROOM_LOWERING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_SCAREDYSHROOM_SCARED;
            PlayBodyReanim("anim_scaredidle", ReanimLoopType::REANIM_LOOP, 10, 0.0f);
        }
    }
    else if (mState == PlantState::STATE_SCAREDYSHROOM_SCARED)
    {
        if (mBoard->IterateZombies(aZombie))
        {
            mState = PlantState::STATE_SCAREDYSHROOM_RAISING;

            float aAnimRate = RandRangeFloat(7.0f, 12.0f);
            PlayBodyReanim("anim_grow", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, aAnimRate);
        }
    }
    else if (mState == PlantState::STATE_SCAREDYSHROOM_RAISING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_READY;

            float aAnimRate = RandRangeFloat(10.0f, 15.0f);
            PlayIdleAnim(aAnimRate);
        }
    }

    if (aHasZombieNearby)
    {
        mBoostCounter++;
    }
    else
    {
        mBoostCounter = 0;
    }

    if (mState != PlantState::STATE_READY)
    {
        mLaunchCounter = mLaunchRate;
    }
}

void Plant::UpdateOakArcher()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_READY)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
        }
        if (mShootingCounter == 28)
        {
            mState = PlantState::STATE_EMPTY_IDLE;   
        }      
    }
    else if (mState == PlantState::STATE_EMPTY_IDLE)
    {
        if (aBodyReanim->ShouldTriggerTimedEvent(.56f))
        {
            mState = PlantState::STATE_RELOAD;
            PlayBodyReanim("anim_idle_empty", ReanimLoopType::REANIM_LOOP, 10, 0.0f); 
        }
    }
    else if (mState == PlantState::STATE_RELOAD)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayBodyReanim("anim_reload", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, aBodyReanim->mDefinition->mFPS);
            mState = PlantState::STATE_READY;
        }
    }   
}

//0x460610
void Plant::UpdateTorchwood()
{

    Rect aAttackRect = GetPlantAttackRect(PlantWeapon::WEAPON_PRIMARY);

    Projectile* aProjectile = nullptr;

    while (mBoard->IterateProjectiles(aProjectile))
    {
        if ((aProjectile->mRow == mRow) && 
            (aProjectile->mProjectileType == ProjectileType::PROJECTILE_PEA || aProjectile->mProjectileType == ProjectileType::PROJECTILE_SNOWPEA || 
            aProjectile->mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN) ||
            aProjectile->mProjectileType == ProjectileType::PROJECTILE_FIREBALL || aProjectile->mProjectileType == ProjectileType::PROJECTILE_PLASMABALL)
        {
            Rect aProjectileRect = aProjectile->GetProjectileRect();
            if (GetRectOverlap(aAttackRect, aProjectileRect) >= 10 && aProjectile->mRow == mRow)
            {
                if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_PEA && mSeedType == SeedType::SEED_TORCHWOOD)
                {
                    aProjectile->ConvertToFireball(mPlantCol);
                }
                else if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_SNOWPEA && mSeedType == SeedType::SEED_TORCHWOOD)
                {
                    aProjectile->ConvertToPea(mPlantCol);
                }
                else if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_FIREBALL && mSeedType == SeedType::SEED_FLAMEWOOD)
                {
                    aProjectile->ConvertToPlasmaball(mPlantCol);
                }
                if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_PEA && mSeedType == SeedType::SEED_FLAMEWOOD)
                {
                    aProjectile->ConvertToPlasmaball(mPlantCol);
                }
                else if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_SNOWPEA && mSeedType == SeedType::SEED_FLAMEWOOD)
                {
                    aProjectile->ConvertToFireball(mPlantCol);
                }
                else if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN && mSeedType == SeedType::SEED_TORCHWOOD)
                {
                    aProjectile->ConvertToSnowPea(mPlantCol);
                }
                else if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_ICEQUEEN && mSeedType == SeedType::SEED_FLAMEWOOD)
                {
                    aProjectile->ConvertToPea(mPlantCol);
                }
            }
        }
    }
}

//0x4606F0
void Plant::DoSquashDamage()
{
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
    Rect aAttackRect = GetPlantAttackRect(PlantWeapon::WEAPON_PRIMARY);

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if ((aZombie->mRow == mRow || aZombie->mZombieType == ZombieType::ZOMBIE_BOSS) && aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            Rect aZombieRect = aZombie->GetZombieRect();
            if (GetRectOverlap(aAttackRect, aZombieRect) > (aZombie->mZombieType == ZombieType::ZOMBIE_FOOTBALL ? -20 : 0))
            {
                aZombie->TakeDamage(1800, 18U);
            }
        }
    }
}

//0x4607E0
Zombie* Plant::FindSquashTarget()
{
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
    Rect aAttackRect = GetPlantAttackRect(PlantWeapon::WEAPON_PRIMARY);

    int aClosestRange = 0;
    Zombie* aClosestZombie = nullptr;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if ((aZombie->mRow == mRow || aZombie->mZombieType == ZombieType::ZOMBIE_BOSS) &&
            aZombie->mHasHead && !aZombie->IsTangleKelpTarget() && aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            Rect aZombieRect = aZombie->GetZombieRect();

            if ((
                    aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT && aZombieRect.mX < mX + 20
                ) || (
                    aZombie->mZombiePhase != ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT && 
                    aZombie->mZombiePhase != ZombiePhase::PHASE_POLEVAULTER_IN_VAULT &&
                    aZombie->mZombiePhase != ZombiePhase::PHASE_SNORKEL_INTO_POOL && 
                    aZombie->mZombiePhase != ZombiePhase::PHASE_DOLPHIN_INTO_POOL &&
                    aZombie->mZombiePhase != ZombiePhase::PHASE_DOLPHIN_RIDING && 
                    aZombie->mZombiePhase != ZombiePhase::PHASE_DOLPHIN_IN_JUMP &&
                    !aZombie->IsBobsledTeamWithSled()
                ))
            {
                int aRange = -GetRectOverlap(aAttackRect, aZombieRect);
                if (aRange <= (aZombie->mIsEating ? 110 : 70))
                {
                    int aPlantX = aAttackRect.mX;
                    /*if (aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_POST_VAULT || aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT ||
                        aZombie->mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_IN_POOL || aZombie->mZombieType == ZombieType::ZOMBIE_IMP ||
                        aZombie->mZombieType == ZombieType::ZOMBIE_FOOTBALL || mApp->IsScaryPotterLevel() || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS)*/
                    {
                        aPlantX = aAttackRect.mX - 60;
                    }

                    if (aZombie->IsWalkingBackwards() || aZombieRect.mX + aZombieRect.mWidth >= aPlantX)
                    {
                        if (mBoard->ZombieGetID(aZombie) == mTargetZombieID)
                            return aZombie;  // 是锁定的目标僵尸，则直接返回该僵尸

                        if (aClosestZombie == nullptr || aRange < aClosestRange)
                        {
                            aClosestZombie = aZombie;
                            aClosestRange = aRange;
                        }
                    }
                }
            }
        }
    }

    return aClosestZombie;
}

//0x4609D0
void Plant::UpdateSquash()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    TOD_ASSERT(aBodyReanim);

    if (mState == PlantState::STATE_NOTREADY)
    {
        Zombie* aZombie = FindSquashTarget();
        if (aZombie)
        {
            mTargetZombieID = mBoard->ZombieGetID(aZombie);
            mTargetX = aZombie->ZombieTargetLeadX(0.0f) - mWidth / 2;
            mState = PlantState::STATE_SQUASH_LOOK;
            mStateCountdown = 80;
            if (mApp->mGameMode == GAMEMODE_CHALLENGE_FLIPPED)
            {
                PlayBodyReanim(mTargetX < mX ? "anim_lookright" : "anim_lookleft", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, 24.0f);
            }
            else
            {
                PlayBodyReanim(mTargetX < mX ? "anim_lookleft" : "anim_lookright", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, 24.0f);
            }
            mApp->PlayFoley(FoleyType::FOLEY_SQUASH_HMM);
        }
    }
    else if (mState == PlantState::STATE_SQUASH_LOOK)
    {
        if (mStateCountdown <= 0)
        {
            PlayBodyReanim("anim_jumpup", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
            mState = PlantState::STATE_SQUASH_PRE_LAUNCH;
            mStateCountdown = 30;
        }
    }
    else if (mState == PlantState::STATE_SQUASH_PRE_LAUNCH)
    {
        if (mStateCountdown <= 0)
        {
            Zombie* aZombie = FindSquashTarget();
            if (aZombie)
            {
                mTargetX = aZombie->ZombieTargetLeadX(30.0f) - mWidth / 2;
            }

            mState = PlantState::STATE_SQUASH_RISING;
            mStateCountdown = 50;
            mRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 0);
        }
    }
    else
    {
        int aTargetCol = mBoard->PixelToGridXKeepOnBoard(mTargetX, mY);
        int aDestY = mBoard->GridToPixelY(aTargetCol, mRow) + 8;

        if (mState == PlantState::STATE_SQUASH_RISING)
        {
            mX = TodAnimateCurve(50, 20, mStateCountdown, mBoard->GridToPixelX(mPlantCol, mStartRow), mTargetX, TodCurves::CURVE_EASE_IN_OUT);
            mY = TodAnimateCurve(50, 20, mStateCountdown, mBoard->GridToPixelY(mPlantCol, mStartRow), aDestY - 120, TodCurves::CURVE_EASE_IN_OUT);

            if (mStateCountdown == 0)
            {
                PlayBodyReanim("anim_jumpdown", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 60.0f);
                mState = PlantState::STATE_SQUASH_FALLING;
                mStateCountdown = 10;
            }
        }
        else if (mState == PlantState::STATE_SQUASH_FALLING)
        {
            mY = TodAnimateCurve(10, 0, mStateCountdown, aDestY - 120, aDestY, TodCurves::CURVE_EASE_IN_OUT);

            if (mStateCountdown == 5)
            {
                DoSquashDamage();
            }

            if (mStateCountdown == 0)
            {
                if (mBoard->IsPoolSquare(aTargetCol, mRow))
                {
                    mApp->AddReanimation(mX - 11, mY + 20, mRenderOrder + 1, ReanimationType::REANIM_SPLASH);
                    mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
                    mApp->PlaySample(SOUND_ZOMBIESPLASH);

                    Die();
                }
                else
                {
                    mState = PlantState::STATE_SQUASH_DONE_FALLING;
                    mStateCountdown = 100;

                    mBoard->ShakeBoard(1, 4);
                    mApp->PlayFoley(FoleyType::FOLEY_THUMP);
                    float aOffsetY = mBoard->StageHasRoof() ? 69.0f : 80.0f;
                    mApp->AddTodParticle(mX + 40, mY + aOffsetY, mRenderOrder + 4, ParticleEffect::PARTICLE_DUST_SQUASH);
                }
            }
        }
        else if (mState == PlantState::STATE_SQUASH_DONE_FALLING)
        {
            if (mStateCountdown == 0)
            {
                Die();
            }
        }
    }
}

//0x460DD0
void Plant::UpdateDoomShroom()
{
    if (mIsAsleep || mState == PlantState::STATE_DOINGSPECIAL)
        return;

    mState = PlantState::STATE_DOINGSPECIAL;
    mDoSpecialCountdown = 100;

    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    TOD_ASSERT(aBodyReanim);

    aBodyReanim->SetFramesForLayer("anim_explode");
    aBodyReanim->mAnimRate = 23.0f;
    aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
    aBodyReanim->SetShakeOverride("DoomShroom_head1", 1.0f);
    aBodyReanim->SetShakeOverride("DoomShroom_head2", 2.0f);
    aBodyReanim->SetShakeOverride("DoomShroom_head3", 2.0f);
    mApp->PlayFoley(FoleyType::FOLEY_REVERSE_EXPLOSION);
}

void Plant::UpdateIceShroom()
{
    if (!mIsAsleep && mState != PlantState::STATE_DOINGSPECIAL)
    {
        mState = PlantState::STATE_DOINGSPECIAL;
        mDoSpecialCountdown = 100;
    }
}

//0x460F00
void Plant::UpdateBlover()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (aBodyReanim->mLoopCount > 0 && aBodyReanim->mLoopType != ReanimLoopType::REANIM_LOOP)
    {
        aBodyReanim->SetFramesForLayer("anim_loop");
        aBodyReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
    }

    if (mState != PlantState::STATE_DOINGSPECIAL && mStateCountdown == 0)
    {
        DoSpecial();
    }
}

void Plant::UpdateFlowerPot()
{
    if (mState == PlantState::STATE_FLOWERPOT_INVULNERABLE && mStateCountdown == 0)
        mState = PlantState::STATE_NOTREADY;
}

void Plant::UpdateLilypad()
{
    if (mState == PlantState::STATE_LILYPAD_INVULNERABLE && mStateCountdown == 0)
        mState = PlantState::STATE_NOTREADY;
}

//0x460F60
void Plant::UpdateCoffeeBean()
{
    if (mState == PlantState::STATE_DOINGSPECIAL)
    {
        Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->mLoopCount > 0)
        {
            Die();
        }
    }
}

//0x460FA0
void Plant::UpdateUmbrella()
{
    if (mState == PlantState::STATE_UMBRELLA_TRIGGERED)
    {
        if (mStateCountdown == 0)
        {
            mRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PROJECTILE, mRow + 1, 0);
            mState = PlantState::STATE_UMBRELLA_REFLECTING;
        }
    }
    else if (mState == PlantState::STATE_UMBRELLA_REFLECTING)
    {
        Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayIdleAnim(0.0f);
            mState = PlantState::STATE_NOTREADY;
            mRenderOrder = CalcRenderOrder();
        }
    }
}

void Plant::UpdateLemon()
{
    //plant::updateabilities
    if (!mToss) {
        if (mDoSpecialCountdown <= 0) {
            int aPosX = mX + mWidth / 2;
            int aPosY = mY + mHeight / 2;
            int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
            mApp->PlayFoley(FoleyType::FOLEY_LEMON);

            mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, 115, 1, true, aDamageRangeFlags, 0, 900, false);

            TodParticleSystem* aParticle = mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_SPLOISH);
            aParticle->OverrideScale(nullptr, 0.5f);
            mBoard->ShakeBoard(3, -4);
            BounceLimit++;
            if (BounceLimit > 2) Die();

            while (XGrid == mPlantCol) {
                XGrid = XOrig + RandRangeInt(-1, 1);
            }
            while (YGrid == mRow) {
                YGrid = YOrig + RandRangeInt(-1, 1);
            }

            if (XGrid < 0 || XGrid >= MAX_GRID_SIZE_X) {
                XGrid = XOrig;
            }
            if (YGrid < 0 || YGrid >= MAX_GRID_SIZE_Y) {
                YGrid = YOrig;
            }

            mNextX = mBoard->GridToPixelX(XGrid, YGrid);
            mNextY = mBoard->GridToPixelY(XGrid, YGrid);
            mApp->PlayFoley(FoleyType::FOLEY_POGO_ZOMBIE);
            mToss = true;
            mDoSpecialCountdown = 90;
        }
    }
    else {
        if (mMoveTimer < 50) {
            mMoveTimer++;
            mShakeOffsetY = TodAnimateCurveFloat(50, 0, mMoveTimer, 0.f, 90.0f, TodCurves::CURVE_BOUNCE_SLOW_MIDDLE); //TodAnimateCurve(0, 50, mMoveTimer, 0, 80, TodCurves::CURVE_EASE_IN_OUT);
            mX = TodAnimateCurve(0, 50, mMoveTimer, mBoard->GridToPixelX(mPlantCol, mRow), mNextX, TodCurves::CURVE_LINEAR);
            mY = TodAnimateCurve(0, 50, mMoveTimer, mBoard->GridToPixelY(mPlantCol, mRow), mNextY, TodCurves::CURVE_LINEAR);
        }
        else {
            mPlantCol = XGrid;
            mRow = YGrid;

            mMoveTimer = 0;
            mRenderOrder = CalcRenderOrder();



            mToss = false;
        }
    }
}

//0x461020
void Plant::UpdateCobCannon()
{
    if (mState == PlantState::STATE_COBCANNON_ARMING)
    {
        if (mStateCountdown == 0)
        {
            mState = PlantState::STATE_COBCANNON_LOADING;
            PlayBodyReanim("anim_charge", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);
        }
    }
    else if (mState == PlantState::STATE_COBCANNON_LOADING)
    {
        Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->ShouldTriggerTimedEvent(0.5f))
        {
            mApp->PlayFoley(FoleyType::FOLEY_SHOOP);
        }
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_COBCANNON_READY;
            PlayIdleAnim(12.0f);
        }
    }
    else if (mState == PlantState::STATE_COBCANNON_READY)
    {
        Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        ReanimatorTrackInstance* aCobTrack = aBodyReanim->GetTrackInstanceByName("CobCannon_cob");
        aCobTrack->mTrackColor = GetFlashingColor(mBoard->mMainCounter, 75);
    }
    else if (mState == PlantState::STATE_COBCANNON_FIRING)
    {
        Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->ShouldTriggerTimedEvent(0.48f))
        {
            mApp->PlayFoley(FoleyType::FOLEY_COB_LAUNCH);
        }
    }
}

//0x4611F0
void Plant::UpdateCactus()
{
    if (mShootingCounter > 0)
        return;

    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_CACTUS_RISING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_CACTUS_HIGH;
            PlayBodyReanim("anim_idlehigh", ReanimLoopType::REANIM_LOOP, 20, 0.0f);
            if (mApp->IsIZombieLevel())
            {
                aBodyReanim->mAnimRate = 0;
            }

            mLaunchCounter = 1;
        }
    }
    else if (mState == PlantState::STATE_CACTUS_HIGH)
    {
        if (FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY) == nullptr)
        {
            mState = PlantState::STATE_CACTUS_LOWERING;
            PlayBodyReanim("anim_lower", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, aBodyReanim->mDefinition->mFPS);
        }
    }
    else if (mState == PlantState::STATE_CACTUS_LOWERING)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_CACTUS_LOW;
            PlayIdleAnim(0.0f);
        }
    }
    else if (FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY))
    {
        mState = PlantState::STATE_CACTUS_RISING;
        PlayBodyReanim("anim_rise", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, aBodyReanim->mDefinition->mFPS);
        mApp->PlayFoley(FoleyType::FOLEY_PLANTGROW);
    }
}

//0x461320
void Plant::UpdateChomper()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (mState == PlantState::STATE_READY)
    {
        Plant* aPlant = FindTargetPlant(mRow, PlantWeapon::WEAPON_PRIMARY);
        if (FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY) || (aPlant && aPlant->mPlantCol == mPlantCol + 1 && aPlant->mSeedType != SEED_DUMMY))
        {
            PlayBodyReanim("anim_bite", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
            mState = PlantState::STATE_CHOMPER_BITING;
            mStateCountdown = 70;
        }
    }
    else if (mState == PlantState::STATE_CHOMPER_BITING)
    {
        if (mStateCountdown == 0)
        {
            mApp->PlayFoley(FoleyType::FOLEY_BIGCHOMP);

            Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
            bool doBite = false;
            if (aZombie)
            {
                if (aZombie->mZombieType == ZombieType::ZOMBIE_GARGANTUAR || aZombie->mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR || aZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR ||
                    aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mZombieType == ZombieType::ZOMBIE_GIGA_FOOTBALL || aZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR_GIGA)
                {
                    doBite = true;
                }
            }
            bool doMiss = false;
            if (aZombie == nullptr)
            {
                doMiss = true;
            }
            else if (!aZombie->IsImmobilizied())
            {
                if (aZombie->IsBouncingPogo() ||
                    aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || (aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT && mSeedType == SeedType::SEED_CHOMPER))
                {
                    doMiss = true;
                }
            }

            if (doBite)
            {
                mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
                aZombie->TakeDamage(40, 0U);
                mState = PlantState::STATE_CHOMPER_BITING_MISSED;
            }
            else if (doMiss)
            {
                mState = PlantState::STATE_CHOMPER_BITING_MISSED;
            }
            else
            {
                aZombie->DieWithLoot();
                mState = PlantState::STATE_CHOMPER_BITING_GOT_ONE;
            }

            Plant* aPlant = FindTargetPlant(mRow, PlantWeapon::WEAPON_PRIMARY);
            if (aPlant && aPlant->mPlantCol == mPlantCol + 1 && aPlant->mSeedType != SEED_DUMMY)
            {
                aPlant->Die();
                mState = PlantState::STATE_CHOMPER_BITING_GOT_ONE;
            }
        }
    }
    else if (mState == PlantState::STATE_CHOMPER_BITING_GOT_ONE)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayBodyReanim("anim_chew", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
            if (mApp->IsIZombieLevel())
            {
                aBodyReanim->mAnimRate = 0;
            }

            mState = PlantState::STATE_CHOMPER_DIGESTING;
            mStateCountdown = 4000;
        }
    }
    else if (mState == PlantState::STATE_CHOMPER_DIGESTING)
    {
        if (mStateCountdown == 0)
        {
            PlayBodyReanim("anim_swallow", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);
            mState = PlantState::STATE_CHOMPER_SWALLOWING;
        }
    }
    else if ((mState == PlantState::STATE_CHOMPER_SWALLOWING || mState == PlantState::STATE_CHOMPER_BITING_MISSED) && aBodyReanim->mLoopCount > 0)
    {
        PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
        mState = PlantState::STATE_READY;
    }
}

void Plant::UpdateBonkChoy() 
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    int aDamage = 12;
    if (mState == PlantState::STATE_READY)
    {
        Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
        if (aZombie) {
            PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 42.0f);
            if (aZombie->CanLoseBodyParts() && aZombie->mHasHead &&
                (aZombie->mBodyHealth - aDamage) < aZombie->mBodyMaxHealth / 3)
            {
                mApp->PlayFoley(FOLEY_BONK2);
                PlayBodyReanim("anim_uppercut", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 42.0f);
            }
            if (aZombie->mX < mX - 20) {
                mIsBackwards = true;
            }
            mApp->PlayFoley(FOLEY_SWING);
            mState = PlantState::STATE_PUNCHING;
            //mStateCountdown = 112;
        }
    }
    else if (mState == PlantState::STATE_PUNCHING)
    {
        if (aBodyReanim->ShouldTriggerTimedEvent(.56f))
        {
            Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);

            if (aZombie) {
                mApp->PlayFoley(FoleyType::FOLEY_SPLAT/*FOLEY_PLASTIC_HIT*/);
                if (aZombie->mZombieType == ZombieType::ZOMBIE_NEWSPAPER || aZombie->mZombieType == ZombieType::ZOMBIE_SCREENDOOR || aZombie->mZombieType == ZombieType::ZOMBIE_TRASHCAN || aZombie->mZombieType == ZombieType::ZOMBIE_LADDER) aZombie->TakeBodyDamage(aDamage, 0U);
                else aZombie->TakeDamage(aDamage, 0U);
            }
        }
        if (aBodyReanim->mLoopCount > 0)
        {
            Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
            if (aZombie) {
                if (aZombie->mX < mX - 20) {
                    mIsBackwards = true;
                }
                else {
                    mIsBackwards = false;
                }
            }
            else {
                mIsBackwards = false;
            }
            PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
            mState = PlantState::STATE_READY;
        }
    }
}

void Plant::UpdateAmpliflower()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (mState == PlantState::STATE_AMPLI_DANCING)
    {
        if (aBodyReanim && mApliflowerCounter <= 0)
        {
            PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
            mState = PlantState::STATE_READY;
        }
    }
}

void Plant::UpdateChardGuard() {
{
        Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
        if (mState == PlantState::STATE_READY && mChardGuardLeafs > 0)
        {
            if (aZombie) {
                PlayBodyReanim("anim_arm", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 20.0f);
                mState = PlantState::STATE_PREPARED;
            }
        }
        else if (mState == PlantState::STATE_PREPARED && mChardGuardLeafs > 0)
        {
            if (aBodyReanim->mLoopCount > 0)
            {
                 PlayCustomIdleAnim(aBodyReanim->mDefinition->mFPS, "anim_arm_idle");
            }

            if (aZombie && aZombie->mHasHead && !aZombie->IsDeadOrDying())
            {
                if (aZombie->mX <= mX + 40.0f && aZombie->mX >= mX - 40 && aZombie->mHasHead)
                {
                    mApp->PlayFoley(FOLEY_SWING);
                    mState = PlantState::STATE_PUSHING;
                }
            }
            else
            {
                //PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
                PlayBodyReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, aBodyReanim->mDefinition->mFPS);
                mState = PlantState::STATE_READY;
            }  
        }
        else if (mState == PlantState::STATE_PUSHING && mChardGuardLeafs > 0)
        {
            bool loseLeaf = false;
            if (aZombie) {               
                Zombie* bZombie = nullptr;
                while (mBoard->IterateZombies(bZombie))
                {
                    if (aZombie->mX <= bZombie->mX + 40.0f && aZombie->mX >= bZombie->mX - 40 && aZombie->mRow == bZombie->mRow && !bZombie->mTossZombie && !bZombie->IsImmuneToKnockback())
                    {
                        int aStartX = bZombie->mPosX;
                        bZombie->XOrig = aStartX + 200.0f;
                        bZombie->mTossZombie = true;
                        loseLeaf = true;
                    }
                }
                if (loseLeaf)
                {
                    mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
                    PlayBodyReanim("anim_attack", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 20.0f);
                    mChardGuardLeafs--;
                    loseLeaf = false;
                }
            }
            if (aBodyReanim->mLoopCount > 0)
            {
                PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
                mState = PlantState::STATE_READY;
            }
        }
    }
}

void Plant::UpdateViolet()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    
    if (!aBodyReanim) return;

    if (IsInPlay() && mState == PlantState::STATE_NOTREADY)   {
        Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
        if (aZombie)
        {
            if (mSeedType == SeedType::SEED_SHRINK && !mStopAnimation)
            {
                aBodyReanim->SetImageOverride("Shrinking_violet_big_petal1", IMAGE_REANIM_VIOLET_PADDLE);
                aBodyReanim->SetImageOverride("Shrinking_violet_big_petal_copy2", IMAGE_REANIM_VIOLET_PADDLE);
                aBodyReanim->SetImageOverride("Shrinking_violet_big_petal3", IMAGE_REANIM_VIOLET_PADDLE);
                aBodyReanim->SetImageOverride("Shrinking_violet_big_petal4", IMAGE_REANIM_VIOLET_PADDLE);
                aBodyReanim->SetImageOverride("Shrinking_violet_big_petal5", IMAGE_REANIM_VIOLET_PADDLE);

                aBodyReanim->SetFramesForLayer("anim_bloom");
                aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
                mState = PlantState::STATE_SHRINKINGVIOLET_EXPLODING;
                mApp->PlayFoley(FoleyType::FOLEY_VIOLET);
                mStopAnimation = true;
            }
        }

    }
    else if (mState == PlantState::STATE_SHRINKINGVIOLET_EXPLODING && aBodyReanim->ShouldTriggerTimedEvent(0.5f)) {
        mBoard->ShrinkAllZombiesInRadius(mRow, mX + mWidth / 2, mY + mHeight / 2, 115, 1, true, GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY), 0);
        mState = PlantState::STATE_SHRINKINGVIOLET_EXPLODED;
    }
    else if (mState == PlantState::STATE_SHRINKINGVIOLET_EXPLODED && aBodyReanim->mLoopCount > 0) {
        Die();
    }
}

void Plant::UpdateAloe()
{
    if (mSeedType == SeedType::SEED_ALOEVERA)
    {
        Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);

        Plant* aPlant = nullptr;
        while (mBoard->IteratePlants(aPlant))
        {
            if (aPlant->mPlantHealth < aPlant->mPlantMaxHealth && mPlantAge % 300 == 0 &&
                (aPlant->mPlantCol == mPlantCol - 1 || aPlant->mPlantCol == mPlantCol || aPlant->mPlantCol == mPlantCol + 1) &&
                (aPlant->mRow == mRow - 1 || aPlant->mRow == mRow || aPlant->mRow == mRow + 1) && aPlant->mSeedType != SeedType::SEED_ALOEVERA)
            {
                PlayBodyReanim("anim_heal", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 0.0f);
            }
            if (aBodyReanim->mLoopCount > 0) PlayBodyReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 10, 12.0f);
        }
    }
}

void Plant::UpdateGhostpepper()
{
    Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (mState == PlantState::STATE_READY) {
        if (aZombie)
        {
            PlayBodyReanim("anim_scared", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
            aBodyReanim->mLoopCount = 0;
            mState = PlantState::STATE_HAUNTING;
        }
    }

    else if (mState == PlantState::STATE_HAUNTING) {
        if (aBodyReanim->mLoopCount > 0)
        {
            if (aBodyReanim->mLoopType != ReanimLoopType::REANIM_LOOP) {
                aBodyReanim->SetFramesForLayer("anim_scaredidle");
                aBodyReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
            }
            if (!mTriggered) {
                mTriggered = true;
                mGhostAge = 1000;
            }
            if (mDoSpecialCountdown <= 0) {
                mDoSpecialCountdown = 80;
                DoRowAreaDamage(30, 2U);
                if (!aZombie)
                {
                    PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
                    mState = PlantState::STATE_READY;
                }
            }
        }
    }

    if (mTriggered) {
        if (mGhostAge > 0) {
            mGhostAge--;
            mGhostFlash += 0.05f * int(1000 / max(300, mGhostAge));
        }
        else {
            if (mState != PlantState::STATE_GHOST_BLOWING) {
                PlayBodyReanim("anim_grow", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
                mState = PlantState::STATE_GHOST_BLOWING;
            }
            else if (mState == PlantState::STATE_GHOST_BLOWING && aBodyReanim->mLoopCount > 0) {
                int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
                Rect aAttackRect = GetPlantAttackRect(PlantWeapon::WEAPON_PRIMARY);

                Zombie* aZombie = nullptr;
                while (mBoard->IterateZombies(aZombie))
                {
                    int aRowDeviation = aZombie->mRow - mRow;
                    if ((!(aRowDeviation < -1 || aRowDeviation > 1) || aZombie->mZombieType == ZombieType::ZOMBIE_BOSS) && aZombie->EffectedByDamage(aDamageRangeFlags))
                    {
                        Rect aZombieRect = aZombie->GetZombieRect();
                        if (GetRectOverlap(aAttackRect, aZombieRect) > (aZombie->mZombieType == ZombieType::ZOMBIE_FOOTBALL ? -20 : 0))
                        {
                            aZombie->TakeDamage(450, 2U);
                        }
                    }
                }
                int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 0);
                mApp->AddTodParticle(mX + 40, mY + 40, aRenderPosition, ParticleEffect::PARTICLE_GLOOMCLOUD);
                mApp->PlayFoley(FoleyType::FOLEY_JALAPENO_IGNITE);
                Die();
            }
        }
    }
}

void Plant::UpdateSuperChomper()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (mState == PlantState::STATE_READY)
    {
        if (FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY))
        {
            PlayBodyReanim("anim_bite", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
            mState = PlantState::STATE_CHOMPER_BITING;
            mStateCountdown = 70;
        }
    }
    else if (mState == PlantState::STATE_CHOMPER_BITING)
    {
        if (mStateCountdown == 0)
        {
            mApp->PlayFoley(FoleyType::FOLEY_BIGCHOMP);
            Zombie* bZombie = nullptr;
            bool doBite = false;
            bool doMiss = false;
            Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
            if (aZombie)
            {
                if (aZombie->mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR || aZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR_GIGA ||
                    aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR)
                {
                    doBite = true;
                }
            }
            if (aZombie == nullptr)
            {
                doMiss = true;
            }
            else if (!aZombie->IsImmobilizied())
            {
                if (aZombie->IsBouncingPogo() ||
                    aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT)
                {
                    doMiss = true;
                }
            }
            if (doBite)
            {
                mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
                aZombie->TakeDamage(40, 0U);
                mState = PlantState::STATE_CHOMPER_BITING_MISSED;
            }
            else if (doMiss)
            {
                mState = PlantState::STATE_CHOMPER_BITING_MISSED;
            }
            else
            {
                aZombie->DieWithLoot();
                mState = PlantState::STATE_CHOMPER_BITING_GOT_ONE;
            }
            float chomperSpacing = 160.0f;
            while (mBoard->IterateZombies(bZombie))
            {
                if (((bZombie->mX > mX - 40.0f && bZombie->mX < mX + chomperSpacing) && bZombie->mRow == mRow && aZombie) && !bZombie->mMindControlled)
                {
                    if (bZombie->mZombieType == ZombieType::ZOMBIE_GARGANTUAR || bZombie->mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR || bZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR ||
                        bZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mZombieType == ZombieType::ZOMBIE_GLADIANTUAR_GIGA)
                    {
                        bZombie->TakeDamage(40, 0U);
                        mState = PlantState::STATE_CHOMPER_BITING_MISSED;
                    }
                    else
                    {
                        bZombie->DieWithLoot();
                        mState = PlantState::STATE_CHOMPER_BITING_GOT_ONE;
                    }
               }
            }
        }
    }
    else if (mState == PlantState::STATE_CHOMPER_BITING_GOT_ONE)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayBodyReanim("anim_chew", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
            if (mApp->IsIZombieLevel())
            {
                aBodyReanim->mAnimRate = 0;
            }

            mState = PlantState::STATE_CHOMPER_DIGESTING;
            mStateCountdown = 2000;
        }
    }
    else if (mState == PlantState::STATE_CHOMPER_DIGESTING)
    {
        if (mStateCountdown == 0)
        {
            PlayBodyReanim("anim_swallow", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);
            mState = PlantState::STATE_CHOMPER_SWALLOWING;
        }
    }
    else if ((mState == PlantState::STATE_CHOMPER_SWALLOWING || mState == PlantState::STATE_CHOMPER_BITING_MISSED) && aBodyReanim->mLoopCount > 0)
    {
        PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
        mState = PlantState::STATE_READY;
    }
}

//0x4615D0
MagnetItem* Plant::GetFreeMagnetItem()
{
    if (mSeedType == SeedType::SEED_GOLD_MAGNET)
    {
        for (int i = 0; i < MAX_MAGNET_ITEMS; i++)
        {
            if (mMagnetItems[i].mItemType == MagnetItemType::MAGNET_ITEM_NONE)
            {
                return &mMagnetItems[i];
            }
        }

        return nullptr;
    }

    return &mMagnetItems[0];
}

//0x460610
void Plant::MagnetShroomAttactItem(Zombie* theZombie)
{
    mState = PlantState::STATE_MAGNETSHROOM_SUCKING;
    mStateCountdown = 1500;
    PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);
    mApp->PlayFoley(FoleyType::FOLEY_MAGNETSHROOM);

    MagnetItem* aMagnetItem = GetFreeMagnetItem();
    if (theZombie->mHelmType == HelmType::HELMTYPE_PAIL)
    {
        int aDamageIndex = theZombie->GetHelmDamageIndex();

        theZombie->mHelmHealth = 0;
        theZombie->mHelmType = HelmType::HELMTYPE_NONE;
        theZombie->GetTrackPosition("anim_bucket", aMagnetItem->mPosX, aMagnetItem->mPosY);
        theZombie->ReanimShowPrefix("anim_bucket", RENDER_GROUP_HIDDEN);
        theZombie->ReanimShowPrefix("anim_hair", RENDER_GROUP_NORMAL);

        aMagnetItem->mPosX -= IMAGE_REANIM_ZOMBIE_BUCKET1->GetWidth() / 2;
        aMagnetItem->mPosY -= IMAGE_REANIM_ZOMBIE_BUCKET1->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 25.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_ITEM_PAIL_1 + aDamageIndex);
    }
    else if (theZombie->mHelmType == HelmType::HELMTYPE_PAIL_GIGA)
    {
        int aDamageIndex = theZombie->GetHelmDamageIndex();

        theZombie->mHelmHealth = 0;
        theZombie->mHelmType = HelmType::HELMTYPE_NONE;
        theZombie->GetTrackPosition("anim_bucket", aMagnetItem->mPosX, aMagnetItem->mPosY);
        theZombie->ReanimShowPrefix("anim_bucket", RENDER_GROUP_HIDDEN);
        theZombie->ReanimShowPrefix("anim_hair", RENDER_GROUP_NORMAL);

        aMagnetItem->mPosX -= IMAGE_REANIM_ZOMBIE_BUCKET1->GetWidth() / 2;
        aMagnetItem->mPosY -= IMAGE_REANIM_ZOMBIE_BUCKET1->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 25.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_ITEM_PAIL_GIGA_1 + aDamageIndex);
    }
    else if (theZombie->mHelmType == HelmType::HELMTYPE_FOOTBALL)
    {
        int aDamageIndex = theZombie->GetHelmDamageIndex();

        theZombie->mHelmHealth = 0;
        theZombie->mHelmType = HelmType::HELMTYPE_NONE;
        theZombie->GetTrackPosition("zombie_football_helmet", aMagnetItem->mPosX, aMagnetItem->mPosY);
        theZombie->ReanimShowPrefix("zombie_football_helmet", RENDER_GROUP_HIDDEN);
        theZombie->ReanimShowPrefix("anim_hair", RENDER_GROUP_NORMAL);

        aMagnetItem->mPosX += 37.0f;
        aMagnetItem->mPosY -= 60.0f;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_ITEM_FOOTBALL_HELMET_1 + aDamageIndex);
    }
    else if (theZombie->mHelmType == HelmType::HELMTYPE_GIGA_FOOTBALL)
    {
        int aDamageIndex = theZombie->GetHelmDamageIndex();

        theZombie->mHelmHealth = 0;
        theZombie->mHelmType = HelmType::HELMTYPE_NONE;
        theZombie->GetTrackPosition("zombie_football_helmet", aMagnetItem->mPosX, aMagnetItem->mPosY);
        theZombie->ReanimShowPrefix("zombie_football_helmet", RENDER_GROUP_HIDDEN);
        theZombie->ReanimShowPrefix("anim_hair", RENDER_GROUP_NORMAL);

        aMagnetItem->mPosX += 37.0f;
        aMagnetItem->mPosY -= 60.0f;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_ITEM_GIGA_FOOTBALL_HELMET_1 +aDamageIndex);
    }
    else if (theZombie->mHelmType == HelmType::HELMTYPE_GLADIANTUAR)
    {
        int aDamageIndex = theZombie->GetHelmDamageIndex();

        theZombie->mHelmHealth = 0;
        theZombie->mHelmType = HelmType::HELMTYPE_NONE;
        theZombie->GetTrackPosition("anim_helmet", aMagnetItem->mPosX, aMagnetItem->mPosY);
        theZombie->ReanimShowPrefix("anim_helmet", RENDER_GROUP_HIDDEN);
        //theZombie->ReanimShowPrefix("anim_head1", RENDER_GROUP_NORMAL);

        aMagnetItem->mPosX += 37.0f;
        aMagnetItem->mPosY -= 60.0f;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_GLADIANTUAR_HELMET_1 + aDamageIndex);
    }
    else if (theZombie->mShieldType == ShieldType::SHIELDTYPE_DOOR)
    {
        int aDamageIndex = theZombie->GetShieldDamageIndex();

        theZombie->DetachShield();
        theZombie->mZombiePhase = ZombiePhase::PHASE_ZOMBIE_NORMAL;
        if (!theZombie->mIsEating)
        {
            TOD_ASSERT(theZombie->mZombieHeight == ZombieHeight::HEIGHT_ZOMBIE_NORMAL);
            theZombie->StartWalkAnim(0);
        }
        theZombie->GetTrackPosition("anim_screendoor", aMagnetItem->mPosX, aMagnetItem->mPosY);

        aMagnetItem->mPosX -= IMAGE_REANIM_ZOMBIE_SCREENDOOR1->GetWidth() / 2;
        aMagnetItem->mPosY -= IMAGE_REANIM_ZOMBIE_SCREENDOOR1->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 30.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f);
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_ITEM_DOOR_1 + aDamageIndex);
    }
    else if (theZombie->mShieldType == ShieldType::SHIELDTYPE_TRASHCAN)
    {
        int aDamageIndex = theZombie->GetShieldDamageIndex();

        theZombie->DetachShield();
        theZombie->mZombiePhase = ZombiePhase::PHASE_ZOMBIE_NORMAL;
        if (!theZombie->mIsEating)
        {
            TOD_ASSERT(theZombie->mZombieHeight == ZombieHeight::HEIGHT_ZOMBIE_NORMAL);
            theZombie->StartWalkAnim(0);
        }
        theZombie->GetTrackPosition("anim_trashcan", aMagnetItem->mPosX, aMagnetItem->mPosY);

        aMagnetItem->mPosX -= IMAGE_REANIM_ZOMBIE_TRASHCAN1->GetWidth() / 2;
        aMagnetItem->mPosY -= IMAGE_REANIM_ZOMBIE_TRASHCAN1->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 30.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f);
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_ITEM_TRASHCAN_1 + aDamageIndex);
    }
    else if (theZombie->mShieldType == ShieldType::SHIELDTYPE_LADDER)
    {
        int aDamageIndex = theZombie->GetShieldDamageIndex();

        theZombie->DetachShield();

        aMagnetItem->mPosX = theZombie->mPosX + 31.0f;
        aMagnetItem->mPosY = theZombie->mPosY + 20.0f;
        aMagnetItem->mPosX -= IMAGE_REANIM_ZOMBIE_LADDER_5->GetWidth() / 2;
        aMagnetItem->mPosY -= IMAGE_REANIM_ZOMBIE_LADDER_5->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 30.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f);
        aMagnetItem->mItemType = (MagnetItemType)((int)MagnetItemType::MAGNET_ITEM_LADDER_1 + aDamageIndex);
    }
    else if (theZombie->mZombieType == ZombieType::ZOMBIE_POGO)
    {
        theZombie->PogoBreak(16U);
        // ZombieDrawPosition aDrawPos;
        // theZombie->GetDrawPos(aDrawPos);
        theZombie->GetTrackPosition("Zombie_pogo_stick", aMagnetItem->mPosX, aMagnetItem->mPosY);

        aMagnetItem->mPosX += 40.0f - IMAGE_REANIM_ZOMBIE_LADDER_5->GetWidth() / 2;
        aMagnetItem->mPosY += 84.0f - IMAGE_REANIM_ZOMBIE_LADDER_5->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 30.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f);
        aMagnetItem->mItemType = theZombie->mHasArm ? MagnetItemType::MAGNET_ITEM_POGO_1 : MagnetItemType::MAGNET_ITEM_POGO_3;
    }
    else if (theZombie->mZombiePhase == ZombiePhase::PHASE_JACK_IN_THE_BOX_RUNNING)
    {
        theZombie->StopZombieSound();
        theZombie->PickRandomSpeed();
        theZombie->mZombiePhase = ZombiePhase::PHASE_ZOMBIE_NORMAL;
        theZombie->ReanimShowPrefix("Zombie_jackbox_box", RENDER_GROUP_HIDDEN);
        theZombie->ReanimShowPrefix("Zombie_jackbox_handle", RENDER_GROUP_HIDDEN);
        theZombie->GetTrackPosition("Zombie_jackbox_box", aMagnetItem->mPosX, aMagnetItem->mPosY);

        aMagnetItem->mPosX -= IMAGE_REANIM_ZOMBIE_JACKBOX_BOX->GetWidth() / 2;
        aMagnetItem->mPosY -= IMAGE_REANIM_ZOMBIE_JACKBOX_BOX->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 20.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f) + 15.0f;
        aMagnetItem->mItemType = MagnetItemType::MAGNET_ITEM_JACK_IN_THE_BOX;
    }
    else if (theZombie->mZombieType == ZombieType::ZOMBIE_DIGGER)
    {
        theZombie->DiggerLoseAxe();
        theZombie->GetTrackPosition("Zombie_digger_pickaxe", aMagnetItem->mPosX, aMagnetItem->mPosY);

        aMagnetItem->mPosX -= IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE->GetWidth() / 2;
        aMagnetItem->mPosY -= IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE->GetHeight() / 2;
        aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 45.0f;
        aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f) + 15.0f;
        aMagnetItem->mItemType = MagnetItemType::MAGNET_ITEM_PICK_AXE;
    }
}

//0x461CD0
bool Plant::DrawMagnetItemsOnTop()
{
    if (mSeedType == SeedType::SEED_GOLD_MAGNET)
    {
        for (int i = 0; i < MAX_MAGNET_ITEMS; i++)
        {
            if (mMagnetItems[i].mItemType != MagnetItemType::MAGNET_ITEM_NONE)
            {
                return true;
            }
        }

        return false;
    }

    if (mSeedType == SeedType::SEED_MAGNETSHROOM)
    {
        for (int i = 0; i < MAX_MAGNET_ITEMS; i++)
        {
            MagnetItem* aMagnetItem = &mMagnetItems[i];
            if (aMagnetItem->mItemType != MagnetItemType::MAGNET_ITEM_NONE)
            {
                SexyVector2 aVectorToPlant(mX + aMagnetItem->mDestOffsetX - aMagnetItem->mPosX, mY + aMagnetItem->mDestOffsetY - aMagnetItem->mPosY);
                if (aVectorToPlant.Magnitude() > 20.0f)
                {
                    return true;
                }
            }
        }

        return false;
    }
}

//0x461D90
void Plant::UpdateMagnetShroom()
{
    for (int i = 0; i < MAX_MAGNET_ITEMS; i++)
    {
        MagnetItem* aMagnetItem = &mMagnetItems[i];
        if (aMagnetItem->mItemType != MagnetItemType::MAGNET_ITEM_NONE)
        {
            SexyVector2 aVectorToPlant(mX + aMagnetItem->mDestOffsetX - aMagnetItem->mPosX, mY + aMagnetItem->mDestOffsetY - aMagnetItem->mPosY);
            if (aVectorToPlant.Magnitude() > 20.0f)
            {
                aMagnetItem->mPosX += aVectorToPlant.x * 0.05f;
                aMagnetItem->mPosY += aVectorToPlant.y * 0.05f;
            }
        }
    }

    if (mState == PlantState::STATE_MAGNETSHROOM_CHARGING)
    {
        if (mStateCountdown == 0)
        {
            mState = PlantState::STATE_READY;

            float aAnimRate = RandRangeFloat(10.0f, 15.0f);
            PlayBodyReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 30, aAnimRate);
            if (mApp->IsIZombieLevel())
            {
                Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
                aBodyReanim->mAnimRate = 0.0f;
            }

            mMagnetItems[0].mItemType = MagnetItemType::MAGNET_ITEM_NONE;
        }
    }
    else if (mState == PlantState::STATE_MAGNETSHROOM_SUCKING)
    {
        Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayBodyReanim("anim_nonactive_idle2", ReanimLoopType::REANIM_LOOP, 20, 2.0f);
            if (mApp->IsIZombieLevel())
            {
                aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
                aBodyReanim->mAnimRate = 0.0f;
            }

            mState = PlantState::STATE_MAGNETSHROOM_CHARGING;
        }
    }
    else
    {
        float aClosestDistance = 0.0f;
        Zombie* aClosestZombie = nullptr;

        Zombie* aZombie = nullptr;
        while (mBoard->IterateZombies(aZombie))
        {
            int aDiffY = aZombie->mRow - mRow;
            Rect aZombieRect = aZombie->GetZombieRect();

            if (aZombie->mMindControlled)
                continue;

            if (!aZombie->mHasHead)
                continue;

            if (aZombie->mZombieHeight != ZombieHeight::HEIGHT_ZOMBIE_NORMAL || aZombie->mZombiePhase == ZombiePhase::PHASE_RISING_FROM_GRAVE)
                continue;

            if (aZombie->IsDeadOrDying())
                continue;

            if (aZombieRect.mX > BOARD_WIDTH || aDiffY > 2 || aDiffY < -2)
                continue;

            if (aZombie->mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING ||
                aZombie->mZombiePhase == ZombiePhase::PHASE_DIGGER_STUNNED ||
                aZombie->mZombiePhase == ZombiePhase::PHASE_DIGGER_WALKING ||
                aZombie->mZombieType == ZombieType::ZOMBIE_POGO)
            {
                if (!aZombie->mHasObject)
                    continue;
            }
            else if (!(aZombie->mHelmType == HelmType::HELMTYPE_PAIL ||
                aZombie->mHelmType == HelmType::HELMTYPE_FOOTBALL ||
                aZombie->mHelmType == HelmType::HELMTYPE_PAIL_GIGA ||
                aZombie->mHelmType == HelmType::HELMTYPE_GIGA_FOOTBALL ||
                aZombie->mHelmType == HelmType::HELMTYPE_GLADIANTUAR ||
                aZombie->mShieldType == ShieldType::SHIELDTYPE_DOOR ||
                aZombie->mShieldType == ShieldType::SHIELDTYPE_TRASHCAN ||
                aZombie->mShieldType == ShieldType::SHIELDTYPE_LADDER ||
                aZombie->mZombiePhase == ZombiePhase::PHASE_JACK_IN_THE_BOX_RUNNING))
                continue;

            int aRadius = aZombie->mIsEating ? 320 : 270;
            if (GetCircleRectOverlap(mX, mY + 20, aRadius, aZombieRect))
            {
                float aDistance = Distance2D(mX, mY, aZombieRect.mX, aZombieRect.mY);
                aDistance += abs(aDiffY) * 80.0f;

                if (aClosestZombie == nullptr || aDistance < aClosestDistance)
                {
                    aClosestZombie = aZombie;
                    aClosestDistance = aDistance;
                }
            }
        }

        if (aClosestZombie)
        {
            MagnetShroomAttactItem(aClosestZombie);
            return;
        }

        ////////////////////

        float aClosestLadderDist = 0.0f;
        GridItem* aClosestLadder = nullptr;
        
        GridItem* aGridItem = nullptr;
        while (mBoard->IterateGridItems(aGridItem))
        {
            if (aGridItem->mGridItemType == GridItemType::GRIDITEM_LADDER)
            {
                int aDiffX = abs(aGridItem->mGridX - mPlantCol);
                int aDiffY = abs(aGridItem->mGridY - mRow);
                int aSquareDistance = max(aDiffX, aDiffY);
                if (aSquareDistance <= 2)
                {
                    float aDistance = aSquareDistance + aDiffY * 0.05f;
                    if (aClosestLadder == nullptr || aDistance < aClosestLadderDist)
                    {
                        aClosestLadder = aGridItem;
                        aClosestLadderDist = aDistance;
                    }
                }
            }
        }

        if (aClosestLadder)
        {
            mState = PlantState::STATE_MAGNETSHROOM_SUCKING;
            mStateCountdown = 1500;
            PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);
            mApp->PlayFoley(FoleyType::FOLEY_MAGNETSHROOM);

            aClosestLadder->GridItemDie();

            MagnetItem* aMagnetItem = GetFreeMagnetItem();
            aMagnetItem->mPosX = mBoard->GridToPixelX(aClosestLadder->mGridX, aClosestLadder->mGridY) + 40;
            aMagnetItem->mPosY = mBoard->GridToPixelY(aClosestLadder->mGridX, aClosestLadder->mGridY);
            aMagnetItem->mDestOffsetX = RandRangeFloat(-10.0f, 10.0f) + 10.0f;
            aMagnetItem->mDestOffsetY = RandRangeFloat(-10.0f, 10.0f);
            aMagnetItem->mItemType = MagnetItemType::MAGNET_ITEM_LADDER_PLACED;
        }
    }
}

//0x462390
Coin* Plant::FindGoldMagnetTarget()
{
    Coin* aClosestCoin = nullptr;
    float aClosestDistance = 0.0f;

    Coin* aCoin = nullptr;
    while (mBoard->IterateCoins(aCoin))
    {
        if (aCoin->IsMoney() && aCoin->mCoinMotion != CoinMotion::COIN_MOTION_FROM_PRESENT && !aCoin->mIsBeingCollected && aCoin->mCoinAge >= 50)
        {
            float aDistance = Distance2D(mX + mWidth / 2, mY + mHeight / 2, aCoin->mPosX + aCoin->mWidth / 2, aCoin->mPosY + aCoin->mHeight / 2);
            if (aClosestCoin == nullptr || aDistance < aClosestDistance)
            {
                aClosestCoin = aCoin;
                aClosestDistance = aDistance;
            }
        }
    }

    return aClosestCoin;
}

//0x4624B0
void Plant::GoldMagnetFindTargets()
{
    if (GetFreeMagnetItem() == nullptr)
    {
        TOD_ASSERT();
        return;
    }

    for (;;)
    {
        MagnetItem* aMagnetItem = GetFreeMagnetItem();
        if (aMagnetItem == nullptr)
            break;

        Coin* aCoin = FindGoldMagnetTarget();
        if (aCoin == nullptr)
            break;

        aMagnetItem->mPosX = aCoin->mPosX + 15.0f;
        aMagnetItem->mPosY = aCoin->mPosY + 15.0f;
        aMagnetItem->mDestOffsetX = RandRangeFloat(20.0f, 40.0f);
        aMagnetItem->mDestOffsetY = RandRangeFloat(-20.0f, 0.0f) + 20.0f;

        switch (aCoin->mType)
        {
        case CoinType::COIN_SILVER:     aMagnetItem->mItemType = MagnetItemType::MAGNET_ITEM_SILVER_COIN;   break;
        case CoinType::COIN_GOLD:       aMagnetItem->mItemType = MagnetItemType::MAGNET_ITEM_GOLD_COIN;     break;
        case CoinType::COIN_DIAMOND:    aMagnetItem->mItemType = MagnetItemType::MAGNET_ITEM_DIAMOND;       break;
        default:                        TOD_ASSERT();                                                       return;
        }
        
        aCoin->Die();
    }
}

//0x4625D0
bool Plant::IsAGoldMagnetAboutToSuck()
{
    Plant* aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant))
    {
        if (!aPlant->NotOnGround() && aPlant->mSeedType == SeedType::SEED_GOLD_MAGNET && aPlant->mState == PlantState::STATE_MAGNETSHROOM_SUCKING)
        {
            Reanimation* aBodyReanim = mApp->ReanimationGet(aPlant->mBodyReanimID);
            if (aBodyReanim->mAnimTime < 0.5f)
            {
                return true;
            }
        }
    }

    return false;
}

//0x462680
void Plant::UpdateGoldMagnetShroom()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);

    bool aIsSuckingCoin = false;
    for (int i = 0; i < MAX_MAGNET_ITEMS; i++)
    {
        MagnetItem* aMagnetItem = &mMagnetItems[i];
        if (aMagnetItem->mItemType != MagnetItemType::MAGNET_ITEM_NONE)
        {
            SexyVector2 aVectorToPlant(mX + aMagnetItem->mDestOffsetX - aMagnetItem->mPosX, mY + aMagnetItem->mDestOffsetY - aMagnetItem->mPosY);
            float aDistance = aVectorToPlant.Magnitude();
            if (aDistance < 20.0f)
            {
                CoinType aCoinType;
                switch (aMagnetItem->mItemType)
                {
                case MagnetItemType::MAGNET_ITEM_SILVER_COIN:   aCoinType = CoinType::COIN_SILVER;      break;
                case MagnetItemType::MAGNET_ITEM_GOLD_COIN:     aCoinType = CoinType::COIN_GOLD;        break;
                case MagnetItemType::MAGNET_ITEM_DIAMOND:       aCoinType = CoinType::COIN_DIAMOND;     break;
                default:                                        TOD_ASSERT();                           return;
                }

                int aValue = Coin::GetCoinValue(aCoinType);
                mApp->mPlayerInfo->AddCoins(aValue);
                mBoard->mCoinsCollected += aValue;
                mApp->PlayFoley(FoleyType::FOLEY_COIN);

                aMagnetItem->mItemType = MagnetItemType::MAGNET_ITEM_NONE;
            }
            else
            {
                float aSpeed = TodAnimateCurveFloatTime(30.0f, 0.0f, aDistance, 0.02f, 0.05f, TodCurves::CURVE_LINEAR);
                aMagnetItem->mPosX += aVectorToPlant.x * aSpeed;
                aMagnetItem->mPosY += aVectorToPlant.y * aSpeed;

                aIsSuckingCoin = true;
            }
        }
    }

    if (mState == PlantState::STATE_MAGNETSHROOM_CHARGING)
    {
        if (mStateCountdown == 0)
        {
            mState = PlantState::STATE_READY;
        }
    }
    else if (mState == PlantState::STATE_MAGNETSHROOM_SUCKING)
    {
        if (aBodyReanim->ShouldTriggerTimedEvent(0.4f))
        {
            mApp->PlayFoley(FoleyType::FOLEY_MAGNETSHROOM);
            GoldMagnetFindTargets();
        }

        if (aBodyReanim->mLoopCount > 0 && !aIsSuckingCoin)
        {
            PlayIdleAnim(14.0f);
            mState = PlantState::STATE_MAGNETSHROOM_CHARGING;
            mStateCountdown = RandRangeInt(200, 300);
        }
    }
    else if (!IsAGoldMagnetAboutToSuck() && Sexy::Rand(50) == 0 && FindGoldMagnetTarget())
    {
        mBoard->ShowCoinBank();
        mState = PlantState::STATE_MAGNETSHROOM_SUCKING;
        PlayBodyReanim("anim_attract", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);
    }
}

//0x4629F0
void Plant::RemoveEffects()
{
    mApp->RemoveParticle(mParticleID);
    mApp->RemoveReanimation(mBodyReanimID);
    mApp->RemoveReanimation(mHeadReanimID);
    mApp->RemoveReanimation(mHeadReanimID2);
    mApp->RemoveReanimation(mHeadReanimID3);
    mApp->RemoveReanimation(mLightReanimID);
    mApp->RemoveReanimation(mBlinkReanimID);
    mApp->RemoveReanimation(mSleepingReanimID);
}

//0x462B80
void Plant::Squish()
{
    if (NotOnGround())
        return;

    if (mSeedType == SEED_GRAVE)
        return;

    if (!mIsAsleep)
    {
        if (mSeedType == SeedType::SEED_CHERRYBOMB || mSeedType == SeedType::SEED_JALAPENO || mSeedType == SeedType::SEED_PICKLEPEPPER ||
            mSeedType == SeedType::SEED_DOOMSHROOM || mSeedType == SeedType::SEED_ICESHROOM || mSeedType == SeedType::SEED_CHILLYPEPPER ||
            mSeedType == SeedType::SEED_LEMON_NADE || mSeedType == SeedType::SEED_BLOODORANGE)
        {
            DoSpecial();
            return;
        }
        else if (mSeedType == SeedType::SEED_POTATOMINE && mState != PlantState::STATE_NOTREADY)
        {
            DoSpecial();
            return;
        }
    }

    if (mSeedType == SeedType::SEED_SQUASH && mState != PlantState::STATE_NOTREADY)
        return;

    if (mBoard->mPlantRow[mRow] == PLANTROW_POOL)
    {
        Die();
        mApp->PlayFoley(FoleyType::FOLEY_ZOMBIESPLASH);
    }
    else
    {
        mRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_GRAVE_STONE, mRow, 8);
        mSquished = true;
        mDisappearCountdown = 500;
        mApp->PlayFoley(FoleyType::FOLEY_SQUISH);
        RemoveEffects();
    }

    GridItem* aLadder = mBoard->GetLadderAt(mPlantCol, mRow);
    if (aLadder)
    {
        aLadder->GridItemDie();
    }

    if (mApp->IsIZombieLevel())
    {
        mBoard->mChallenge->IZombiePlantDropRemainingSun(this);
    }
}

//0x462CE0
void Plant::UpdateBowling()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim && aBodyReanim->TrackExists("_ground"))
    {
        float aSpeed = aBodyReanim->GetTrackVelocity("_ground");
        if (mSeedType == SeedType::SEED_GIANT_WALLNUT)
        {
            aSpeed *= 2;
        }

        mX -= aSpeed;
        if (mX > 800)
            Die();
    }

    if (mState == PlantState::STATE_BOWLING_UP)
    {
        mY -= 2;
    }
    else if (mState == PlantState::STATE_BOWLING_DOWN)
    {
        mY += 2;
    }
    int aDistToGrid = mBoard->GridToPixelY(0, mRow) - mY;
    if (aDistToGrid < -2 || aDistToGrid > 2)
        return;

    PlantState aNewState = mState;
    if (mState == PlantState::STATE_BOWLING_UP && mRow <= 0)
    {
        aNewState = PlantState::STATE_BOWLING_DOWN;
    }
    else if (mState == PlantState::STATE_BOWLING_DOWN && mRow >= 4)
    {
        aNewState = PlantState::STATE_BOWLING_UP;
    }

    Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
    if (aZombie)
    {
        int aPosX = mX + mWidth / 2;
        int aPosY = mY + mHeight / 2;

        if (mSeedType == SeedType::SEED_EXPLODE_O_NUT)
        {
            mApp->PlayFoley(FoleyType::FOLEY_CHERRYBOMB);
            mApp->PlaySample(SOUND_BOWLINGIMPACT2);

            int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY) | 32U;
            //mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, 90, 1, true, aDamageRangeFlags, 0);
            mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_POWIE);
            mBoard->ShakeBoard(3, -4);

            Die();

            return;
        }
        if (mSeedType == SeedType::SEED_ICENUT)
        {
            /*mApp->PlayFoley(FoleyType::FOLEY_FROZEN);
            mApp->PlaySample(SOUND_BOWLINGIMPACT2);

            IceZombies();
            mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_ICE_TRAP);

            Die();

            return;*/
            mApp->PlayFoley(FoleyType::FOLEY_FROZEN);
            mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_ICE_TRAP_RELEASE);
            aZombie->HitIceTrap();
        }

        mApp->PlayFoley(FoleyType::FOLEY_BOWLINGIMPACT);
        mBoard->ShakeBoard(1, -2);

        if (mSeedType == SeedType::SEED_GIANT_WALLNUT)
        {
            aZombie->TakeDamage(1800, 0U);
        }
        else if (aZombie->mShieldType == ShieldType::SHIELDTYPE_DOOR && mState != PlantState::STATE_NOTREADY)
        {
            aZombie->TakeDamage(1800, 0U);
        }
        else if (aZombie->mShieldType == ShieldType::SHIELDTYPE_TRASHCAN && mState != PlantState::STATE_NOTREADY)
        {
            aZombie->TakeDamage(1800, 0U);
        }
        else if (aZombie->mZombieType == ZOMBIE_ZOMBONI)
        {
            aZombie->TakeDamage(400, 0U);
        }
        else if (aZombie->mShieldType != ShieldType::SHIELDTYPE_NONE)
        {
            aZombie->TakeShieldDamage(400, 0U);
        }
        else if (aZombie->mHelmType != HelmType::HELMTYPE_NONE)
        {
            if (aZombie->mHelmType == HelmType::HELMTYPE_PAIL || aZombie->mHelmType == HelmType::HELMTYPE_PAIL_GIGA)
            {
                mApp->PlayFoley(FoleyType::FOLEY_SHIELD_HIT);
            }
            else if (aZombie->mHelmType == HelmType::HELMTYPE_TRAFFIC_CONE)
            {
                mApp->PlayFoley(FoleyType::FOLEY_PLASTIC_HIT);
            }
            
            aZombie->TakeHelmDamage(900, 0U);
        }
        else
        {
            aZombie->TakeDamage(1800, 0U);
        }

        if ((!mApp->IsFirstTimeAdventureMode() || mApp->mPlayerInfo->GetLevel() > 10) && mSeedType == SeedType::SEED_WALLNUT)
        {
            mLaunchCounter++;
            if (mLaunchCounter == 2)
            {
                mApp->PlayFoley(FoleyType::FOLEY_SPAWN_SUN);
                mBoard->AddCoin(aPosX, aPosY, CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
            }
            else if (mLaunchCounter == 3)
            {
                mApp->PlayFoley(FoleyType::FOLEY_SPAWN_SUN);
                mBoard->AddCoin(aPosX - 5.0f, aPosY, CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
                mBoard->AddCoin(aPosX + 5.0f, aPosY, CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
            }
            else if (mLaunchCounter == 4)
            {
                mApp->PlayFoley(FoleyType::FOLEY_SPAWN_SUN);
                mBoard->AddCoin(aPosX - 10.0f, aPosY, CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
                mBoard->AddCoin(aPosX, aPosY, CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
                mBoard->AddCoin(aPosX + 10.0f, aPosY, CoinType::COIN_SILVER, CoinMotion::COIN_MOTION_COIN);
            }
            else if (mLaunchCounter >= 5)
            {
                mApp->PlayFoley(FoleyType::FOLEY_SPAWN_SUN);
                mBoard->AddCoin(aPosX, aPosY, CoinType::COIN_GOLD, CoinMotion::COIN_MOTION_COIN);
            }
        }

        if (mSeedType != SeedType::SEED_GIANT_WALLNUT)
        {
            if (mRow == 4 || mState == PlantState::STATE_BOWLING_DOWN)
            {
                aNewState = PlantState::STATE_BOWLING_UP;
            }
            else if (mRow == 0 || mState == PlantState::STATE_BOWLING_UP)
            {
                aNewState = PlantState::STATE_BOWLING_DOWN;
            }
            else
            {
                aNewState = Sexy::Rand(2) ? PlantState::STATE_BOWLING_UP : PlantState::STATE_BOWLING_DOWN;
            }
        }
    }

    if (aNewState == PlantState::STATE_BOWLING_UP)
    {
        mRow--;
        mState = PlantState::STATE_BOWLING_UP;
        mRenderOrder = CalcRenderOrder();
    }
    else if (aNewState == PlantState::STATE_BOWLING_DOWN)
    {
        mState = PlantState::STATE_BOWLING_DOWN;
        mRenderOrder = CalcRenderOrder();
        mRow++;
    }
}

//0x463150
void Plant::UpdateAbilities()
{
    if (!IsInPlay())
        return;

    if (mState == PlantState::STATE_DOINGSPECIAL || mSquished)
    {
        mDisappearCountdown--;
        if (mDisappearCountdown < 0)
        {
            Die();
            return;
        }
    }

    if (mWakeUpCounter > 0)
    {
        mWakeUpCounter--;
        if (mWakeUpCounter == 60)
        {
            mApp->PlayFoley(FoleyType::FOLEY_WAKEUP);
            if (mSeedType == SEED_LUMESHROOM)
            {
                AddAttachedParticle(mX + 40, mY + 40, (int)RenderLayer::RENDER_LAYER_FOG + 1, ParticleEffect::PARTICLE_LANTERN_SHINE);
                mApp->PlaySample(Sexy::SOUND_PLANTERN);
            }
        }
        if (mWakeUpCounter == 0)
        {
            SetSleeping(false);
        }
    }

    if (mIsAsleep || mSquished || mOnBungeeState != PlantOnBungeeState::NOT_ON_BUNGEE)
        return;
    
    UpdateShooting();

    if (mStateCountdown > 0)
        mStateCountdown--;

    if (mApp->IsWallnutBowlingLevel())
    {
        UpdateBowling();
        return;
    }

    if      (mSeedType == SeedType::SEED_SQUASH)                                                                            UpdateSquash();
    else if (mSeedType == SeedType::SEED_DOOMSHROOM)                                                                        UpdateDoomShroom();
    else if (mSeedType == SeedType::SEED_ICESHROOM)                                                                         UpdateIceShroom();
    else if (mSeedType == SeedType::SEED_CHOMPER)                                                                           UpdateChomper();
    else if (mSeedType == SeedType::SEED_REVERSE_CHOMPER)                                                                   UpdateChomper();
    else if (mSeedType == SeedType::SEED_BONKCHOY)                                                                          UpdateBonkChoy();
    else if (mSeedType == SeedType::SEED_CHARD_GUARD)                                                                       UpdateChardGuard();
    else if (mSeedType == SeedType::SEED_SUPERCHOMP)                                                                        UpdateSuperChomper();
    else if (mSeedType == SeedType::SEED_BLOVER)                                                                            UpdateBlover();
    else if (mSeedType == SeedType::SEED_HURRIKALE)                                                                         UpdateBlover();
    else if (mSeedType == SeedType::SEED_FLOWERPOT)                                                                         UpdateFlowerPot();
    else if (mSeedType == SeedType::SEED_WATERPOT)                                                                          UpdateFlowerPot();
    else if (mSeedType == SeedType::SEED_LILYPAD)                                                                           UpdateLilypad();
    else if (mSeedType == SeedType::SEED_IMITATER)                                                                          UpdateImitater();
    else if (mSeedType == SeedType::SEED_INSTANT_COFFEE)                                                                    UpdateCoffeeBean();
    else if (mSeedType == SeedType::SEED_UMBRELLA)                                                                          UpdateUmbrella();
    else if (mSeedType == SeedType::SEED_COBCANNON)                                                                         UpdateCobCannon();
    else if (mSeedType == SeedType::SEED_CACTUS)                                                                            UpdateCactus();
    else if (mSeedType == SeedType::SEED_MAGNETSHROOM)                                                                      UpdateMagnetShroom();
    else if (mSeedType == SeedType::SEED_GOLD_MAGNET)                                                                       UpdateGoldMagnetShroom();
    else if (mSeedType == SeedType::SEED_SUNSHROOM)                                                                         UpdateSunShroom();
    else if (MakesSun() || mSeedType == SeedType::SEED_MARIGOLD)                                                            UpdateProductionPlant();
    else if (mSeedType == SeedType::SEED_GRAVEBUSTER)                                                                       UpdateGraveBuster();
    else if (mSeedType == SeedType::SEED_TORCHWOOD || mSeedType == SeedType::SEED_FLAMEWOOD)                                UpdateTorchwood();
    else if (mSeedType == SeedType::SEED_POTATOMINE)                                                                        UpdatePotato();
    else if (mSeedType == SeedType::SEED_SPIKEWEED || mSeedType == SeedType::SEED_SPIKEROCK)                                UpdateSpikeweed();
    else if (mSeedType == SeedType::SEED_THORNMOSS)                                                                         UpdateThornmoss();
    else if (mSeedType == SeedType::SEED_TANGLEKELP)                                                                        UpdateTanglekelp();
    else if (mSeedType == SeedType::SEED_SCAREDYSHROOM)                                                                     UpdateScaredyShroom();
    else if (mSeedType == SeedType::SEED_BRAVESHROOM)                                                                       UpdateBraveShroom();
    else if (mSeedType == SeedType::SEED_OAK_ARCHER)                                                                        UpdateOakArcher();
    else if (mSeedType == SeedType::SEED_LEMON_NADE)                                                                        UpdateLemon();
    else if (mSeedType == SeedType::SEED_SHRINK)                                                                            UpdateViolet();
    else if (mSeedType == SeedType::SEED_ALOEVERA)                                                                          UpdateAloe();
    else if (mSeedType == SeedType::SEED_GHOSTPEPPER)                                                                       UpdateGhostpepper();
    else if (mSeedType == SeedType::SEED_FLYING_GARLIC)                                                                     UpdateFlyingGarlic();

    if (mSubclass == PlantSubClass::SUBCLASS_SHOOTER)
    {
        UpdateShooter();
    }
    if (mDoSpecialCountdown > 0)
    {
        mDoSpecialCountdown--;
        if (mDoSpecialCountdown == 0)
        {
            DoSpecial();
        }
    }
}

void Plant::UpdateFlyingGarlic()
{
    int mTargetY = mBoard->GridToPixelY(4, mRow) - 10;
    mY = (mY + mTargetY) / 2;
    mPlantHealth = 99999;
}

//0x463420
bool Plant::IsPartOfUpgradableTo(SeedType theUpgradedType)
{
    if (theUpgradedType == SeedType::SEED_COBCANNON && mSeedType == SeedType::SEED_KERNELPULT)
    {
        return mBoard->IsValidCobCannonSpot(mPlantCol, mRow) || mBoard->IsValidCobCannonSpot(mPlantCol - 1, mRow);
    }

    return IsUpgradableTo(theUpgradedType);
}

//0x463470
bool Plant::IsUpgradableTo(SeedType theUpgradedType)
{
    if (theUpgradedType == SeedType::SEED_GATLINGPEA && mSeedType == SeedType::SEED_REPEATER)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_WINTERMELON && mSeedType == SeedType::SEED_MELONPULT)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_TWINSUNFLOWER && mSeedType == SeedType::SEED_SUNFLOWER)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_SPIKEROCK && mSeedType == SeedType::SEED_SPIKEWEED)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_COBCANNON && mSeedType == SeedType::SEED_KERNELPULT)
    {
        return mBoard->IsValidCobCannonSpot(mPlantCol, mRow);
    }
    if (theUpgradedType == SeedType::SEED_GOLD_MAGNET && mSeedType == SeedType::SEED_MAGNETSHROOM)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_GLOOMSHROOM && mSeedType == SeedType::SEED_FUMESHROOM)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_ICYFUME && mSeedType == SeedType::SEED_FUMESHROOM)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_SUPERCHOMP && mSeedType == SeedType::SEED_CHOMPER)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_QUEENPEA && mSeedType == SeedType::SEED_SNOWPEA)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_VINENUT && mSeedType == SeedType::SEED_TALLNUT)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_THORNMOSS && mSeedType == SeedType::SEED_SPIKEWEED)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_BRAVESHROOM && mSeedType == SeedType::SEED_SCAREDYSHROOM)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_ECACTUS && mSeedType == SeedType::SEED_CACTUS)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_PLASMAPEA && mSeedType == SeedType::SEED_FLAMEPEA)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_SHOOTINGSTAR && (mSeedType == SeedType::SEED_STARFRUIT || mSeedType == SeedType::SEED_PINKSTAR))
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_FLAMEWOOD && mSeedType == SeedType::SEED_TORCHWOOD)
    {
        return true;
    }
    if (theUpgradedType == SeedType::SEED_CATTAIL && mSeedType == SeedType::SEED_LILYPAD)
    {
        Plant* aPlant = mBoard->GetTopPlantAt(mPlantCol, mRow, PlantPriority::TOPPLANT_ONLY_NORMAL_POSITION);
        return aPlant == nullptr || aPlant->mSeedType != SeedType::SEED_SPROUT;
    }
    return false;
}

//0x4635C0
void Plant::UpdateReanimColor()
{
    if (!IsOnBoard())
        return;

    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim == nullptr)
        return;

    SeedType aSeedType = mBoard->GetSeedTypeInCursor();
    Color aColorOverride = Color::White;
    Color aExtraAdditiveColor = Color::Black;
    bool aEnableExtraAdditiveDraw = false;

    bool isOnGlove = false;
    if (mBoard->mCursorObject->mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_GLOVE)
    {
        Plant* aPlant = mBoard->mPlants.DataArrayTryToGet((unsigned int)mBoard->mCursorObject->mGlovePlantID);
        if (aPlant && aPlant->mPlantCol == mPlantCol && aPlant->mRow == mRow)
        {
            isOnGlove = true;
        }
    }

    if (isOnGlove)
    {
        aColorOverride = Color(128, 128, 128);
    }
    else if (IsPartOfUpgradableTo(aSeedType) && mBoard->CanPlantAt(mPlantCol, mRow, aSeedType) == PLANTING_OK)
    {
        aColorOverride = GetFlashingColor(mBoard->mMainCounter, 90);
    }
    else if (aSeedType == SeedType::SEED_COBCANNON && mSeedType == SeedType::SEED_KERNELPULT && mBoard->CanPlantAt(mPlantCol - 1, mRow, aSeedType) == PLANTING_OK)
    {
        aColorOverride = GetFlashingColor(mBoard->mMainCounter, 90);
    }
    /*else if (mSeedType == SeedType::SEED_EXPLODE_O_NUT)
    {
        aColorOverride = Color(255, 64, 64);
    }*/
    /*if (mSeedType == SeedType::SEED_ICENUT)
    {
        //aColorOverride = Color(100, 160, 255);
        int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_LAWN_MOWER, mRow, 1);
        mApp->AddTodParticle(mX + 8, mY + 13, aRenderPosition, ParticleEffect::PARTICLE_SNOWPEA_PUFF);
    }*/
    else if (mSeedType == SeedType::SEED_GHOSTPEPPER && mTriggered)
    {
        int bAlpha;
        bAlpha = abs(cos(mGhostFlash)) * 255;
        aColorOverride = Color(255, 255, 255, bAlpha);
    }
    else if (mChilledCounter > 0)
    {
        aColorOverride = aColorOverride = Color(75, 75, 255);
        aExtraAdditiveColor = aColorOverride;
        aEnableExtraAdditiveDraw = true;
    }
    else if (mHypnotized)
    {
        aColorOverride = Color(128, 64, 192);
        aExtraAdditiveColor = aColorOverride;
        aEnableExtraAdditiveDraw = true;
    }
    else if (mPlantHealth < mPlantMaxHealth && mBoard->FindAloePlant(mPlantCol, mRow) && mSeedType != SeedType::SEED_ALOEVERA)
    {
        if (mPlantAge % 300 == 0)
        {
            int aRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 1);

            mApp->PlayFoley(FoleyType::FOLEY_COFFEE);

            Reanimation* aHeal = mApp->AddReanimation(mX+10, mY-30, aRenderOrder, ReanimationType::REANIM_HEAL);
            aHeal->OverrideScale(0.5f, 0.5f);
            mEatenFlashCountdown = 25;
        }
    }

    if (mHighlighted)
    {
        aExtraAdditiveColor = ColorAdd(mImitaterType == SeedType::SEED_IMITATER ? Color(255, 255, 255, 92) : Color(255, 255, 255, 196), aBodyReanim->mExtraAdditiveColor);
        aEnableExtraAdditiveDraw = true;
    }
    else if (mBeghouledFlashCountdown > 0)
    {
        int anAlpha = TodAnimateCurve(50, 0, mBeghouledFlashCountdown % 50, 0, 128, TodCurves::CURVE_BOUNCE);
        aExtraAdditiveColor = ColorAdd(Color(255, 255, 255, anAlpha), aExtraAdditiveColor);
        aEnableExtraAdditiveDraw = true;
    }
    else if (mSeedType == SeedType::SEED_SHRINK && mState == PlantState::STATE_SHRINKINGVIOLET_EXPLODING)
    {
        int anAlpha = TodAnimateCurveFloatTime(0.1f, 0.3f, aBodyReanim->mAnimTime, 255, 0, TodCurves::CURVE_LINEAR);
        aExtraAdditiveColor = Color(255, 255, 255, anAlpha);
        aEnableExtraAdditiveDraw = true;
    }
    else if (mBoostCounter > 0)
    {
        int anAlpha = TodAnimateCurve(50, 0, mBoard->mMainCounter % 50, 0, 64, TodCurves::CURVE_BOUNCE);
        aExtraAdditiveColor = Color(255, 255, 255, anAlpha);
        aEnableExtraAdditiveDraw = true;
    }
    else if (mEatenFlashCountdown > 0)
    {
        int aGrayness = ClampInt(mEatenFlashCountdown * 3, 0, mImitaterType == SeedType::SEED_IMITATER ? 128 : 255);
        Color aHighlightColor(aGrayness, aGrayness, aGrayness, 255);
        aExtraAdditiveColor = ColorAdd(aHighlightColor, aExtraAdditiveColor);
        aEnableExtraAdditiveDraw = true;
    }
    else if (mChilledCounter <= 0 && !mHypnotized)
    {
        aBodyReanim->mEnableExtraAdditiveDraw = false;
    }


    aBodyReanim->mColorOverride = aColorOverride;
    aBodyReanim->mExtraAdditiveColor = aExtraAdditiveColor;
    aBodyReanim->mEnableExtraAdditiveDraw = aEnableExtraAdditiveDraw;


    if (mBeghouledFlashCountdown > 0)
    {
        int anAlpha = TodAnimateCurve(50, 0, mBeghouledFlashCountdown % 50, 0, 128, TodCurves::CURVE_BOUNCE);
        aBodyReanim->mExtraOverlayColor = Color(255, 255, 255, anAlpha);
        aBodyReanim->mEnableExtraOverlayDraw = true;
    }
    else
    {
        aBodyReanim->mEnableExtraOverlayDraw = false;
    }

    aBodyReanim->PropogateColorToAttachments();
}

bool Plant::IsOnBoard()
{
    if (!mIsOnBoard)
        return false;

    TOD_ASSERT(mBoard);
    return true;
}

//0x4638F0
bool Plant::IsInPlay()
{
    return IsOnBoard() && mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN && mApp->mGameMode != GameMode::GAMEMODE_TREE_OF_WISDOM && !mIsPreview;
}

//0x463920
void Plant::UpdateReanim()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim == nullptr)
        return;

    UpdateReanimColor();

    /*if (mSeedType == SeedType::SEED_STARFRUIT)
    {
        aBodyReanim->mOverlayMatrix.m10 = sin(180);
        aBodyReanim->mOverlayMatrix.m01 = -sin(180);//

        aBodyReanim->mOverlayMatrix.m00 = cos(180);//stetch l-r (24)
        aBodyReanim->mOverlayMatrix.m11 = cos(180);//stretch u-d (34)
    } */


    float aOffsetX = mShakeOffsetX;
    float aOffsetY = PlantDrawHeightOffset(mBoard, this, mSeedType, mPlantCol, mRow);
    float aScaleX = 1.0f, aScaleY = 1.0f;
    if ((mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BIG_TIME) &&
        (mSeedType == SeedType::SEED_WALLNUT || mSeedType == SeedType::SEED_SUNFLOWER || mSeedType == SeedType::SEED_MARIGOLD))
    {
        aScaleX = 1.5f;
        aScaleY = 1.5f;
        aOffsetX -= 20.0f;
        aOffsetY -= 40.0f;
    }
    if (mSeedType == SeedType::SEED_GIANT_WALLNUT)
    {
        aScaleX = 2.0f;
        aScaleY = 2.0f;
        aOffsetX -= 76.0f;
        aOffsetY -= 64.0f;
    }
    //if (mSeedType == SeedType::SEED_GRAVE && mBoard->mPlantRow[mRow] == PLANTROW_POOL)
    {
        //aOffsetY += 10.0f;
    }
    if (mSeedType == SeedType::SEED_BONKCHOY)
    {
        aScaleX = 1.2f;
        aScaleY = 1.2f;
        aOffsetX += 0.0f;
        aOffsetY += -10.0f;
        if (mIsBackwards)
        {
            aOffsetX += 80.0f * aScaleX;
            aScaleX = -1.0f;
        }
    }
    if (mSeedType == SeedType::SEED_INSTANT_COFFEE)
    {
        aScaleX = 0.8f;
        aScaleY = 0.8f;
        aOffsetX += 12.0f;
        aOffsetY += 10.0f;
    }
    if (mSeedType == SeedType::SEED_POTATOMINE)
    {
        aScaleX = 0.8f;
        aScaleY = 0.8f;
        aOffsetX += 12.0f;
        aOffsetY += 12.0f;
    }
    if (mSeedType == SeedType::SEED_FIRESHROOM)
    {
        aScaleX = 1.0f;
        aScaleY = 1.0f;
        aOffsetX -= 3.0f;
        aOffsetY -= 8.0f;
    }

    if (mSeedType == SeedType::SEED_AMPLI_FLOWER)
    {
        aScaleX *= 0.8f;
        aScaleY *= 0.8f;
        aOffsetX += 5.0f;
        aOffsetY += 10.0f;
    }
    if (mSeedType == SeedType::SEED_FLYING_GARLIC)
    {
        aOffsetX += 8.0f;
        aOffsetY -= 10.0f;
    }

    if (mSeedType == SeedType::SEED_SHRINK)
    {
        aScaleX = 0.8f;
        aScaleY = 0.8f;
        aOffsetX += 10.0f;
        aOffsetY += 15.0f;

        /*if (mDeathCounter > 0)
        {
            float aShrinkNumber = (float)mShrinkCounter;

            aScaleX = 1.0f * aShrinkNumber / 200;
            aScaleY = 1.0f * aShrinkNumber / 200;
            if (mAnimCounter % 6 == 0)
            {
                mY += 1.0f;
                mX += 1.0f;
            }
        }*/
    }
    if (mSeedType == SeedType::SEED_CHARD_GUARD)
    {
        aScaleX = 0.55f;
        aScaleY = 0.55f;
        aOffsetX -= 30.0f;
        aOffsetY -= 60.0f;
    }
    if (mSeedType == SeedType::SEED_OAK_ARCHER)
    {
        aScaleX = 0.8f;
        aScaleY = 0.8f;
        aOffsetX += 10.0f;
        aOffsetY += 15.0f;
    }
    if (mSeedType == SeedType::SEED_ALOEVERA)
    {
        aScaleX = 0.9f;
        aScaleY = 0.9f;
        aOffsetX += 5.0f;
        aOffsetY += 7.5f;
    }
    if (mState == PlantState::STATE_GRAVEBUSTER_EATING)
    {
        aOffsetY += TodAnimateCurveFloat(400, 0, mStateCountdown, 0.0f, 30.0f, TodCurves::CURVE_LINEAR);
    }
    if (mGridItemCounter > 0 && mSeedType == SEED_GRAVE && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_ROOF && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_MOON)
    {
        aOffsetY -= TodAnimateCurveFloat(100, 0, mGridItemCounter*10, -90.0f, 0.0f, TodCurves::CURVE_EASE_IN_OUT);
    }
    if (mWakeUpCounter > 0)
    {
        float aScaleFactor = TodAnimateCurveFloat(70, 0, mWakeUpCounter, 1.0f, 0.8f, TodCurves::CURVE_EASE_SIN_WAVE);
        aScaleY *= aScaleFactor;
        aOffsetY += 80.0f - 80.0f * aScaleFactor;
    }

    if (mToss) {
        aOffsetY -= TodAnimateCurveFloat(50, 0, mMoveTimer, 0.f, 90.0f, TodCurves::CURVE_BOUNCE_SLOW_MIDDLE);
    }

    aBodyReanim->Update();

    if (mSeedType == SeedType::SEED_LEFTPEATER || mSeedType == SeedType::SEED_REVERSE_PEASHOOTER || mSeedType == SeedType::SEED_REVERSE_SNOWPEA || mSeedType == SeedType::SEED_REVERSE_CHOMPER || mSeedType == SeedType::SEED_REVERSE_PUFFSHROOM || mSeedType == SeedType::SEED_REVERSE_FUMESHROOM || mSeedType == SeedType::SEED_REVERSE_CACTUS || mSeedType == SeedType::SEED_REVERSE_STARFRUIT || 
        mSeedType == SeedType::SEED_REVERSE_THREEPEATER || mHypnotized)
    {
        aOffsetX += 80.0f * aScaleX;
        aScaleX *= -1.0f;
    }

    if ((mSeedType == SeedType::SEED_SUNFLOWER || mSeedType == SeedType::SEED_WALLNUT || mSeedType == SeedType::SEED_BLOVER || mSeedType == SeedType::SEED_SUNSHROOM || mSeedType == SeedType::SEED_SQUASH || mSeedType == SeedType::SEED_ICESHROOM || mSeedType == SeedType::SEED_GARLIC) && mApp->mGameMode == GAMEMODE_CHALLENGE_FLIPPED)
    {
        aOffsetX += 80.0f * aScaleX;
        aScaleX *= -1.0f;
    }

    if (mPottedPlantIndex != -1)
    {
        PottedPlant* aPottedPlant = &mApp->mPlayerInfo->mPottedPlant[mPottedPlantIndex];

        if (aPottedPlant->mFacing == PottedPlant::FacingDirection::FACING_LEFT)
        {
            aOffsetX += 80.0f * aScaleX;
            aScaleX *= -1.0f;
        }

        float aOffsetXStart, aOffsetXEnd;
        float aOffsetYStart, aOffsetYEnd;
        float aScaleStart, aScaleEnd;
        if (aPottedPlant->mPlantAge == PottedPlantAge::PLANTAGE_SMALL)
        {
            aOffsetXStart = 20.0f;
            aOffsetXEnd = 20.0f;
            aOffsetYStart = 40.0f;
            aOffsetYEnd = 40.0f;
            aScaleStart = 0.5f;
            aScaleEnd = 0.5f;
        }
        else if (aPottedPlant->mPlantAge == PottedPlantAge::PLANTAGE_MEDIUM)
        {
            aOffsetXStart = 20.0f;
            aOffsetXEnd = 10.0f;
            aOffsetYStart = 40.0f;
            aOffsetYEnd = 20.0f;
            aScaleStart = 0.5f;
            aScaleEnd = 0.75f;
        }
        else
        {
            aOffsetXStart = 10.0f;
            aOffsetXEnd = 0.0f;
            aOffsetYStart = 20.0f;
            aOffsetYEnd = 0.0f;
            aScaleStart = 0.75f;
            aScaleEnd = 1.0f;
        }

        float aAnimatedOffsetX = TodAnimateCurveFloat(100, 0, mStateCountdown, aOffsetXStart, aOffsetXEnd, TodCurves::CURVE_LINEAR);
        float aAnimatedOffsetY = TodAnimateCurveFloat(100, 0, mStateCountdown, aOffsetYStart, aOffsetYEnd, TodCurves::CURVE_LINEAR);
        float aAnimatedScale = TodAnimateCurveFloat(100, 0, mStateCountdown, aScaleStart, aScaleEnd, TodCurves::CURVE_LINEAR);

        aOffsetX += aAnimatedOffsetX * aScaleX;
        aOffsetY += aAnimatedOffsetY * aScaleY;
        aScaleX *= aAnimatedScale;
        aScaleY *= aAnimatedScale;
        aOffsetX += mApp->mZenGarden->ZenPlantOffsetX(aPottedPlant);
        aOffsetY += mApp->mZenGarden->PlantPottedDrawHeightOffset(mSeedType, aScaleY);
    }

    if (mSeedType == SEED_GRAVE && mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES)
    {
        aBodyReanim->SetPosition(aOffsetX + 80.0f, aOffsetY);
        aBodyReanim->OverrideScale(-aScaleX, aScaleY);
    }
    else
    {
        aBodyReanim->SetPosition(aOffsetX, aOffsetY);
        aBodyReanim->OverrideScale(aScaleX, aScaleY);
    }
    


    /*if (mSeedType == SeedType::SEED_BONKCHOY)
    {
        //SPRITE FLIP
        Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
        if (aZombie)
        {
            if (aZombie->mX < mX - 20) {
                aOffsetX += 80.0f * aScaleX;
                aScaleX *= -1.0f;
            }
        }
    }*/
}

//0x463E40
void Plant::Update()
{
    if (mSoundCounter > 0)
    {
        mSoundCounter--;
        if (mSoundCounter == 0) mApp->PlayFoley(FOLEY_THUMP);
    }

    if (mMushroomAge > 0 && !mIsAsleep)
    {
        mMushroomAge--;

        if (mMushroomAge == 150)
        {            
            PlayBodyReanim("anim_end", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);
            mBlinkCountdown = 0;
        }
        else if (mMushroomAge == 0)
        {
            Die();
        }

        if (mMushroomAge <= 255)
        {
            TodParticleSystem* aParticle = mApp->ParticleTryToGet(mParticleID);
            aParticle->OverrideColor(nullptr, Color(255, 255, 102, mMushroomAge));
        }
    }

    if (mGridItemCounter > 0)
    {
        mGridItemCounter--;
    }
    
    if (mMoveOffset > 0)
    {     
        mMoveOffset--;
        mX--;
    }

    if (mShrinkCounter > 0)
    {
        mShrinkCounter--;
    }

    if (mApliflowerCounter > 0)
    {
        mApliflowerCounter--;
    }

    if (mChilledCounter > 0)
    {
        mChilledCounter--;        
        if (mBoard->FindFirePlant(mPlantCol, mRow)) mChilledCounter = 0;
    }

    if (mPlantHealth < mPlantMaxHealth && mBoard->FindAloePlant(mPlantCol, mRow) && mSeedType != SeedType::SEED_ALOEVERA)
    {
        if (mAnimCounter % 4 == 0)
        {
            mPlantHealth++;      
        }
    }

    bool doUpdate = false;
    if (IsOnBoard() && mApp->mGameScene == GameScenes::SCENE_LEVEL_INTRO && mApp->IsWallnutBowlingLevel())
        doUpdate = true;
    else if (IsOnBoard() && mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN)
        doUpdate = true;
    else if (IsOnBoard() && mBoard->mCutScene->ShouldRunUpsellBoard())
        doUpdate = true;
    else if (!IsOnBoard() || mApp->mGameScene == GameScenes::SCENE_PLAYING)
        doUpdate = true;
    //else if (!IsOnBoard() || mBoard->mCutScene->mContinueAfterLoss)
        //doUpdate = true;

    if (doUpdate)
    {
        int skipEverySecondFrame = mChilledCounter % 2; //teleport plant freeze

        if (mChilledCounter > 0 && skipEverySecondFrame == 1) {
            if (mRecentlyEatenCountdown > 0)
            {
                mRecentlyEatenCountdown--;
            }
            if (mEatenFlashCountdown > 0)
            {
                mEatenFlashCountdown--;
            }
            if (mBeghouledFlashCountdown > 0)
            {
                mBeghouledFlashCountdown--;
            }

            if (mSquished)
            {
                mFrame = 0;
            }
        }

        if (skipEverySecondFrame == 0 && mStunnedWeb <= 0 && mStunned <= 0)
        {
            UpdateAbilities();
            Animate();

            if (mPlantHealth < 0)
                Die();

            UpdateReanim();

            if (mBoard != NULL && (mBoard->FindAmpliflower(mPlantCol, mRow) && mSeedType != SeedType::SEED_AMPLI_FLOWER))
            {
                mBoostCounter++;
            }

            if (mBoostCounter > 0)
            {
                UpdateAbilities();
                Animate();

                if (mPlantHealth < 0)
                    Die();

                UpdateReanim();
                mBoostCounter--;
            }
        }
    }

    if (mSeedType == SeedType::SEED_AMPLI_FLOWER)
    {
        UpdateAmpliflower();
    }
    mPlantAge++;

    if (IsInPlay()  && (mSeedType == SeedType::SEED_FUMESHROOM || mSeedType == SeedType::SEED_ICYFUME) && mBoard->StageHasRoof() && mPlantCol <= 4) {
        TodParticleSystem* aParticle = mApp->ParticleTryToGet(mParticleID);
        if (aParticle) {
            for (TodListNode<ParticleEmitterID>* aNode = aParticle->mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
            {
                TodParticleEmitter* aEmitter = aParticle->mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
                for (TodListNode<ParticleID>* aNode = aEmitter->mParticleList.mHead; aNode != nullptr; aNode = aNode->mNext)
                {
                    TodParticle* aParti = aEmitter->mParticleSystem->mParticleHolder->mParticles.DataArrayGet((unsigned int)aNode->mValue);
                    float aSlopeHeightChange = mBoard->GetPosYBasedOnRow(aParti->mPosition.x, mRow) + 47.f - aEmitter->mSystemCenter.y;
                    aParti->mPosition.y += aSlopeHeightChange;
                    aParti->mVelocity.y = -aSlopeHeightChange;
                }
            }
        }
    }
}

void Plant::FreezePlant()
{
      if (!IsFirePlant() && !IsFrozenPlant() && !mBoard->FindFirePlant(mPlantCol, mRow))  mChilledCounter = 1000;
}

//0x463EF0
bool Plant::NotOnGround()
{
    if (mSeedType == SeedType::SEED_SQUASH)
    {
        if (mState == PlantState::STATE_SQUASH_RISING || mState == PlantState::STATE_SQUASH_FALLING || mState == PlantState::STATE_SQUASH_DONE_FALLING)
            return true;
    }

    return mSquished || mOnBungeeState == PlantOnBungeeState::RISING_WITH_BUNGEE || mDead;
}

//0x463F30
Reanimation* Plant::AttachBlinkAnim(Reanimation* theReanimBody)
{
    const PlantDefinition& aPlantDef = GetPlantDefinition(mSeedType);
    LawnApp* aApp = (LawnApp*)gSexyAppBase;
    Reanimation* aAnimToAttach = theReanimBody;
    const char* aTrackToPlay = "anim_blink";
    const char* aTrackToAttach = nullptr;

    if (mSeedType == SeedType::SEED_WALLNUT || mSeedType == SeedType::SEED_TALLNUT || mSeedType == SeedType::SEED_VINENUT || 
        mSeedType == SeedType::SEED_EXPLODE_O_NUT || mSeedType == SeedType::SEED_GIANT_WALLNUT || mSeedType == SeedType::SEED_ICENUT)
    {
        int aHit = Rand(10);
        if (aHit < 1 && theReanimBody->TrackExists("anim_blink_twitch"))
        {
            aTrackToPlay = "anim_blink_twitch";
        }
        else
        {
            aTrackToPlay = aHit < 7 ? "anim_blink_twice" : "anim_blink_thrice";
        }
    }
    else if (mSeedType == SeedType::SEED_THREEPEATER || mSeedType == SeedType::SEED_REVERSE_THREEPEATER)
    {
        int aHit = Rand(3);
        if (aHit == 0)
        {
            aTrackToPlay = "anim_blink1";
            aTrackToAttach = "anim_face1";
            ReanimatorTrackInstance* aTrackInstance = theReanimBody->GetTrackInstanceByName("anim_head1");
            aAnimToAttach = FindReanimAttachment(aTrackInstance->mAttachmentID);
        }
        else if (aHit == 1)
        {
            aTrackToPlay = "anim_blink2";
            aTrackToAttach = "anim_face2";
            ReanimatorTrackInstance* aTrackInstance = theReanimBody->GetTrackInstanceByName("anim_head2");
            aAnimToAttach = FindReanimAttachment(aTrackInstance->mAttachmentID);
        }
        else
        {
            aTrackToPlay = "anim_blink3";
            aTrackToAttach = "anim_face3";
            ReanimatorTrackInstance* aTrackInstance = theReanimBody->GetTrackInstanceByName("anim_head3");
            aAnimToAttach = FindReanimAttachment(aTrackInstance->mAttachmentID);
        }
    }
    else if (mSeedType == SeedType::SEED_SPLITPEA)
    {
        if (Rand(2) == 0)
        {
            aTrackToPlay = "anim_blink";
            aTrackToAttach = "anim_face";
            aAnimToAttach = mApp->ReanimationTryToGet(mHeadReanimID);
        }
        else
        {
            aTrackToPlay = "anim_blink2";
            aTrackToAttach = "anim_face2";
            aAnimToAttach = mApp->ReanimationTryToGet(mHeadReanimID2);
        }
    }
    else if (mSeedType == SeedType::SEED_TWINSUNFLOWER)
    {
        if (Rand(2) == 0)
        {
            aTrackToPlay = "anim_blink";
            aTrackToAttach = "anim_face";
        }
        else
        {
            aTrackToPlay = "anim_blink2";
            aTrackToAttach = "anim_face2";
        }
    }
    else if (mSeedType == SeedType::SEED_PEASHOOTER || mSeedType == SeedType::SEED_SNOWPEA || mSeedType == SeedType::SEED_REPEATER || mSeedType == SeedType::SEED_LEFTPEATER || 
             mSeedType == SeedType::SEED_GATLINGPEA || mSeedType == SeedType::SEED_FLAMEPEA || mSeedType == SeedType::SEED_QUEENPEA || mSeedType == SeedType::SEED_PLASMAPEA ||
             mSeedType == SeedType::SEED_EPEA || mSeedType == SeedType::SEED_BEE_SHOOTER || mSeedType == SeedType::SEED_REVERSE_PEASHOOTER || mSeedType == SeedType::SEED_REVERSE_SNOWPEA)
    {
        if (theReanimBody->TrackExists("anim_stem"))
        {
            ReanimatorTrackInstance* aTrackInstance = theReanimBody->GetTrackInstanceByName("anim_stem");
            aAnimToAttach = FindReanimAttachment(aTrackInstance->mAttachmentID);
        }
        else if (theReanimBody->TrackExists("anim_idle"))
        {
            ReanimatorTrackInstance* aTrackInstance = theReanimBody->GetTrackInstanceByName("anim_idle");
            aAnimToAttach = FindReanimAttachment(aTrackInstance->mAttachmentID);
        }
    }

    if (aAnimToAttach == nullptr)
    {
        TodTrace("Missing head anim");
        return nullptr;
    }

    if (!theReanimBody->TrackExists(aTrackToPlay))
        return nullptr;

    Reanimation* aBlinkReanim = aApp->mEffectSystem->mReanimationHolder->AllocReanimation(0.0f, 0.0f, 0, aPlantDef.mReanimationType);
    aBlinkReanim->SetFramesForLayer(aTrackToPlay);
    aBlinkReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD;
    aBlinkReanim->mAnimRate = 15.0f;
    aBlinkReanim->mColorOverride = theReanimBody->mColorOverride;

    if (aTrackToAttach && aAnimToAttach->TrackExists(aTrackToAttach))
    {
        aBlinkReanim->AttachToAnotherReanimation(aAnimToAttach, aTrackToAttach);
    }
    else if (aAnimToAttach->TrackExists("anim_face"))
    {
        aBlinkReanim->AttachToAnotherReanimation(aAnimToAttach, "anim_face");
    }
    else if (aAnimToAttach->TrackExists("anim_idle"))
    {
        aBlinkReanim->AttachToAnotherReanimation(aAnimToAttach, "anim_idle");
    }
    else
    {
        TodTrace("Missing anim_idle for blink");
    }

    aBlinkReanim->mFilterEffect = theReanimBody->mFilterEffect;
    return aBlinkReanim;
}

//0x464230
void Plant::DoBlink()
{
    mBlinkCountdown = 400 + Rand(400);

    if (NotOnGround() || mShootingCounter != 0)
        return;

    if (mSeedType == SeedType::SEED_POTATOMINE && mState != PlantState::STATE_POTATO_ARMED)
        return;

    if (mState == PlantState::STATE_CACTUS_RISING || mState == PlantState::STATE_CACTUS_HIGH || mState == PlantState::STATE_CACTUS_LOWERING ||
        mState == PlantState::STATE_MAGNETSHROOM_SUCKING || mState == PlantState::STATE_MAGNETSHROOM_CHARGING)
        return;

    EndBlink();
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim == nullptr)
        return;

    if (((mSeedType == SeedType::SEED_TALLNUT || mSeedType == SeedType::SEED_VINENUT) && aBodyReanim->GetImageOverride("anim_idle") == IMAGE_REANIM_TALLNUT_CRACKED2) ||
        (mSeedType == SeedType::SEED_GARLIC && aBodyReanim->GetImageOverride("anim_face") == IMAGE_REANIM_GARLIC_BODY3))
        return;

    if (mSeedType == SeedType::SEED_WALLNUT || mSeedType == SeedType::SEED_TALLNUT || mSeedType == SeedType::SEED_VINENUT || 
        mSeedType == SeedType::SEED_EXPLODE_O_NUT || mSeedType == SeedType::SEED_GIANT_WALLNUT || mSeedType == SeedType::SEED_ICENUT)
    {
        mBlinkCountdown = 1000 + Rand(1000);
    }

    Reanimation* aBlinkReanim = AttachBlinkAnim(aBodyReanim);
    if (aBlinkReanim)
    {
        mBlinkReanimID = mApp->ReanimationGetID(aBlinkReanim);
    }
    aBodyReanim->AssignRenderGroupToPrefix("anim_eye", RENDER_GROUP_HIDDEN);
}

//0x464390
void Plant::EndBlink()
{
    if (mBlinkReanimID != ReanimationID::REANIMATIONID_NULL)
    {
        mApp->RemoveReanimation(mBlinkReanimID);
        mBlinkReanimID = ReanimationID::REANIMATIONID_NULL;

        Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        if (aBodyReanim)
        {
            aBodyReanim->AssignRenderGroupToPrefix("anim_eye", RENDER_GROUP_NORMAL);
        }
    }
}

//0x464410
void Plant::UpdateBlink()
{
    if (mBlinkReanimID != ReanimationID::REANIMATIONID_NULL)
    {
        Reanimation* aBlinkReanim = mApp->ReanimationTryToGet(mBlinkReanimID);
        if (aBlinkReanim == nullptr || aBlinkReanim->mLoopCount > 0)
        {
            EndBlink();
        }
    }

    if (mIsAsleep)
        return;

    if (mBlinkCountdown > 0)
    {
        mBlinkCountdown--;
        if (mBlinkCountdown == 0)
        {
            DoBlink();
        }
    }
}

//0x464480
void Plant::AnimateNuts()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim == nullptr)
        return;

    Image* aCracked1;
    Image* aCracked2;
    const char* aTrackToOverride;
    if (mSeedType == SeedType::SEED_WALLNUT || mSeedType == SeedType::SEED_EXPLODE_O_NUT || mSeedType == SeedType::SEED_CHARD_GUARD)
    {
        aCracked1 = IMAGE_REANIM_WALLNUT_CRACKED1;
        aCracked2 = IMAGE_REANIM_WALLNUT_CRACKED2;
        aTrackToOverride = "anim_face";
    }
    else if (mSeedType == SeedType::SEED_TALLNUT)
    {
        aCracked1 = IMAGE_REANIM_TALLNUT_CRACKED1;
        aCracked2 = IMAGE_REANIM_TALLNUT_CRACKED2;
        aTrackToOverride = "anim_idle";
    }
    else if (mSeedType == SeedType::SEED_DUMMY)
    {
        aCracked1 = IMAGE_REANIM_DUMMY_CRACKED1;
        aCracked2 = IMAGE_REANIM_DUMMY_CRACKED2;
        aTrackToOverride = "anim_face";
    }
    else return;

    int aPosX = mX + 40;
    int aPosY = mY + 10;
    if (mSeedType == SeedType::SEED_TALLNUT)
    {
        aPosY -= 32;
    }

    Image* aImageOverride = aBodyReanim->GetImageOverride(aTrackToOverride);
    if (mPlantHealth < mPlantMaxHealth / 3)
    {
        if (aImageOverride != aCracked2)
        {
            aBodyReanim->SetImageOverride(aTrackToOverride, aCracked2);
            mApp->AddTodParticle(aPosX, aPosY, mRenderOrder + 4, ParticleEffect::PARTICLE_WALLNUT_EAT_LARGE);
        }
    }
    else if (mPlantHealth < mPlantMaxHealth * 2 / 3)
    {
        if (aImageOverride != aCracked1)
        {
            aBodyReanim->SetImageOverride(aTrackToOverride, aCracked1);
            mApp->AddTodParticle(aPosX, aPosY, mRenderOrder + 4, ParticleEffect::PARTICLE_WALLNUT_EAT_LARGE);
        }
    }
    else
    {
        aBodyReanim->SetImageOverride(aTrackToOverride, nullptr);
    }

    if (IsInPlay() && !mApp->IsIZombieLevel())
    {
        if (mRecentlyEatenCountdown > 0)
        {
            aBodyReanim->mAnimRate = 0.1f;
            return;
        }

        if (aBodyReanim->mAnimRate < 1.0f && mOnBungeeState != PlantOnBungeeState::RISING_WITH_BUNGEE)
        {
            aBodyReanim->mAnimRate = RandRangeFloat(10.0f, 15.0f);
        }
    }
}

void Plant::AnimateVineNut()
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim == nullptr)
        return;

    Image* aCracked1;
    Image* aCracked2;
    const char* aTrackToOverride;
    aCracked1 = IMAGE_VINENUT_2_BODY;
    aCracked2 = IMAGE_VINENUT_3_BODY;
    aTrackToOverride = "anim_idle";

    int aPosX = mX + 40;
    int aPosY = mY - 22;
    
    Image* aImageOverride = aBodyReanim->GetImageOverride(aTrackToOverride);
    if (mPlantHealth < mPlantMaxHealth / 3)
    {
        if (aImageOverride != aCracked2)
        {
            aBodyReanim->SetImageOverride("Layer_10", IMAGE_VINENUT_3);
            aBodyReanim->SetImageOverride(aTrackToOverride, aCracked2);
            mApp->AddTodParticle(aPosX, aPosY, mRenderOrder + 4, ParticleEffect::PARTICLE_WALLNUT_EAT_LARGE);
        }
    }
    else if (mPlantHealth < mPlantMaxHealth * 2 / 3)
    {
        if (aImageOverride != aCracked1)
        {
            aBodyReanim->SetImageOverride("Layer_10", IMAGE_VINENUT_2);
            aBodyReanim->SetImageOverride(aTrackToOverride, aCracked1);
            mApp->AddTodParticle(aPosX, aPosY, mRenderOrder + 4, ParticleEffect::PARTICLE_WALLNUT_EAT_LARGE);
        }
    }
    else
    {
        aBodyReanim->SetImageOverride(aTrackToOverride, nullptr);
    }

    if (IsInPlay() && !mApp->IsIZombieLevel())
    {
        if (mRecentlyEatenCountdown > 0)
        {
            aBodyReanim->mAnimRate = 0.1f;
            return;
        }

        if (aBodyReanim->mAnimRate < 1.0f && mOnBungeeState != PlantOnBungeeState::RISING_WITH_BUNGEE)
        {
            aBodyReanim->mAnimRate = RandRangeFloat(10.0f, 15.0f);
        }
    }
}

//0x464680
void Plant::AnimateGarlic()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    Image* aImageOverride = aBodyReanim->GetImageOverride("anim_face");

    if (mPlantHealth < mPlantMaxHealth / 3)
    {
        if (aImageOverride != IMAGE_REANIM_GARLIC_BODY3)
        {
            aBodyReanim->SetImageOverride("anim_face", IMAGE_REANIM_GARLIC_BODY3);
            aBodyReanim->AssignRenderGroupToPrefix("Garlic_stem", RENDER_GROUP_HIDDEN);
        }
    }
    else if (mPlantHealth < mPlantMaxHealth * 2 / 3)
    {
        if (aImageOverride != IMAGE_REANIM_GARLIC_BODY2)
        {
            aBodyReanim->SetImageOverride("anim_face", IMAGE_REANIM_GARLIC_BODY2);
        }
    }
    else
    {
        aBodyReanim->SetImageOverride("anim_face", nullptr);
    }
}

//0x464760
void Plant::AnimatePumpkin()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    Image* aImageOverride = aBodyReanim->GetImageOverride("Pumpkin_front");

    if (mPlantHealth < mPlantMaxHealth / 3)
    {
        if (aImageOverride != IMAGE_REANIM_PUMPKIN_DAMAGE3)
            aBodyReanim->SetImageOverride("Pumpkin_front", IMAGE_REANIM_PUMPKIN_DAMAGE3);
    }
    else if (mPlantHealth < mPlantMaxHealth * 2 / 3)
    {
        if (aImageOverride != IMAGE_REANIM_PUMPKIN_DAMAGE1)
            aBodyReanim->SetImageOverride("Pumpkin_front", IMAGE_REANIM_PUMPKIN_DAMAGE1);
    }
    else
    {
        aBodyReanim->SetImageOverride("Pumpkin_front", nullptr);
    }
}

void Plant::AnimateFireshroom()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    Image* aImageOverride = aBodyReanim->GetImageOverride("FireShroom_cap");

    if (mPlantHealth < mPlantMaxHealth / 3)
    {
        if (aImageOverride != IMAGE_REANIM_FIRESHROOM_CRACKED2)
            aBodyReanim->SetImageOverride("FireShroom_cap", IMAGE_REANIM_FIRESHROOM_CRACKED2);
        aBodyReanim->SetImageOverride("anim_face", IMAGE_REANIM_FIRESHROOM_BODY2);
    }
    else if (mPlantHealth < mPlantMaxHealth * 2 / 3)
    {
        if (aImageOverride != IMAGE_REANIM_FIRESHROOM_CRACKED1)
            aBodyReanim->SetImageOverride("FireShroom_cap", IMAGE_REANIM_FIRESHROOM_CRACKED1);
    }
    else
    {
        aBodyReanim->SetImageOverride("FireShroom_cap", nullptr);
    }
}

void Plant::AnimateChardGuard()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);

    if (mChardGuardLeafs == 2)
    {
        aBodyReanim->SetImageOverride("ChardGuard_back_stem", IMAGE_BLANK);
        aBodyReanim->SetImageOverride("ChardGuard_leaf1", IMAGE_BLANK);
    }
    else if (mChardGuardLeafs == 1)
    {
        aBodyReanim->SetImageOverride("ChardGuard_left_stem", IMAGE_BLANK);
        aBodyReanim->SetImageOverride("ChardGuard_leaf2", IMAGE_BLANK);
    }
    else if (mChardGuardLeafs == 0)
    {
        if ((aBodyReanim->ShouldTriggerTimedEvent(.56f)))
        {
            PlayCustomIdleAnim(aBodyReanim->mDefinition->mFPS, "anim_idle_broken");
        }
    }
}

void Plant::AnimateGrave()
{
    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    Image* aImageOverride = aBodyReanim->GetImageOverride("Stone");
   
    if (mPlantHealth < mPlantMaxHealth / 5)
    {
        if (aImageOverride != IMAGE_STONE5)
        {
            aBodyReanim->SetImageOverride("Stone", IMAGE_STONE5);
            if (mBoard->mPlantRow[mRow] == PLANTROW_POOL) PlayBodyReanim("anim_break5_water", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else if ((mBoard->mBackground == BACKGROUND_5_ROOF || mBoard->mBackground == BACKGROUND_6_BOSS)) PlayBodyReanim("anim_break5_roof", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else PlayBodyReanim("anim_break5", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
        }
    }
    else if (mPlantHealth < mPlantMaxHealth * 2 / 5)
    {
        if (aImageOverride != IMAGE_STONE4)
        {
            aBodyReanim->SetImageOverride("Stone", IMAGE_STONE4);
            if (mBoard->mPlantRow[mRow] == PLANTROW_POOL) PlayBodyReanim("anim_break4_water", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else if ((mBoard->mBackground == BACKGROUND_5_ROOF || mBoard->mBackground == BACKGROUND_6_BOSS)) PlayBodyReanim("anim_break4_roof", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else PlayBodyReanim("anim_break4", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
        }
    }
    else if (mPlantHealth < mPlantMaxHealth * 3 / 5)
    {
        if (aImageOverride != IMAGE_STONE3)
        {
            aBodyReanim->SetImageOverride("Stone", IMAGE_STONE3);
            if (mBoard->mPlantRow[mRow] == PLANTROW_POOL) PlayBodyReanim("anim_break3_water", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else if ((mBoard->mBackground == BACKGROUND_5_ROOF || mBoard->mBackground == BACKGROUND_6_BOSS)) PlayBodyReanim("anim_break3_roof", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else PlayBodyReanim("anim_break3", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
        }
    }
    else if (mPlantHealth < mPlantMaxHealth * 4 / 5)
    {
        if (aImageOverride != IMAGE_STONE2)
        {
            aBodyReanim->SetImageOverride("Stone", IMAGE_STONE2);
            if (mBoard->mPlantRow[mRow] == PLANTROW_POOL)  PlayBodyReanim("anim_break2_water", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else if ((mBoard->mBackground == BACKGROUND_5_ROOF || mBoard->mBackground == BACKGROUND_6_BOSS)) PlayBodyReanim("anim_break2_roof", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
            else PlayBodyReanim("anim_break2", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 13.0f);
        }
    }
    else
    {
        aBodyReanim->SetImageOverride("Stone", nullptr);
    }
}

//0x464820
void Plant::UpdateShooting()
{
    if (NotOnGround() || mShootingCounter == 0)
        return;

    mShootingCounter--;

    if (mShootingCounter == 1 && mSeedType == SEED_ECACTUS) // delay CactusKing shooting animation
    {
        PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
    }
    if (mSeedType == SeedType::SEED_FUMESHROOM && mShootingCounter == 15)
    {
        int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 0);
        AddAttachedParticle(mX + 85, mY + 31, aRenderPosition, ParticleEffect::PARTICLE_FUMECLOUD);
    }
    if (mSeedType == SeedType::SEED_ICYFUME && mShootingCounter == 15)
    {
        int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 0);
        AddAttachedParticle(mX + 85, mY + 31, aRenderPosition, ParticleEffect::PARTICLE_FROSTCLOUD);
    }

    if (mSeedType == SeedType::SEED_GLOOMSHROOM)
    {
        if (mShootingCounter == 136 || mShootingCounter == 108 || mShootingCounter == 80 || mShootingCounter == 52)
        {
            int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 0);
            AddAttachedParticle(mX + 40, mY + 40, aRenderPosition, ParticleEffect::PARTICLE_GLOOMCLOUD);
        }
        if (mShootingCounter == 126 || mShootingCounter == 98 || mShootingCounter == 70 || mShootingCounter == 42)
        {
            Fire(nullptr, mRow, PlantWeapon::WEAPON_PRIMARY);
        }
    }
    else if (mSeedType == SeedType::SEED_GATLINGPEA)
    {
        if (mShootingCounter == 18 || mShootingCounter == 35 || mShootingCounter == 51 || mShootingCounter == 68)
        {
            Fire(nullptr, mRow, PlantWeapon::WEAPON_PRIMARY);
        }
    }
    else if (mSeedType == SeedType::SEED_CATTAIL || mSeedType == SeedType::SEED_BEE_SHOOTER)
    {
        if (mShootingCounter == 19)
        {
            Zombie* aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
            //GridItem* aGriditem = FindTargetGridItem(mRow);
            //if (aZombie)
            {
                Fire(aZombie, mRow, PlantWeapon::WEAPON_PRIMARY);
            }
        }
    }
    else if (mShootingCounter == 1)
    {
        if (mSeedType == SeedType::SEED_THREEPEATER || mSeedType == SeedType::SEED_REVERSE_THREEPEATER)
        {
            int rowAbove = mRow - 1;
            int rowBelow = mRow + 1;
            Reanimation* aHeadReanim2 = mApp->ReanimationGet(mHeadReanimID2);
            Reanimation* aHeadReanim3 = mApp->ReanimationGet(mHeadReanimID3);
            Reanimation* aHeadReanim1 = mApp->ReanimationGet(mHeadReanimID);

            if (aHeadReanim1->mLoopType == ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD)
            {
                Fire(nullptr, rowBelow, PlantWeapon::WEAPON_PRIMARY);
            }
            if (aHeadReanim2->mLoopType == ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD)
            {
                Fire(nullptr, mRow, PlantWeapon::WEAPON_PRIMARY);
            }
            if (aHeadReanim3->mLoopType == ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD)
            {
                Fire(nullptr, rowAbove, PlantWeapon::WEAPON_PRIMARY);
            }
        }
        else if (mSeedType == SeedType::SEED_SPLITPEA)
        {
            Reanimation* aHeadBackReanim = mApp->ReanimationTryToGet(mHeadReanimID2);
            Reanimation* aHeadFrontReanim = mApp->ReanimationTryToGet(mHeadReanimID);
            if (aHeadFrontReanim->mLoopType == ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD)
            {
                Fire(nullptr, mRow, PlantWeapon::WEAPON_PRIMARY);
            }
            if (aHeadBackReanim->mLoopType == ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD)
            {
                Fire(nullptr, mRow, PlantWeapon::WEAPON_SECONDARY);
            }
        }
        else if (mState == PlantState::STATE_CACTUS_LOW)
        {
            Fire(nullptr, mRow, PlantWeapon::WEAPON_SECONDARY);
        }
        else if (mSeedType == SeedType::SEED_CABBAGEPULT || mSeedType == SeedType::SEED_KERNELPULT || mSeedType == SeedType::SEED_MELONPULT || mSeedType == SeedType::SEED_WINTERMELON || 
                 mSeedType == SeedType::SEED_PEPPER || mSeedType == SeedType::SEED_PULTSHROOM || mSeedType == SeedType::SEED_MORTARSHROOM)
        {
            PlantWeapon aPlantWeapon = PlantWeapon::WEAPON_PRIMARY;
            if (mState == PlantState::STATE_KERNELPULT_BUTTER)
            {
                Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
                aBodyReanim->AssignRenderGroupToPrefix("Cornpult_butter", RENDER_GROUP_HIDDEN);
                aBodyReanim->AssignRenderGroupToPrefix("Cornpult_kernal", RENDER_GROUP_NORMAL);
                mState = PlantState::STATE_NOTREADY;
                aPlantWeapon = PlantWeapon::WEAPON_SECONDARY;
            }

            Zombie* aZombie = FindTargetZombie(mRow, aPlantWeapon);
            Fire(aZombie, mRow, aPlantWeapon);
        }
        else
        {
            Fire(nullptr, mRow, PlantWeapon::WEAPON_PRIMARY);
        }

        return;
    }

    if (mShootingCounter != 0)
        return;

    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    Reanimation* aHeadReanim = mApp->ReanimationTryToGet(mHeadReanimID);
    if (mSeedType == SeedType::SEED_THREEPEATER || mSeedType == SeedType::SEED_REVERSE_THREEPEATER)
    {
        Reanimation* aHeadReanim2 = mApp->ReanimationGet(mHeadReanimID2);
        Reanimation* aHeadReanim3 = mApp->ReanimationGet(mHeadReanimID3);

        if (aHeadReanim2->mLoopCount > 0)
        {
            if (aHeadReanim->mLoopType == ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD)
            {
                aHeadReanim->StartBlend(20);
                aHeadReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
                aHeadReanim->SetFramesForLayer("anim_head_idle1");
                aHeadReanim->mAnimRate = aBodyReanim->mAnimRate;
                aHeadReanim->mAnimTime = aBodyReanim->mAnimTime;
            }

            aHeadReanim2->StartBlend(20);
            aHeadReanim2->mLoopType = ReanimLoopType::REANIM_LOOP;
            aHeadReanim2->SetFramesForLayer("anim_head_idle2");
            aHeadReanim2->mAnimRate = aBodyReanim->mAnimRate;
            aHeadReanim2->mAnimTime = aBodyReanim->mAnimTime;

            if (aHeadReanim3->mLoopType == ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD)
            {
                aHeadReanim3->StartBlend(20);
                aHeadReanim3->mLoopType = ReanimLoopType::REANIM_LOOP;
                aHeadReanim3->SetFramesForLayer("anim_head_idle3");
                aHeadReanim3->mAnimRate = aBodyReanim->mAnimRate;
                aHeadReanim3->mAnimTime = aBodyReanim->mAnimTime;
            }
            
            return;
        }
    }
    else if (mSeedType == SeedType::SEED_SPLITPEA)
    {
        Reanimation* aHeadReanim2 = mApp->ReanimationGet(mHeadReanimID2);

        if (aHeadReanim->mLoopCount > 0)
        {
            aHeadReanim->StartBlend(20);
            aHeadReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
            aHeadReanim->SetFramesForLayer("anim_head_idle");
            aHeadReanim->mAnimRate = aBodyReanim->mAnimRate;
            aHeadReanim->mAnimTime = aBodyReanim->mAnimTime;
        }

        if (aHeadReanim2->mLoopCount > 0)
        {
            aHeadReanim2->StartBlend(20);
            aHeadReanim2->mLoopType = ReanimLoopType::REANIM_LOOP;
            aHeadReanim2->SetFramesForLayer("anim_splitpea_idle");
            aHeadReanim2->mAnimRate = aBodyReanim->mAnimRate;
            aHeadReanim2->mAnimTime = aBodyReanim->mAnimTime;
        }

        return;
    }
    else if (mState == PlantState::STATE_CACTUS_HIGH)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            PlayBodyReanim("anim_idlehigh", ReanimLoopType::REANIM_LOOP, 20, 0.0f);

            aBodyReanim->mAnimRate = aBodyReanim->mDefinition->mFPS;
            if (mApp->IsIZombieLevel())
            {
                aBodyReanim->mAnimRate = 0.0f;
            }

            return;
        }
    }
    else if (aHeadReanim)
    {
        if (aHeadReanim->mLoopCount > 0)
        {
            aHeadReanim->StartBlend(20);
            aHeadReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
            aHeadReanim->SetFramesForLayer("anim_head_idle");
            aHeadReanim->mAnimRate = aBodyReanim->mAnimRate;
            aHeadReanim->mAnimTime = aBodyReanim->mAnimTime;
            return;
        }
    }
    else if (mSeedType == SeedType::SEED_COBCANNON)
    {
        if (aBodyReanim->mLoopCount > 0)
        {
            mState = PlantState::STATE_COBCANNON_ARMING;
            mStateCountdown = 3000;
            PlayBodyReanim("anim_unarmed_idle", ReanimLoopType::REANIM_LOOP, 20, aBodyReanim->mDefinition->mFPS);
            return;
        }
    }
    else if (aBodyReanim && aBodyReanim->mLoopCount > 0 && mSeedType != SEED_OAK_ARCHER) //fix empty idle animation
    {
        PlayIdleAnim(aBodyReanim->mDefinition->mFPS);
        return;
    }

    mShootingCounter = 1;
}

//0x464DB0
void Plant::Animate()
{
    if ((mSeedType == SeedType::SEED_CHERRYBOMB || mSeedType == SeedType::SEED_JALAPENO || mSeedType == SeedType::SEED_PICKLEPEPPER || mSeedType == SeedType::SEED_CHILLYPEPPER || mSeedType == SeedType::SEED_LEMON_NADE || mSeedType == SeedType::SEED_BLOODORANGE)
        && mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN)
    {
        mShakeOffsetX = RandRangeFloat(-1.0f, 1.0f);
        mShakeOffsetY = RandRangeFloat(-1.0f, 1.0f);
    }

    if (mRecentlyEatenCountdown > 0)
    {
        mRecentlyEatenCountdown--;
    }
    if (mEatenFlashCountdown > 0)
    {
        mEatenFlashCountdown--;
    }
    if (mBeghouledFlashCountdown > 0)
    {
        mBeghouledFlashCountdown--;
    }

    if (mSquished)
    {
        mFrame = 0;
        return;
    }
    
    if (mSeedType == SeedType::SEED_WALLNUT || mSeedType == SeedType::SEED_TALLNUT || mSeedType == SeedType::SEED_EXPLODE_O_NUT || mSeedType == SeedType::SEED_DUMMY)
    {
        AnimateNuts();
    }
    else if (mSeedType == SeedType::SEED_VINENUT)
    {
        AnimateVineNut();
    }
    else if (mSeedType == SeedType::SEED_GARLIC)
    {
        AnimateGarlic();
    }
    else if (mSeedType == SeedType::SEED_PUMPKINSHELL)
    {
        AnimatePumpkin();
    }
    else if (mSeedType == SeedType::SEED_FIRESHROOM)
    {
        AnimateFireshroom();
    }
    else if (mSeedType == SeedType::SEED_CHARD_GUARD)
    {
        AnimateChardGuard();
    }
    else if (mSeedType == SeedType::SEED_GRAVE)
    {
        AnimateGrave();
    }

    UpdateBlink();

    if (mAnimPing)
    {
        if (mAnimCounter < mFrameLength * mNumFrames - 1)
        {
            mAnimCounter++;
        }
        else
        {
            mAnimPing = false;
            mAnimCounter -= mFrameLength;
        }
    }
    else if (mAnimCounter > 0)
    {
        mAnimCounter--;
    }
    else
    {
        mAnimPing = true;
        mAnimCounter += mFrameLength;
    }
    mFrame = mAnimCounter / mFrameLength;
}

//0x464EF0
float PlantFlowerPotHeightOffset(SeedType theSeedType, float theFlowerPotScale)
{
    float aHeightOffset = -5.0f * theFlowerPotScale;
    float aScaleOffsetFix = 0.0f;

    switch (theSeedType)
    {
    case SeedType::SEED_CHOMPER:
    case SeedType::SEED_REVERSE_CHOMPER:
    case SeedType::SEED_BONKCHOY:
    case SeedType::SEED_SUPERCHOMP:
    case SeedType::SEED_PLANTERN:
    case SeedType::SEED_LUMESHROOM:
        aHeightOffset -= 5.0f;
        break;
    case SeedType::SEED_SCAREDYSHROOM:
    case SeedType::SEED_BRAVESHROOM:
        aHeightOffset += 5.0f;
        aScaleOffsetFix -= 8.0f;
        break;
    case SeedType::SEED_SUNSHROOM:
    case SeedType::SEED_PUFFSHROOM:
    case SeedType::SEED_REVERSE_PUFFSHROOM:
    case SeedType::SEED_PULTSHROOM:
        aScaleOffsetFix -= 4.0f;
        break;
    case SeedType::SEED_HYPNOSHROOM:
    case SeedType::SEED_MAGNETSHROOM:
    case SeedType::SEED_PEASHOOTER:
    case SeedType::SEED_BEE_SHOOTER:
    case SeedType::SEED_REPEATER:
    case SeedType::SEED_LEFTPEATER:
    case SeedType::SEED_REVERSE_PEASHOOTER:
    case SeedType::SEED_REVERSE_SNOWPEA:
    case SeedType::SEED_SNOWPEA:
    case SeedType::SEED_FLAMEPEA:
    case SeedType::SEED_QUEENPEA:
    case SeedType::SEED_PLASMAPEA:
    case SeedType::SEED_EPEA:
    case SeedType::SEED_THREEPEATER:
    case SeedType::SEED_REVERSE_THREEPEATER:
    case SeedType::SEED_SUNFLOWER:
    case SeedType::SEED_MARIGOLD:
    case SeedType::SEED_CABBAGEPULT:
    case SeedType::SEED_MELONPULT:
    case SeedType::SEED_PEPPER:
    case SeedType::SEED_BLOVER:
    case SeedType::SEED_HURRIKALE:
    case SeedType::SEED_SPIKEWEED:
    case SeedType::SEED_THORNMOSS:
    case SeedType::SEED_AMPLI_FLOWER:
        aScaleOffsetFix -= 8.0f;
        break;
    case SeedType::SEED_SEASHROOM:
        aHeightOffset -= 15.0f;
    case SeedType::SEED_POTATOMINE:
        aScaleOffsetFix -= 4.0f;
        break;
    case SeedType::SEED_LILYPAD:
    case SeedType::SEED_TANGLEKELP:
    case SeedType::SEED_PINKSTAR:
        aHeightOffset -= 16.0f;
        aScaleOffsetFix -= 16.0f;
        break;
    case SeedType::SEED_INSTANT_COFFEE:
        aScaleOffsetFix -= 20.0f;
        break;
    }

    return aHeightOffset + (theFlowerPotScale * aScaleOffsetFix - aScaleOffsetFix);
}

//0x465040
float PlantDrawHeightOffset(Board* theBoard, Plant* thePlant, SeedType theSeedType, int theCol, int theRow)
{
    float aHeightOffset = 0.0f;

    bool doFloating = false;
    if (Plant::IsFlying(theSeedType))
    {
        doFloating = false;
    }
    else if (theBoard == nullptr)
    {
        if (Plant::IsAquatic(theSeedType))
        {
            doFloating = true;
        }
    }
    else if (theBoard->IsPoolSquare(theCol, theRow))
    {
        doFloating = true;
    }

    //------------------------------------------------------------------------------------------------------------------

    bool highFloating = false;

    if (thePlant && thePlant->mSeedType == SEED_SHOOTINGSTAR && !thePlant->mSquished)
    {
        highFloating = true;
        doFloating = true;
    }

    //------------------------------------------------------------------------------------------------------------------

    if (doFloating)
    {
        int aCounter;
        if (theBoard)
        {
            aCounter = theBoard->mMainCounter;
        }
        else
        {
            aCounter = gLawnApp->mAppCounter;
        }

        float aPos = theRow * PI + theCol * 0.25f * PI;
        float aTime = aCounter * 2.0f * PI / 200.0f;
        float aFloatingHeight = sin(aPos + aTime) * 2.0f;
        if (highFloating)
            aFloatingHeight *= 2.0f;
        aHeightOffset += aFloatingHeight;
    }

    if (theBoard && (thePlant == nullptr || !thePlant->mSquished))
    {
        Plant* aPot = theBoard->GetFlowerPotAt(theCol, theRow);
        if ((aPot && !aPot->mSquished && theSeedType != SeedType::SEED_FLOWERPOT) || (aPot && !aPot->mSquished && theSeedType != SeedType::SEED_WATERPOT))
        {
            aHeightOffset += PlantFlowerPotHeightOffset(theSeedType, 1.0f);
        }
    }

    if (theSeedType == SeedType::SEED_FLOWERPOT)
    {
        aHeightOffset += 26.0f;
    }
    else if (theSeedType == SeedType::SEED_WATERPOT)
    {
        aHeightOffset += 26.0f;
    }
    else if (theSeedType == SeedType::SEED_LILYPAD)
    {
        aHeightOffset += 25.0f;
    }
    else if (theSeedType == SeedType::SEED_STARFRUIT || theSeedType == SeedType::SEED_REVERSE_STARFRUIT || theSeedType == SeedType::SEED_SHOOTINGSTAR)
    {
        aHeightOffset += 10.0f;
    }
    else if (theSeedType == SeedType::SEED_TANGLEKELP)
    {
        aHeightOffset += 24.0f;
    }
    else if (theSeedType == SeedType::SEED_SEASHROOM)
    {
        aHeightOffset += 28.0f;
    }
    else if (theSeedType == SeedType::SEED_INSTANT_COFFEE)
    {
        aHeightOffset -= 20.0f;
    }
    //else if (Plant::IsFlying(theSeedType))
    //{
    //    aHeightOffset -= 30.0f;
    //}
    else if (theSeedType == SeedType::SEED_CACTUS)
    {
        return aHeightOffset;
    }
    else if (theSeedType == SeedType::SEED_PUMPKINSHELL)
    {
        aHeightOffset += 15.0f;
    }
    else if (theSeedType == SeedType::SEED_PUFFSHROOM || theSeedType == SeedType::SEED_PULTSHROOM || theSeedType == SeedType::SEED_REVERSE_PUFFSHROOM)
    {
        aHeightOffset += 5.0f;
    }
    else if (theSeedType == SeedType::SEED_SCAREDYSHROOM || theSeedType == SeedType::SEED_BRAVESHROOM)
    {
        aHeightOffset -= 14.0f;
    }
    else if (theSeedType == SeedType::SEED_GRAVEBUSTER)
    {
        aHeightOffset -= 40.0f;
    }
    else if (theSeedType == SeedType::SEED_PINKSTAR)
    {
        aHeightOffset -= -20.0f;
    }
    else if (theSeedType == SeedType::SEED_SPIKEWEED || theSeedType == SeedType::SEED_SPIKEROCK || theSeedType == SeedType::SEED_THORNMOSS)
    {
        int aBottomRow = 4;
        if (theBoard && theBoard->StageHas6Rows())
        {
            aBottomRow = 5;
        }

        if (theSeedType == SeedType::SEED_SPIKEROCK || theSeedType == SeedType::SEED_THORNMOSS)
        {
            aHeightOffset += 6.0f;
        }

        if (theBoard && theBoard->GetFlowerPotAt(theCol, theRow) && gLawnApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN)
        {
            aHeightOffset += 5.0f;
        }
        else if (theBoard && theBoard->StageHasRoof())
        {
            aHeightOffset += 15.0f;
        }
        else if (theBoard && theBoard->IsPoolSquare(theCol, theRow))
        {
            aHeightOffset += 0.0f;
        }
        else if (theRow == aBottomRow && theCol >= 7 && theBoard->StageHas6Rows())
        {
            aHeightOffset += 1.0f;
        }
        else if (theRow == aBottomRow && theCol < 7)
        {
            aHeightOffset += 12.0f;
        }
        else
        {
            aHeightOffset += 15.0f;
        }
    }

    return aHeightOffset;
}

//0x465380
void Plant::GetPeaHeadOffset(int& theOffsetX, int& theOffsetY)
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);

    int aTrackIndex = 0;
    if (aBodyReanim->TrackExists("anim_stem"))
    {
        aTrackIndex = aBodyReanim->FindTrackIndex("anim_stem");
    }
    else if(aBodyReanim->TrackExists("anim_idle"))
    {
        aTrackIndex = aBodyReanim->FindTrackIndex("anim_idle");
    }

    ReanimatorTransform aTransform;
    aBodyReanim->GetCurrentTransform(aTrackIndex, &aTransform);
    theOffsetX = aTransform.mTransX;
    theOffsetY = aTransform.mTransY;
}

//0x465460
void Plant::DrawMagnetItems(Graphics* g)
{
    float aOffsetX = 0.0f;
    float aOffsetY = PlantDrawHeightOffset(mBoard, this, mSeedType, mPlantCol, mRow);

    for (int i = 0; i < MAX_MAGNET_ITEMS; i++)
    {
        MagnetItem* aMagnetItem = &mMagnetItems[i];
        if (aMagnetItem->mItemType != MagnetItemType::MAGNET_ITEM_NONE)
        {
            int aCelRow = 0, aCelCol = 0;
            Image* aImage = nullptr;
            float aScale = 0.8f;

            if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_PAIL_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_BUCKET1;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_PAIL_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_BUCKET2;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_PAIL_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_BUCKET3;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_PAIL_GIGA_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_BUCKET1_GIGA;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_PAIL_GIGA_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_BUCKET2_GIGA;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_PAIL_GIGA_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_BUCKET3_GIGA;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_FOOTBALL_HELMET_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_FOOTBALL_HELMET_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_FOOTBALL_HELMET_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_DOOR_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_SCREENDOOR1;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_DOOR_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_SCREENDOOR2;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_DOOR_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_SCREENDOOR3;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_TRASHCAN_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_TRASHCAN1;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_TRASHCAN_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_TRASHCAN2;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_TRASHCAN_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_TRASHCAN3;
            }
            else if (aMagnetItem->mItemType >= MagnetItemType::MAGNET_ITEM_POGO_1 && aMagnetItem->mItemType <= MagnetItemType::MAGNET_ITEM_POGO_3)
            {
                aCelCol = (int)aMagnetItem->mItemType - (int)MagnetItemType::MAGNET_ITEM_POGO_1;
                aImage = IMAGE_ZOMBIEPOGO;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_LADDER_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_LADDER_1;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_LADDER_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_LADDER_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_LADDER_PLACED)
            {
                aImage = IMAGE_REANIM_ZOMBIE_LADDER_5;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_JACK_IN_THE_BOX)
            {
                aImage = IMAGE_REANIM_ZOMBIE_JACKBOX_BOX;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_PICK_AXE)
            {
                aImage = IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_GIGA_FOOTBALL_HELMET_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET1;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_GIGA_FOOTBALL_HELMET_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET2;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_GIGA_FOOTBALL_HELMET_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET3;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_GLADIANTUAR_HELMET_1)
            {
                aImage = IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET1;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_GLADIANTUAR_HELMET_2)
            {
                aImage = IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET2;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_GLADIANTUAR_HELMET_3)
            {
                aImage = IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET3;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_SILVER_COIN)
            {
                aScale = 1.0f;
                aImage = IMAGE_REANIM_COIN_SILVER_DOLLAR;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_GOLD_COIN)
            {
                aScale = 1.0f;
                aImage = IMAGE_REANIM_COIN_GOLD_DOLLAR;
            }
            else if (aMagnetItem->mItemType == MagnetItemType::MAGNET_ITEM_DIAMOND)
            {
                aScale = 1.0f;
                aImage = IMAGE_REANIM_DIAMOND;
            }
            else
            {
                TOD_ASSERT();
            }

            if (aScale == 1.0f)
            {
                g->DrawImageCel(aImage, aMagnetItem->mPosX - mX + aOffsetX, aMagnetItem->mPosY - mY + aOffsetY, aCelCol, aCelRow);
            }
            else
            {
                TodDrawImageCelScaledF(g, aImage, aMagnetItem->mPosX - mX + aOffsetX, aMagnetItem->mPosY - mY + aOffsetY, aCelCol, aCelRow, aScale, aScale);
            }
        }
    }
}

Image* Plant::GetImage(SeedType theSeedType)
{
    Image** aImages = GetPlantDefinition(theSeedType).mPlantImage;
    return aImages ? aImages[0] : nullptr;
}

//0x465680
void Plant::DrawShadow(Sexy::Graphics* g, float theOffsetX, float theOffsetY)
{
    if (mSeedType == SeedType::SEED_LILYPAD || mSeedType == SeedType::SEED_STARFRUIT || mSeedType == SeedType::SEED_TANGLEKELP || mSeedType == SeedType::SEED_GRAVE ||
        mSeedType == SeedType::SEED_SEASHROOM || mSeedType == SeedType::SEED_COBCANNON || mSeedType == SeedType::SEED_SPIKEWEED || mSeedType == SeedType::SEED_SHOOTINGSTAR ||
        mSeedType == SeedType::SEED_SPIKEROCK || mSeedType == SeedType::SEED_GRAVEBUSTER || mSeedType == SeedType::SEED_CATTAIL || 
        mSeedType == SeedType::SEED_PINKSTAR || mSeedType == SeedType::SEED_THORNMOSS || mSeedType == SeedType::SEED_REVERSE_STARFRUIT ||
        mOnBungeeState == PlantOnBungeeState::RISING_WITH_BUNGEE)
        return;

    if (IsOnBoard() && mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN && mApp->mZenGarden->mGardenType == GardenType::GARDEN_MAIN)
        return;

    if (mIsPreview)  return; // Preview plants don't have shadows... we use beghauled shadow

    if (IsInPlay() && mSeedType == SeedType::SEED_SHRINK && mState == PlantState::STATE_SHRINKINGVIOLET_EXPLODED)
    {
        Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        if (aBodyReanim && aBodyReanim->mAnimTime >= 0.5f) {
            return;
        }
    }

    int aShadowType = 0;
    float aShadowOffsetX = -3.0f;
    float aShadowOffsetY = 51.0f;
    float aScale = 1.0f;
    if (mBoard && mBoard->StageIsNight())
    {
        aShadowType = 1;
    }

    if (mSeedType == SeedType::SEED_SQUASH)
    {
        if (mBoard)
        {
            aShadowOffsetY += mBoard->GridToPixelY(mPlantCol, mRow) - mY;
        }
        aShadowOffsetY += 5.0f;
    }
    /*else if (mSeedType == SeedType::SEED_SHRINK)
    {
        if (mDeathCounter > 0)
        {
            aScale = 0.0f;
        }
    }*/
    else if (mSeedType == SeedType::SEED_PUFFSHROOM || mSeedType == SeedType::SEED_PULTSHROOM || mSeedType == SeedType::SEED_REVERSE_PUFFSHROOM)
    {
        aScale = 0.5f;
        aShadowOffsetY = 42.0f;
    }
    else if (mSeedType == SeedType::SEED_SUNSHROOM)
    {
        aShadowOffsetY = 42.0f;
        if (mState == PlantState::STATE_SUNSHROOM_SMALL)
        {
            aScale = 0.5f;
        }
        else if (mState == PlantState::STATE_SUNSHROOM_GROWING)
        {
            Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
            aScale = 0.5f + 0.5f * aBodyReanim->mAnimTime;
        }
    }
    else if (mSeedType == SeedType::SEED_UMBRELLA)
    {
        aScale = 0.5f;
        aShadowOffsetX = -7.0f;
        aShadowOffsetY = 52.0f;
    }
    else if (mSeedType == SeedType::SEED_FUMESHROOM || mSeedType == SeedType::SEED_ICYFUME || mSeedType == SeedType::SEED_GLOOMSHROOM)
    {
        aScale = 1.3f;
        aShadowOffsetY = 47.0f;
    }
    else if (mSeedType == SeedType::SEED_CABBAGEPULT || mSeedType == SeedType::SEED_MELONPULT || mSeedType == SeedType::SEED_WINTERMELON || mSeedType == SeedType::SEED_PEPPER)
    {
        aShadowOffsetY = 47.0f;
    }
    else if (mSeedType == SeedType::SEED_KERNELPULT)
    {
        aShadowOffsetX = 0.0f;
        aShadowOffsetY = 47.0f;
    }
    else if (mSeedType == SeedType::SEED_SCAREDYSHROOM || mSeedType == SeedType::SEED_BRAVESHROOM)
    {
        aShadowOffsetX = -9.0f;
        aShadowOffsetY = 55.0f;
    }
    else if (mSeedType == SeedType::SEED_CHOMPER || mSeedType == SeedType::SEED_CHOMPER)
    {
        aShadowOffsetX = -21.0f;
        aShadowOffsetY = 57.0f;
    }
    else if (mSeedType == SeedType::SEED_SUPERCHOMP)
    {
        aShadowOffsetX = -21.0f;
        aShadowOffsetY = 57.0f;
    }
    else if (mSeedType == SeedType::SEED_FLOWERPOT || mSeedType == SeedType::SEED_WATERPOT)
    {
        aShadowOffsetX = -4.0f;
        aShadowOffsetY = 46.0f;
    }
    else if (mSeedType == SeedType::SEED_TALLNUT || mSeedType == SeedType::SEED_VINENUT)
    {
        aShadowOffsetY = 54.0f;
        aScale = 1.3f;
    }
    else if (mSeedType == SeedType::SEED_PUMPKINSHELL)
    {
        aShadowOffsetY = 46.0f;
        aScale = 1.4f;
    }
    else if (mSeedType == SeedType::SEED_CACTUS)
    {
        aShadowOffsetX = -8.0f;
        aShadowOffsetY = 50.0f;
    }
    else if (mSeedType == SeedType::SEED_PLANTERN)
    {
        aShadowOffsetY = 57.0f;
    }
    else if (mSeedType == SeedType::SEED_INSTANT_COFFEE)
    {
        aShadowOffsetY = 71.0f;
    }
    else if (mSeedType == SeedType::SEED_GIANT_WALLNUT)
    {
        aShadowOffsetX = -33.0f;
        aShadowOffsetY = 56.0f;
        aScale = 1.7f;
    }

    if (Plant::IsFlying(mSeedType))
    {
        aShadowOffsetY += 10.0f;
        if (mBoard && (mBoard->GetTopPlantAt(mPlantCol, mRow, TOPPLANT_ONLY_NORMAL_POSITION) || mBoard->GetTopPlantAt(mPlantCol, mRow, TOPPLANT_ONLY_PUMPKIN)))
            return;
    }

    if (aShadowType == 0)
    {
        TodDrawImageCelCenterScaledF(g, IMAGE_PLANTSHADOW, theOffsetX + aShadowOffsetX, theOffsetY + aShadowOffsetY, 0, aScale, aScale);
    }
    else
    {
        TodDrawImageCelCenterScaledF(g, IMAGE_PLANTSHADOW2, theOffsetX + aShadowOffsetX, theOffsetY + aShadowOffsetY, 0, aScale, aScale);
    }
}

//0x465A90
void Plant::Draw(Graphics* g)
{
    float aOffsetX = 0.0f;
    float aOffsetY = PlantDrawHeightOffset(mBoard, this, mSeedType, mPlantCol, mRow);
    if (Plant::IsFlying(mSeedType) && mSquished)
    {
        aOffsetY += 30.0f;
    }

    int aImageIndex = mFrame;
    Image* aPlantImage = Plant::GetImage(mSeedType);

    if (mSquished)
    {
        if (mSeedType == SeedType::SEED_FLOWERPOT || mSeedType == SeedType::SEED_WATERPOT)
        {
            aOffsetY -= 15.0f;
        }
        if (mSeedType == SeedType::SEED_INSTANT_COFFEE)
        {
            aOffsetY -= 20.0f;
        }

        g->SetScale(1.0f, 0.25f, 0.0f, 0.0f);
        DrawSeedType(g, mSeedType, mImitaterType, DrawVariation::VARIATION_NORMAL, aOffsetX, 60.0f + aOffsetY);
        g->SetScale(1.0f, 1.0f, 0.0f, 0.0f);
    }
    else
    {
        bool aDrawPumpkinBack = false;
        Plant* aPumpkin = nullptr;

        if (IsOnBoard())
        {
            aPumpkin = mBoard->GetPumpkinAt(mPlantCol, mRow);
            if (aPumpkin)
            {
                Plant* aPlantInPumpkin = mBoard->GetTopPlantAt(mPlantCol, mRow, PlantPriority::TOPPLANT_ONLY_NORMAL_POSITION);
                if (aPlantInPumpkin)
                {
                    if (aPlantInPumpkin->mRenderOrder > aPumpkin->mRenderOrder || aPlantInPumpkin->mOnBungeeState == GETTING_GRABBED_BY_BUNGEE)
                    {
                        aPlantInPumpkin = nullptr;
                    }
                }

                if (aPlantInPumpkin == this)
                {
                    aDrawPumpkinBack = true;
                }
                if (aPlantInPumpkin == nullptr && mSeedType == SeedType::SEED_PUMPKINSHELL)
                {
                    aDrawPumpkinBack = true;
                }
            }
            else if (mSeedType == SeedType::SEED_PUMPKINSHELL)
            {
                aDrawPumpkinBack = true;
                aPumpkin = this;
            }
        }
        else if (mSeedType == SeedType::SEED_PUMPKINSHELL)
        {
            aDrawPumpkinBack = true;
            aPumpkin = this;
        }

        DrawShadow(g, aOffsetX, aOffsetY);

        if (Plant::IsFlying(mSeedType))
        {
            int aCounter;
            if (IsOnBoard())
            {
                aCounter = mBoard->mMainCounter;
            }
            else
            {
                aCounter = mApp->mAppCounter;
            }

            float aTime = (mRow * 97 + mPlantCol * 61 + aCounter) * 0.03f;
            float aWave = sin(aTime) * 2.0f;
            aOffsetY += aWave;
        }

        if (aDrawPumpkinBack)
        {
            Reanimation* aPumpkinReanim = mApp->ReanimationGet(aPumpkin->mBodyReanimID);
            Graphics aPumpkinGraphics(*g);
            aPumpkinGraphics.mTransX += aPumpkin->mX - mX;
            aPumpkinGraphics.mTransY += aPumpkin->mY - mY;
            aPumpkinReanim->DrawRenderGroup(&aPumpkinGraphics, 1);
        }

        aOffsetX += mShakeOffsetX;
        aOffsetY += mShakeOffsetY;
        if (IsInPlay() && mApp->IsIZombieLevel())
        {
            mBoard->mChallenge->IZombieDrawPlant(g, this);
        }
        else if (mBodyReanimID != ReanimationID::REANIMATIONID_NULL)
        {
            Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
            if (aBodyReanim)
            {
                if (!mApp->Is3DAccelerated() && mSeedType == SeedType::SEED_FLOWERPOT && IsOnBoard() &&
                    aBodyReanim->mAnimRate == 0.0f && aBodyReanim->IsAnimPlaying("anim_idle"))
                {
                    mApp->mReanimatorCache->DrawCachedPlant(g, aOffsetX, aOffsetY, mSeedType, DrawVariation::VARIATION_NORMAL);
                }
                else
                {
                    aBodyReanim->Draw(g);
                }
            }
        }
        else
        {
            SeedType aSeedType = SeedType::SEED_NONE;
            if (mBoard)
            {
                aSeedType = mBoard->GetSeedTypeInCursor();
            }

            if (IsPartOfUpgradableTo(aSeedType) && mBoard->CanPlantAt(mPlantCol, mRow, aSeedType) == PlantingReason::PLANTING_OK)
            {
                g->SetColorizeImages(true);
                g->SetColor(GetFlashingColor(mBoard->mMainCounter, 90));
            }
            else if (aSeedType == SeedType::SEED_COBCANNON && mBoard->CanPlantAt(mPlantCol - 1, mRow, aSeedType) == PlantingReason::PLANTING_OK)
            {
                g->SetColorizeImages(true);
                g->SetColor(GetFlashingColor(mBoard->mMainCounter, 90));
            }
            else if (mBoard && mBoard->mTutorialState == TutorialState::TUTORIAL_SHOVEL_DIG)
            {
                g->SetColorizeImages(true);
                g->SetColor(GetFlashingColor(mBoard->mMainCounter, 90));
            }

            TodDrawImageCelF(g, aPlantImage, aOffsetX, aOffsetY, aImageIndex, 0);
            g->SetColorizeImages(false);
            if (mHighlighted)
            {
                g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
                g->SetColorizeImages(true);
                g->SetColor(Color(255, 255, 255, 196));
                TodDrawImageCelF(g, aPlantImage, aOffsetX, aOffsetY, aImageIndex, 0);
                g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
                g->SetColorizeImages(false);
            }
            else if (mEatenFlashCountdown > 0)
            {
                g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
                g->SetColorizeImages(true);
                g->SetColor(Color(255, 255, 255, ClampInt(mEatenFlashCountdown * 3, 0, 255)));
                TodDrawImageCelF(g, aPlantImage, aOffsetX, aOffsetY, aImageIndex, 0);
                g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
                g->SetColorizeImages(false);
            }
        }

        if (mSeedType == SeedType::SEED_MAGNETSHROOM && !DrawMagnetItemsOnTop())
        {
            DrawMagnetItems(g);
        }

        if (mStunnedWeb > 0)
        {
            TodDrawImageScaledF(g, IMAGE_NET, 0, 0, 1, 1);
            if(!mBoard->mPaused) mStunnedWeb--;
        }
        if (mStunned > 0)
        {
            if (!mBoard->mPaused) mStunned--;
        }
    }
}

//0x4660B0
void Plant::DrawSeedType(Graphics* g, SeedType theSeedType, SeedType theImitaterType, DrawVariation theDrawVariation, float thePosX, float thePosY)
{
    Graphics aSeedG(*g);
    int aCelRow = 0;
    int aCelCol = 2;
    float aOffsetX = 0.0f;
    float aOffsetY = 0.0f;
    SeedType aSeedType = theSeedType;
    DrawVariation aDrawVariation = theDrawVariation;

    if (theSeedType == SeedType::SEED_IMITATER && theImitaterType != SeedType::SEED_NONE)
    {
        aSeedType = theImitaterType;
        aDrawVariation = DrawVariation::VARIATION_IMITATER;
        if (theImitaterType == SeedType::SEED_HYPNOSHROOM || theImitaterType == SeedType::SEED_SQUASH || theImitaterType == SeedType::SEED_POTATOMINE ||
            theImitaterType == SeedType::SEED_GARLIC || theImitaterType == SeedType::SEED_LILYPAD)
            aDrawVariation = DrawVariation::VARIATION_IMITATER_LESS;
    }
    else if (theDrawVariation == DrawVariation::VARIATION_NORMAL && theSeedType == SeedType::SEED_TANGLEKELP)
    {
        aDrawVariation = DrawVariation::VARIATION_AQUARIUM;
    }

    if (((LawnApp*)gSexyAppBase)->mGameMode == GameMode::GAMEMODE_CHALLENGE_BIG_TIME &&
        (aSeedType == SeedType::SEED_WALLNUT || aSeedType == SeedType::SEED_SUNFLOWER || aSeedType == SeedType::SEED_MARIGOLD))
    {
        aSeedG.mScaleX *= 1.5f;
        aSeedG.mScaleY *= 1.5f;
        aOffsetX = -20.0f;
        aOffsetY = -40.0f;
    }
    if (aSeedType == SeedType::SEED_LEFTPEATER || aSeedType == SeedType::SEED_REVERSE_PEASHOOTER || aSeedType == SeedType::SEED_REVERSE_SNOWPEA || aSeedType == SeedType::SEED_REVERSE_CHOMPER || aSeedType == SeedType::SEED_REVERSE_PUFFSHROOM || aSeedType == SeedType::SEED_REVERSE_FUMESHROOM || aSeedType == SeedType::SEED_REVERSE_CACTUS || aSeedType == SeedType::SEED_REVERSE_STARFRUIT ||
        aSeedType == SeedType::SEED_REVERSE_THREEPEATER)
    {
        aOffsetX += aSeedG.mScaleX * 80.0f;
        aSeedG.mScaleX *= -1.0f;
    }

    if ((aSeedType == SeedType::SEED_SUNFLOWER || aSeedType == SeedType::SEED_WALLNUT || aSeedType == SeedType::SEED_BLOVER || aSeedType == SeedType::SEED_SUNSHROOM || aSeedType == SeedType::SEED_SQUASH || aSeedType == SeedType::SEED_ICESHROOM || aSeedType == SeedType::SEED_GARLIC) && ((LawnApp*)gSexyAppBase)->mGameMode == GAMEMODE_CHALLENGE_FLIPPED && ((LawnApp*)gSexyAppBase)->mBoard)
    {
        aOffsetX += aSeedG.mScaleX * 80.0f;
        aSeedG.mScaleX *= -1.0f;
    }

    if (aSeedType == SeedType::SEED_OAK_ARCHER)
    {
        aSeedG.mScaleX *= 0.8f;
        aSeedG.mScaleY *= 0.8f;
        aOffsetX += 10.0f;
        aOffsetY += 15.0f;
    }

    if (aSeedType == SeedType::SEED_BONKCHOY)
    {
        aSeedG.mScaleX *= 1.2f;
        aSeedG.mScaleY *= 1.2f;
        aOffsetX += 0.0f;
        aOffsetY += -10.0f;
    }

    if (aSeedType == SeedType::SEED_ALOEVERA)
    {
        aSeedG.mScaleX *= 0.9f;
        aSeedG.mScaleY *= 0.9f;
        aOffsetX += 5.0f;
        aOffsetY += 7.5f;
    }

    if (aSeedType == SeedType::SEED_SHRINK)
    {
        aSeedG.mScaleX *= 0.8f;
        aSeedG.mScaleY *= 0.8f;
        aOffsetX += 10.0f;
        aOffsetY += 15.0f;
    }

    if (aSeedType == SeedType::SEED_AMPLI_FLOWER)
    {
        aSeedG.mScaleX *= 0.8f;
        aSeedG.mScaleY *= 0.8f;
        aOffsetX += 5.0f;
        aOffsetY += 10.0f;
    }

    if (aSeedType == SeedType::SEED_CHARD_GUARD)
    {
        aSeedG.mScaleX *= 0.55f;
        aSeedG.mScaleY *= 0.55f;
        aOffsetX -= 30.0f;
        aOffsetY -= 60.0f;
    }

    if (Challenge::IsZombieSeedType(aSeedType))
    {
        ZombieType aZombieType = Challenge::IZombieSeedTypeToZombieType(aSeedType);
        gLawnApp->mReanimatorCache->DrawCachedZombie(&aSeedG, thePosX + aOffsetX, thePosY + aOffsetY, aZombieType);
    }
    else
    {
        const PlantDefinition& aPlantDef = GetPlantDefinition(aSeedType);

        if (aSeedType == SeedType::SEED_GIANT_WALLNUT)
        {
            aSeedG.mScaleX *= 1.4f;
            aSeedG.mScaleY *= 1.4f;
            TodDrawImageScaledF(&aSeedG, IMAGE_REANIM_WALLNUT_BODY, thePosX - 53.0f, thePosY - 56.0f, aSeedG.mScaleX, aSeedG.mScaleY);
        }
        else if (aPlantDef.mReanimationType != ReanimationType::REANIM_NONE)
        {
            gLawnApp->mReanimatorCache->DrawCachedPlant(&aSeedG, thePosX + aOffsetX, thePosY + aOffsetY, aSeedType, aDrawVariation);
        }
        else
        {
            if (aSeedType == SeedType::SEED_KERNELPULT)
            {
                aCelRow = 2;
            }
            else if (aSeedType == SeedType::SEED_TWINSUNFLOWER)
            {
                aCelRow = 1;
            }

            Image* aPlantImage = Plant::GetImage(aSeedType);
            if (aPlantImage->mNumCols <= 2)
            {
                aCelCol = aPlantImage->mNumCols - 1;
            }

            TodDrawImageCelScaledF(&aSeedG, aPlantImage, thePosX + aOffsetX, thePosY + aOffsetY, aCelCol, aCelRow, aSeedG.mScaleX, aSeedG.mScaleY);
        }
    }
}

//0x466390
void Plant::MouseDown(int x, int y, int theClickCount)
{
    if (theClickCount < 0)
        return;

    if (mState == PlantState::STATE_COBCANNON_READY)
    {
        mBoard->ClearCursor();
        mBoard->mCursorObject->mType = SeedType::SEED_NONE;
        mBoard->mCursorObject->mCursorType = CursorType::CURSOR_TYPE_COBCANNON_TARGET;
        mBoard->mCursorObject->mSeedBankIndex = -1;
        mBoard->mCursorObject->mCoinID = CoinID::COINID_NULL;
        mBoard->mCursorObject->mCobCannonPlantID = (PlantID)mBoard->mPlants.DataArrayGetID(this);
        mBoard->mCobCannonCursorDelayCounter = 30;
        mBoard->mCobCannonMouseX = x;
        mBoard->mCobCannonMouseY = y;
    }
}

//0x466420
void Plant::IceZombies()
{
    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        aZombie->HitIceTrap();
    }

    mBoard->mIceTrapCounter = 300;
    TodParticleSystem* aPoolSparklyParticle = mApp->ParticleTryToGet(mBoard->mPoolSparklyParticleID);
    if (aPoolSparklyParticle)
    {
        aPoolSparklyParticle->mDontUpdate = false;
    }

    Zombie* aBossZombie = mBoard->GetBossZombie();
    if (aBossZombie)
    {
        aBossZombie->BossDestroyFireball();
    }
}

//0x4664B0
void Plant::BurnRow(int theRow)
{
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if ((aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mRow == theRow) && aZombie->EffectedByDamage(aDamageRangeFlags) && aZombie->mZombieType != ZOMBIE_TARGET)
        {
            aZombie->RemoveColdEffects();
            aZombie->ApplyBurn(1800);
            if (aZombie->mHelmType == HelmType::HELMTYPE_ICE) aZombie->ApplyBurn(1800);
        }
    }

    GridItem* aGridItem = nullptr;
    while (mBoard->IterateGridItems(aGridItem))
    {
        if (aGridItem->mGridY == theRow && (aGridItem->mGridItemType == GridItemType::GRIDITEM_LADDER || aGridItem->mGridItemType == GridItemType::GRIDITEM_BUSH || aGridItem->mGridItemType == GridItemType::GRIDITEM_WOOD_LOG))
        {
            aGridItem->GridItemDie();
            mApp->AddReanimation(mBoard->GridToPixelX(aGridItem->mGridX, aGridItem->mGridY) - 30.0f, mBoard->GridToPixelY(aGridItem->mGridX, aGridItem->mGridY) - 15.0f, aGridItem->mRenderOrder, REANIM_ZOMBIE_CHARRED_BUSH);
        }
    }

    Zombie* aBossZombie = mBoard->GetBossZombie();
    if (aBossZombie && aBossZombie->mFireballRow == theRow)
    {
        // 注：原版中将 Zombie::BossDestroyIceballInRow(int) 函数改为了 Zombie::BossDestroyIceball()，冰球是否位于目标行的判断则移动至此处进行
        aBossZombie->BossDestroyIceballInRow(theRow);
    }
}

void Plant::BurnColumn(int theColumn)
{
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if ((aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || (aZombie->mPosX > 80 * (theColumn-0.5) && aZombie->mPosX < 80 * (theColumn + 1))) && aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            aZombie->RemoveColdEffects();
            aZombie->ApplyBurn(1800);
            if (aZombie->mHelmType == HelmType::HELMTYPE_ICE) aZombie->ApplyBurn(1800);
        }
    }

    GridItem* aGridItem = nullptr;
    while (mBoard->IterateGridItems(aGridItem))
    {
        if (aGridItem->mGridX == theColumn && (aGridItem->mGridItemType == GridItemType::GRIDITEM_LADDER || aGridItem->mGridItemType == GridItemType::GRIDITEM_BUSH || aGridItem->mGridItemType == GridItemType::GRIDITEM_WOOD_LOG))
        {
            aGridItem->GridItemDie();
            mApp->AddReanimation(mBoard->GridToPixelX(aGridItem->mGridX, aGridItem->mGridY) - 30.0f, mBoard->GridToPixelY(aGridItem->mGridX, aGridItem->mGridY) - 15.0f, aGridItem->mRenderOrder, REANIM_ZOMBIE_CHARRED_BUSH);
        }
    }
    Zombie* aBossZombie = mBoard->GetBossZombie();
    if (aBossZombie)
    {
        aBossZombie->BossDestroyIceball(theColumn);
   }
}

void Plant::FreezeRow(int theRow)
{
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if ((aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mRow == theRow) && aZombie->EffectedByDamage(aDamageRangeFlags) && aZombie->mZombieType != ZOMBIE_TARGET)
        {
            aZombie->HitIceTrap();
            if (aZombie->mZombieType == ZombieType::ZOMBIE_NEWSPAPER || aZombie->mZombieType == ZombieType::ZOMBIE_SCREENDOOR || aZombie->mZombieType == ZombieType::ZOMBIE_TRASHCAN || aZombie->mZombieType == ZombieType::ZOMBIE_LADDER) aZombie->TakeBodyDamage(900, 0U);
            else aZombie->TakeDamage(900, 0U);
        }
    }

    GridItem* aGridItem = nullptr;
    while (mBoard->IterateGridItems(aGridItem))
    {
        if (aGridItem->mGridY == theRow && aGridItem->mGridItemType == GridItemType::GRIDITEM_LADDER)
        {
            aGridItem->GridItemDie();
        }
    }

    Zombie* aBossZombie = mBoard->GetBossZombie();
    if (aBossZombie && aBossZombie->mFireballRow == theRow)
    {
        // 注：原版中将 Zombie::BossDestroyIceballInRow(int) 函数改为了 Zombie::BossDestroyIceball()，冰球是否位于目标行的判断则移动至此处进行
        aBossZombie->BossDestroyFireball();
    }
}

bool Plant::IsFirePlant()
{
    if (mSeedType == SeedType::SEED_TORCHWOOD || mSeedType == SeedType::SEED_FLAMEWOOD || mSeedType == SeedType::SEED_PEPPER || mSeedType == SeedType::SEED_FLAMEPEA || mSeedType == SeedType::SEED_PLASMAPEA || 
        mSeedType == SeedType::SEED_JALAPENO || mSeedType == SeedType::SEED_PICKLEPEPPER || mSeedType == SeedType::SEED_FIRESHROOM) return true;   
    else return false;
}

bool Plant::IsFrozenPlant()
{
    if (mSeedType == SeedType::SEED_QUEENPEA) return true;
    else return false;
}

//0x4665B0
void Plant::BlowAwayFliers(int theX, int theRow)
{
    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if (!aZombie->IsDeadOrDying())
        {
            Rect aZombieRect = aZombie->GetZombieRect();
            if (aZombie->mRow == theRow && mSeedType == SeedType::SEED_HURRIKALE && (aZombie->mZombieType != ZOMBIE_GLADIANTUAR && aZombie->mZombieType != ZOMBIE_GLADIANTUAR_GIGA && 
                aZombie->mZombieType != ZOMBIE_ZOMBONI && aZombie->mZombieType != ZOMBIE_TARGET))
            {         
                if (aZombie->IsFlying()) aZombie->mBlowingAway = true;
                else if (aZombie->mZombieType != ZOMBIE_GIGA_FOOTBALL && aZombie->mZombieType != ZOMBIE_CATAPULT) aZombie->mBlowingAwayHur = true;
                if (aZombie->CanBeChilled()) aZombie->ApplyChill(false);
                aZombie->mHurCounter = 1000;
                aZombie->mButteredCounter = 0;
            }
            else if (aZombie->IsFlying() && mSeedType == SeedType::SEED_BLOVER)
            {
                aZombie->mBlowingAway = true;
            }
        }
    }

    mApp->PlaySample(SOUND_BLOVER);
    mBoard->mFogBlownCountDown = 4000;
}

//0x466650
void Plant::KillAllPlantsNearDoom()
{
    Plant* aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant))
    {
        if (aPlant->mRow == mRow && aPlant->mPlantCol == mPlantCol)
        {
            aPlant->Die();
        }
    }
}

//0x4666A0
void Plant::DoSpecial()
{
    int aPosX = mX + mWidth / 2;
    int aPosY = mY + mHeight / 2;
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);

    switch (mSeedType)
    {
    case SeedType::SEED_BLOVER:
    case SeedType::SEED_HURRIKALE:
    {
        if (mState != PlantState::STATE_DOINGSPECIAL)
        {
            mState = PlantState::STATE_DOINGSPECIAL;
            BlowAwayFliers(mX, mRow);

            Plant* aPlant = nullptr;
            while (mBoard->IteratePlants(aPlant))
            {
                aPlant->mStunnedWeb = 0;
            }
        }
        break;
    }
    case SeedType::SEED_CHERRYBOMB:
    {
        mApp->PlayFoley(FoleyType::FOLEY_CHERRYBOMB);
        mApp->PlayFoley(FoleyType::FOLEY_JUICY);

        mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, 115, 1, true, aDamageRangeFlags, 0, 1800, mHypnotized);

        mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_POWIE);
        mBoard->ShakeBoard(3, -4);

        Die();
        break;
    }
    case SeedType::SEED_BLOODORANGE:
    {
        mApp->PlayFoley(FoleyType::FOLEY_BLOOD_EXPLOSION);
        mApp->PlayFoley(FoleyType::FOLEY_JUICY);

        mBoard->DamageAllZombiesInRadius(mRow, aPosX, aPosY, 115, 1, 900);

        mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_BLOOD_SPLASH);
        mBoard->ShakeBoard(3, -4);

        int aRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 1);

        Reanimation* aBloodReanim = mApp->AddReanimation(aPosX - 50, aPosY - 20, aRenderOrder, ReanimationType::REANIM_BLOODSPLASH);

        Die();
        break;
    }
    case SeedType::SEED_DOOMSHROOM:
    {
        mApp->PlaySample(SOUND_DOOMSHROOM);

        mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, 250, 3, true, aDamageRangeFlags, 1, 1800, false);
        if (!mApp->mPlayerInfo->mHardmodeIsOff) mBoard->KillAllPlantsInRadius(aPosX, aPosY, 250);
        KillAllPlantsNearDoom();

        mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_DOOM);
        mBoard->AddACrater(mPlantCol, mRow)->mGridItemCounter = 18000;
        mBoard->ShakeBoard(3, -4);

        Die();
        break;
    }
    case SeedType::SEED_JALAPENO:
    {
        mApp->PlayFoley(FoleyType::FOLEY_JALAPENO_IGNITE);
        mApp->PlayFoley(FoleyType::FOLEY_JUICY);

        mBoard->DoFwoosh(mRow);
        mBoard->ShakeBoard(3, -4);

        BurnRow(mRow);
        mBoard->mIceTimer[mRow] = 20;

        Die();
        break;
    }
    case SeedType::SEED_CHILLYPEPPER:
    {
        int aRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 1);

        mApp->PlayFoley(FoleyType::FOLEY_CHILLY_FREEZE);
        mApp->PlayFoley(FoleyType::FOLEY_JUICY);

        Reanimation* bFwoosh = mApp->AddReanimation(aPosX - 50, aPosY - 50, aRenderOrder, ReanimationType::REANIM_CHILOOSH);
        bFwoosh->SetFramesForLayer("anim_chiloosh");

        mBoard->DoFwooshChillyPepper(mRow);
        mBoard->ShakeBoard(3, -4);

        FreezeRow(mRow);
        //mBoard->mIceTimer[mRow] = 20;

        Die();
        break;
    }
    case SeedType::SEED_PICKLEPEPPER:
    {
        mApp->PlayFoley(FoleyType::FOLEY_JALAPENO_IGNITE);
        mApp->PlayFoley(FoleyType::FOLEY_JUICY);

        mBoard->DoFwooshChilly(mRow, mPlantCol);
        mBoard->ShakeBoard(3, -4);

        BurnColumn(mPlantCol);
        //mBoard->mIceTimer[mPlantCol] = 20;

        Die();
        break;
    }
    case SeedType::SEED_UMBRELLA:
    {
        if (mState != PlantState::STATE_UMBRELLA_TRIGGERED && mState != PlantState::STATE_UMBRELLA_REFLECTING)
        {
            mState = PlantState::STATE_UMBRELLA_TRIGGERED;
            mStateCountdown = 5;

            PlayBodyReanim("anim_block", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 22.0f);
        }

        break;
    }
    case SeedType::SEED_ICESHROOM:
    {
        mApp->PlayFoley(FoleyType::FOLEY_FROZEN);
        IceZombies();
        mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_ICE_TRAP);

        Die();
        break;
    }
    case SeedType::SEED_POTATOMINE:
    {
        aPosX = mX + mWidth / 2 - 20;
        aPosY = mY + mHeight / 2;

        mApp->PlaySample(SOUND_POTATO_MINE);
        mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, 60, 0, false, aDamageRangeFlags, 0, 1800, false);

        int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 0);
        mApp->AddTodParticle(aPosX + 20.0f, aPosY, aRenderPosition, ParticleEffect::PARTICLE_POTATO_MINE);
        mBoard->ShakeBoard(3, -4);

        Die();
        break;
    }
    case SeedType::SEED_INSTANT_COFFEE: //coffeeteleport
    {
        /*Plant* aPlant = NULL;
        while (mBoard->IteratePlants(aPlant)) {
            if (aPlant == this || aPlant->mPlantCol != mPlantCol || aPlant->mRow != mRow) continue;
            aPlant->mWakeUpCounter = 100;
        } */

        Plant* aPlant = mBoard->GetTopPlantAt(mPlantCol, mRow, PlantPriority::TOPPLANT_ONLY_NORMAL_POSITION);
        if (aPlant && aPlant->mIsAsleep)
        {
            aPlant->mWakeUpCounter = 100;
        }

        mState = PlantState::STATE_DOINGSPECIAL;
        PlayBodyReanim("anim_crumble", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 22.0f);
        mApp->PlayFoley(FoleyType::FOLEY_COFFEE);

        break;
    }
    }
}

//0x466B80
void Plant::ImitaterMorph()
{
    Die();
    Plant* aPlant = mBoard->AddPlant(mPlantCol, mRow, mImitaterType, SeedType::SEED_IMITATER);

    FilterEffect aFilter = FilterEffect::FILTER_EFFECT_WASHED_OUT;
    if (mImitaterType == SeedType::SEED_HYPNOSHROOM || mImitaterType == SeedType::SEED_SQUASH || mImitaterType == SeedType::SEED_POTATOMINE ||
        mImitaterType == SeedType::SEED_GARLIC || mImitaterType == SeedType::SEED_LILYPAD)
        aFilter = FilterEffect::FILTER_EFFECT_LESS_WASHED_OUT;

    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(aPlant->mBodyReanimID);
    if (aBodyReanim)
    {
        aBodyReanim->mFilterEffect = aFilter;
    }
    Reanimation* aHeadReanim = mApp->ReanimationTryToGet(aPlant->mHeadReanimID);
    if (aHeadReanim)
    {
        aHeadReanim->mFilterEffect = aFilter;
    }Reanimation* aHeadReanim2 = mApp->ReanimationTryToGet(aPlant->mHeadReanimID2);
    if (aHeadReanim2)
    {
        aHeadReanim2->mFilterEffect = aFilter;
    }Reanimation* aHeadReanim3 = mApp->ReanimationTryToGet(aPlant->mHeadReanimID3);
    if (aHeadReanim3)
    {
        aHeadReanim3->mFilterEffect = aFilter;
    }
}

//0x466CA0
void Plant::UpdateImitater()
{
    if (mState != PlantState::STATE_IMITATER_MORPHING)
    {
        if (mStateCountdown == 0)
        {
            mState = PlantState::STATE_IMITATER_MORPHING;
            PlayBodyReanim("anim_explode", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 26.0f);
        }
    }
    else
    {
        Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->ShouldTriggerTimedEvent(0.8f))
        {
            mApp->AddTodParticle(mX + 40, mY + 40, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_IMITATER_MORPH);
        }
        if (aBodyReanim->mLoopCount > 0)
        {
            ImitaterMorph();
        }
    }
}

//0x466D50
void Plant::CobCannonFire(int theTargetX, int theTargetY)
{
    //TOD_ASSERT(mState == PlantState::STATE_COBCANNON_READY);
    if (mState != PlantState::STATE_COBCANNON_READY)
    {
        mBoard->mCobActivated = false;
        return;
    }

    mState = PlantState::STATE_COBCANNON_FIRING;
    mShootingCounter = 206;
    PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0f);

    mTargetX = theTargetX - 47.0f;
    mTargetY = theTargetY;

    Reanimation* aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("CobCannon_Cob");
    aTrackInstance->mTrackColor = Color::White;
    mBoard->mCobActivated = false;
}

//0x466E00
void Plant::Fire(Zombie* theTargetZombie, int theRow, PlantWeapon thePlantWeapon)
{
    if (mSeedType == SeedType::SEED_FUMESHROOM)
    {
        DoRowAreaDamage(20, 2U);
        mApp->PlayFoley(FoleyType::FOLEY_FUME);
        return;
    }
    if (mSeedType == SeedType::SEED_ICYFUME)
    {
        DoRowAreaDamage(20, 2U);
        mApp->PlayFoley(FoleyType::FOLEY_FUME);
        return;
    }
    if (mSeedType == SeedType::SEED_GLOOMSHROOM)
    {
        DoRowAreaDamage(20, 2U);
        return;
    }
    if (mSeedType == SeedType::SEED_STARFRUIT)
    {
        StarFruitFire();
        return;
    }
    if (mSeedType == SeedType::SEED_REVERSE_STARFRUIT)
    {
        StarFruitFireReverse();
        return;
    }
    if (mSeedType == SeedType::SEED_VOLTSHROOM)
    {
        VoltShroomFire();
        return;
    }
    if (mSeedType == SeedType::SEED_SHOOTINGSTAR) {
        mApp->PlayFoley(FOLEY_SHOOTINGSTAR);
        unsigned int aDamageRangeFlags = GetDamageRangeFlags(WEAPON_SECONDARY);
        mApp->PlayFoley(FoleyType::FOLEY_FIREPEA);
        for (int gridY = 0; gridY < MAX_GRID_SIZE_Y; gridY++) {
            Zombie* aZombie = FindTargetZombie(gridY, WEAPON_PRIMARY);
            if (aZombie) {
                Rect aZombieRect = aZombie->GetZombieRect();
                if (aZombie->EffectedByDamage(aDamageRangeFlags))
                {
                    Projectile* aProjectile = mBoard->AddProjectile(aZombie->ZombieTargetLeadX(50.0f) - 330, aZombieRect.mY - 300, mRenderOrder - 1, theRow, PROJECTILE_SHOOTING_STAR);
                    //aProjectile->mPlantParentID = (PlantID)mBoard->mPlants.DataArrayGetID(this);
                    aProjectile->mDamageRangeFlags = GetDamageRangeFlags(thePlantWeapon);
                    aProjectile->mMotionType = MOTION_LOBBED;
                    aProjectile->mVelX = 3.33f;
                    aProjectile->mVelY = 0.0f;
                    aProjectile->mVelZ = 3.33f;
                    aProjectile->mAccZ = 0.0f;
                    aProjectile->mRow = aZombie->mRow;
                }
            }
        }
        return;
    }
    if (mSeedType == SeedType::SEED_ECACTUS)
    {
        KingCactusFire();
        return;
    }
    if (mSeedType == SeedType::SEED_PINKSTAR)
    {
        if (mSeaStarCycle)
        {
            SeaStarFruitFire();
        }
        else StarFruitFire();
        return;
    }
    if (mSeedType == SeedType::SEED_REED)
    {
        LightningReedFire();
        //ReedFire();
        return;
    }

    ProjectileType aProjectileType;
    switch (mSeedType)
    {
    case SeedType::SEED_PEASHOOTER:
    case SeedType::SEED_REPEATER:
    case SeedType::SEED_THREEPEATER:
    case SeedType::SEED_REVERSE_THREEPEATER:
    case SeedType::SEED_SPLITPEA:
    case SeedType::SEED_GATLINGPEA:
    case SeedType::SEED_LEFTPEATER:
    case SeedType::SEED_REVERSE_PEASHOOTER:
        if (mHypnotized) aProjectileType = ProjectileType::PROJECTILE_ZOMBIE_PEA;
        else aProjectileType = ProjectileType::PROJECTILE_PEA;
        break;
    case SeedType::SEED_SNOWPEA:
    case SeedType::SEED_REVERSE_SNOWPEA:
        if (mHypnotized) aProjectileType = ProjectileType::PROJECTILE_ZOMBIE_SNOWPEA;
        else aProjectileType = ProjectileType::PROJECTILE_SNOWPEA;
        break;
    case SeedType::SEED_PLASMAPEA:
        aProjectileType = ProjectileType::PROJECTILE_PLASMABALL;
        break;
    case SeedType::SEED_QUEENPEA:
        aProjectileType = ProjectileType::PROJECTILE_ICEQUEEN;
        break;
    case SeedType::SEED_EPEA:
        aProjectileType = ProjectileType::PROJECTILE_ELECTRIC;
        break;
    case SeedType::SEED_FLAMEPEA:
        aProjectileType = ProjectileType::PROJECTILE_FIREBALL;
        break;
    case SeedType::SEED_PUFFSHROOM:
    case SeedType::SEED_REVERSE_PUFFSHROOM:
    case SeedType::SEED_SCAREDYSHROOM:
    case SeedType::SEED_BRAVESHROOM:
    case SeedType::SEED_SEASHROOM:
    case SeedType::SEED_PULTSHROOM:
        aProjectileType = ProjectileType::PROJECTILE_PUFF;
        break;
    case SeedType::SEED_MORTARSHROOM:
        aProjectileType = ProjectileType::PROJECTILE_BIG_PUFF;
        break;
    case SeedType::SEED_CACTUS:
    case SeedType::SEED_CATTAIL:
        aProjectileType = ProjectileType::PROJECTILE_SPIKE;
        break;
    case SeedType::SEED_OAK_ARCHER:
        aProjectileType = ProjectileType::PROJECTILE_ARROW;
        break;
    case SeedType::SEED_CABBAGEPULT:
        aProjectileType = ProjectileType::PROJECTILE_CABBAGE;
        break;
    case SeedType::SEED_KERNELPULT:
        aProjectileType = ProjectileType::PROJECTILE_KERNEL;
        break;
    case SeedType::SEED_MELONPULT:
        aProjectileType = ProjectileType::PROJECTILE_MELON;
        break;
    case SeedType::SEED_PEPPER:
        aProjectileType = ProjectileType::PROJECTILE_PEPPER;
        break;
    case SeedType::SEED_WINTERMELON:
        aProjectileType = ProjectileType::PROJECTILE_WINTERMELON;
        break;
    case SeedType::SEED_COBCANNON:
        aProjectileType = ProjectileType::PROJECTILE_COBBIG;
        break;
    case SeedType::SEED_BEE_SHOOTER:
        aProjectileType = ProjectileType::PROJECTILE_BEE;
        break;
    default:
        TOD_ASSERT();
        break;
    }
    if (mSeedType == SeedType::SEED_KERNELPULT && thePlantWeapon == PlantWeapon::WEAPON_SECONDARY)
    {
        aProjectileType = ProjectileType::PROJECTILE_BUTTER;
    }

    mApp->PlayFoley(FoleyType::FOLEY_THROW);
    if (mSeedType == SeedType::SEED_SNOWPEA || mSeedType == SeedType::SEED_WINTERMELON)
    {
        mApp->PlayFoley(FoleyType::FOLEY_SNOW_PEA_SPARKLES);
    }
    else if (mSeedType == SeedType::SEED_PUFFSHROOM || mSeedType == SeedType::SEED_SCAREDYSHROOM || mSeedType == SeedType::SEED_SEASHROOM || mSeedType == SeedType::SEED_BRAVESHROOM || mSeedType == SeedType::SEED_REVERSE_PUFFSHROOM)
    {
        mApp->PlayFoley(FoleyType::FOLEY_PUFF);
    }

    int aOriginX, aOriginY;
    if (mSeedType == SeedType::SEED_PUFFSHROOM || mSeedType == SeedType::SEED_REVERSE_PUFFSHROOM)
    {
        aOriginX = mX + 40;
        aOriginY = mY + 40;
    }
    else if (mSeedType == SeedType::SEED_LEFTPEATER || mSeedType == SeedType::SEED_REVERSE_PEASHOOTER || mSeedType == SeedType::SEED_REVERSE_SNOWPEA || mHypnotized)
    {
        int aOffsetX, aOffsetY;
        GetPeaHeadOffset(aOffsetX, aOffsetY);
        aOriginX = mX + aOffsetX - 50;
        aOriginY = mY + aOffsetY - 33;
    }
    else if (mSeedType == SeedType::SEED_SEASHROOM)
    {
        if (mBoard->GetFlowerPotAt(mPlantCol, mRow))
        {
            aOriginX = mX + 40;
            aOriginY = mY + 40;
        }
        else
        {
            aOriginX = mX + 45;
            aOriginY = mY + 63;
        }
    }
    else if (mSeedType == SeedType::SEED_CABBAGEPULT || mSeedType == SeedType::SEED_PEPPER )
    {
        aOriginX = mX + 5;
        aOriginY = mY - 12;
    }
    else if (mSeedType == SeedType::SEED_MELONPULT || mSeedType == SeedType::SEED_WINTERMELON)
    {
        aOriginX = mX + 25;
        aOriginY = mY - 46;
    }
    else if (mSeedType == SeedType::SEED_CATTAIL)
    {
        aOriginX = mX + 20;
        aOriginY = mY - 3;
    }
    else if (mSeedType == SeedType::SEED_PULTSHROOM)
    {
        aOriginX = mX + 15;
        aOriginY = mY - 12;
    }
    else if (mSeedType == SeedType::SEED_MORTARSHROOM)
    {
        aOriginX = mX + 15;
        aOriginY = mY - 12;
    }
    else if (mSeedType == SeedType::SEED_KERNELPULT && thePlantWeapon == PlantWeapon::WEAPON_PRIMARY)
    {
        aOriginX = mX + 19;
        aOriginY = mY - 37;
    }
    else if (mSeedType == SeedType::SEED_KERNELPULT && thePlantWeapon == PlantWeapon::WEAPON_SECONDARY)
    {
        aOriginX = mX + 12;
        aOriginY = mY - 56;
    }
    else if (mSeedType == SeedType::SEED_PEASHOOTER || mSeedType == SeedType::SEED_SNOWPEA || mSeedType == SeedType::SEED_REPEATER || 
             mSeedType == SeedType::SEED_FLAMEPEA ||mSeedType == SeedType::SEED_QUEENPEA || mSeedType == SeedType::SEED_PLASMAPEA ||
             mSeedType == SeedType::SEED_EPEA || mSeedType == SeedType::SEED_BEE_SHOOTER)
    {
        int aOffsetX, aOffsetY;
        GetPeaHeadOffset(aOffsetX, aOffsetY);
        aOriginX = mX + aOffsetX + 24;
        aOriginY = mY + aOffsetY - 33;
    }
    else if (mSeedType == SeedType::SEED_GATLINGPEA)
    {
        int aOffsetX, aOffsetY;
        GetPeaHeadOffset(aOffsetX, aOffsetY);
        aOriginX = mX + aOffsetX + 34;
        aOriginY = mY + aOffsetY - 33;
    }
    else if (mSeedType == SeedType::SEED_SPLITPEA)
    {
        int aOffsetX, aOffsetY;
        GetPeaHeadOffset(aOffsetX, aOffsetY);
        aOriginY = mY + aOffsetY - 33;

        if (thePlantWeapon == PlantWeapon::WEAPON_SECONDARY)
        {
            aOriginX = mX + aOffsetX - 64;
        }
        else
        {
            aOriginX = mX + aOffsetX + 24;
        }
    }
    else if (mSeedType == SeedType::SEED_THREEPEATER || mSeedType == SeedType::SEED_REVERSE_THREEPEATER)
    {
        aOriginX = mX + 45;
        aOriginY = mY + 10;
    }
    else if (mSeedType == SeedType::SEED_SCAREDYSHROOM || mSeedType == SeedType::SEED_BRAVESHROOM)
    {
        aOriginX = mX + 29;
        aOriginY = mY + 21;
    }
    else if (mSeedType == SeedType::SEED_CACTUS)
    {
        if (thePlantWeapon == PlantWeapon::WEAPON_PRIMARY)
        {
            aOriginX = mX + 93;
            aOriginY = mY - 50;
        }
        else
        {
            aOriginX = mX + 70;
            aOriginY = mY + 23;
        }
    }
    else if (mSeedType == SeedType::SEED_COBCANNON)
    {
        aOriginX = mX - 44;
        aOriginY = mY - 184;
    }
    else
    {
        aOriginX = mX + 10;
        aOriginY = mY + 5;
    }
    if (mBoard->GetFlowerPotAt(mPlantCol, mRow))
    {
        aOriginY -= 5;
    }
    
    if (mSeedType == SeedType::SEED_SNOWPEA)
    {
        int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_LAWN_MOWER, mRow, 1);
        mApp->AddTodParticle(aOriginX + 8, aOriginY + 13, aRenderPosition, ParticleEffect::PARTICLE_SNOWPEA_PUFF);
    }
    else if (mSeedType == SeedType::SEED_PUFFSHROOM || mSeedType == SeedType::SEED_REVERSE_PUFFSHROOM)
    {
        int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_LAWN_MOWER, mRow, 1);
        mApp->AddTodParticle(aOriginX + 18, aOriginY + 13, aRenderPosition, ParticleEffect::PARTICLE_PUFFSHROOM_MUZZLE);
    }
    else if (mSeedType == SeedType::SEED_SCAREDYSHROOM || mSeedType == SeedType::SEED_BRAVESHROOM)
    {
        int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_LAWN_MOWER, mRow, 1);
        mApp->AddTodParticle(aOriginX + 27, aOriginY + 13, aRenderPosition, ParticleEffect::PARTICLE_PUFFSHROOM_MUZZLE);
    }

    Projectile* aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder - 1, theRow, aProjectileType);
    aProjectile->mDamageRangeFlags = GetDamageRangeFlags(thePlantWeapon);
    if (aProjectile->mProjectileType == PROJECTILE_ELECTRIC)
    {
        aProjectile->mMotionType = ProjectileMotion::MOTION_STAR;
        aProjectile->mVelX = 3.33f / 2;
    }

    if (mSeedType == SeedType::SEED_CABBAGEPULT || mSeedType == SeedType::SEED_KERNELPULT || mSeedType == SeedType::SEED_PULTSHROOM || mSeedType == SeedType::SEED_MORTARSHROOM ||
        mSeedType == SeedType::SEED_MELONPULT || mSeedType == SeedType::SEED_WINTERMELON || mSeedType == SeedType::SEED_PEPPER)
    {
        float aRangeX, aRangeY;
        Plant* aPlant = FindTargetPlant(theRow, thePlantWeapon);
        if (theTargetZombie)
        {
            if (aPlant && aPlant->mSeedType == SEED_GRAVE && theTargetZombie->mZombieType == ZOMBIE_TARGET)
            {
                Rect aPlantRect = aPlant->GetPlantRect();
                aRangeX = aPlant->mX - aOriginX;
                aRangeY = aPlant->mY - aOriginY;
            }
            else
            {
                Rect aZombieRect = theTargetZombie->GetZombieRect();
                aRangeX = theTargetZombie->ZombieTargetLeadX(50.0f) - aOriginX - 30.0f;
                aRangeY = aZombieRect.mY - aOriginY;

                if (theTargetZombie->mZombiePhase == ZombiePhase::PHASE_DOLPHIN_RIDING)
                {
                    aRangeX -= 60.0f;
                }
                if (theTargetZombie->mZombieType == ZombieType::ZOMBIE_POGO && theTargetZombie->mHasObject)
                {
                    aRangeX -= 60.0f;
                }
                if (theTargetZombie->mZombiePhase == ZombiePhase::PHASE_SNORKEL_WALKING_IN_POOL)
                {
                    aRangeX -= 40.0f;
                }
                if (theTargetZombie->mZombieType == ZombieType::ZOMBIE_BOSS)
                {
                    aRangeY = mBoard->GridToPixelY(8, mRow) - aOriginY;
                }
            }
        }
        else if (aPlant && aPlant->mSeedType == SEED_GRAVE)
        {
            Rect aPlantRect = aPlant->GetPlantRect();
            aRangeX = aPlant->mX - aOriginX;
            aRangeY = aPlant->mY - aOriginY;
        }
        else
        {
            aRangeX = 700.0f - aOriginX;
            aRangeY = 0.0f;
        }
        if (aRangeX < 40.0f)
        {
            aRangeX = 40.0f;
        }

        aProjectile->mMotionType = ProjectileMotion::MOTION_LOBBED;
        aProjectile->mVelX = aRangeX / 120.0f;
        aProjectile->mVelY = 0.0f;
        aProjectile->mVelZ = aRangeY / 120.0f - 7.0f;
        aProjectile->mAccZ = 0.115f;
    }
    else if (mSeedType == SeedType::SEED_THREEPEATER)
    {
        if (theRow < mRow)
        {
            aProjectile->mMotionType = ProjectileMotion::MOTION_THREEPEATER;
            aProjectile->mVelY = -3.0f;
            aProjectile->mShadowY += 80.0f;
        }
        else if (theRow > mRow)
        {
            aProjectile->mMotionType = ProjectileMotion::MOTION_THREEPEATER;
            aProjectile->mVelY = 3.0f;
            aProjectile->mShadowY -= 80.0f;
        }
    }
    else if (mSeedType == SeedType::SEED_REVERSE_THREEPEATER)
    {
        if (theRow < mRow)
        {
            aProjectile->mMotionType = ProjectileMotion::MOTION_THREEPEATER_BACKWARDS;
            aProjectile->mVelY = -3.0f;
            aProjectile->mShadowY += 80.0f;
        }
        else if (theRow > mRow)
        {
            aProjectile->mMotionType = ProjectileMotion::MOTION_THREEPEATER_BACKWARDS;
            aProjectile->mVelY = 3.0f;
            aProjectile->mShadowY -= 80.0f;
        }
        else aProjectile->mMotionType = ProjectileMotion::MOTION_BACKWARDS;
    }
    else if (mSeedType == SeedType::SEED_PUFFSHROOM || mSeedType == SeedType::SEED_SEASHROOM)
    {
        aProjectile->mMotionType = ProjectileMotion::MOTION_PUFF;
    }
    else if (mSeedType == SeedType::SEED_SPLITPEA && thePlantWeapon == PlantWeapon::WEAPON_SECONDARY)
    {
        aProjectile->mMotionType = ProjectileMotion::MOTION_BACKWARDS;
    }
    else if (mSeedType == SeedType::SEED_LEFTPEATER || mSeedType == SeedType::SEED_REVERSE_PEASHOOTER || mSeedType == SeedType::SEED_REVERSE_SNOWPEA || mSeedType == SeedType::SEED_REVERSE_PUFFSHROOM || mHypnotized)
    {
        aProjectile->mMotionType = ProjectileMotion::MOTION_BACKWARDS;
    }
    else if (mSeedType == SeedType::SEED_CATTAIL || mSeedType == SeedType::SEED_BEE_SHOOTER)
    {
        aProjectile->mVelX = 2.0f;
        if (theTargetZombie == NULL || theTargetZombie->mZombieType == ZOMBIE_TARGET)
        {
            aProjectile->mMotionType = ProjectileMotion::MOTION_STRAIGHT;
        }
        else
        {
            aProjectile->mMotionType = ProjectileMotion::MOTION_HOMING;
            aProjectile->mTargetZombieID = mBoard->ZombieGetID(theTargetZombie);
        }
    }
    else if (mSeedType == SeedType::SEED_COBCANNON)
    {
        aProjectile->mVelX = 0.001f;
        aProjectile->mDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
        aProjectile->mMotionType = ProjectileMotion::MOTION_LOBBED;
        aProjectile->mVelY = 0.0f;
        aProjectile->mAccZ = 0.0f;
        aProjectile->mVelZ = -8.0f;
        aProjectile->mCobTargetX = mTargetX - 40;
        aProjectile->mCobTargetRow = mBoard->PixelToGridYKeepOnBoard(mTargetX, mTargetY);
    }
}

Plant* Plant::FindTargetPlant(int theRow, PlantWeapon thePlantWeapon)
{
    Plant* aPlant = nullptr;
    Plant* aBestPlant = nullptr;
    while (mBoard->IteratePlants(aPlant))
    {        
        if ((aPlant->mSeedType == SEED_GRAVE || aPlant->mHypnotized) && 
            (abs(theRow - aPlant->mRow) <= GetAttackRowRange()) && 
            (thePlantWeapon == WEAPON_PRIMARY || mSeedType == SEED_KERNELPULT))
        { 
            if (aBestPlant == nullptr)
            {
                aBestPlant = aPlant;
            }
            else if (aPlant->mPlantCol < aBestPlant->mPlantCol)
            {
                aBestPlant = aPlant;
            }
        }
    }
    if (aBestPlant && (mSeedType == SEED_PUFFSHROOM && mPlantCol < aBestPlant->mPlantCol - 3)) return nullptr;
    if (aBestPlant && (mSeedType == SEED_PULTSHROOM && mPlantCol < aBestPlant->mPlantCol - 6) && (mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_ROOF && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_MOON)) return nullptr;
    if (aBestPlant && (mSeedType == SEED_PULTSHROOM && mPlantCol < aBestPlant->mPlantCol - 3) && (mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON)) return nullptr;
    else if (aBestPlant && ((mSeedType == SEED_FUMESHROOM || mSeedType == SEED_ICYFUME) && mPlantCol < aBestPlant->mPlantCol - 4)) return nullptr;
    return aBestPlant;
}

GridItem* Plant::FindTargetGridItem(int theRow)
{
    GridItem* aGridItem = nullptr;
    while (mBoard->IterateGridItems(aGridItem))
    {
        if (abs(theRow - aGridItem->mGridY) <= GetAttackRowRange() && 
            aGridItem->mGridItemType == GRIDITEM_WOOD_LOG) return aGridItem;
    }
    return nullptr;
}

//0x4675C0
Zombie* Plant::FindTargetZombie(int theRow, PlantWeapon thePlantWeapon)
{
    int aDamageRangeFlags = GetDamageRangeFlags(thePlantWeapon);
    Rect aAttackRect = GetPlantAttackRect(thePlantWeapon);
    int aHighestWeight = 0;
    Zombie* aBestZombie = nullptr;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if (mSeedType == SEED_REED && aZombie->mZombiePhase == ZombiePhase::PHASE_BALLOON_FLYING) continue;
        //lame

        int aRowDeviation = aZombie->mRow - theRow;
        if (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS)
        {
            aRowDeviation = 0;
        }

        if (!aZombie->mHasHead || aZombie->IsTangleKelpTarget())
        {
            if (mSeedType == SeedType::SEED_POTATOMINE || mSeedType == SeedType::SEED_CHOMPER || mSeedType == SeedType::SEED_REVERSE_CHOMPER || mSeedType == SeedType::SEED_SUPERCHOMP || mSeedType == SeedType::SEED_TANGLEKELP ||
                mSeedType == SeedType::SEED_BONKCHOY)
            {
                continue;
            }
        }
        bool aIsBushSquare =
            mBoard->GetBushAt(mBoard->PixelToGridX(aZombie->mX + 75, aZombie->mY), mRow) &&
            mBoard->GetBushAt(mBoard->PixelToGridX(aZombie->mX + 45, mY), aZombie->mRow) &&
            mX < 680;
        if (aIsBushSquare && mSeedType != SeedType::SEED_BEE_SHOOTER && mSeedType != SeedType::SEED_OAK_ARCHER)
        {
            continue;
        }

        bool needPortalCheck = false;
        if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_PORTAL_COMBAT)
        {
            if (mSeedType == SeedType::SEED_PEASHOOTER || mSeedType == SeedType::SEED_CACTUS || mSeedType == SeedType::SEED_REPEATER)
            {
                needPortalCheck = true;
            }
        }

        if (mSeedType != SeedType::SEED_CATTAIL && mSeedType != SeedType::SEED_BEE_SHOOTER)
        {
            if (mSeedType == SeedType::SEED_GLOOMSHROOM || mSeedType == SeedType::SEED_REED || mSeedType == SeedType::SEED_VOLTSHROOM)
            {
                if (aRowDeviation < -1 || aRowDeviation > 1)
                {
                    continue;
                }
            }
            else if (needPortalCheck)
            {
                if (!mBoard->mChallenge->CanTargetZombieWithPortals(this, aZombie))
                {
                    continue;
                }
            }
            else if (aRowDeviation)
            {
                continue;
            }
        }

        if (aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            int aExtraRange = 0;

            if (mSeedType == SeedType::SEED_CHOMPER || mSeedType == SeedType::SEED_REVERSE_CHOMPER || mSeedType == SeedType::SEED_SUPERCHOMP || mSeedType == SeedType::SEED_BONKCHOY)
            {
                if (aZombie->mZombiePhase == ZombiePhase::PHASE_DIGGER_WALKING)
                {
                    aAttackRect.mX += 20;
                    aAttackRect.mWidth -= 20;
                }

                if (aZombie->mZombiePhase == ZombiePhase::PHASE_POGO_BOUNCING || (aZombie->mZombieType == ZombieType::ZOMBIE_BUNGEE && aZombie->mTargetCol == mPlantCol))
                {
                    continue;
                }

                if (aZombie->mIsEating || mState == PlantState::STATE_CHOMPER_BITING)
                {
                    aExtraRange = 60;
                }
            }

            if (mSeedType == SeedType::SEED_CHARD_GUARD)
            {
                if (!aZombie->mHasHead || aZombie->IsImmuneToKnockback())
                {
                    continue;
                }
            }

            if (mSeedType == SeedType::SEED_POTATOMINE)
            {
                if ((aZombie->mZombieType == ZombieType::ZOMBIE_POGO && aZombie->mHasObject) ||
                    aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT)
                {
                    continue;
                }

                if (aZombie->mZombieType == ZombieType::ZOMBIE_POLEVAULTER)
                {
                    aAttackRect.mX += 40;
                    aAttackRect.mWidth -= 40;  // 原版经典土豆地雷 Bug 及“四撑杆引雷”的原理
                }

                if (aZombie->mZombieType == ZombieType::ZOMBIE_BUNGEE && aZombie->mTargetCol != mPlantCol)
                {
                    continue;
                }

                if (aZombie->mIsEating)
                {
                    aExtraRange = 30;
                }
            }

            if ((mSeedType == SeedType::SEED_EXPLODE_O_NUT && aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT) ||
                (mSeedType == SeedType::SEED_ICENUT && aZombie->mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT))
            {
                continue;
            }

            if (mSeedType == SeedType::SEED_SHRINK && aZombie->mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING)
            {
                continue;
            }

            Rect aZombieRect = aZombie->GetZombieRect();
            if (!needPortalCheck && GetRectOverlap(aAttackRect, aZombieRect) < -aExtraRange)
            {
                continue;
            }

            ////////////////////

            int aWeight = -aZombieRect.mX;
            if (mSeedType == SeedType::SEED_CATTAIL || mSeedType == SeedType::SEED_BEE_SHOOTER)
            {
                aWeight = -Distance2D(mX + 40.0f, mY + 40.0f, aZombieRect.mX + aZombieRect.mWidth / 2, aZombieRect.mY + aZombieRect.mHeight / 2);
                if (aZombie->IsFlying())
                {
                    aWeight += 10000;  // 优先攻击飞行单位
                }
            }

            if ((aBestZombie == nullptr || aWeight > aHighestWeight) && mSeedType != SeedType::SEED_BEE_SHOOTER)
            {
                aHighestWeight = aWeight;
                aBestZombie = aZombie;
            }

            if (mSeedType == SeedType::SEED_BEE_SHOOTER)
            {
                Zombie* bZombie = nullptr;
                while (mBoard->IterateZombies(bZombie))
                {
                    if (bZombie->mRow == mRow && !bZombie->IsFlying())
                    {
                        if ((aBestZombie == nullptr || aWeight > aHighestWeight) && bZombie->mRow == mRow)
                        {
                            aHighestWeight = aWeight;
                            aBestZombie = bZombie;
                        }
                        else if (bZombie->mPosX < aBestZombie->mPosX && bZombie->mHasHead && bZombie->mRow == mRow)
                        {
                            aBestZombie = bZombie;
                        }
                        /*else if ((bZombie->mBodyMaxHealth + bZombie->mHelmMaxHealth) > (aBestZombie->mBodyMaxHealth + aBestZombie->mHelmMaxHealth) && bZombie->mHasHead)
                        {
                            aBestZombie = bZombie;
                        }*/
                    }
                }
            }
        }
    }

    return aBestZombie;
}

//0x4678B0
int Plant::DistanceToClosestZombie()
{
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);
    Rect aAttackRect = GetPlantAttackRect(PlantWeapon::WEAPON_PRIMARY);
    int aClosestDistance = 1000;

    Zombie* aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie))
    {
        if (aZombie->mRow == mRow && aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            Rect aZombieRect = aZombie->GetZombieRect();
            int aDistance = -GetRectOverlap(aAttackRect, aZombieRect);
            if (aDistance < aClosestDistance)
            {
                aClosestDistance = max(aDistance, 0);
            }
        }
    }

    return aClosestDistance;
}

//0x4679B0
void Plant::Die()
{
    if (mSeedType == SEED_EXPLODE_O_NUT)
    {
        mApp->PlayFoley(FoleyType::FOLEY_CHERRYBOMB);
        mApp->PlayFoley(FoleyType::FOLEY_JUICY);

        mBoard->KillAllZombiesInRadius(mRow, mX + 50, mY + 30, 115, 1, true, GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY), 0, 1800, false);

        mApp->AddTodParticle(mX + 50, mY + 30, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_POWIE);
        mBoard->ShakeBoard(3, -4);
    }
    if (mSeedType == SEED_LUMESHROOM && mBoard && !mIsAsleep)
    {
        Zombie* aZombie = nullptr;
        while (mBoard->IterateZombies(aZombie))
        {
            aZombie->mIsLumed = false;
            aZombie->StartWalkAnim(0);
        }
    }
    if (mSeedType == SEED_DUMMY && mBoard)
    {
        mBoard->IncreaseDummyCounter(mHypnotized);
    }
    if (mSeedType == SEED_ICENUT && !mApp->IsWallnutBowlingLevel())
    {
        mApp->PlayFoley(FoleyType::FOLEY_FROZEN);
        IceZombies();
        mApp->AddTodParticle(mX + 50, mY + 30, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_ICE_TRAP);
    }
    if (IsOnBoard() && mSeedType == SeedType::SEED_TANGLEKELP)
    {
        Zombie* aZombie = mBoard->ZombieTryToGet(mTargetZombieID);
        if (aZombie)
        {
            aZombie->DieWithLoot();
        }
    }

    mDead = true;
    RemoveEffects();

    if (!Plant::IsFlying(mSeedType) && IsOnBoard())
    {
        GridItem* aLadder = mBoard->GetLadderAt(mPlantCol, mRow);
        if (aLadder)
        {
            aLadder->GridItemDie();
        }
    }

    if (IsOnBoard())
    {
        Plant* aTopPlant = mBoard->GetTopPlantAt(mPlantCol, mRow, PlantPriority::TOPPLANT_BUNGEE_ORDER);
        Plant* aFlowerPot = mBoard->GetFlowerPotAt(mPlantCol, mRow);
        if (aFlowerPot && aTopPlant == aFlowerPot)
        {
            Reanimation* aPotReanim = mApp->ReanimationGet(aFlowerPot->mBodyReanimID);
            aPotReanim->mAnimRate = RandRangeFloat(10.0f, 15.0f);
        }
        if (mSeedType == SEED_PLANTERN && mBoard->StageHasDarkness())
        {
            mBoard->mUpdateDarkness = true;
        }
    }
}

PlantDefinition& GetPlantDefinition(SeedType theSeedType)
{
    //TOD_ASSERT(gPlantDefs[theSeedType].mSeedType == theSeedType);
    //TOD_ASSERT(theSeedType >= 0 && theSeedType < (int)SeedType::NUM_SEED_TYPES);
    
    return gPlantDefs[theSeedType];
}

//0x467B00
int Plant::GetCost(SeedType theSeedType, SeedType theImitaterType)
{
    if (gLawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || gLawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST)
    {
        if (theSeedType == SeedType::SEED_REPEATER)
        {
            return 1000;
        }
        else if (theSeedType == SeedType::SEED_FUMESHROOM)
        {
            return 500;
        }
        else if (theSeedType == SeedType::SEED_TALLNUT)
        {
            return 250;
        }
        else if (theSeedType == SeedType::SEED_BEGHOULED_BUTTON_SHUFFLE)
        {
            return 100;
        }
        else if (theSeedType == SeedType::SEED_BEGHOULED_BUTTON_CRATER)
        {
            return 200;
        }
    }

    switch (theSeedType)
    {
    case SeedType::SEED_SLOT_MACHINE_SUN:           return 0;
    case SeedType::SEED_SLOT_MACHINE_DIAMOND:       return 0;
    case SeedType::SEED_ZOMBIQUARIUM_SNORKLE:       return 100;
    case SeedType::SEED_ZOMBIQUARIUM_TROPHY:        return 1000;
    case SeedType::SEED_ZOMBIE_NORMAL:              return 50;
    case SeedType::SEED_ZOMBIE_TRAFFIC_CONE:        return 75;
    case SeedType::SEED_ZOMBIE_POLEVAULTER:         return 75;
    case SeedType::SEED_ZOMBIE_PAIL:                return 125;
    case SeedType::SEED_ZOMBIE_LADDER:              return 150;
    case SeedType::SEED_ZOMBIE_DIGGER:              return 125;
    case SeedType::SEED_ZOMBIE_BUNGEE:              return 125;
    case SeedType::SEED_ZOMBIE_FOOTBALL:            return 175;
    case SeedType::SEED_ZOMBIE_BALLOON:             return 150;
    case SeedType::SEED_ZOMBIE_SCREEN_DOOR:         return 100;
    case SeedType::SEED_ZOMBONI:                    return 175;
    case SeedType::SEED_ZOMBIE_POGO:                return 200;
    case SeedType::SEED_ZOMBIE_DANCER:              return 350;
    case SeedType::SEED_ZOMBIE_GARGANTUAR:          return 300;
    case SeedType::SEED_ZOMBIE_IMP:                 return 50;
    case SeedType::SEED_ZOMBIE_SCARECROW:           return 200;
    case SeedType::SEED_ZOMBIE_GIGA_FOOTBALL:       return 250;
    case SeedType::SEED_ZOMBIE_ICE:                 return 150;
    case SeedType::SEED_ZOMBIE_SNORKEL:             return 100;
    case SeedType::SEED_ZOMBIE_ZOMBOSS:             return 1000;
    default:
    {
        if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_REPEATER) return 150;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_GRAVEBUSTER) return 75;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_ICESHROOM) return 75;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_DOOMSHROOM) return 125;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_LILYPAD) return 25;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_THREEPEATER) return 200;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_SPIKEWEED) return 100;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_TALLNUT) return 125;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_PLANTERN) return 25;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_BLOVER) return 100;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_PUMPKINSHELL) return 125;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_FLOWERPOT) return 25;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_KERNELPULT) return 100;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_GARLIC) return 75;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_UMBRELLA) return 100;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_MELONPULT) return 300;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_VERSUS_POLE) return 100;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_VERSUS_ZOMBONI) return 175;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_VERSUS_JACK) return 100;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_VERSUS_DIGGER) return 150;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_VERSUS_POGO) return 225;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_VERSUS_CATAPULT) return 200;
        else if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SeedType::SEED_VERSUS_GARGANTUAR) return 250;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_REPEATER) return 175; 
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_SNOWPEA) return 150;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_DOOMSHROOM && gLawnApp->mBoard->StageIsNight()) return 250;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_DOOMSHROOM) return 225;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_SQUASH) return 75;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_TORCHWOOD) return 75;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_CACTUS) return 100;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_THREEPEATER) return 225;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_STARFRUIT) return 175;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_INSTANT_COFFEE) return 25;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_GARLIC) return 50;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_GRAVEBUSTER) return 50;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_PEPPER) return 175;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_ICESHROOM && gLawnApp->mBoard->StageIsNight()) return 75;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_ICESHROOM) return 50;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_PLANTERN) return 0;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_TALLNUT) return 100;
        //else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_FIRESHROOM && gLawnApp->mBoard->StageIsNight()) return 125;
        //else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_FIRESHROOM) return 100;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_MELONPULT) return 250;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_OAK_ARCHER) return 150;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_EPEA) return 250;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_AMPLI_FLOWER) return 50;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_KERNELPULT) return 75;
        //else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_BEE_SHOOTER) return 75;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_BLOVER) return 50;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_FLAMEPEA) return 175;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_BONKCHOY) return 100;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_PINKSTAR) return 175;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_PUMPKINSHELL) return 100;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_LEMON_NADE) return 225;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_SPIKEWEED) return 100;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_ALOEVERA) return 25;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_UMBRELLA) return 50;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_FLOWERPOT) return 0;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_WATERPOT) return 0;
        else if (gLawnApp->IsVersusLevel() && theSeedType == SeedType::SEED_LILYPAD) return 0;
        else
        {
            if (theSeedType == SeedType::SEED_IMITATER && theImitaterType != SeedType::SEED_NONE)
            {
                const PlantDefinition& aPlantDef = GetPlantDefinition(theImitaterType);
                return aPlantDef.mSeedCost;
            }
            else
            {
                const PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
                if (IsNocturnal(aPlantDef.mSeedType) && (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_NIGHT || gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_FOG || gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON)) return aPlantDef.mSeedCost + 25;
                //else if (SeedPacket::IsZombiePack(aPlantDef.mSeedType) && (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || gLawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_VERSUS_MOON) && aPlantDef.mSeedType == SEED_VERSUS_NORMAL) return aPlantDef.mSeedCost + 25;
                else return aPlantDef.mSeedCost;
            }
        }
    }
    }
}

//0x467C00
SexyString Plant::GetNameString(SeedType theSeedType, SeedType theImitaterType)
{
    const PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
    SexyString aName = StrFormat(_S("[%s]"), aPlantDef.mPlantName);
    SexyString aTranslatedName = TodStringTranslate(StringToSexyStringFast(aName));

    if (theSeedType == SeedType::SEED_IMITATER && theImitaterType != SeedType::SEED_NONE)
    {
        const PlantDefinition& aImitaterDef = GetPlantDefinition(theImitaterType);
        std::string aImitaterName = StrFormat(_S("[%s]"), aImitaterDef.mPlantName);
        std::string aTranslatedImitaterName = TodStringTranslate(StringToSexyStringFast(aImitaterName));
        return StrFormat(_S("%s %s"), aTranslatedName.c_str(), aTranslatedImitaterName.c_str());
    }

    return aTranslatedName;
}

//0x467DB0
SexyString Plant::GetToolTip(SeedType theSeedType)
{
    const PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
    SexyString aToolTip = StrFormat(_S("[%s_TOOLTIP]"), aPlantDef.mPlantName);
    return TodStringTranslate(aToolTip);
}

//0x467E30
int Plant::GetRefreshTime(SeedType theSeedType, SeedType theImitaterType)
{
    if (Challenge::IsZombieSeedType(theSeedType) && !Challenge::IsVersusSeedType(theSeedType))
    {
        return 0;
    }

    if (((LawnApp*)gSexyAppBase)->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && ((LawnApp*)gSexyAppBase)->mBoard->mBoardAge >= 30000 && !SeedPacket::IsLegacyNotAffectedbySuddenDeath(theSeedType))
    {
        if (theSeedType == SEED_MELONPULT || theSeedType == SEED_REVERSE_THREEPEATER)
            return 500;
        else if (theSeedType == SEED_GRAVEBUSTER)
            return 5000;
        const PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
        return aPlantDef.mRefreshTime / 3;
    }
    else if (theSeedType == SeedType::SEED_IMITATER && theImitaterType != SeedType::SEED_NONE)
    {
        const PlantDefinition& aPlantDef = GetPlantDefinition(theImitaterType);
        return aPlantDef.mRefreshTime;
    }
    else if (((LawnApp*)gSexyAppBase)->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD && (theSeedType == SEED_THREEPEATER || theSeedType == SEED_MELONPULT))
    {
        return 1500;
    }
    else if (((LawnApp*)gSexyAppBase)->IsVersusLevel() && ((LawnApp*)gSexyAppBase)->mGameMode != GAMEMODE_CHALLENGE_VERSUS_OLD && theSeedType == SEED_PLANTERN)
    {
        return 1500;
    }
    else if (((LawnApp*)gSexyAppBase)->IsVersusLevel() && theSeedType == SEED_GRAVEBUSTER)
    {
        return 3000;
    }
    else if (((LawnApp*)gSexyAppBase)->IsVersusLevel() && theSeedType == SEED_GARLIC)
    {
        return 1500;
    }
    else if (((LawnApp*)gSexyAppBase)->IsVersusLevel() && theSeedType == SEED_TORCHWOOD)
    {
        return 3000;
    }
    //else if (theSeedType == SEED_VERSUS_NORMAL && (((LawnApp*)gSexyAppBase)->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || ((LawnApp*)gSexyAppBase)->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON))
    //{
        //return 1500;
    //}
    else
    {
        const PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
        return aPlantDef.mRefreshTime;
    }
}

//0x467E60
bool Plant::IsNocturnal(SeedType theSeedtype)
{
    return
        theSeedtype == SeedType::SEED_PUFFSHROOM ||
        theSeedtype == SeedType::SEED_REVERSE_PUFFSHROOM ||
        theSeedtype == SeedType::SEED_PULTSHROOM ||
        theSeedtype == SeedType::SEED_SEASHROOM ||
        theSeedtype == SeedType::SEED_SUNSHROOM ||
        theSeedtype == SeedType::SEED_FUMESHROOM ||
        theSeedtype == SeedType::SEED_HYPNOSHROOM ||
        theSeedtype == SeedType::SEED_DOOMSHROOM ||
        theSeedtype == SeedType::SEED_ICESHROOM ||
        theSeedtype == SeedType::SEED_MAGNETSHROOM ||
        theSeedtype == SeedType::SEED_SCAREDYSHROOM ||
        theSeedtype == SeedType::SEED_BRAVESHROOM ||
        theSeedtype == SeedType::SEED_GLOOMSHROOM ||
        theSeedtype == SeedType::SEED_ICYFUME ||
        theSeedtype == SeedType::SEED_LUMESHROOM ||
        theSeedtype == SeedType::SEED_MORTARSHROOM ||
        theSeedtype == SeedType::SEED_VOLTSHROOM ||
        theSeedtype == SeedType::SEED_FIRESHROOM;
}

//0x467EA0
bool Plant::IsAquatic(SeedType theSeedType)
{
    return
        theSeedType == SeedType::SEED_LILYPAD ||
        theSeedType == SeedType::SEED_TANGLEKELP ||
        theSeedType == SeedType::SEED_SEASHROOM ||
        theSeedType == SeedType::SEED_PINKSTAR ||
        theSeedType == SeedType::SEED_CATTAIL;
}

bool Plant::IsFlying(SeedType theSeedtype)
{
    return theSeedtype == SeedType::SEED_INSTANT_COFFEE || theSeedtype == SeedType::SEED_FLYING_GARLIC;
}

bool Plant::IsHovering(SeedType theSeedtype)
{
    return theSeedtype == SeedType::SEED_BLOODORANGE;
}

//0x467EC0
bool Plant::IsUpgrade(SeedType theSeedtype)
{
    return 
        theSeedtype == SeedType::SEED_GATLINGPEA ||
        theSeedtype == SeedType::SEED_TWINSUNFLOWER ||
        theSeedtype == SeedType::SEED_GLOOMSHROOM ||
        theSeedtype == SeedType::SEED_CATTAIL ||
        theSeedtype == SeedType::SEED_WINTERMELON ||
        theSeedtype == SeedType::SEED_GOLD_MAGNET ||
        theSeedtype == SeedType::SEED_SPIKEROCK ||
        theSeedtype == SeedType::SEED_COBCANNON ||
        theSeedtype == SeedType::SEED_ICYFUME ||
        theSeedtype == SeedType::SEED_QUEENPEA ||
        theSeedtype == SeedType::SEED_PLASMAPEA ||
        theSeedtype == SeedType::SEED_SHOOTINGSTAR ||
        theSeedtype == SeedType::SEED_FLAMEWOOD ||
        theSeedtype == SeedType::SEED_VINENUT ||
        theSeedtype == SeedType::SEED_THORNMOSS ||
        theSeedtype == SeedType::SEED_BRAVESHROOM ||
        theSeedtype == SeedType::SEED_ECACTUS ||
        theSeedtype == SeedType::SEED_SUPERCHOMP;
}

//0x467EF0
Rect Plant::GetPlantRect()
{
    Rect aRect;
    if (mSeedType == SeedType::SEED_TALLNUT || mSeedType == SeedType::SEED_VINENUT)
    {
        aRect = Rect(mX + 10, mY, mWidth, mHeight);
    }
    else if (mSeedType == SeedType::SEED_PUMPKINSHELL)
    {
        aRect = Rect(mX, mY, mWidth - 20, mHeight);
    }
    else if (mSeedType == SeedType::SEED_COBCANNON)
    {
        aRect = Rect(mX, mY, 140, 80);
    }
    else
    {
        aRect = Rect(mX + 10, mY, mWidth - 20, mHeight);
    }

    return aRect;
}

//0x467F90
Rect Plant::GetPlantAttackRect(PlantWeapon thePlantWeapon)
{
    Rect aRect;
    if (mApp->IsWallnutBowlingLevel())
    {
        aRect = Rect(mX, mY, mWidth - 20, mHeight);
    }
    else if (thePlantWeapon == PlantWeapon::WEAPON_SECONDARY && (mSeedType == SeedType::SEED_SPLITPEA || mSeedType == SeedType::SEED_REVERSE_THREEPEATER))
    {
        aRect = Rect(0, mY, mX + 16, mHeight);
    }
    else switch (mSeedType)
    {
    case SeedType::SEED_LEFTPEATER:         //aRect = Rect(0,             mY,             mX,                 mHeight);               break;
    case SeedType::SEED_REVERSE_PEASHOOTER: //aRect = Rect(0,             mY,             mX,                 mHeight);               break;
    case SeedType::SEED_REVERSE_SNOWPEA:    aRect = Rect(0,             mY,             mX,                 mHeight);               break;
    case SeedType::SEED_SQUASH:             aRect = Rect(mX + 20,       mY,             mWidth - 35,        mHeight);               break;
    case SeedType::SEED_CHOMPER:            aRect = Rect(mX + 80,       mY,             40,                 mHeight);               break;
    case SeedType::SEED_REVERSE_CHOMPER:    aRect = Rect(mX - 80,       mY,             40,                 mHeight);               break;
    case SeedType::SEED_CHARD_GUARD:        aRect = Rect(mX + 40,       mY,             120,                mHeight);               break;
    case SeedType::SEED_SHRINK:             //aRect = Rect(mX - 80,       mY - 80,        240,                mHeight);               break;
    case SeedType::SEED_BONKCHOY:           aRect = Rect(mX - 80,       mY - 80,        240,                mHeight);               break;
    case SeedType::SEED_GHOSTPEPPER:        aRect = Rect(mX - 80,       mY,             240,                mHeight);               break;
    case SeedType::SEED_SUPERCHOMP:         aRect = Rect(mX + 80,       mY,             40,                 mHeight);               break;
    case SeedType::SEED_THORNMOSS:
    case SeedType::SEED_SPIKEWEED:
    case SeedType::SEED_SPIKEROCK:          aRect = Rect(mX + 20,       mY,             mWidth - 50,        mHeight);               break;
    case SeedType::SEED_POTATOMINE:         aRect = Rect(mX,            mY,             mWidth - 25,        mHeight);               break;
    case SeedType::SEED_TORCHWOOD:          //aRect = Rect(mX + 50,       mY,             30,                 mHeight);               break;
    case SeedType::SEED_FLAMEWOOD:          aRect = Rect(mX + 50,       mY,             30,                 mHeight);               break;
    case SeedType::SEED_PULTSHROOM:         aRect = Rect(mX + 60,       mY,             500,                mHeight);               break;
    case SeedType::SEED_MORTARSHROOM:       aRect = Rect(mX + 240,      mY,             500,                mHeight);               break;
    case SeedType::SEED_REVERSE_PUFFSHROOM: aRect = Rect(mX - 200,      mY,             230,                mHeight);               break;
    case SeedType::SEED_PUFFSHROOM:  
    case SeedType::SEED_SEASHROOM:          aRect = Rect(mX + 60,       mY,             230,                mHeight);               break;
    case SeedType::SEED_FUMESHROOM:         //aRect = Rect(mX + 60,       mY,             340,                mHeight);               break;
    case SeedType::SEED_ICYFUME:            aRect = Rect(mX + 60,       mY,             340,                mHeight);               break;
    case SeedType::SEED_GLOOMSHROOM:        aRect = Rect(mX - 80,       mY - 80,        240,                240);                   break;
    case SeedType::SEED_TANGLEKELP:         aRect = Rect(mX,            mY,             mWidth,             mHeight);               break;
    case SeedType::SEED_CATTAIL:            //aRect = Rect(-BOARD_WIDTH,  -BOARD_HEIGHT,  BOARD_WIDTH * 2,    BOARD_HEIGHT * 2);      break;
    case SeedType::SEED_BEE_SHOOTER:        aRect = Rect(-BOARD_WIDTH,  -BOARD_HEIGHT,  BOARD_WIDTH * 2,    BOARD_HEIGHT * 2);      break;
    case SeedType::SEED_REED:               aRect = Rect(mX + 60,       -BOARD_HEIGHT,  BOARD_WIDTH,        BOARD_HEIGHT * 2);      break;
    case SeedType::SEED_VOLTSHROOM:         aRect = Rect(mX - 160,      mY - 80,        400,                240);      break;
    default:                                aRect = Rect(mX + 60,       mY,             BOARD_WIDTH,        mHeight);               break;
    }
    
    if (mHypnotized) aRect = Rect(0, mY, mX, mHeight);
    if ((mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON) && mSeedType == SEED_PULTSHROOM)  aRect = Rect(mX + 60, mY, 230, mHeight);

    return aRect;
}

//0x4681E0
void Plant::PreloadPlantResources(SeedType theSeedType)
{
    const PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
    if (aPlantDef.mReanimationType != ReanimationType::REANIM_NONE)
    {
        ReanimatorEnsureDefinitionLoaded(aPlantDef.mReanimationType, true);
    }

    if (theSeedType == SeedType::SEED_CHERRYBOMB)
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_ZOMBIE_CHARRED, true);
    }
    else if (theSeedType == SeedType::SEED_JALAPENO)
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_JALAPENO_FIRE, true);
    }
    else if (theSeedType == SeedType::SEED_BLOODORANGE)
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_ZOMBIE_CHARRED, true);
    }
    else if (theSeedType == SeedType::SEED_PICKLEPEPPER)
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_PICKLED_FIRE, true);
    }
    else if (theSeedType == SeedType::SEED_CHILLYPEPPER)
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_JALAPENO_FIRE, true);
    }
    else if (theSeedType == SeedType::SEED_TORCHWOOD)
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_FIRE_PEA, true);
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_JALAPENO_FIRE, true);
    }
    else if (theSeedType == SeedType::SEED_FLAMEWOOD)
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_PLASMA_PEA, true);
    }
    else if (Plant::IsNocturnal(theSeedType))
    {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_SLEEPING, true);
    }
}

//0x468280
void Plant::PlayIdleAnim(float theRate)
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim)
    {
        PlayBodyReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 20, theRate);
        if (mApp->IsIZombieLevel())
        {
            aBodyReanim->mAnimRate = 0.0f;
        }
    }
}
void Plant::PlayCustomIdleAnim(float theRate, const char* theTrackNamet)
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim)
    {
        PlayBodyReanim(theTrackNamet, ReanimLoopType::REANIM_LOOP, 20, theRate);
        if (mApp->IsIZombieLevel())
        {
            aBodyReanim->mAnimRate = 0.0f;
        }
    }
}
int PlantDefinition::getPage()
{
    if (thePage != -10000) return thePage;
    int realIndex = -1;
    for (int i = 0; i < NUM_SEED_TYPES; i++)
    {
        if (true) realIndex++;
        if (this->mSeedType == gPlantDefs[i].mSeedType) return (realIndex / 49);
    }
}

void Plant::MovePlantLeft(int theGridX, int theGridY)
{
    Plant* aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant))
    {
        if (aPlant->mPlantCol == theGridX && aPlant->mRow == theGridY && aPlant->mSeedType != SEED_GRAVE)
        {
            if (mBoard->CanPlantAt(aPlant->mPlantCol - 1, aPlant->mRow, aPlant->mSeedType))
            {
                MovePlantLeft(aPlant->mPlantCol - 1, aPlant->mRow);
            }
            GridItem* aGridItem = nullptr;
            while (mBoard->IterateGridItems(aGridItem))
            {
                if (aGridItem->mGridY == aPlant->mRow && aGridItem->mGridX == aPlant->mPlantCol && aGridItem->mGridItemType == GridItemType::GRIDITEM_LADDER)
                {
                    aGridItem->GridItemDie();
                }
            }
            aPlant->mPlantCol--;
            aPlant->mMoveOffset = 80;
            aPlant->mRenderOrder = CalcRenderOrder();
            bool isOnCob = false;
            Plant* cobPlant = nullptr;
            while (mBoard->IteratePlants(cobPlant))
            {
                if (cobPlant->mPlantCol == aPlant->mPlantCol - 1 && cobPlant->mSeedType == SeedType::SEED_COBCANNON)
                {
                    isOnCob = true;
                }
            }
            if (aPlant->mPlantCol < 0 || isOnCob)
            {
                aPlant->Die();
            }
        }
    }
}

ReanimationType Plant::SetUpCostumes(ReanimationType theReanimationType)
{
    switch (theReanimationType)
    {
    case REANIM_LEMONADE:		return REANIM_LEMONADE_LEGACY;
    default:						TOD_ASSERT();
    }
}

float Plant::PlantTargetLeadX(float theTime)
{
    Rect aPlantRect = GetPlantRect();
    float aCurrentPosX = aPlantRect.mX + aPlantRect.mWidth / 2;
    return aCurrentPosX;
}

void Plant::LightningReedFire()
{
    //I hope you guys dont mind me experimenting :3
    Zombie* aZombie = nullptr;
    GridItem* aGI = nullptr;
    Plant* aPlant = nullptr;
    /*if (aTarget = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY))
    {
        //lol
    }
    else if (aTarget = FindTargetGridItem(mRow))
    {
        aType1 = 1;
    }
    else if (aTarget = FindTargetPlant(mRow))
    {
        aType1 = 2;
    }*/
    aZombie = FindTargetZombie(mRow, PlantWeapon::WEAPON_PRIMARY);
    aGI = FindTargetGridItem(mRow);
    aPlant = FindTargetPlant(mRow);
    if (!(aZombie || aGI || aPlant)) return;
    int aZWeight, aGWeight, aPWeight;

    aZWeight = aZombie ? -aZombie->GetZombieRect().mX : 0;
    aGWeight = aGI ? -aGI->GetGridItemRect().mX : 0;
    aPWeight = aPlant ? -aPlant->GetPlantRect().mX : 0;
    /*char aType = aZWeight > aGWeight ?
        aZWeight > aPWeight ? */
    mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
    unsigned aRangeFlags = GetDamageRangeFlags(WEAPON_PRIMARY);
    int aHitRow;
    int aHitCol;
    Rect aTargetRect;
    SexyVector2 aCenterPoint;
    //int aType = help(aZWeight, aGWeight, aPWeight);
    int aType = 3;
    int aBestWeight = 1;
    //brutforcing it here for fucks sake
    if (aZombie)
    {
        aType = 0;
        aBestWeight = aZWeight;
    }
    if (aGI)
    {
        if (aGWeight > aBestWeight || aBestWeight == 1)
        {
            aType = 1;
            aBestWeight = aGWeight;
        }
    }
    if (aPlant)
    {
        if (aPWeight > aBestWeight || aBestWeight == 1)
        {
            aType = 2;
        }
    }

    void* aHits[3] = { nullptr, nullptr, nullptr };
    switch (aType)
    {
    case 0:
    {
        aZombie->TakeDamage(aZombie->mZombiePhase == PHASE_BALLOON_FLYING ? 2 : 10, 1U);
        aTargetRect = aZombie->GetZombieRect();
        aHitRow = aZombie->mRow;
        aHitCol = mBoard->PixelToGridXKeepOnBoard(aCenterPoint.x, aCenterPoint.y);
        aHits[0] = aZombie;
        break;
    }
    case 1:
    {
        aGI->mJustGotShotCounter = 25;
        aGI->mHealth -= 10;
        aHitRow = aGI->mGridY;
        aHitCol = aGI->mGridX;
        aTargetRect = aGI->GetGridItemRect();
        aHits[0] = aGI;
        break;
    }
    case 2:
    {
        aPlant->mPlantHealth -= 10;
        aPlant->mEatenFlashCountdown = max(aPlant->mEatenFlashCountdown, 25);
        aHitRow = aPlant->mRow;
        aHitCol = aPlant->mPlantCol;
        aTargetRect = aPlant->GetPlantRect();
        aHits[0] = aPlant;
        break;
    }
    case 3:
        return;
    }
    aCenterPoint = SexyVector2(aTargetRect.mX + aTargetRect.mWidth / 2, aTargetRect.mY + aTargetRect.mHeight / 2);
    DrawChain(mX + 50, aCenterPoint.x, mY - 15, aCenterPoint.y, 0);
    /*if (!aZombie)
    {
        if (!(aGI = FindTargetGridItem(mRow)))
        {
            if (!(aPlant = FindTargetPlant(mRow)))return;
            else aType = 2;
        }
        else aType = 1;
    }*/
    /*aZombie->TakeDamage(/*aZombie->mZombiePhase == PHASE_BALLOON_FLYING ? 1 : 10, 1U);
    mApp->PlayFoley(FoleyType::FOLEY_SPLAT);
    Zombie* aZombies[3]{ aZombie, nullptr, nullptr };
    unsigned aRangeFlags = GetDamageRangeFlags(WEAPON_PRIMARY);
    Rect aZombieRect = aZombie->GetZombieRect();
    DrawChain(mX + 50, aZombieRect.mX + aZombieRect.mWidth / 2, mY - 15, aZombieRect.mY + aZombieRect.mHeight / 2, 250);*/
    for (int aHitCount = 1; aHitCount < 4; aHitCount++)
    {
        aZombie = nullptr;
        void* aBestTarget = nullptr;
        int aWeight, aBestWeight = 0;
        bool hasHit = false;
        while (mBoard->IterateZombies(aZombie))
        {
            if (abs(aZombie->mRow - aHitRow) > 1)
                continue;
            if (!aZombie->EffectedByDamage(aRangeFlags))
                continue;
            bool alreadyHit = false;
            for (int i = 0; i < aHitCount; i++)
            {
                if (aHits[i] == aZombie)
                {
                    alreadyHit = true;
                    break;
                }
            }
            if (alreadyHit) continue;
            if (mBoard->GetBushAt(mBoard->PixelToGridX(aZombie->mX + 75, aZombie->mY), mRow) &&
                mBoard->GetBushAt(mBoard->PixelToGridX(aZombie->mX + 45, mY), aZombie->mRow) &&
                mX < 680)
                continue;
            Rect aRangeRect = Rect(aCenterPoint.x - 120, aCenterPoint.y - 120, 240, 240);
            Rect aZombieRect = aZombie->GetZombieRect();
            if (GetRectOverlap(aRangeRect, aZombieRect) <= 0)
                continue;
            SexyVector2 aZombieCenter = SexyVector2(aZombieRect.mX + aZombieRect.mWidth / 2, aZombieRect.mY + aZombieRect.mHeight / 2);
            aWeight = (aZombieCenter.x - aCenterPoint.x) * (aZombieCenter.x - aCenterPoint.x) + (aZombieCenter.y - aCenterPoint.y) * (aZombieCenter.y - aCenterPoint.y);
            hasHit = true;
            if (aWeight < aBestWeight || aBestTarget == nullptr)
            {
                aBestTarget = aZombie;
                aBestWeight = aWeight;
            }
        }
        if (hasHit)
        {
            aZombie = (Zombie*)aBestTarget;
            aTargetRect = aZombie->GetZombieRect();
            SexyVector2 aOldCenter = aCenterPoint;
            aCenterPoint = SexyVector2(aTargetRect.mX + aTargetRect.mWidth / 2, aTargetRect.mY + aTargetRect.mHeight / 2);
            aHitRow = aZombie->mRow;
            aHitCol = mBoard->PixelToGridXKeepOnBoard(aCenterPoint.x, aCenterPoint.y);
            //aTarget = aBestTarget;
            DrawChain(aOldCenter.x, aCenterPoint.x, aOldCenter.y, aCenterPoint.y, 0);
            aZombie->TakeDamage(aZombie->mZombiePhase == PHASE_BALLOON_FLYING ? 3 : 10, 1U);
            if (aHitCount < 3)
                aHits[aHitCount] = aZombie;
            continue;
        }
        aGI = nullptr;
        //aBestTarget = nullptr;
        //aWeight, aBestWeight = 0;
        while (mBoard->IterateGridItems(aGI))
        {
            if (aGI->mGridItemType != GRIDITEM_WOOD_LOG) continue;
            if (abs(aGI->mGridY - aHitRow) > 1)
                continue;
            if (abs(aGI->mGridX - aHitCol) > 1)
                continue;
            bool alreadyHit = false;
            for (int i = 0; i < aHitCount; i++)
            {
                if (aHits[i] == aGI)
                {
                    alreadyHit = true;
                    break;
                }
            }
            if (alreadyHit) continue;
            hasHit = true;
            break;
        }
        if (hasHit)
        {
            aTargetRect = aGI->GetGridItemRect();
            SexyVector2 aOldCenter = aCenterPoint;
            aCenterPoint = SexyVector2(aTargetRect.mX + aTargetRect.mWidth / 2, aTargetRect.mY + aTargetRect.mHeight / 2);
            DrawChain(aOldCenter.x, aCenterPoint.x, aOldCenter.y, aCenterPoint.y, 0);
            if (aHitCount < 3)
                aHits[aHitCount] = aGI;
            aGI->mJustGotShotCounter = 25;
            aGI->mHealth -= 10;
            aHitRow = aGI->mGridY;
            aHitCol = aGI->mGridX;
            continue;
        }
        aPlant = nullptr;
        //aBestTarget = nullptr;
        //aWeight, aBestWeight = 0;
        while (mBoard->IteratePlants(aPlant))
        {
            if (mHypnotized == aPlant->mHypnotized && aPlant->mSeedType != SeedType::SEED_GRAVE)
                continue;
            if (abs(aPlant->mRow - aHitRow) > 1)
                continue;
            if (abs(aPlant->mPlantCol - aHitCol) > 1)
                continue;
            bool alreadyHit = false;
            for (int i = 0; i < aHitCount; i++)
            {
                if (aHits[i] == aPlant)
                {
                    alreadyHit = true;
                    break;
                }
            }
            if (alreadyHit) continue;
            hasHit = true;
            break;
        }
        if (!hasHit)    return;
        aTargetRect = aPlant->GetPlantRect();
        SexyVector2 aOldCenter = aCenterPoint;
        aCenterPoint = SexyVector2(aTargetRect.mX + aTargetRect.mWidth / 2, aTargetRect.mY + aTargetRect.mHeight / 2);
        DrawChain(aOldCenter.x, aCenterPoint.x, aOldCenter.y, aCenterPoint.y, 0);
        aHitRow = aPlant->mRow;
        aHitCol = aPlant->mPlantCol;
        if (aHitCount < 3)
            aHits[aHitCount] = aPlant;
        aPlant->mPlantHealth -= 10;
        aPlant->mEatenFlashCountdown = max(aPlant->mEatenFlashCountdown, 25);

        //void* aLastTarget = 
    }
        /*
        aZombie = nullptr;
        Zombie* aBestZombie = nullptr;
        int aWeight, aBestWeight = 0;
        Zombie* aLastZombie = aZombies[aHitCount - 1];
        Rect aLastZombieRect;
        bool hasHit = false;

        while (mBoard->IterateZombies(aZombie))
        {
            //CCHECK FOR ADJACENT ROW
            if (abs(aZombie->mRow - aLastZombie->mRow) > 1)
                continue;

            if (!aZombie->EffectedByDamage(aRangeFlags))
                continue;

            bool alreadyHit = false;
            for (int i = 0; i < aHitCount; i++)
            {
                if (aZombies[i] == aZombie)
                {
                    alreadyHit = true;
                    break;
                }
            }
            if (alreadyHit) continue;

            aLastZombieRect = aLastZombie->GetZombieRect();
            Rect aRangeRect = Rect(aLastZombieRect.mX - 120, aLastZombieRect.mY - 120, 240, 240);
            aZombieRect = aZombie->GetZombieRect();
            if (GetRectOverlap(aZombie->GetZombieRect(), aRangeRect) <= 0)
                continue;

            aWeight = (aZombie->mPosX - aLastZombie->mPosX) * (aZombie->mPosX - aLastZombie->mPosX) + (aZombie->mPosY - aLastZombie->mPosY) * (aZombie->mPosY - aLastZombie->mPosY);
            if (aWeight < aBestWeight || aBestZombie == nullptr)
            {
                hasHit = true;
                aBestZombie = aZombie;
                aBestWeight = aWeight;
            }

            /*
            ;
        }
        if (!hasHit)
            return;

        aZombie = aBestZombie;
        aZombieRect = aZombie->GetZombieRect();

        DrawChain(aZombieRect.mX + aZombieRect.mWidth / 2, aLastZombieRect.mX + aLastZombieRect.mWidth / 2, aZombieRect.mY + aZombieRect.mHeight / 2, aLastZombieRect.mY + aLastZombieRect.mHeight / 2, 250);
        aZombie->TakeDamage(aZombie->mZombiePhase == PHASE_BALLOON_FLYING ? 3 : 10, 1U);
        if (aHitCount < 3)
            aZombies[aHitCount] = aZombie; */
}

void Plant::DrawChain(int X1, int X2, int Y1, int Y2, int aPointDistance)
{
    Projectile* aProjectile = mBoard->AddProjectile(X1, Y1, mRenderOrder + 2, mRow, ProjectileType::PROJECTILE_REED_ZAP);
    aProjectile->mWidth = X2 - X1;
    aProjectile->mHeight = Y2 - Y1;
    aProjectile->TransformZap();
    /*int aPoints = sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2)) / 10;
    for (int i = 0; i <= aPoints; i++)
    {
        int aX = TodAnimateCurve(0, aPoints, i, X1, X2, TodCurves::CURVE_LINEAR);
        int aY = TodAnimateCurve(0, aPoints, i, Y1, Y2, TodCurves::CURVE_LINEAR);
        mApp->AddTodParticle(aX, aY, RENDER_LAYER_GROUND + 1, ParticleEffect::PARTICLE_PEA_SPLAT);
    }*/
}

int Plant::GetAttackRowRange()
{
    switch (mSeedType)
    {
    case SEED_GLOOMSHROOM:
    case SEED_REED:
    case SEED_VOLTSHROOM:
        return 1;
    case SEED_CATTAIL:
    case SEED_MORTARSHROOM:
        return 99;
    }
    return 0;
}

void Plant::VoltShroomFire()
{
    void*   aTargets[4]{ nullptr, nullptr, nullptr, nullptr };
    char    aTypes[4]{ 0 };
    int     aBestWeights[4]{ 0 };
    Zombie* aZombie = nullptr;
    Rect aAttackRect = GetPlantAttackRect();
    int aHitCount = 0;
    while (mBoard->IterateZombies(aZombie))
    {

        int aRowDiff = abs(aZombie->mRow - mRow);
        if (aRowDiff > 1)
            continue;

        Rect aZombieRect = aZombie->GetZombieRect();
        if (!aZombie->EffectedByDamage(GetDamageRangeFlags()))
            continue;

        if (GetRectOverlap(aAttackRect, aZombieRect) <= 0)
            continue;

        if (mBoard->GetBushAt(mBoard->PixelToGridX(aZombie->mX + 75, aZombie->mY), mRow) &&
            mBoard->GetBushAt(mBoard->PixelToGridX(aZombie->mX + 45, mY), aZombie->mRow) &&
            mX < 680)
            continue;
        int aX = aZombieRect.mX + aZombieRect.mWidth / 2;
        int aY = aZombieRect.mY + aZombieRect.mHeight / 2;

        int aWeight = (aX - mX - 40) * (aX - mX - 40) + (aRowDiff * 100) * (aRowDiff * 100);
        if (aHitCount < 4)
        {
            aTargets[aHitCount] = aZombie;
            aBestWeights[aHitCount] = aWeight;
            ++aHitCount;
        }
        else
        {
            int aWorstWeight = aBestWeights[0];
            int aWorstID = 0;
            for (int i = 1; i < 4; i++)
            {
                if (aBestWeights[i] > aWorstWeight)
                {
                    aWorstID = i;
                    aWorstWeight = aBestWeights[i];
                }
            }
            if (aWeight < aWorstWeight)
            {
                aTargets[aWorstID] = aZombie;
                aBestWeights[aWorstID] = aWeight;
                aTypes[aWorstID] = 0;
            }
        }
    }
    GridItem* aGI = nullptr;
    while (mBoard->IterateGridItems(aGI))
    {
        if (aGI->mGridItemType != GRIDITEM_WOOD_LOG)
            continue;
        int aRowDiff = abs(aGI->mGridY - mRow);
        if (aRowDiff > 1)
            continue;

        Rect aGIRect = aGI->GetGridItemRect();
        //if (!aZombie->EffectedByDamage(GetDamageRangeFlags()))
            //continue;

        if (GetRectOverlap(aAttackRect, aGIRect) <= 0)
            continue;

        int aX = aGIRect.mX + aGIRect.mWidth / 2;
        int aY = aGIRect.mY + aGIRect.mHeight / 2;

        int aWeight = (aX - mX - 40) * (aX - mX - 40) + (aRowDiff * 100) * (aRowDiff * 100);
        if (aHitCount < 4)
        {
            aTargets[aHitCount] = aGI;
            aBestWeights[aHitCount] = aWeight;
            ++aHitCount;
        }
        else
        {
            int aWorstWeight = aBestWeights[0];
            int aWorstID = 0;
            for (int i = 1; i < 4; i++)
            {
                if (aBestWeights[i] > aWorstWeight)
                {
                    aWorstID = i;
                    aWorstWeight = aBestWeights[i];
                }
            }
            if (aWeight < aWorstWeight)
            {
                aTargets[aWorstID] = aGI;
                aBestWeights[aWorstID] = aWeight;
                aTypes[aWorstID] = 1;
            }
        }
    }
    Plant* aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant))
    {
        if (aPlant->mHypnotized == mHypnotized && aPlant->mSeedType != SEED_GRAVE)
            continue;
        int aRowDiff = abs(aPlant->mRow - mRow);
        if (aRowDiff > 1)
            continue;

        Rect aPlantRect = aPlant->GetPlantRect();
        //if (!aZombie->EffectedByDamage(GetDamageRangeFlags()))
            //continue;

        if (abs(mPlantCol - aPlant->mPlantCol) > 2)
            continue;

        int aX = aPlantRect.mX + aPlantRect.mWidth / 2;
        int aY = aPlantRect.mY + aPlantRect.mHeight / 2;

        int aWeight = (aX - mX - 40) * (aX - mX - 40) + (aRowDiff * 100) * (aRowDiff * 100);
        if (aHitCount < 4)
        {
            aTargets[aHitCount] = aPlant;
            aBestWeights[aHitCount] = aWeight;
            ++aHitCount;
        }
        else
        {
            int aWorstWeight = aBestWeights[0];
            int aWorstID = 0;
            for (int i = 1; i < 4; i++)
            {
                if (aBestWeights[i] > aWorstWeight)
                {
                    aWorstID = i;
                    aWorstWeight = aBestWeights[i];
                }
            }
            if (aWeight < aWorstWeight)
            {
                aTargets[aWorstID] = aPlant;
                aBestWeights[aWorstID] = aWeight;
                aTypes[aWorstID] = 2;
            }
        }
    }

    if (aHitCount <= 0)
        return;

    mApp->PlayFoley(FOLEY_SPLAT);
    int aDamage = 80 / aHitCount;
    for (int i = 0; i < aHitCount; i++)
    {
        switch (aTypes[i])
        {
        case 0:
        {
            aZombie = (Zombie*)aTargets[i];
            Rect aZombieRect = aZombie->GetZombieRect();
            int aX = aZombieRect.mX + aZombieRect.mWidth / 2;
            int aY = aZombieRect.mY + aZombieRect.mHeight / 2;

            DrawChain(mX + 40, aX, mY + 40, aY, 10);

            aZombie->TakeDamage(aDamage, 1U);
            break;
        }
        case 1:
        {
            aGI = (GridItem*)aTargets[i];
            Rect aGIRect = aGI->GetGridItemRect();
            int aX = aGIRect.mX + aGIRect.mWidth / 2;
            int aY = aGIRect.mY + aGIRect.mHeight / 2;

            DrawChain(mX + 40, aX, mY + 40, aY, 10);

            aGI->mJustGotShotCounter = 25;
            aGI->mHealth -= aDamage;
            break;
        }
        case 2:
        {
            aPlant = (Plant*)aTargets[i];
            Rect aPlantRect = aPlant->GetPlantRect();
            int aX = aPlantRect.mX + aPlantRect.mWidth / 2;
            int aY = aPlantRect.mY + aPlantRect.mHeight / 2;

            DrawChain(mX + 40, aX, mY + 40, aY, 10);

            aPlant->mPlantHealth -= aDamage;
            aPlant->mEatenFlashCountdown = max(aPlant->mEatenFlashCountdown, 25);
            break;
        }
        }
    }
}
