/* This file is part of PKSV
> MIT License
> Copyright (c) 2016/17 Bernardo Giordano
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE. */

#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>
#include <stdio.h>
#include <time.h>
#include "graphic.h"
#include "fx.h"
#include "editor.h"
#include "http.h"

int lookup[] = {0x0, 0x1, 0x2, 0x4, 0x5, 0x3};

sftd_font *fontBold18, *fontBold15, *fontBold12, *fontBold9; 
sf2d_texture *upperTextGS, *male, *female, *editorBar, *backgroundTop, *balls, *shinyStar, *normalBar, *topBorder, *gameSelectorTop, *mainMenuBottom, *left, *right, *spritesSmall, *warningTop, *warningBottom, *boxView, *infoView, *selector, *back, *pokemonBufferBox, *cleanTop, *item, *alternativeSpritesSmall;

char *gamesList[] = {"X", "Y", "OR", "AS", "S", "M"};

static char *abilities[] = {"None", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy", "Damp", "Limber", "Sand Veil", "Static", "Volt Absorb", "Water Absorb", "Oblivious", "Cloud Nine", "Compound Eyes", "Insomnia", "Color Change", "Immunity", "Flash Fire", "Shield Dust", "Own Tempo", "Suction Cups", "Intimidate", "Shadow Tag", "Rough Skin", "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Clear Body", "Natural Cure", "Lightning Rod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace", "Huge Power", "Poison Point", "Inner Focus", "Magma Armor", "Water Veil", "Magnet Pull", "Soundproof", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Early Bird", "Flame Body", "Run Away", "Keen Eye", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Cute Charm", "Plus", "Minus", "Forecast", "Sticky Hold", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze", "Overgrow", "Blaze", "Torrent", "Swarm", "Rock Head", "Drought", "Arena Trap", "Vital Spirit", "White Smoke", "Pure Power", "Shell Armor", "Air Lock", "Tangled Feet", "Motor Drive", "Rivalry", "Steadfast", "Snow Cloak", "Gluttony", "Anger Point", "Unburden", "Heatproof", "Simple", "Dry Skin", "Download", "Iron Fist", "Poison Heal", "Adaptability", "Skill Link", "Hydration", "Solar Power", "Quick Feet", "Normalize", "Sniper", "Magic Guard", "No Guard", "Stall", "Technician", "Leaf Guard", "Klutz", "Mold Breaker", "Super Luck", "Aftermath", "Anticipation", "Forewarn", "Unaware", "Tinted Lens", "Filter", "Slow Start", "Scrappy", "Storm Drain", "Ice Body", "Solid Rock", "Snow Warning", "Honey Gather", "Frisk", "Reckless", "Multitype", "Flower Gift", "Bad Dreams", "Pickpocket", "Sheer Force", "Contrary", "Unnerve", "Defiant", "Defeatist", "Cursed Body", "Healer", "Friend Guard", "Weak Armor", "Heavy Metal", "Light Metal", "Multiscale", "Toxic Boost", "Flare Boost", "Harvest", "Telepathy", "Moody", "Overcoat", "Poison Touch", "Regenerator", "Big Pecks", "Sand Rush", "Wonder Skin", "Analytic", "Illusion", "Imposter", "Infiltrator", "Mummy", "Moxie", "Justified", "Rattled", "Magic Bounce", "Sap Sipper", "Prankster", "Sand Force", "Iron Barbs", "Zen Mode", "Victory Star", "Turboblaze", "Teravolt", "Aroma Veil", "Flower Veil", "Cheek Pouch", "Protean", "Fur Coat", "Magician", "Bulletproof", "Competitive", "Strong Jaw", "Refrigerate", "Sweet Veil", "Stance Change", "Gale Wings", "Mega Launcher", "Grass Pelt", "Symbiosis", "Tough Claws", "Pixilate", "Gooey", "Aerilate", "Parental Bond", "Dark Aura", "Fairy Aura", "Aura Break", "Primordial Sea", "Desolate Land", "Delta Stream", "Stamina", "Wimp Out", "Emergency Exit", "Water Compaction", "Merciless", "Shields Down", "Stakeout", "Water Bubble", "Steelworker", "Berserk", "Slush Rush", "Long Reach", "Liquid Voice", "Triage", "Galvanize", "Surge Surfer", "Schooling", "Disguise", "Battle Bond", "Power Construct", "Corrosion", "Comatose", "Queenly Majesty", "Innards Out", "Dancer", "Battery", "Fluffy", "Dazzling", "Soul-Heart", "Tangling Hair", "Receiver", "Power of Alchemy", "Beast Boost", "RKS System", "Electric Surge", "Psychic Surge", "Misty Surge", "Grassy Surge", "Full Metal Body", "Shadow Shield", "Prism Armor"};
static char *moves[] = {"None", "Pound", "Karate Chop", "Double Slap", "Comet Punch", "Mega Punch", "Pay Day", "Fire Punch", "Ice Punch", "Thunder Punch", "Scratch", "Vice Grip", "Guillotine", "Razor Wind", "Swords Dance", "Cut", "Gust", "Wing Attack", "Whirlwind", "Fly", "Bind", "Slam", "Vine Whip", "Stomp", "Double Kick", "Mega Kick", "Jump Kick", "Rolling Kick", "Sand Attack", "Headbutt", "Horn Attack", "Fury Attack", "Horn Drill", "Tackle", "Body Slam", "Wrap", "Take Down", "Thrash", "Double-Edge", "Tail Whip", "Poison Sting", "Twineedle", "Pin Missile", "Leer", "Bite", "Growl", "Roar", "Sing", "Supersonic", "Sonic Boom", "Disable", "Acid", "Ember", "Flamethrower", "Mist", "Water Gun", "Hydro Pump", "Surf", "Ice Beam", "Blizzard", "Psybeam", "Bubble Beam", "Aurora Beam", "Hyper Beam", "Peck", "Drill Peck", "Submission", "Low Kick", "Counter", "Seismic Toss", "Strength", "Absorb", "Mega Drain", "Leech Seed", "Growth", "Razor Leaf", "Solar Beam", "Poison Powder", "Stun Spore", "Sleep Powder", "Petal Dance", "String Shot", "Dragon Rage", "Fire Spin", "Thunder Shock", "Thunderbolt", "Thunder Wave", "Thunder", "Rock Throw", "Earthquake", "Fissure", "Dig", "Toxic", "Confusion", "Psychic", "Hypnosis", "Meditate", "Agility", "Quick Attack", "Rage", "Teleport", "Night Shade", "Mimic", "Screech", "Double Team", "Recover", "Harden", "Minimize", "Smokescreen", "Confuse Ray", "Withdraw", "Defense Curl", "Barrier", "Light Screen", "Haze", "Reflect", "Focus Energy", "Bide", "Metronome", "Mirror Move", "Self-Destruct", "Egg Bomb", "Lick", "Smog", "Sludge", "Bone Club", "Fire Blast", "Waterfall", "Clamp", "Swift", "Skull Bash", "Spike Cannon", "Constrict", "Amnesia", "Kinesis", "Soft-Boiled", "High Jump Kick", "Glare", "Dream Eater", "Poison Gas", "Barrage", "Leech Life", "Lovely Kiss", "Sky Attack", "Transform", "Bubble", "Dizzy Punch", "Spore", "Flash", "Psywave", "Splash", "Acid Armor", "Crabhammer", "Explosion", "Fury Swipes", "Bonemerang", "Rest", "Rock Slide", "Hyper Fang", "Sharpen", "Conversion", "Tri Attack", "Super Fang", "Slash", "Substitute", "Struggle", "Sketch", "Triple Kick", "Thief", "Spider Web", "Mind Reader", "Nightmare", "Flame Wheel", "Snore", "Curse", "Flail", "Conversion 2", "Aeroblast", "Cotton Spore", "Reversal", "Spite", "Powder Snow", "Protect", "Mach Punch", "Scary Face", "Feint Attack", "Sweet Kiss", "Belly Drum", "Sludge Bomb", "Mud-Slap", "Octazooka", "Spikes", "Zap Cannon", "Foresight", "Destiny Bond", "Perish Song", "Icy Wind", "Detect", "Bone Rush", "Lock-On", "Outrage", "Sandstorm", "Giga Drain", "Endure", "Charm", "Rollout", "False Swipe", "Swagger", "Milk Drink", "Spark", "Fury Cutter", "Steel Wing", "Mean Look", "Attract", "Sleep Talk", "Heal Bell", "Return", "Present", "Frustration", "Safeguard", "Pain Split", "Sacred Fire", "Magnitude", "Dynamic Punch", "Megahorn", "Dragon Breath", "Baton Pass", "Encore", "Pursuit", "Rapid Spin", "Sweet Scent", "Iron Tail", "Metal Claw", "Vital Throw", "Morning Sun", "Synthesis", "Moonlight", "Hidden Power", "Cross Chop", "Twister", "Rain Dance", "Sunny Day", "Crunch", "Mirror Coat", "Psych Up", "Extreme Speed", "Ancient Power", "Shadow Ball", "Future Sight", "Rock Smash", "Whirlpool", "Beat Up", "Fake Out", "Uproar", "Stockpile", "Spit Up", "Swallow", "Heat Wave", "Hail", "Torment", "Flatter", "Will-O-Wisp", "Memento", "Facade", "Focus Punch", "Smelling Salts", "Follow Me", "Nature Power", "Charge", "Taunt", "Helping Hand", "Trick", "Role Play", "Wish", "Assist", "Ingrain", "Superpower", "Magic Coat", "Recycle", "Revenge", "Brick Break", "Yawn", "Knock Off", "Endeavor", "Eruption", "Skill Swap", "Imprison", "Refresh", "Grudge", "Snatch", "Secret Power", "Dive", "Arm Thrust", "Camouflage", "Tail Glow", "Luster Purge", "Mist Ball", "Feather Dance", "Teeter Dance", "Blaze Kick", "Mud Sport", "Ice Ball", "Needle Arm", "Slack Off", "Hyper Voice", "Poison Fang", "Crush Claw", "Blast Burn", "Hydro Cannon", "Meteor Mash", "Astonish", "Weather Ball", "Aromatherapy", "Fake Tears", "Air Cutter", "Overheat", "Odor Sleuth", "Rock Tomb", "Silver Wind", "Metal Sound", "Grass Whistle", "Tickle", "Cosmic Power", "Water Spout", "Signal Beam", "Shadow Punch", "Extrasensory", "Sky Uppercut", "Sand Tomb", "Sheer Cold", "Muddy Water", "Bullet Seed", "Aerial Ace", "Icicle Spear", "Iron Defense", "Block", "Howl", "Dragon Claw", "Frenzy Plant", "Bulk Up", "Bounce", "Mud Shot", "Poison Tail", "Covet", "Volt Tackle", "Magical Leaf", "Water Sport", "Calm Mind", "Leaf Blade", "Dragon Dance", "Rock Blast", "Shock Wave", "Water Pulse", "Doom Desire", "Psycho Boost", "Roost", "Gravity", "Miracle Eye", "Wake-Up Slap", "Hammer Arm", "Gyro Ball", "Healing Wish", "Brine", "Natural Gift", "Feint", "Pluck", "Tailwind", "Acupressure", "Metal Burst", "U-turn", "Close Combat", "Payback", "Assurance", "Embargo", "Fling", "Psycho Shift", "Trump Card", "Heal Block", "Wring Out", "Power Trick", "Gastro Acid", "Lucky Chant", "Me First", "Copycat", "Power Swap", "Guard Swap", "Punishment", "Last Resort", "Worry Seed", "Sucker Punch", "Toxic Spikes", "Heart Swap", "Aqua Ring", "Magnet Rise", "Flare Blitz", "Force Palm", "Aura Sphere", "Rock Polish", "Poison Jab", "Dark Pulse", "Night Slash", "Aqua Tail", "Seed Bomb", "Air Slash", "X-Scissor", "Bug Buzz", "Dragon Pulse", "Dragon Rush", "Power Gem", "Drain Punch", "Vacuum Wave", "Focus Blast", "Energy Ball", "Brave Bird", "Earth Power", "Switcheroo", "Giga Impact", "Nasty Plot", "Bullet Punch", "Avalanche", "Ice Shard", "Shadow Claw", "Thunder Fang", "Ice Fang", "Fire Fang", "Shadow Sneak", "Mud Bomb", "Psycho Cut", "Zen Headbutt", "Mirror Shot", "Flash Cannon", "Rock Climb", "Defog", "Trick Room", "Draco Meteor", "Discharge", "Lava Plume", "Leaf Storm", "Power Whip", "Rock Wrecker", "Cross Poison", "Gunk Shot", "Iron Head", "Magnet Bomb", "Stone Edge", "Captivate", "Stealth Rock", "Grass Knot", "Chatter", "Judgment", "Bug Bite", "Charge Beam", "Wood Hammer", "Aqua Jet", "Attack Order", "Defend Order", "Heal Order", "Head Smash", "Double Hit", "Roar of Time", "Spacial Rend", "Lunar Dance", "Crush Grip", "Magma Storm", "Dark Void", "Seed Flare", "Ominous Wind", "Shadow Force", "Hone Claws", "Wide Guard", "Guard Split", "Power Split", "Wonder Room", "Psyshock", "Venoshock", "Autotomize", "Rage Powder", "Telekinesis", "Magic Room", "Smack Down", "Storm Throw", "Flame Burst", "Sludge Wave", "Quiver Dance", "Heavy Slam", "Synchronoise", "Electro Ball", "Soak", "Flame Charge", "Coil", "Low Sweep", "Acid Spray", "Foul Play", "Simple Beam", "Entrainment", "After You", "Round", "Echoed Voice", "Chip Away", "Clear Smog", "Stored Power", "Quick Guard", "Ally Switch", "Scald", "Shell Smash", "Heal Pulse", "Hex", "Sky Drop", "Shift Gear", "Circle Throw", "Incinerate", "Quash", "Acrobatics", "Reflect Type", "Retaliate", "Final Gambit", "Bestow", "Inferno", "Water Pledge", "Fire Pledge", "Grass Pledge", "Volt Switch", "Struggle Bug", "Bulldoze", "Frost Breath", "Dragon Tail", "Work Up", "Electroweb", "Wild Charge", "Drill Run", "Dual Chop", "Heart Stamp", "Horn Leech", "Sacred Sword", "Razor Shell", "Heat Crash", "Leaf Tornado", "Steamroller", "Cotton Guard", "Night Daze", "Psystrike", "Tail Slap", "Hurricane", "Head Charge", "Gear Grind", "Searing Shot", "Techno Blast", "Relic Song", "Secret Sword", "Glaciate", "Bolt Strike", "Blue Flare", "Fiery Dance", "Freeze Shock", "Ice Burn", "Snarl", "Icicle Crash", "V-create", "Fusion Flare", "Fusion Bolt", "Flying Press", "Mat Block", "Belch", "Rototiller", "Sticky Web", "Fell Stinger", "Phantom Force", "Trick-or-Treat", "Noble Roar", "Ion Deluge", "Parabolic Charge", "Forest’s Curse", "Petal Blizzard", "Freeze-Dry", "Disarming Voice", "Parting Shot", "Topsy-Turvy", "Draining Kiss", "Crafty Shield", "Flower Shield", "Grassy Terrain", "Misty Terrain", "Electrify", "Play Rough", "Fairy Wind", "Moonblast", "Boomburst", "Fairy Lock", "King’s Shield", "Play Nice", "Confide", "Diamond Storm", "Steam Eruption", "Hyperspace Hole", "Water Shuriken", "Mystical Fire", "Spiky Shield", "Aromatic Mist", "Eerie Impulse", "Venom Drench", "Powder", "Geomancy", "Magnetic Flux", "Happy Hour", "Electric Terrain", "Dazzling Gleam", "Celebrate", "Hold Hands", "Baby-Doll Eyes", "Nuzzle", "Hold Back", "Infestation", "Power-Up Punch", "Oblivion Wing", "Thousand Arrows", "Thousand Waves", "Land’s Wrath", "Light of Ruin", "Origin Pulse", "Precipice Blades", "Dragon Ascent", "Hyperspace Fury", "Breakneck Blitz", "Breakneck Blitz", "All-Out Pummeling", "All-Out Pummeling", "Supersonic Skystrike", "Supersonic Skystrike", "Acid Downpour", "Acid Downpour", "Tectonic Rage", "Tectonic Rage", "Continental Crush", "Continental Crush", "Savage Spin-Out", "Savage Spin-Out", "Never-Ending Nightmare", "Never-Ending Nightmare", "Corkscrew Crash", "Corkscrew Crash", "Inferno Overdrive", "Inferno Overdrive", "Hydro Vortex", "Hydro Vortex", "Bloom Doom", "Bloom Doom", "Gigavolt Havoc", "Gigavolt Havoc", "Shattered Psyche", "Shattered Psyche", "Subzero Slammer", "Subzero Slammer", "Devastating Drake", "Devastating Drake", "Black Hole Eclipse", "Black Hole Eclipse", "Twinkle Tackle", "Twinkle Tackle", "Catastropika", "Shore Up", "First Impression", "Baneful Bunker", "Spirit Shackle", "Darkest Lariat", "Sparkling Aria", "Ice Hammer", "Floral Healing", "High Horsepower", "Strength Sap", "Solar Blade", "Leafage", "Spotlight", "Toxic Thread", "Laser Focus", "Gear Up", "Throat Chop", "Pollen Puff", "Anchor Shot", "Psychic Terrain", "Lunge", "Fire Lash", "Power Trip", "Burn Up", "Speed Swap", "Smart Strike", "Purify", "Revelation Dance", "Core Enforcer", "Trop Kick", "Instruct", "Beak Blast", "Clanging Scales", "Dragon Hammer", "Brutal Swing", "Aurora Veil", "Sinister Arrow Raid", "Malicious Moonsault", "Oceanic Operetta", "Guardian of Alola", "Soul-Stealing 7-Star Strike", "Stoked Sparksurfer", "Pulverizing Pancake", "Extreme Evoboost", "Genesis Supernova", "Shell Trap", "Fleur Cannon", "Psychic Fangs", "Stomping Tantrum", "Shadow Bone", "Accelerock", "Liquidation", "Prismatic Laser", "Spectral Thief", "Sunsteel Strike", "Moongeist Beam", "Tearful Look", "Zing Zap", "Nature’s Madness", "Multi-Attack", "10,000,000 Volt Thunderbolt"};
static char *natures[] = {"Hardy", "Lonely", "Brave", "Adamant", "Naughty", "Bold", "Docile", "Relaxed", "Impish", "Lax", "Timid", "Hasty", "Serious", "Jolly", "Naive", "Modest", "Mild", "Quiet", "Bashful", "Rash", "Calm", "Gentle", "Sassy", "Careful", "Quirky"};
static char *items[] = {"None", "Master Ball", "Ultra Ball", "Great Ball", "Poke Ball", "Safari Ball", "Net Ball", "Dive Ball", "Nest Ball", "Repeat Ball", "Timer Ball", "Luxury Ball", "Premier Ball", "Dusk Ball", "Heal Ball", "Quick Ball", "Cherish Ball", "Potion", "Antidote", "Burn Heal", "Ice Heal", "Awakening", "Paralyze Heal", "Full Restore", "Max Potion", "Hyper Potion", "Super Potion", "Full Heal", "Revive", "Max Revive", "Fresh Water", "Soda Pop", "Lemonade", "Moomoo Milk", "Energy Powder", "Energy Root", "Heal Powder", "Revival Herb", "Ether", "Max Ether", "Elixir", "Max Elixir", "Lava Cookie", "Berry Juice", "Sacred Ash", "HP Up", "Protein", "Iron", "Carbos", "Calcium", "Rare Candy", "PP Up", "Zinc", "PP Max", "Old Gateau", "Guard Spec.", "Dire Hit", "X Attack", "X Defense", "X Speed", "X Accuracy", "X Sp. Atk", "X Sp. Def", "Poké Doll", "Fluffy Tail", "Blue Flute", "Yellow Flute", "Red Flute", "Black Flute", "White Flute", "Shoal Salt", "Shoal Shell", "Red Shard", "Blue Shard", "Yellow Shard", "Green Shard", "Super Repel", "Max Repel", "Escape Rope", "Repel", "Sun Stone", "Moon Stone", "Fire Stone", "Thunder Stone", "Water Stone", "Leaf Stone", "Tiny Mushroom", "Big Mushroom", "Pearl", "Big Pearl", "Stardust", "Star Piece", "Nugget", "Heart Scale", "Honey", "Growth Mulch", "Damp Mulch", "Stable Mulch", "Gooey Mulch", "Root Fossil", "Claw Fossil", "Helix Fossil", "Dome Fossil", "Old Amber", "Armor Fossil", "Skull Fossil", "Rare Bone", "Shiny Stone", "Dusk Stone", "Dawn Stone", "Oval Stone", "Odd Keystone", "Griseous Orb", "???", "???", "???", "Douse Drive", "Shock Drive", "Burn Drive", "Chill Drive", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "Sweet Heart", "Adamant Orb", "Lustrous Orb", "Greet Mail", "Favored Mail", "RSVP Mail", "Thanks Mail", "Inquiry Mail", "Like Mail", "Reply Mail", "Bridge Mail S", "Bridge Mail D", "Bridge Mail T", "Bridge Mail V", "Bridge Mail M", "Cheri Berry", "Chesto Berry", "Pecha Berry", "Rawst Berry", "Aspear Berry", "Leppa Berry", "Oran Berry", "Persim Berry", "Lum Berry", "Sitrus Berry", "Figy Berry", "Wiki Berry", "Mago Berry", "Aguav Berry", "Iapapa Berry", "Razz Berry", "Bluk Berry", "Nanab Berry", "Wepear Berry", "Pinap Berry", "Pomeg Berry", "Kelpsy Berry", "Qualot Berry", "Hondew Berry", "Grepa Berry", "Tamato Berry", "Cornn Berry", "Magost Berry", "Rabuta Berry", "Nomel Berry", "Spelon Berry", "Pamtre Berry", "Watmel Berry", "Durin Berry", "Belue Berry", "Occa Berry", "Passho Berry", "Wacan Berry", "Rindo Berry", "Yache Berry", "Chople Berry", "Kebia Berry", "Shuca Berry", "Coba Berry", "Payapa Berry", "Tanga Berry", "Charti Berry", "Kasib Berry", "Haban Berry", "Colbur Berry", "Babiri Berry", "Chilan Berry", "Liechi Berry", "Ganlon Berry", "Salac Berry", "Petaya Berry", "Apicot Berry", "Lansat Berry", "Starf Berry", "Enigma Berry", "Micle Berry", "Custap Berry", "Jaboca Berry", "Rowap Berry", "Bright Powder", "White Herb", "Macho Brace", "Exp. Share", "Quick Claw", "Soothe Bell", "Mental Herb", "Choice Band", "King’s Rock", "Silver Powder", "Amulet Coin", "Cleanse Tag", "Soul Dew", "Deep Sea Tooth", "Deep Sea Scale", "Smoke Ball", "Everstone", "Focus Band", "Lucky Egg", "Scope Lens", "Metal Coat", "Leftovers", "Dragon Scale", "Light Ball", "Soft Sand", "Hard Stone", "Miracle Seed", "Black Glasses", "Black Belt", "Magnet", "Mystic Water", "Sharp Beak", "Poison Barb", "Never-Melt Ice", "Spell Tag", "Twisted Spoon", "Charcoal", "Dragon Fang", "Silk Scarf", "Up-Grade", "Shell Bell", "Sea Incense", "Lax Incense", "Lucky Punch", "Metal Powder", "Thick Club", "Stick", "Red Scarf", "Blue Scarf", "Pink Scarf", "Green Scarf", "Yellow Scarf", "Wide Lens", "Muscle Band", "Wise Glasses", "Expert Belt", "Light Clay", "Life Orb", "Power Herb", "Toxic Orb", "Flame Orb", "Quick Powder", "Focus Sash", "Zoom Lens", "Metronome", "Iron Ball", "Lagging Tail", "Destiny Knot", "Black Sludge", "Icy Rock", "Smooth Rock", "Heat Rock", "Damp Rock", "Grip Claw", "Choice Scarf", "Sticky Barb", "Power Bracer", "Power Belt", "Power Lens", "Power Band", "Power Anklet", "Power Weight", "Shed Shell", "Big Root", "Choice Specs", "Flame Plate", "Splash Plate", "Zap Plate", "Meadow Plate", "Icicle Plate", "Fist Plate", "Toxic Plate", "Earth Plate", "Sky Plate", "Mind Plate", "Insect Plate", "Stone Plate", "Spooky Plate", "Draco Plate", "Dread Plate", "Iron Plate", "Odd Incense", "Rock Incense", "Full Incense", "Wave Incense", "Rose Incense", "Luck Incense", "Pure Incense", "Protector", "Electirizer", "Magmarizer", "Dubious Disc", "Reaper Cloth", "Razor Claw", "Razor Fang", "TM01", "TM02", "TM03", "TM04", "TM05", "TM06", "TM07", "TM08", "TM09", "TM10", "TM11", "TM12", "TM13", "TM14", "TM15", "TM16", "TM17", "TM18", "TM19", "TM20", "TM21", "TM22", "TM23", "TM24", "TM25", "TM26", "TM27", "TM28", "TM29", "TM30", "TM31", "TM32", "TM33", "TM34", "TM35", "TM36", "TM37", "TM38", "TM39", "TM40", "TM41", "TM42", "TM43", "TM44", "TM45", "TM46", "TM47", "TM48", "TM49", "TM50", "TM51", "TM52", "TM53", "TM54", "TM55", "TM56", "TM57", "TM58", "TM59", "TM60", "TM61", "TM62", "TM63", "TM64", "TM65", "TM66", "TM67", "TM68", "TM69", "TM70", "TM71", "TM72", "TM73", "TM74", "TM75", "TM76", "TM77", "TM78", "TM79", "TM80", "TM81", "TM82", "TM83", "TM84", "TM85", "TM86", "TM87", "TM88", "TM89", "TM90", "TM91", "TM92", "HM01", "HM02", "HM03", "HM04", "HM05", "HM06", "???", "???", "Explorer Kit", "Loot Sack", "Rule Book", "Poké Radar", "Point Card", "Journal", "Seal Case", "Fashion Case", "Seal Bag", "Pal Pad", "Works Key", "Old Charm", "Galactic Key", "Red Chain", "Town Map", "Vs. Seeker", "Coin Case", "Old Rod", "Good Rod", "Super Rod", "Sprayduck", "Poffin Case", "Bike", "Suite Key", "Oak’s Letter", "Lunar Wing", "Member Card", "Azure Flute", "S.S. Ticket", "Contest Pass", "Magma Stone", "Parcel", "Coupon 1", "Coupon 2", "Coupon 3", "Storage Key", "Secret Potion", "Vs. Recorder", "Gracidea", "Secret Key", "Apricorn Box", "Unown Report", "Berry Pots", "Dowsing Machine", "Blue Card", "Slowpoke Tail", "Clear Bell", "Card Key", "Basement Key", "Squirt Bottle", "Red Scale", "Lost Item", "Pass", "Machine Part", "Silver Wing", "Rainbow Wing", "Mystery Egg", "Red Apricorn", "Blue Apricorn", "Yellow Apricorn", "Green Apricorn", "Pink Apricorn", "White Apricorn", "Black Apricorn", "Fast Ball", "Level Ball", "Lure Ball", "Heavy Ball", "Love Ball", "Friend Ball", "Moon Ball", "Sport Ball", "Park Ball", "Photo Album", "GB Sounds", "Tidal Bell", "Rage Candy Bar", "Data Card 01", "Data Card 02", "Data Card 03", "Data Card 04", "Data Card 05", "Data Card 06", "Data Card 07", "Data Card 08", "Data Card 09", "Data Card 10", "Data Card 11", "Data Card 12", "Data Card 13", "Data Card 14", "Data Card 15", "Data Card 16", "Data Card 17", "Data Card 18", "Data Card 19", "Data Card 20", "Data Card 21", "Data Card 22", "Data Card 23", "Data Card 24", "Data Card 25", "Data Card 26", "Data Card 27", "Jade Orb", "Lock Capsule", "Red Orb", "Blue Orb", "Enigma Stone", "Prism Scale", "Eviolite", "Float Stone", "Rocky Helmet", "Air Balloon", "Red Card", "Ring Target", "Binding Band", "Absorb Bulb", "Cell Battery", "Eject Button", "Fire Gem", "Water Gem", "Electric Gem", "Grass Gem", "Ice Gem", "Fighting Gem", "Poison Gem", "Ground Gem", "Flying Gem", "Psychic Gem", "Bug Gem", "Rock Gem", "Ghost Gem", "Dragon Gem", "Dark Gem", "Steel Gem", "Normal Gem", "Health Wing", "Muscle Wing", "Resist Wing", "Genius Wing", "Clever Wing", "Swift Wing", "Pretty Wing", "Cover Fossil", "Plume Fossil", "Liberty Pass", "Pass Orb", "Dream Ball", "Poké Toy", "Prop Case", "Dragon Skull", "Balm Mushroom", "Big Nugget", "Pearl String", "Comet Shard", "Relic Copper", "Relic Silver", "Relic Gold", "Relic Vase", "Relic Band", "Relic Statue", "Relic Crown", "Casteliacone", "Dire Hit 2", "X Speed 2", "X Sp. Atk 2", "X Sp. Def 2", "X Defense 2", "X Attack 2", "X Accuracy 2", "X Speed 3", "X Sp. Atk 3", "X Sp. Def 3", "X Defense 3", "X Attack 3", "X Accuracy 3", "X Speed 6", "X Sp. Atk 6", "X Sp. Def 6", "X Defense 6", "X Attack 6", "X Accuracy 6", "Ability Urge", "Item Drop", "Item Urge", "Reset Urge", "Dire Hit 3", "Light Stone", "Dark Stone", "TM93", "TM94", "TM95", "Xtransceiver", "???", "Gram 1", "Gram 2", "Gram 3", "Xtransceiver", "Medal Box", "DNA Splicers", "DNA Splicers", "Permit", "Oval Charm", "Shiny Charm", "Plasma Card", "Grubby Hanky", "Colress Machine", "Dropped Item", "Dropped Item", "Reveal Glass", "Weakness Policy", "Assault Vest", "Holo Caster", "Prof’s Letter", "Roller Skates", "Pixie Plate", "Ability Capsule", "Whipped Dream", "Sachet", "Luminous Moss", "Snowball", "Safety Goggles", "Poké Flute", "Rich Mulch", "Surprise Mulch", "Boost Mulch", "Amaze Mulch", "Gengarite", "Gardevoirite", "Ampharosite", "Venusaurite", "Charizardite X", "Blastoisinite", "Mewtwonite X", "Mewtwonite Y", "Blazikenite", "Medichamite", "Houndoominite", "Aggronite", "Banettite", "Tyranitarite", "Scizorite", "Pinsirite", "Aerodactylite", "Lucarionite", "Abomasite", "Kangaskhanite", "Gyaradosite", "Absolite", "Charizardite Y", "Alakazite", "Heracronite", "Mawilite", "Manectite", "Garchompite", "Latiasite", "Latiosite", "Roseli Berry", "Kee Berry", "Maranga Berry", "Sprinklotad", "TM96", "TM97", "TM98", "TM99", "TM100", "Power Plant Pass", "Mega Ring", "Intriguing Stone", "Common Stone", "Discount Coupon", "Elevator Key", "TMV Pass", "Honor of Kalos", "Adventure Rules", "Strange Souvenir", "Lens Case", "Makeup Bag", "Travel Trunk", "Lumiose Galette", "Shalour Sable", "Jaw Fossil", "Sail Fossil", "Looker Ticket", "Bike", "Holo Caster", "Fairy Gem", "Mega Charm", "Mega Glove", "Mach Bike", "Acro Bike", "Wailmer Pail", "Devon Parts", "Soot Sack", "Basement Key", "Pokéblock Kit", "Letter", "Eon Ticket", "Scanner", "Go-Goggles", "Meteorite", "Key to Room 1", "Key to Room 2", "Key to Room 4", "Key to Room 6", "Storage Key", "Devon Scope", "S.S. Ticket", "HM07", "Devon Scuba Gear", "Contest Costume", "Contest Costume", "Magma Suit", "Aqua Suit", "Pair of Tickets", "Mega Bracelet", "Mega Pendant", "Mega Glasses", "Mega Anchor", "Mega Stickpin", "Mega Tiara", "Mega Anklet", "Meteorite", "Swampertite", "Sceptilite", "Sablenite", "Altarianite", "Galladite", "Audinite", "Metagrossite", "Sharpedonite", "Slowbronite", "Steelixite", "Pidgeotite", "Glalitite", "Diancite", "Prison Bottle", "Mega Cuff", "Cameruptite", "Lopunnite", "Salamencite", "Beedrillite", "Meteorite", "Meteorite", "Key Stone", "Meteorite Shard", "Eon Flute", "Normalium Z", "Firium Z", "Waterium Z", "Electrium Z", "Grassium Z", "Icium Z", "Fightinium Z", "Poisonium Z", "Groundium Z", "Flyinium Z", "Psychium Z", "Buginium Z", "Rockium Z", "Ghostium Z", "Dragonium Z", "Darkinium Z", "Steelium Z", "Fairium Z", "Pikanium Z", "Bottle Cap", "Gold Bottle Cap", "Z-Ring", "Decidium Z", "Incinium Z", "Primarium Z", "Tapunium Z", "Marshadium Z", "Aloraichium Z", "Snorlium Z", "Eevium Z", "Mewnium Z", "Normalium Z", "Firium Z", "Waterium Z", "Electrium Z", "Grassium Z", "Icium Z", "Fightinium Z", "Poisonium Z", "Groundium Z", "Flyinium Z", "Psychium Z", "Buginium Z", "Rockium Z", "Ghostium Z", "Dragonium Z", "Darkinium Z", "Steelium Z", "Fairium Z", "Pikanium Z", "Decidium Z", "Incinium Z", "Primarium Z", "Tapunium Z", "Marshadium Z", "Aloraichium Z", "Snorlium Z", "Eevium Z", "Mewnium Z", "Pikashunium Z", "Pikashunium Z", "???", "???", "???", "???", "Forage Bag", "Fishing Rod", "Professor’s Mask", "Festival Ticket", "Sparkling Stone", "Adrenaline Orb", "Zygarde Cube", "???", "Ice Stone", "Ride Pager", "Beast Ball", "Big Malasada", "Red Nectar", "Yellow Nectar", "Pink Nectar", "Purple Nectar", "Sun Flute", "Moon Flute", "???", "Enigmatic Card", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "Terrain Extender", "Protective Pads", "Electric Seed", "Psychic Seed", "Misty Seed", "Grassy Seed", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "Fighting Memory", "Flying Memory", "Poison Memory", "Ground Memory", "Rock Memory", "Bug Memory", "Ghost Memory", "Steel Memory", "Fire Memory", "Water Memory", "Grass Memory", "Electric Memory", "Psychic Memory", "Ice Memory", "Dragon Memory", "Dark Memory", "Fairy Memory"};
char *hpList[] = {"Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", " ", " "};

void GUIElementsInit() {
	fontBold18 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold15 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold12 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold9 = sftd_load_font_file("romfs:/res/Bold.ttf");
	warningTop = sfil_load_PNG_file("romfs:/res/Warning Top.png", SF2D_PLACE_RAM);
	warningBottom = sfil_load_PNG_file("romfs:/res/Warning Bottom.png", SF2D_PLACE_RAM);
	freezeMsg("Loading graphics...");
	
	init_font_cache();
	cleanTop = sfil_load_PNG_file("romfs:/res/Clean Top.png", SF2D_PLACE_RAM);
	mainMenuBottom = sfil_load_PNG_file("romfs:/res/Main Menu Bottom.png", SF2D_PLACE_RAM);
}

void GUIElementsSpecify() {
	freezeMsg("Loading graphics...");
	alternativeSpritesSmall = sfil_load_PNG_file("/3ds/data/PKSM/additionalassets/alternative_icons_spritesheet.png", SF2D_PLACE_RAM);
	spritesSmall = sfil_load_PNG_file("/3ds/data/PKSM/additionalassets/pokemon_icons_spritesheet.png", SF2D_PLACE_RAM);
	balls = sfil_load_PNG_file("/3ds/data/PKSM/additionalassets/balls_spritesheet.png", SF2D_PLACE_RAM);
	
	editorBar = sfil_load_PNG_file("/3ds/data/PKSM/additionalassets/editor_bar.png", SF2D_PLACE_RAM);
	boxView = sfil_load_PNG_file("/3ds/data/PKSM/additionalassets/editor_bottom.png", SF2D_PLACE_RAM);
	back = sfil_load_PNG_file("/3ds/data/PKSM/additionalassets/back_button.png", SF2D_PLACE_RAM);

	male = sfil_load_PNG_file("romfs:/res/Male.png", SF2D_PLACE_RAM);
	female = sfil_load_PNG_file("romfs:/res/Female.png", SF2D_PLACE_RAM);
	backgroundTop = sfil_load_PNG_file("romfs:/res/Background.png", SF2D_PLACE_RAM);
	shinyStar = sfil_load_PNG_file("romfs:/res/Shiny.png", SF2D_PLACE_RAM);
	normalBar = sfil_load_PNG_file("romfs:/res/Normal Bar.png", SF2D_PLACE_RAM);
	left = sfil_load_PNG_file("romfs:/res/Left.png", SF2D_PLACE_RAM);
	right = sfil_load_PNG_file("romfs:/res/Right.png", SF2D_PLACE_RAM);
	infoView = sfil_load_PNG_file("romfs:/res/Info View.png", SF2D_PLACE_RAM);
	selector = sfil_load_PNG_file("romfs:/res/Selector.png", SF2D_PLACE_RAM);
	pokemonBufferBox = sfil_load_PNG_file("romfs:/res/Pokemon Box.png", SF2D_PLACE_RAM);
	item = sfil_load_PNG_file("romfs:/res/item.png", SF2D_PLACE_RAM);
}

void GUIGameElementsInit() {
	upperTextGS = sfil_load_PNG_file("romfs:/res/3DS.png", SF2D_PLACE_RAM);
	topBorder = sfil_load_PNG_file("romfs:/res/3dsborder.png", SF2D_PLACE_RAM);
	gameSelectorTop = sfil_load_PNG_file("/3ds/data/PKSM/additionalassets/3dsicons.png", SF2D_PLACE_RAM);
}

void GUIGameElementsExit() {
	sf2d_free_texture(upperTextGS);
	sf2d_free_texture(gameSelectorTop);
	sf2d_free_texture(topBorder);
}

void GUIElementsExit() {
	sf2d_free_texture(male);
	sf2d_free_texture(female);
	sf2d_free_texture(editorBar);
	sf2d_free_texture(backgroundTop);
	sf2d_free_texture(balls);
	sf2d_free_texture(shinyStar);
	sf2d_free_texture(normalBar);
	sf2d_free_texture(alternativeSpritesSmall);
	sf2d_free_texture(item);
	sf2d_free_texture(cleanTop);
	sf2d_free_texture(pokemonBufferBox);
	sf2d_free_texture(back);
	sf2d_free_texture(boxView);
	sf2d_free_texture(infoView);
	sf2d_free_texture(selector);
	sf2d_free_texture(warningTop);
	sf2d_free_texture(warningBottom);
	sf2d_free_texture(spritesSmall);
	sf2d_free_texture(left);
	sf2d_free_texture(right);
	sf2d_free_texture(mainMenuBottom);
	sftd_free_font(fontBold9);
	sftd_free_font(fontBold12);
	sftd_free_font(fontBold15);
	sftd_free_font(fontBold18);
}

void init_font_cache() {
	sftd_draw_text(fontBold18, 0, 0, RGBA8(0, 0, 0, 0), 18, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
	sftd_draw_text(fontBold15, 0, 0, RGBA8(0, 0, 0, 0), 15, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
	sftd_draw_text(fontBold12, 0, 0, RGBA8(0, 0, 0, 0), 12, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
	sftd_draw_text(fontBold9, 0, 0, RGBA8(0, 0, 0, 0), 9, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
}

void infoDisp(char* message) {
	while (aptMainLoop()) {
		hidScanInput();

		if (hidKeysDown() & KEY_A) break;
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(warningTop, 0, 0);
			sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, message)) / 2, 95, WHITE, 15, message);
			sftd_draw_text(fontBold12, (400 - sftd_get_text_width(fontBold12, 12, "Press A to continue.")) / 2, 130, WHITE, 12, "Press A to continue.");
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(warningBottom, 0, 0);
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
}

void freezeMsg(char* message) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(warningTop, 0, 0);
		sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, message)) / 2, 95, WHITE, 15, message);
		sftd_draw_text(fontBold12, (400 - sftd_get_text_width(fontBold12, 12, "Please wait.")) / 2, 130, WHITE, 12, "Please wait.");
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(warningBottom, 0, 0);
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void printAnimatedBG(bool isUp) {
	sf2d_draw_texture(backgroundTop, 0, 0);
	animateBG(isUp);
}

void printBottomIndications(const char* message) {
	sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, message)) / 2, 225, LIGHTBLUE, 9, message);
}

void gameSelectorMenu(int n) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(cleanTop, 0, 0);
		sf2d_draw_texture(upperTextGS, 172, 65);
		
		sftd_draw_text(fontBold9, (400 - sftd_get_text_width(fontBold9, 9, "Cart has priority over digital copy.")) / 2, 6, BLUE, 9, "Cart has priority over digital copy.");
		sf2d_draw_texture(topBorder, 21 + 60 * n, 112);
		sf2d_draw_texture(gameSelectorTop, 26, 117);
		
		for (int i = 0; i < 6; i++) 
			sftd_draw_text(fontBold18, 17 + 60 * i + (68 - sftd_get_text_width(fontBold18, 18, gamesList[i])) / 2, 170, LIGHTBLUE, 18, gamesList[i]);
		
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		printBottomIndications("Move your DPAD. Press A to continue, B to exit.");
	sf2d_end_frame();
	sf2d_swapbuffers();
}

u16 getAlternativeSprite(u8* pkmn) {
    u16 tempspecies;
    if (getForm(pkmn)) {
		memcpy(&tempspecies, &personal.pkmData[getPokedexNumber(pkmn)][0x1C], 2);
		
		switch (tempspecies) {
			case 829 : return 2;
			case 922 : return 3;
			case 828 : return 4;
			case 827 : return 5;
			case 945 : return 6;
			case 917 : return 7;
			case 916 : return 8;
			case 921 : return 10;
			case 920 : return 11;
			case 826 : return 12;
			case 919 : return 13;
			case 907 : return 14;
			case 823 : return 15;
			case 918 : return 16;
			case 898 : return 17;
			case 944 : return 18;
			case 913 : return 19;
			case 912 : return 20;
			case 808 : return 21;
			case 911 : return 22;
			case 909 : return 23;
			case 923 : return 24;
			case 908 : return 25;
			case 924 : return 26;
			case 914 : return 27;
			case 915 : return 28;
			case 809 : return 30;
		}
	}
	
	return 0;
}

void printElement(u8* pkmn, u16 n, int x, int y) {
	u16 t = getAlternativeSprite(pkmn);
	if (t) {
		t -= 1;
		sf2d_draw_texture_part(alternativeSpritesSmall, x, y, 40 * (t % 6) + 4, 30 * (t / 6), 34, 30); 
	} else 
		sf2d_draw_texture_part(spritesSmall, x, y, 40 * (n % 25) + 4, 30 * (n / 25), 34, 30);
	if (isEgg(pkmn))
		sf2d_draw_texture_part(spritesSmall, x + 6, y + 6, 40 * (EGGSPRITEPOS % 25) + 4, 30 * (EGGSPRITEPOS / 25), 34, 30);
	if (getItem(pkmn))
		sf2d_draw_texture(item, x + 3, y + 21);
}

void infoViewer(u8* pkmn, int game) {
	int y_desc = 29;
	char* entries[] = {"Nickname:", "OT:", "Pokerus:", "Nature", "Ability:", "Item:", "ESV / TSV:", "TID / SID:", "HT/OT Fr.ship:", "Hidden Power:"};
	char* values[] = {"HP", "Attack", "Defence", "Sp. Atk", "Sp. Def", "Speed"};
	
	printAnimatedBG(true);
	sf2d_draw_texture(infoView, 0, 0);

	sf2d_draw_texture(normalBar, 252, 155);
	sf2d_draw_texture(normalBar, 252, 176);
	sf2d_draw_texture(normalBar, 252, 197);
	sf2d_draw_texture(normalBar, 252, 218);
	
	sftd_draw_text(fontBold12, 251, 138, WHITE, 12, "Moves");		
	for (int i = 0; i < 10; i++) {
		sftd_draw_text(fontBold12, 2, y_desc, BLUE, 12, entries[i]);
		y_desc += 20;
		if (i == 2) y_desc += 5;
		if (i == 5) y_desc += 6;
	}
	
	y_desc = 8;
	for (int i = 0; i < 6; i++) {
		sftd_draw_text(fontBold12, 225, y_desc, LIGHTBLUE, 12, values[i]);
		y_desc += 20;
	}
	
	if (getPokedexNumber(pkmn)) {
		sf2d_draw_texture_part(balls, -2, -5, 32 * (getBall(pkmn) % 8), 32 * (getBall(pkmn) / 8), 32, 32);
		sftd_draw_text(fontBold12, 30, 6, WHITE, 12, (char*)personal.species[getPokedexNumber(pkmn)]);
		
		if (getGender(pkmn) == 0)
			sf2d_draw_texture(male, 146, 7);
		else if (getGender(pkmn) == 1)
			sf2d_draw_texture(female, 148, 7);
		
		char* level = (char*)malloc(8 * sizeof(char));
		snprintf(level, 8, "Lv.%u", getLevel(pkmn));
		sftd_draw_text(fontBold12, 160, 6, WHITE, 12, level);
		free(level);
		
		char *nick = (char*)malloc(26 * sizeof(char));
		getNickname(pkmn, nick);
		sftd_draw_text(fontBold12, 215 - (sftd_get_text_width(fontBold12, 12, nick)), 29, WHITE, 12, nick);
		free(nick);
		
		char *ot_name = (char*)malloc(0x17 * sizeof(char));
		getOT(pkmn, ot_name);
		sftd_draw_text(fontBold12, 215 - (sftd_get_text_width(fontBold12, 12, ot_name)), 49, WHITE, 12, ot_name);
		free(ot_name);	
		
		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, (isInfected(pkmn) ? "Yes" : "No")), 69, WHITE, 12, isInfected(pkmn) ? "Yes" : "No");
		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, natures[getNature(pkmn)]), 94, WHITE, 12, natures[getNature(pkmn)]);
		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, abilities[getAbility(pkmn)]), 114, WHITE, 12, abilities[getAbility(pkmn)]);
		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, items[getItem(pkmn)]), 134, WHITE, 12, items[getItem(pkmn)]);
		
		if (isShiny(pkmn))
			sf2d_draw_texture(shinyStar, 205, 9);
		
		char* friendship = (char*)malloc(11 * sizeof(char));
		snprintf(friendship, 11, "%u / %u", getFriendship(pkmn), getOTFriendship(pkmn));
		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, friendship), 200, WHITE, 12, friendship);
		free(friendship);
		
		char* otid = (char*)malloc(18 * sizeof(char));
		snprintf(otid, 18, "%u / %u", getPSV(pkmn), getTSV(pkmn));
		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, otid), 160, (getPSV(pkmn) == getTSV(pkmn)) ? SHINYRED : WHITE, 12, otid);
		snprintf(otid, 18, "%lu / %u", (game < 4) ? (u32)getOTID(pkmn) : (((u32)(getSOTID(pkmn) * 65536) + getOTID(pkmn)) % 1000000), getSOTID(pkmn));
		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, otid), 180, WHITE, 12, otid);
		free(otid);

		sftd_draw_text(fontBold12, 215 - sftd_get_text_width(fontBold12, 12, hpList[getHPType(pkmn)]), 220, WHITE, 12, hpList[getHPType(pkmn)]);
		
		int max = sftd_get_text_width(fontBold12, 12, "252");		
		int y_moves = 159;
		for (int i = 0; i < 4; i++) {
			if (getMove(pkmn, i))
				sftd_draw_text(fontBold12, 396 - sftd_get_text_width(fontBold12, 12, moves[getMove(pkmn, i)]), y_moves, WHITE, 12, moves[getMove(pkmn, i)]);
			y_moves += 21;
		}
		
		char* tmp = (char*)malloc(4);
		for (int i = 0; i < 6; i++) {
			snprintf(tmp, 4, "%d", getIV(pkmn, lookup[i]));
			sftd_draw_text(fontBold12, 289 + (max - sftd_get_text_width(fontBold12, 12, tmp)) / 2, 8 + i * 20, WHITE, 12, tmp);
			snprintf(tmp, 4, "%d", getEV(pkmn, lookup[i]));
			sftd_draw_text(fontBold12, 328 + (max - sftd_get_text_width(fontBold12, 12, tmp)) / 2, 8 + i * 20, WHITE, 12, tmp);
			snprintf(tmp, 4, "%d", getStat(pkmn, lookup[i]));
			sftd_draw_text(fontBold12, 369 + (max - sftd_get_text_width(fontBold12, 12, tmp)) / 2, 8 + i * 20, WHITE, 12, tmp);
		}
		free(tmp);
	}
}

void printPKViewer(u8* mainbuf, bool isTeam, int game, int currentEntry, int box, int modeFlag) {
	int x;
	char* page = (char*)malloc(7 * sizeof(char));
	snprintf(page, 7, "Box %d", box + 1);
	
	u8* pkmn = (u8*)malloc(PKMNLENGTH * sizeof(u8));
	getPkmn(mainbuf, (isTeam) ? 33 : box, currentEntry, pkmn, game);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		infoViewer(pkmn, game);
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(boxView, 0, 0);
		sf2d_draw_texture(editorBar, 0, 210);
		sftd_draw_text(fontBold12, 12 + (178 - sftd_get_text_width(fontBold12, 12, page)) / 2, 19, WHITE, 12, page);
		sf2d_draw_texture(left, 7, 17);
		sf2d_draw_texture(right, 185, 17);
		sf2d_draw_texture(back, 280, 210);
		sftd_draw_text(fontBold12, 247, 7, WHITE, 12, "Team");
		
		int y = 45;
		int pointer[2] = {0, 0};
		for (int i = 0; i < 5; i++) {
			x = 4;
			for (int j = 0; j < 6; j++) {
				getPkmn(mainbuf, box, i * 6 + j, pkmn, game);
				u16 n = getPokedexNumber(pkmn);
				if (n)
					printElement(pkmn, n, x, y);

				if ((currentEntry == (i * 6 + j)) && !isTeam) {
					pointer[0] = x + 18;
					pointer[1] = y - 8;
				}
				x += 34;
			}
			y += 30;
		}
		
		for (int i = 0; i < 3; i++) {
			sf2d_draw_texture(pokemonBufferBox, 214, 40 + i * 45);
			sf2d_draw_texture(pokemonBufferBox, 266, 60 + i * 45);
		}
		
		y = 45;
		for (int i = 0; i < 3; i++) {
			x = 222;
			for (int j = 0; j < 2; j++) {
				getPkmn(mainbuf, 33, i * 2 + j, pkmn, game);
				u16 n = getPokedexNumber(pkmn);
				if (n)
					printElement(pkmn, n, x, (j == 1) ? y + 20 : y);

				if ((currentEntry == (i * 2 + j)) && isTeam) {
					pointer[0] = x + 18;
					pointer[1] = y - 8 + ((j == 1) ? 20 : 0);
				}
				x += 52;
			}
			y += 45;
		}
		
		sf2d_draw_texture(selector, pointer[0], pointer[1] - movementOffsetSlow(3));
		if (modeFlag == ED_STANDARD)
			sftd_draw_textf(fontBold9, 16, 220, WHITE, 9, "TID: %lu / SID: %u / TSV: %u", (game < 4) ? (u32)getSaveTID(mainbuf, game) : (((u32)(getSaveSID(mainbuf, game) * 65536) + getSaveTID(mainbuf, game)) % 1000000), getSaveSID(mainbuf, game), getSaveTSV(mainbuf, game));	
		else
			sftd_draw_textf(fontBold9, 16, 220, WHITE, 9, "Seed: %lx %lx %lx %lx", getSaveSeed(mainbuf, game, 3), getSaveSeed(mainbuf, game, 2), getSaveSeed(mainbuf, game, 1), getSaveSeed(mainbuf, game, 0));	
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(pkmn);
	free(page);
}