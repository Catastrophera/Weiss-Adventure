#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <map>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <thread>
#include <chrono>
#include <io.h>
#include <fcntl.h>

using namespace std;


struct Item {
    string name;
    string type;
    int value; 
    string description;
    int statRequirement;
    int price; 
};

struct Weapon {
    string name;
    int attackPower;
    int strengthRequired;
    int intelligenceRequired;
    string description; 
    bool equipped;
    int price; 
    string requiredStoryFlagKey; 
    int requiredStoryFlagValue;  
};

struct Magic {
    string name;
    int power;
    int manaCost;
    string description;
    vector<string> prerequisites;
    bool learned;
};

struct MagicSpell {
    string id;                      
    string name;                    
    string description;
    string elementType;             
    int tier;                       
    int manaCost;
    int basePower;                 
    string targetType;              
    bool isEnchantment;          
    int enchantTurns;               
    int enchantAttackBonus;        
    vector<string> prerequisites;  
 
};

struct ActiveEnchantment {
    string spellId;
    string spellName; 
    int remainingTurns;
    int attackBonus;
    int defenseBonus;
    int evasionBonus;
    int intelligenceBonus; 
    int agilityBonus;      
    int shieldHp;
    double criticalChanceBonus; 
    bool isPhysicallyImmune;    
    int retaliateDamage;        
    bool hasRevive;   
    ActiveEnchantment(string id = "", string name = "", int turns = 0,
                      int atk = 0, int def = 0, int evas = 0,
                      int intel = 0, int agi = 0, int shield = 0,
                      double critChance = 0.0, bool physImmune = false, int retDmg = 0, bool revive = false)
        : spellId(id), spellName(name), remainingTurns(turns),
          attackBonus(atk), defenseBonus(def), evasionBonus(evas),
          intelligenceBonus(intel), agilityBonus(agi), shieldHp(shield),
          criticalChanceBonus(critChance), isPhysicallyImmune(physImmune), retaliateDamage(retDmg), hasRevive(revive) {}
};

struct ActiveDoTEffect {
    string spellId;
    wstring spellName;
    string elementType;
    int damagePerTurn;
    int remainingTurns;

    ActiveDoTEffect(string id, wstring name, string element, int dmg, int turns)
        : spellId(id), spellName(name), elementType(element),
          damagePerTurn(dmg), remainingTurns(turns) {}
};


struct ActiveHoTEffect {
    string spellId;
    string spellName;
    int healPerTurn;
    int remainingTurns;
};

struct ActiveRuneEffect {
    string spellId;         
    string spellName;     
    string elementType;     
    int damageOnTrigger;    
    int turnsUntilTrigger;  
    ActiveRuneEffect(string id = "", string name = "", string eType = "None", int dmg = 0, int turns = 0)
        : spellId(id), spellName(name), elementType(eType), damageOnTrigger(dmg), turnsUntilTrigger(turns) {}
};

struct PlayerSpellUndoState {
    int skillPoints;
    vector<string> knownSpells;
};

struct Character {
    string name;
    int level;
    int hp;
    int maxHp;
    int magicAttack;
    int mana;
    int maxMana;
    int strength;
    int defense;
    int intelligence;
    int agility;
    int exp;
    int gold;
    int temporaryStrengthBuff = 0;
    int temporaryIntelligenceBuff = 0;
    vector<Item*> inventory;
    vector<Weapon*> weapons;
    
    Weapon* equippedWeapon;

    long long expToNextLevel; 
    int skillPoints;
    vector<string> unlockedMagicElements; 
    vector<string> knownSpells;         
    vector<ActiveEnchantment> activeEnchantments;
    vector<ActiveHoTEffect> activeHoTs;
};

struct MagicElement {
    string name; 
    string description;
    map<string, MagicSpell> spells; 
                                    
};

struct Enemy {
    string name;
    int level;
    int maxHp;
    int hp;
    int attack;
    int defense;
    int expReward;
    int goldDrop;
    int magicDefense;
    bool isBoss;

    
    bool isStunned;
    int stunDuration;
    bool isFeared;
    int fearDuration;
    bool isSilenced;
    int silenceDuration;

    int attackDebuffValue;
    int attackDebuffDuration;
    int accuracyDebuffValue;
    int accuracyDebuffDuration;
    int physicalDefenseDebuffValue;
    int physicalDefenseDebuffDuration;
    int magicDefenseDebuffValue;
    int magicDefenseDebuffDuration;

    string enemyType;
    vector<ActiveDoTEffect> activeDoTs;
    vector<ActiveRuneEffect> activeRunes; 

    
    Enemy(string n = "", int lvl = 1, int mHp = 10, int chp = 10, int atk = 5, int def = 0,
          int expr = 5, int gld = 1, int mdef = 0, bool boss = false,
          bool stunned = false, int stundur = 0,
          int atkdebuffval = 0, int atkdebuffdur = 0,
          int accdebuffval = 0, int accdebuffdur = 0,
          string etype = "Normal", vector<ActiveDoTEffect> adts = {},
          int physDefDebuffVal = 0, int physDefDebuffDur = 0,
          int magDefDebuffVal = 0, int magDefDebuffDur = 0,
          bool feared = false, int fearDur = 0,
          bool silenced = false, int silenceDur = 0, vector<ActiveRuneEffect> runes = {})
        : name(n), level(lvl), maxHp(mHp), hp(chp), attack(atk), defense(def),
          expReward(expr), goldDrop(gld), magicDefense(mdef), isBoss(boss),
          isStunned(stunned), stunDuration(stundur),
          attackDebuffValue(atkdebuffval), attackDebuffDuration(atkdebuffdur),
          accuracyDebuffValue(accdebuffval), accuracyDebuffDuration(accdebuffdur),
          enemyType(etype), activeDoTs(adts),
          physicalDefenseDebuffValue(physDefDebuffVal), physicalDefenseDebuffDuration(physDefDebuffDur),
          magicDefenseDebuffValue(magDefDebuffVal), magicDefenseDebuffDuration(magDefDebuffDur),
          isFeared(feared), fearDuration(fearDur),
          isSilenced(silenced), silenceDuration(silenceDur), activeRunes(runes) {}
};

struct Companion {
    string name;
    int initialLoyalty; 
    string personality; 
    string description; 
    vector<string> coreAbilitiesOrTraits; 
    bool met; 
    map<int, wstring> detailedInfoPerLevel; 
    map<int, vector<wstring>> traitsRevealedPerLevel; 
};

struct GameEvent {
    string eventName;
    string description;
    int dayTrigger;
    bool triggered;
};

struct Quest {
    string title;
    string description;
    bool completed;
    int reward;
    Quest* next;
};

struct DailyQuest {
    string title;
    string description;
    string type; 
    string target;
    int dungeonFloor = 0;
    string dungeonName;
    bool taken = false;
    bool completed = false;
    int expReward = 0;
    int goldReward = 0;
    string rank = "C"; 
};

struct ActiveDailyQuestNode {
    DailyQuest data; 
    ActiveDailyQuestNode* next;
};

struct Location {
    string name;
    string description;
    vector<string> connections;
    bool visited;
};

struct SubArea {
    string name;
    vector<string> actions;
};

struct WorldArea {
    string name;
    string startSubArea;
    unordered_map<string, SubArea> subAreas;
};
struct CampArea {
    int floor;
    bool visited = false;
    int restUsed = 0;
    bool diaryAccessible = true;
};

struct Dungeon {
    string name;
    string type; 
    int currentFloor = 1;
    int maxUnlockedFloor = 1;
    bool printAsBasement = false;

    map<int, vector<string>> floorEnemies; 
    map<int, string> miniBosses;
    map<int, string> finalBoss;
    vector<int> storyLockedFloors;
    map<int, CampArea> campAreas;
    vector<int> visitedCampAreas;
    unordered_set<int> exploredOnceFloors;
};

struct SocialLink {
    string characterName;
    int currentLevel = 1; 
    bool completed = false;
};

struct SocialLinkStory {
    vector<wstring> levelDialogs; 
    unordered_set<int> lockedLevels; 
};

enum BattleResult {
    PLAYER_DEAD,
    PLAYER_ESCAPED,
    ENEMY_DEAD
};


struct SaveSlot {
    bool isUsed = false;
    string slotName; // Bisa diisi nama pemain + hari ke-berapa, atau input dari pemain
    time_t saveTime;

    // Data Pemain
    string playerName;
    int playerLevel;
    int playerHp;
    int playerMaxHp;
    int playerMana;
    int playerMaxMana;
    int playerStrength;
    int playerDefense;
    int playerIntelligence;
    int playerAgility;
    int playerExp;
    long long playerExpToNextLevel;
    int playerGold;
    int playerSkillPoints;
    vector<string> playerUnlockedMagicElements;
    vector<string> playerKnownSpells;
    Weapon* playerEquippedWeaponData; // Simpan nama atau ID, lalu resolve saat load
    string playerEquippedWeaponName; // Lebih aman untuk serialisasi

    // Inventory Pemain
    vector<string> playerInventoryItemNames; // Simpan nama item
    vector<string> playerWeaponNames;      // Simpan nama senjata

    // Progres Cerita & Dunia
    int currentDay;
    int currentActionsRemaining;
    string currentWorld;
    string currentSubArea;
    unordered_map<string, int> storyFlagsData;
    queue<GameEvent> scheduledEventsData; // Mungkin perlu diserialisasi secara khusus
    vector<GameEvent> scheduledEventsVector; // Lebih mudah diserialisasi daripada queue

    // Progres Companion
    vector<string> companionNamesMet;
    unordered_map<string, string> companionCurrentLocations;
    unordered_map<string, int> companionRelationsData;
    unordered_map<string, int> companionSocialLinkLevels;
    unordered_map<string, bool> companionSocialLinkCompleted;

    // Progres Dungeon
    map<string, vector<int>> dungeonVisitedCampAreasData;
    map<string, unordered_set<int>> dungeonExploredOnceFloorsData;
    unordered_map<string, bool> defeatedBossesData;
    

    // Quest
    vector<DailyQuest> activeDailyQuestsData; // Simpan quest aktif saat ini
};

unordered_map<string, WorldArea> allWorlds;
unordered_map<string, vector<string>> locationGraph;
unordered_map<string, Dungeon> allDungeons;
unordered_map<string, Enemy> enemyDatabase;
unordered_map<string, bool> defeatedBosses;
unordered_map<string, vector<wstring>> asciiArtMap;
unordered_map<string, SocialLink> socialLinks;
unordered_map<string, SocialLinkStory> socialLinkStories;
unordered_map<string, bool> talkedToday;
unordered_set<string> subAreasExploredOnceGlobal;

string currentWorld = "Mansion Astra";
string currentSubArea = "Kamar Weiss";
string currentDungeonName;


Character player;
vector<Companion> companions;
unordered_map<string, string> companionCurrentLocations;
vector<Item> allItems;
vector<Weapon> allWeapons;
vector<Magic> allMagic;
vector<DailyQuest> allDailyQuestPool;
vector<DailyQuest> dailyQuests;
ActiveDailyQuestNode* activeDailyQuestsHead = nullptr;

unordered_map<string, Item*> itemDatabase;
unordered_map<string, Weapon*> weaponDatabase;
unordered_map<string, Magic*> magicDatabase;
unordered_map<string, int> storyFlags;
unordered_map<string, int> companionRelations;
map<string, Location> worldMap;
map<string, MagicElement> allMagicElements;
queue<GameEvent> scheduledEvents;
stack<PlayerSpellUndoState> spellLearnUndoStack;
Quest* questHead = nullptr;
const int MAX_SAVE_SLOTS = 3; 
vector<SaveSlot> saveSlots(MAX_SAVE_SLOTS);
string SAVE_FILE_NAME = "savegame.dat"; 
const double BASE_XP = 7.0;
const double XP_EXPONENT = 1.1;
const vector<int> MAGIC_ELEMENT_UNLOCK_LEVELS = {20, 40, 60, 80, 100}; 
int currentDay = 1;
int maxActionsPerDay = 5;
int currentActionsRemaining = 5;
bool gameRunning = true;
string currentLocation = "Noble's Room";

void delayPrint(const wstring& text, int delayMs = 10);
void printLine(int len = 100, wchar_t ch = L'═');
void centerText(const wstring& text, int width = 100);
void showTitleScreen();
void showBeforePrologue();
void showPrologue();
void inputPlayerName();
void showTutorial();
void initializeCompanions();
void initializeDungeons();
void initializeGame();
void showGameMenu();
void exploreArea();
void setupConnections();
void showItemShop();
void showBlacksmith();
void showLocationMenu();
void showInventoryCategory();
void showItemList();
void showItemDetail(Item* item);
void showWeaponList();
void showWeaponDetail(Weapon* weapon);
void showCompanionList();
void showCompanionDetail(Companion& companion);
bool sudahBertemuCompanion(const string& namaCompanion);
void showGenericCompanionDialogue(const string& npcName);
void showCalendar();
void showDiaryMenu();
void setupWorldAreas();
BattleResult startBattle(Enemy& baseEnemy, const string& dungeonName);
void displayEnemyASCII(const string& enemyName);
void initializeAllQuests();
void generateDailyQuests();
void loadEnemyASCIIFromFile(const string& filename);
void applySocialLinkBonus(const string& npcName);
void advanceToNextDay();
void checkStoryTriggers();
void temporarilyGrantAllMagicToPlayer(Character& playerChar, bool grant);
void setupBuffedAllainForDuel(Enemy& allainDuelTarget);


wstring utf8_to_wstring(const string& str_utf8) {
    
    if (str_utf8.empty()) {
        return wstring();
    }
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str_utf8[0], (int)str_utf8.length(), NULL, 0);
    if (size_needed == 0) {
        
        
        
        return wstring(); 
    }
    wstring wstr_to(size_needed, 0);
    int chars_converted = MultiByteToWideChar(CP_UTF8, 0, &str_utf8[0], (int)str_utf8.length(), &wstr_to[0], size_needed);
    if (chars_converted == 0) {
        
        
        return wstring(); 
    }
    return wstr_to;
}

map<string, MagicSpell> getAllSpells() {
    map<string, MagicSpell> allSpells;
    for (const auto& [_, element] : allMagicElements) {
        for (const auto& [id, spell] : element.spells) {
            allSpells[id] = spell;
        }
    }
    return allSpells;
}

const MagicSpell* getSpellDetails(const string& spellId) {
    static auto allSpells = getAllSpells();  
    auto it = allSpells.find(spellId);
    if (it != allSpells.end()) return &it->second;
    return nullptr;
}



string getQuestRankLetter() {
    if (storyFlags["pedang_pahlawan"] > 0) return "SS";
    if (storyFlags["invasi_arcadia"] > 0) return "S";
    if (storyFlags["invasi_mansion"] > 0) return "A";
    if (storyFlags["duel_persahabatan"] > 0) return "B";
    return "C";
}


void delayPrint(const wstring& text, int delayMs) {
    for (wchar_t ch : text) {
        wcout << ch << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    wcout << endl;
}

void printLine(int len, wchar_t ch) {
    for (int i = 0; i < len; i++) wcout << ch;
    wcout << endl;
}

void centerText(const wstring& text, int width) {
    if (text.length() >= width) {
        wcout << text << endl;
        return;
    }
    int pad = (width - text.length()) / 2;
    for (int i = 0; i < pad; i++) wcout << L' ';
    wcout << text << endl;
}

void waitForEnter(const wstring& message = L"Tekan Enter untuk melanjutkan...") {
    wcout << message << flush; 

    if (cin.fail()) {
        cin.clear();
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



wstring padRight(const wstring& text, int width) {
    if (text.length() >= width) return text;
    return text + wstring(width - text.length(), L' ');
}


string trim(const string& str) {
    const string whitespace = " \t\n\r\f\v\u00A0\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200A\u2028\u2029\u202F\u205F\u3000";
    size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; 

    size_t strEnd = str.find_last_not_of(whitespace);
    size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

wstring formatDungeonFloor(const Dungeon& dungeon, int floor) {
    if (dungeon.printAsBasement) {
        return L"B" + to_wstring(floor);
    } else {
        return to_wstring(floor);
    }
}

int getValidatedChoice(int minOption, int maxOption) {
    int choice;
    while (true) {
        if (cin >> choice) {
            if (choice >= minOption && choice <= maxOption) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return choice;
            } else {
                wcout << L"❌ Pilihan harus antara " << minOption << L" dan " << maxOption << L".\n";
            }
        } else {
            wcout << L"❌ Input tidak valid. Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


void dfsTravel(string current, string target, unordered_set<string>& visited, vector<string>& path) {
    visited.insert(current);
    path.push_back(current);
    if (current == target) return;

    for (const auto& neighbor : locationGraph[current]) {
        if (visited.find(neighbor) == visited.end()) {
            dfsTravel(neighbor, target, visited, path);
            if (!path.empty() && path.back() == target) return;
        }
    }
    path.pop_back(); 
}


void showTitleScreen() {
    system("cls");
    setlocale(LC_ALL, "");
    wcout << L"\n";
    centerText(L"╔════════════════════════════════════════════════════════════════════════════════════════════════╗");
    centerText(L"║ ⚜  So I Woke Up as the Lazy Villainous Noble Destined for a Bad End,                         ⚜ ║");
    centerText(L"║ ⚜  Which, Frankly, is Inconvenient: My Ongoing Efforts to Derail the Plot,                   ⚜ ║");
    centerText(L"║ ⚜  Become Ludicrously Powerful with Magic, and Perhaps Find a Decent Cup of Tea              ⚜ ║");
    centerText(L"║ ⚜  in This new World.                                                                        ⚜ ║");
    centerText(L"╚════════════════════════════════════════════════════════════════════════════════════════════════╝");
    delayPrint(L"  ✦✦✦ Main Menu ✦✦✦");
    delayPrint(L"  ❖ 1. New Game");
    delayPrint(L"  ❖ 2. Load Game");
    delayPrint(L"  ❖ 3. About");
    delayPrint(L"  ❖ 4. Exit");
    delayPrint(L"⚜═══════════════════════════════════════════════════════════════════════════════════════⚜");
    wcout << L"Masukkan pilihanmu ✦: ";
}

void showBeforePrologue() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ PROLOGUE ✦✦✦");
    printLine();
    wcout << endl;
    
    delayPrint(L"Fiuuhh... Akhirnya kelar juga maraton novel seharian. Mata perih, perut keroncongan!", 30);
    delayPrint(L"Tapi endingnya... wow, nggak nyangka bakal begitu twist-nya.", 30);
    delayPrint(L"Pantes aja novel ini jadi top selling bulan ini di mana-mana.", 30);
    delayPrint(L"Dan si tokoh antagonis sampingan nyebelin itu, si Weiss... haha, mati konyol! Rasain! Udah sombong, nasibnya memalukan pula.", 30); 
    wcout << endl;
    delayPrint(L"Oke, misi penyelamatan perut dimulai: waktunya berburu makanan di minimarket!", 30);
    delayPrint(L"Mungkin sekalian cari teh kotak dingin buat teman begadang nanti, kalau masih ada.", 30);
    delayPrint(L"Astaga, udah mau tengah malam! Semoga aja belum tutup. Kudu ngebut nih.", 30);
    wcout << endl;
    delayPrint(L"Yes, lampunya masih nyala! Tinggal nyebrang sekali lagi...", 30);
    delayPrint(L"Kalau lari sedikit, pasti masih keburu.", 30);
    wcout << endl;
    delayPrint(L"Eh? Lampu truk itu... kenapa terang banget dan makin dekat?! Kayak... REM BLONG?!", 30); 
    delayPrint(L"BRAKK! Semuanya jadi gelap... sakit... dingin...", 30);
    delayPrint(L"Jadi... begini ya, rasanya...? Sial andai aku bisa hidup lebih lama.....", 30); 
    wcout << endl;
    
    printLine();
    waitForEnter();
}

void showPrologue() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ PROLOGUE ✦✦✦");
    printLine();
    wcout << endl;
    
    delayPrint(L"Ugh... kepalaku serasa mau pecah. Pandanganku kabur... di mana ini?", 30);
    delayPrint(L"Ini... jelas bukan kamarku. Langit-langit tinggi, perabot aneh... mewah?", 30);
    delayPrint(L"Kamar siapa ini? Dan... kenapa badanku terasa aneh?", 30);
    delayPrint(L"Cermin itu... aku harus lihat. Sosok di cermin itu... rambut pirang, mata biru... TUNGGU! INI BUKAN AKU!", 30);
    wcout << endl;
    delayPrint(L"Tidak mungkin... ingatan ini... nama ini... Aku bereinkarnasi sebagai...", 30);
    delayPrint(L"WEISS VON ASTRA?! Antagonis sombong dari novel itu?!", 30); 
    delayPrint(L"Yang di novel aslinya... MATI dengan cara paling memalukan dan konyol yang pernah ada!", 30); 
    wcout << endl;
    delayPrint(L"Oke, tenang. Ini situasi gila. Super merepotkan, jelas.", 30);
    delayPrint(L"Tapi aku menolak keras takdir konyol itu! Tidak akan ada mati memalukan untuk Weiss yang ini!", 30); 
    delayPrint(L"Saatnya membalikkan alur cerita brengsek ini dan jadi yang terkuat... atau setidaknya bertahan hidup dengan elegan.", 30);
    delayPrint(L"Oh, dan prioritas utama lainnya: menemukan secangkir teh yang benar-benar enak di dunia antah berantah ini.", 30); 
    wcout << endl;
    
    printLine();
    waitForEnter();
}

void chooseInitialMagicElements(Character& character) {

    system("cls");
    printLine();
    centerText(L"✦✦✦ PEMILIHAN ELEMEN MAGIC AWAL ✦✦✦");
    printLine();
    delayPrint(L"Setiap penyihir memulai perjalanan mereka dengan afinitas terhadap satu elemen.", 20);
    delayPrint(L"Pilihlah satu elemen yang akan menjadi fondasi kekuatan sihirmu:", 20);
    wcout << endl;

    vector<pair<string, wstring>> availableElementsDisplay; 
    for(const auto& pair : allMagicElements) {
        availableElementsDisplay.push_back({pair.first, utf8_to_wstring(pair.first)});
    }

    wcout << L"Pilih Elemen Awalmu:" << endl;
    for (size_t j = 0; j < availableElementsDisplay.size(); ++j) {
        wcout << L"  " << (j + 1) << L". " << availableElementsDisplay[j].second << endl;
    }

    int choice = -1;
    bool validChoice = false;
    while(!validChoice) {
        wcout << L"Pilihanmu (1-" << availableElementsDisplay.size() << L") ✦: ";
        choice = getValidatedChoice(1, 6); 

        if (cin.fail() || choice < 1 || choice > availableElementsDisplay.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wcout << L"Pilihan tidak valid. Coba lagi." << endl;
        } else {
            validChoice = true; 
        }
    }
    
    string selectedElementName = availableElementsDisplay[choice - 1].first;
    character.unlockedMagicElements.push_back(selectedElementName); 

    delayPrint(L"Kamu telah memilih afinitas dengan elemen: " + utf8_to_wstring(selectedElementName) + L"!", 20);
    delayPrint(L"Kamu akan perlu menggunakan Skill Point untuk mempelajari sihir pertama dari elemen ini.", 20);

    wcout << endl;

    printLine();
}


void inputPlayerName() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ CHARACTER SETUP ✦✦✦");
    printLine();
    wcout << endl;
    
    delayPrint(L"Meskipun tubuh ini adalah Weiss von Astra...", 20);
    delayPrint(L"Jiwa di dalamnya adalah dirimu!", 20);
    wcout << endl;
    
    wcout << L"Siapa nama aslimu (sebelum reinkarnasi)? ✦: ";
    string realName;
    
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, realName);
    
    player.name = "Weiss von Astra (" + realName + ")";
    
    wcout << endl;
    delayPrint(L"Baiklah, " + utf8_to_wstring(realName) + L"...", 20);
    delayPrint(L"Sekarang kamu adalah Weiss von Astra!", 20);
    delayPrint(L"Tapi jiwamu tetap " + utf8_to_wstring(realName) + L"!", 20);
}

void showTutorial() {
    bool tutorialSkipped = false;
    int currentPage = 1;
    int totalPages = 4; 

    while (currentPage <= totalPages && !tutorialSkipped) {
        system("cls");
        printLine();

        if (currentPage == 1) {
            centerText(L"✦ TUTORIAL - HALAMAN 1 DARI " + to_wstring(totalPages) + L": SELAMAT DATANG, WEISS! ✦");
            printLine();
            wcout << endl;

            delayPrint(L"Selamat datang kembali di dunia ini, jiwa yang bereinkarnasi!", 20);
            delayPrint(L"kamu kini adalah Weiss von Astra, seorang bangsawan muda yang di novel aslinya bernasib... yah, cukup tragis dan konyol.", 20);
            delayPrint(L"Tujuan utamamu di sini sangat jelas: HINDARI TAKDIR BURUK ITU! Ubah alur cerita, jadilah kuat, dan tulis ulang akhir kisahmu.", 30);
            wcout << endl;

            delayPrint(L"=== AKSI DASAR & NAVIGASI ===", 20);
            delayPrint(L"  ❖ MENU UTAMA (AKSI DI LOKASI):", 20);
            delayPrint(L"    ✧ CEK SEKITAR   : Melihat-lihat area saat ini. Siapa tahu ada item tersembunyi, kejadian kecil, atau petunjuk menarik? Hanya bisa dilakukan sekali per area.", 20);
            delayPrint(L"    ✧ BUKA DIARY    : Ini adalah pusat komandomu! Dari sini kamu bisa melihat status karakter, inventory (item & senjata), daftar quest, mempelajari sihir baru di Skill Tree, mengecek hubungan dengan rekanan (Companion), dan melihat Kalender Event.", 20);
            delayPrint(L"    ✧ PILIH LOKASI  : Berpindah ke sub-area lain dalam wilayah duniamu saat ini (misalnya, dari Kamar ke Dapur di Mansion Astra).", 20);
            delayPrint(L"    ✧ ISTIRAHAT     : (Biasanya tersedia di tempat aman seperti kamarmu) Mengakhiri hari, memulihkan HP & Mana, dan melanjutkan ke hari berikutnya. Ini akan menghabiskan sisa aksimu.", 20);
            wcout << endl;
            delayPrint(L"  ❖ AKSI HARIAN   : Setiap hari, kamu memiliki sejumlah 'Aksi Harian' (misalnya 5 aksi). Berpindah lokasi antar wilayah dunia (World Map), berbicara dengan NPC untuk meningkatkan hubungan, atau masuk dungeon akan mengurangi jumlah aksimu. Gunakan dengan bijak!", 20);
            wcout << endl;
            delayPrint(L"Ingat nama aslimu, " + utf8_to_wstring(player.name.substr(player.name.find("(") + 1, player.name.find(")") - player.name.find("(") - 1)) + L"? Jiwa itu kini ada dalam diri Weiss!", 20);

        } else if (currentPage == 2) {
            centerText(L"✦ TUTORIAL - HALAMAN 2 DARI " + to_wstring(totalPages) + L": PENGEMBANGAN KARAKTER & SIHIR ✦");
            printLine();
            wcout << endl;

            delayPrint(L"=== MENJADI LEBIH KUAT ===", 20);
            delayPrint(L"  ❖ LEVEL & EXP      : Kalahkan musuh dalam pertarungan dan selesaikan quest (terutama Quest Harian dari Cross Guild) untuk mendapatkan EXP (Experience Points).", 20);
            delayPrint(L"  ❖ NAIK LEVEL       : Ketika EXP mencapai batas tertentu, levelmu akan naik! Ini akan meningkatkan statistik dasar (Max HP, Max Mana, Strength, Intelligence, Defense, Agility) secara otomatis.", 20);
            delayPrint(L"  ❖ SKILL POINT (SP) : Setiap beberapa level (misalnya tiap 5 level), atau saat membuka elemen sihir baru, kamu akan mendapatkan Skill Point. Ini SANGAT PENTING!", 20);
            wcout << endl;

            delayPrint(L"=== MENGUASAI SIHIR ===", 20);
            delayPrint(L"  ❖ ELEMEN SIHIR AWAL: Di awal permainan, kamu memilih satu elemen sihir dasar (Api, Es, Petir, Angin, Kegelapan, atau Cahaya). Ini menentukan sihir awal yang bisa kamu pelajari.", 20);
            delayPrint(L"  ❖ MEMBUKA ELEMEN BARU: Seiring kenaikan levelmu (pada level 20, 40, 60, 80, 100), kamu akan berkesempatan membuka akses ke elemen sihir baru secara acak. Beberapa sihir dasar dari elemen baru itu akan langsung bisa kamu pelajari.", 20);
            delayPrint(L"  ❖ SKILL TREE       : Akses 'Skill Tree' melalui 'Buka Diary'. Di sini kamu bisa menggunakan Skill Point untuk mempelajari sihir baru dari elemen yang sudah kamu kuasai. Perhatikan prasyarat (sihir sebelumnya yang harus dikuasai) untuk sihir tingkat lanjut!", 20);
            delayPrint(L"  ❖ MANA             : Setiap sihir membutuhkan Mana untuk dirapal. Pastikan cadangan Mana-mu cukup, atau gunakan Mana Potion!", 20);
            wcout << endl;
            delayPrint(L"Kekuatan sihir adalah kunci untuk mengubah takdirmu. Pelajari dan gunakan dengan bijak!", 20);

        } else if (currentPage == 3) {
            centerText(L"✦ TUTORIAL - HALAMAN 3 DARI " + to_wstring(totalPages) + L": PERTARUNGAN DETAIL & STATUS EFEK ✦");
            printLine();
            wcout << endl;

            delayPrint(L"=== MEMAHAMI PERTARUNGAN (TURN-BASED) ===", 20);
            delayPrint(L"  ❖ AKSI DALAM BERTARUNG:", 20);
            delayPrint(L"    ✧ SERANG   : Serangan fisik dasar. Kekuatannya dipengaruhi oleh stat Strength dan senjata yang kamu pakai.", 20);
            delayPrint(L"    ✧ MAGIC    : Menggunakan sihir yang sudah kamu pelajari. Efektivitasnya dipengaruhi stat Intelligence.", 20);
            delayPrint(L"    ✧ ITEM     : Menggunakan item dari inventory, seperti Potion untuk memulihkan HP atau Mana.", 20);
            delayPrint(L"    ✧ BERTAHAN : Kamu fokus menghindar, meningkatkan Evasion-mu secara signifikan untuk serangan musuh berikutnya. Berguna untuk menghindari serangan kuat!", 20);
            delayPrint(L"    ✧ KABUR    : Mencoba melarikan diri dari pertarungan. Tidak selalu berhasil, dan mustahil jika melawan Boss.", 20);
            wcout << endl;
            delayPrint(L"  ❖ STATISTIK PENTING DALAM PERTARUNGAN:", 20);
            delayPrint(L"    ✧ STRENGTH (STR)    : Meningkatkan damage serangan fisikmu.", 20);
            delayPrint(L"    ✧ INTELLIGENCE (INT): Meningkatkan damage sihirmu, efektivitas beberapa sihir pendukung, dan sedikit pertahanan terhadap sihir musuh.", 20);
            delayPrint(L"    ✧ DEFENSE (DEF)     : Mengurangi damage fisik yang kamu terima dari musuh.", 20);
            delayPrint(L"    ✧ AGILITY (AGI)     : Meningkatkan kemungkinanmu menghindari serangan musuh (evasion) dan mungkin akurasimu.", 20);
            delayPrint(L"    ✧ CRITICAL HIT      : Ada peluang kecil seranganmu menghasilkan Critical Hit (damage 1.5x lebih besar!).", 20);
            wcout << endl;

            delayPrint(L"=== STATUS EFEK (BUFF, DEBUFF, DLL) ===", 20);
            delayPrint(L"  ❖ ENCHANTMENT (BUFF): Sihir yang memberikan efek positif sementara pada dirimu (misal 'Flame Weapon' menambah attack, 'Frost Armor' menambah defense, 'Shroud' menambah evasion). Perhatikan durasinya!", 20);
            delayPrint(L"  ❖ DEBUFF MUSUH    : Beberapa sihirmu bisa melemahkan musuh (misalnya 'Curse of Fatigue' mengurangi Attack & Agility musuh, 'Scorching Haze' mengurangi akurasi musuh).", 20);
            delayPrint(L"  ❖ DoT & HoT       : Damage over Time (DoT) seperti 'Ignite' akan melukai musuh setiap giliran. Heal over Time (HoT) seperti dari 'Phoenix Blessing' akan memulihkan HP-mu setiap giliran.", 20);
            delayPrint(L"  ❖ KONDISI NEGATIF : Musuh bisa menyebabkan Stun (lumpuh), Fear (gagal beraksi), atau Silence (tak bisa sihir) padamu. Beberapa sihir cahayamu seperti 'Purification' bisa menghilangkannya.", 20);
            delayPrint(L"  ❖ PERISAI (SHIELD): Sihir seperti 'Guardian Angel' menciptakan perisai HP tambahan. Damage akan mengenai perisai dulu sebelum HP aslimu.", 20);

        } else if (currentPage == 4) {
            centerText(L"✦ TUTORIAL - HALAMAN 4 DARI " + to_wstring(totalPages) + L": DUNIA, TAKDIR & AKHIR CERITA ✦");
            printLine();
            wcout << endl;

            delayPrint(L"=== MENJELAJAHI DUNIA & BERINTERAKSI ===", 20);
            delayPrint(L"  ❖ PETA DUNIA & LOKASI: Gunakan 'Pilih Lokasi' untuk berpindah antar sub-area. Untuk pindah ke wilayah dunia yang berbeda (misal, dari Mansion ke Kota Arcadia), gunakan opsi 'Ke World Map'. Perjalanan antar wilayah dunia memakan Aksi Harian.", 20);
            delayPrint(L"  ❖ DUNGEON           : Lokasi seperti 'Ancient Temple' atau 'Goa Avernix' adalah Dungeon. 'Eksplorasi Lantai' hanya bisa dilakukan sekali per lantai untuk mencari suasana atau temuan kecil. Musuh utama biasanya menunggu di akhir lantai atau sebagai penjaga.", 20);
            delayPrint(L"  ❖ REKANAN (COMPANION): Berbicaralah dengan karakter-karakter penting yang kamu temui ('Bicara dengan [Nama]'). Meningkatkan hubungan (Social Link) dengan mereka akan membuka cerita pribadi mereka, mengungkap sifat mereka, dan pada level maksimal, mereka mungkin memberimu hadiah spesial (seperti senjata unik!) dan bonus stat permanen. Interaksi untuk meningkatkan hubungan memakan Aksi Harian, namun berbicara santai dengan rekanan yang sudah maksimal tidak.", 20);
            wcout << endl;

            delayPrint(L"=== MENGUKIR TAKDIRMU ===", 20);
            delayPrint(L"  ❖ STORY FLAGS       : Setiap keputusan penting, kemenangan, atau bahkan kekalahan dalam event cerita utama (yang muncul di Kalender) akan mengubah 'Story Flags'. Flag ini adalah penentu utama bagaimana ceritamu akan berkembang.", 20);
            delayPrint(L"  ❖ KALENDER & EVENT UTAMA: Perhatikan Kalender di Diary! Event-event utama yang telah dijadwalkan (seperti 'Undangan Tak Terduga' atau 'Bayangan di Kediaman') adalah momen krusial. Keberhasilanmu di sini akan sangat mempengaruhi flag dan jalan ceritamu.", 20);
            delayPrint(L"  ❖ BEBERAPA AKHIR CERITA: Berdasarkan kombinasi Story Flags yang kamu kumpulkan, kisah Weiss von Astra bisa memiliki BEBERAPA AKHIR yang sangat berbeda. Apakah kamu akan berhasil menghindari 'mati konyol' dan menjadi pahlawan? Atau takdir kelam lain menantimu? Semua ada di tanganmu!", 30);
            delayPrint(L"  ❖ JADILAH ARSITEK NASIBMU: Jangan pasrah pada alur novel asli! Eksplorasi, jadi kuat, bangun hubungan, buat pilihan sulit, dan hadapi tantangan. Hanya dengan begitu kamu bisa benar-benar 'menderail plot'!", 30);
            wcout << endl;
            delayPrint(L"Oh, dan jangan lupakan tujuan mulia lainnya: menemukan secangkir TEH YANG LAYAK di dunia antah berantah ini!", 20);
            delayPrint(L"Petualanganmu untuk menulis ulang takdir dimulai sekarang. Semoga berhasil, Weiss!", 20);
        }

        printLine();
        int choiceTutorial;
        if (currentPage < totalPages) {
            wcout << L"Pilihanmu:" << endl;
            wcout << L"  1. Lanjut ke Halaman " << (currentPage + 1) << endl;
            wcout << L"  2. Lewati Sisa Tutorial" << endl;
            wcout << L"Pilih (1-2) ✦: ";
            choiceTutorial = getValidatedChoice(1, 2);
            if (choiceTutorial == 1) {
                currentPage++;
            } else {
                tutorialSkipped = true;
            }
        } else { 
            wcout << L"Pilihanmu:" << endl;
            wcout << L"  1. Selesai Tutorial (Mulai Petualangan)" << endl;
            wcout << L"Pilih (1) ✦: ";
            choiceTutorial = getValidatedChoice(1, 1);
            if (choiceTutorial == 1) {
                tutorialSkipped = true; 
            }
        }
    }

    system("cls");
    if (currentPage == totalPages && tutorialSkipped ) { 
         delayPrint(L"Tutorial selesai! Semoga berhasil mengubah takdirmu dan menemukan teh terenak, Weiss!", 30);
    } else if (tutorialSkipped && currentPage < totalPages) { 
         delayPrint(L"Baiklah, sepertinya kamu sudah tidak sabar! Semoga berhasil mengubah takdirmu, Weiss!", 30);
    } else { 
         delayPrint(L"Tutorial selesai! Semoga berhasil mengubah takdirmu dan menemukan teh terenak, Weiss!", 30);
    }
    printLine();
    waitForEnter(L"Tekan Enter untuk memulai petualanganmu...");
}


long long calculateExpToNextLevel(int currentLevel) {
    if (currentLevel <= 0) return static_cast<long long>(BASE_XP); 
    return static_cast<long long>(floor(BASE_XP * pow(static_cast<double>(currentLevel), XP_EXPONENT)));
}

void advanceToNextDay() {
    currentDay++;
    currentActionsRemaining = maxActionsPerDay; 
    talkedToday.clear(); 

    ActiveDailyQuestNode* currentListNode = activeDailyQuestsHead;
    while (currentListNode != nullptr) {
        ActiveDailyQuestNode* nextNode = currentListNode->next;
        delete currentListNode;
        currentListNode = nextNode;
    }
    activeDailyQuestsHead = nullptr;

    generateDailyQuests(); 

    system("cls"); 
    printLine();
    centerText(L"🌅 HARI BARU TELAH TIBA 🌅");
    printLine();
    delayPrint(L"Matahari pagi menyinari Arcadia, memulai lembaran baru petualanganmu.", 30);
    centerText(L"✦ Sekarang Hari ke-" + to_wstring(currentDay) + L" ✦");
    printLine();

    checkStoryTriggers(); 
    waitForEnter(L"Tekan Enter untuk memulai hari...");
}

void checkEndOfDay() {
    if (currentActionsRemaining <= 0) {
        system("cls");
        printLine();
        centerText(L"⚠ Hari telah menuju malam...");
        printLine();
        delayPrint(L"Aku merasa lelah... Sebaiknya aku segera kembali beristirahat dan mengakhiri hariku.", 30);
        waitForEnter();
    }
}

void consumeAction() {
    if (currentActionsRemaining > 0) {
        currentActionsRemaining--;
    }
    checkEndOfDay();
}




void initializeSpellsForElement(MagicElement& element) {
    
    if (element.name == "Fire") {
        element.description = "An element that controls scorching flames, burning enemies to ash.";
        MagicSpell f1_1, f1_2, f1_3, f1_4, f1_5;

        f1_1.id = "FIRE_BALL_1"; f1_1.name = "Fireball"; f1_1.description = "Serangan api dasar ke satu target.";
        f1_1.elementType = "Fire"; f1_1.tier = 1; f1_1.manaCost = 10; f1_1.basePower = 20;
        f1_1.targetType = "SingleEnemy"; f1_1.isEnchantment = false; element.spells[f1_1.id] = f1_1;

        f1_2.id = "FIRE_EMBER_1"; f1_2.name = "Ember"; f1_2.description = "Serangan api cepat dengan biaya MP rendah, damage kecil.";
        f1_2.elementType = "Fire"; f1_2.tier = 1; f1_2.manaCost = 5; f1_2.basePower = 12;
        f1_2.targetType = "SingleEnemy"; f1_2.isEnchantment = false; element.spells[f1_2.id] = f1_2;

        f1_3.id = "FIRE_IGNITE_1"; f1_3.name = "Ignite"; f1_3.description = "Menyebabkan target terbakar, menerima damage api kecil selama beberapa giliran (DoT).";
        f1_3.elementType = "Fire"; f1_3.tier = 1; f1_3.manaCost = 12; f1_3.basePower = 5; 
        f1_3.targetType = "SingleEnemy"; f1_3.isEnchantment = false; element.spells[f1_3.id] = f1_3;

        f1_4.id = "FIRE_FLAME_WEAPON_1"; f1_4.name = "Flame Weapon"; f1_4.description = "Menyelimuti senjata dengan api, menambah sedikit fire damage pada serangan.";
        f1_4.elementType = "Fire"; f1_4.tier = 1; f1_4.manaCost = 15; f1_4.basePower = 0;
        f1_4.targetType = "Self"; f1_4.isEnchantment = true; f1_4.enchantTurns = 3; f1_4.enchantAttackBonus = 8; element.spells[f1_4.id] = f1_4;

        f1_5.id = "FIRE_SCORCHING_HAZE_1"; f1_5.name = "Scorching Haze"; f1_5.description = "Menciptakan kabut panas yang sedikit mengurangi akurasi musuh untuk beberapa giliran.";
        f1_5.elementType = "Fire"; f1_5.tier = 1; f1_5.manaCost = 8; f1_5.basePower = 0;
        f1_5.targetType = "SingleEnemy"; f1_5.isEnchantment = false; element.spells[f1_5.id] = f1_5;

        MagicSpell f2_1, f2_2, f2_3, f2_4, f2_5;
        f2_1.id = "FIRE_BLAST_2"; f2_1.name = "Fire Blast"; f2_1.description = "Ledakan api terkonsentrasi pada satu target, damage tinggi.";
        f2_1.elementType = "Fire"; f2_1.tier = 2; f2_1.manaCost = 22; f2_1.basePower = 45;
        f2_1.targetType = "SingleEnemy"; f2_1.isEnchantment = false; f2_1.prerequisites = {"FIRE_BALL_1"}; element.spells[f2_1.id] = f2_1;

        f2_2.id = "FIRE_ENGULFING_FLAMES_2"; f2_2.name = "Engulfing Flames"; f2_2.description = "Menyelimuti satu target dengan api besar, memberikan damage tinggi dan efek terbakar yang kuat.";
        f2_2.elementType = "Fire"; f2_2.tier = 2; f2_2.manaCost = 28; f2_2.basePower = 35; 
        f2_2.targetType = "SingleEnemy"; f2_2.isEnchantment = false; f2_2.prerequisites = {"FIRE_IGNITE_1"}; element.spells[f2_2.id] = f2_2;

        f2_3.id = "FIRE_INTENSE_BURN_2"; f2_3.name = "Intense Burn"; f2_3.description = "Meningkatkan damage dari efek terbakar (DoT) yang sudah ada pada target.";
        f2_3.elementType = "Fire"; f2_3.tier = 2; f2_3.manaCost = 25; f2_3.basePower = 10; 
        f2_3.targetType = "SingleEnemy"; f2_3.isEnchantment = false; f2_3.prerequisites = {"FIRE_IGNITE_1"}; element.spells[f2_3.id] = f2_3;

        f2_4.id = "FIRE_BLAZING_SOUL_2"; f2_4.name = "Blazing Soul"; f2_4.description = "Meningkatkan kekuatan sihir api (Intelligence) pengguna untuk sementara waktu.";
        f2_4.elementType = "Fire"; f2_4.tier = 2; f2_4.manaCost = 20; f2_4.basePower = 0;
        f2_4.targetType = "Self"; f2_4.isEnchantment = true; f2_4.enchantTurns = 4; f2_4.prerequisites = {"FIRE_EMBER_1"}; element.spells[f2_4.id] = f2_4;

        f2_5.id = "FIRE_EXPLOSIVE_RUNE_2"; f2_5.name = "Explosive Rune"; f2_5.description = "Menanam rune api pada target yang akan meledak setelah beberapa giliran.";
        f2_5.elementType = "Fire"; f2_5.tier = 2; f2_5.manaCost = 18; f2_5.basePower = 50; 
        f2_5.targetType = "SingleEnemy"; f2_5.isEnchantment = false; f2_5.prerequisites = {"FIRE_FLAME_WEAPON_1"}; element.spells[f2_5.id] = f2_5;

        MagicSpell f3_1, f3_2, f3_3, f3_4, f3_5;
        f3_1.id = "FIRE_METEOR_STRIKE_3"; f3_1.name = "Meteor Strike"; f3_1.description = "Menjatuhkan satu meteor besar pada target, damage masif.";
        f3_1.elementType = "Fire"; f3_1.tier = 3; f3_1.manaCost = 45; f3_1.basePower = 85;
        f3_1.targetType = "SingleEnemy"; f3_1.isEnchantment = false; f3_1.prerequisites = {"FIRE_BLAST_2"}; element.spells[f3_1.id] = f3_1;

        f3_2.id = "FIRE_FIRE_ARMAGEDDON_3"; f3_2.name = "Fire Armageddon"; f3_2.description = "Memanggil badai api yang menghanguskan target dengan damage sangat besar.";
        f3_2.elementType = "Fire"; f3_2.tier = 3; f3_2.manaCost = 70; f3_2.basePower = 90;
        f3_2.targetType = "SingleEnemy"; f3_2.isEnchantment = false; f3_2.prerequisites = {"FIRE_ENGULFING_FLAMES_2", "FIRE_INTENSE_BURN_2"}; element.spells[f3_2.id] = f3_2;

        f3_3.id = "FIRE_PHOENIX_BLESSING_3"; f3_3.name = "Phoenix Blessing"; f3_3.description = "Memberi pengguna regenerasi HP kuat dan sekali bangkit dari kematian jika HP mencapai 0.";
        f3_3.elementType = "Fire"; f3_3.tier = 3; f3_3.manaCost = 60; f3_3.basePower = 0;
        f3_3.targetType = "Self"; f3_3.isEnchantment = true; f3_3.enchantTurns = 5; f3_3.prerequisites = {"FIRE_BLAZING_SOUL_2"}; element.spells[f3_3.id] = f3_3;

        f3_4.id = "FIRE_VOLCANIC_ERUPTION_3"; f3_4.name = "Volcanic Eruption"; f3_4.description = "Menyebabkan tanah di bawah musuh meletus, damage besar berkelanjutan (DoT).";
        f3_4.elementType = "Fire"; f3_4.tier = 3; f3_4.manaCost = 55; f3_4.basePower = 40; 
        f3_4.targetType = "SingleEnemy"; f3_4.isEnchantment = false; f3_4.prerequisites = {"FIRE_EXPLOSIVE_RUNE_2"}; element.spells[f3_4.id] = f3_4;

        f3_5.id = "FIRE_INFERNO_PILLAR_3"; f3_5.name = "Inferno Pillar"; f3_5.description = "Memanggil pilar api raksasa untuk menghanguskan satu target dengan damage masif.";
        f3_5.elementType = "Fire"; f3_5.tier = 3; f3_5.manaCost = 80; f3_5.basePower = 150;
        f3_5.targetType = "SingleEnemy"; f3_5.isEnchantment = false; f3_5.prerequisites = {"FIRE_METEOR_STRIKE_3", "FIRE_PHOENIX_BLESSING_3"}; element.spells[f3_5.id] = f3_5;
    }
    
    else if (element.name == "Ice") {
        element.description = "An element that manipulates freezing ice, stopping enemies in their tracks.";
        MagicSpell i1_1, i1_2, i1_3, i1_4, i1_5;
        i1_1.id = "ICE_SHARD_1"; i1_1.name = "Ice Shard"; i1_1.description = "Proyektil es tajam ke satu target.";
        i1_1.elementType = "Ice"; i1_1.tier = 1; i1_1.manaCost = 12; i1_1.basePower = 22;
        i1_1.targetType = "SingleEnemy"; i1_1.isEnchantment = false; element.spells[i1_1.id] = i1_1;

        i1_2.id = "ICE_FROST_ARMOR_1"; i1_2.name = "Frost Armor"; i1_2.description = "Menciptakan lapisan es tipis yang meningkatkan pertahanan diri sementara.";
        i1_2.elementType = "Ice"; i1_2.tier = 1; i1_2.manaCost = 10; i1_2.basePower = 0;
        i1_2.targetType = "Self"; i1_2.isEnchantment = true; i1_2.enchantTurns = 4; element.spells[i1_2.id] = i1_2;

        i1_3.id = "ICE_CHILLING_WIND_1"; i1_3.name = "Chilling Wind"; i1_3.description = "Hembusan angin es ke satu target, sedikit damage dan berpotensi memperlambat (Slow - Agility Debuff).";
        i1_3.elementType = "Ice"; i1_3.tier = 1; i1_3.manaCost = 9; i1_3.basePower = 10;
        i1_3.targetType = "SingleEnemy"; i1_3.isEnchantment = false; element.spells[i1_3.id] = i1_3;

        i1_4.id = "ICE_FROZEN_GROUND_1"; i1_4.name = "Frozen Ground"; i1_4.description = "Membekukan tanah, berpotensi membuat musuh terpeleset (mengurangi agility musuh sementara).";
        i1_4.elementType = "Ice"; i1_4.tier = 1; i1_4.manaCost = 14; i1_4.basePower = 5;
        i1_4.targetType = "SingleEnemy"; i1_4.isEnchantment = false; element.spells[i1_4.id] = i1_4;

        i1_5.id = "ICE_ICY_EDGE_1"; i1_5.name = "Icy Edge"; i1_5.description = "Menyelimuti senjata dengan lapisan es tipis, menambah sedikit ice damage.";
        i1_5.elementType = "Ice"; i1_5.tier = 1; i1_5.manaCost = 15; i1_5.basePower = 0;
        i1_5.targetType = "Self"; i1_5.isEnchantment = true; i1_5.enchantTurns = 3; i1_5.enchantAttackBonus = 9; element.spells[i1_5.id] = i1_5;

        MagicSpell i2_1, i2_2, i2_3, i2_4, i2_5;
        i2_1.id = "ICE_FROZEN_LANCE_2"; i2_1.name = "Frozen Lance"; i2_1.description = "Tombak es menusuk dengan damage sedang dan peluang membekukan (Stun) musuh.";
        i2_1.elementType = "Ice"; i2_1.tier = 2; i2_1.manaCost = 22; i2_1.basePower = 35;
        i2_1.targetType = "SingleEnemy"; i2_1.isEnchantment = false; i2_1.prerequisites = {"ICE_SHARD_1"}; element.spells[i2_1.id] = i2_1;

        i2_2.id = "ICE_GLACIAL_ARMOR_2"; i2_2.name = "Glacial Armor"; i2_2.description = "Menciptakan zirah es tebal yang sangat meningkatkan pertahanan.";
        i2_2.elementType = "Ice"; i2_2.tier = 2; i2_2.manaCost = 20; i2_2.basePower = 0;
        i2_2.targetType = "Self"; i2_2.isEnchantment = true; i2_2.enchantTurns = 5; i2_2.prerequisites = {"ICE_FROST_ARMOR_1"}; element.spells[i2_2.id] = i2_2;

        i2_3.id = "ICE_DEEP_FREEZE_2"; i2_3.name = "Deep Freeze"; i2_3.description = "Serangan es terkonsentrasi yang memberikan damage besar dan berpeluang tinggi membekukan (Stun) target.";
        i2_3.elementType = "Ice"; i2_3.tier = 2; i2_3.manaCost = 30; i2_3.basePower = 40;
        i2_3.targetType = "SingleEnemy"; i2_3.isEnchantment = false; i2_3.prerequisites = {"ICE_CHILLING_WIND_1", "ICE_FROZEN_GROUND_1"}; element.spells[i2_3.id] = i2_3;

        i2_4.id = "ICE_FROSTBITE_WEAPON_2"; i2_4.name = "Frostbite Weapon"; i2_4.description = "Menyihir senjata dengan aura dingin ekstrem, menambah ice damage dan menyebabkan efek frostbite (DoT kecil).";
        i2_4.elementType = "Ice"; i2_4.tier = 2; i2_4.manaCost = 25; i2_4.basePower = 0;
        i2_4.targetType = "Self"; i2_4.isEnchantment = true; i2_4.enchantTurns = 4; i2_4.enchantAttackBonus = 18; i2_4.prerequisites = {"ICE_ICY_EDGE_1"}; element.spells[i2_4.id] = i2_4;

        i2_5.id = "ICE_ICE_CLONE_2"; i2_5.name = "Ice Clone"; i2_5.description = "Menciptakan duplikat es pengguna yang meningkatkan evasion sementara.";
        i2_5.elementType = "Ice"; i2_5.tier = 2; i2_5.manaCost = 28; i2_5.basePower = 0;
        i2_5.targetType = "Self"; i2_5.isEnchantment = true; i2_5.enchantTurns = 3; i2_5.prerequisites = {"ICE_FROST_ARMOR_1"}; element.spells[i2_5.id] = i2_5;

        MagicSpell i3_1, i3_2, i3_3, i3_4, i3_5;
        i3_1.id = "ICE_DIAMOND_DUST_3"; i3_1.name = "Diamond Dust"; i3_1.description = "Menyebarkan partikel es super dingin yang merusak target dan berpeluang tinggi membekukan (stun).";
        i3_1.elementType = "Ice"; i3_1.tier = 3; i3_1.manaCost = 50; i3_1.basePower = 70;
        i3_1.targetType = "SingleEnemy"; i3_1.isEnchantment = false; i3_1.prerequisites = {"ICE_DEEP_FREEZE_2"}; element.spells[i3_1.id] = i3_1;

        i3_2.id = "ICE_CRYSTAL_PRISON_3"; i3_2.name = "Crystal Prison"; i3_2.description = "Menjebak target dalam penjara kristal es, membuatnya tidak bisa bergerak (stun lama) dan sangat rentan (defense down).";
        i3_2.elementType = "Ice"; i3_2.tier = 3; i3_2.manaCost = 45; i3_2.basePower = 20;
        i3_2.targetType = "SingleEnemy"; i3_2.isEnchantment = false; i3_2.prerequisites = {"ICE_FROZEN_LANCE_2"}; element.spells[i3_2.id] = i3_2;

        i3_3.id = "ICE_WINTERS_MANTLE_3"; i3_3.name = "Winter's Mantle"; i3_3.description = "Memberi pengguna aura es yang sangat meningkatkan pertahanan dan membalas serangan fisik dengan damage es.";
        i3_3.elementType = "Ice"; i3_3.tier = 3; i3_3.manaCost = 60; i3_3.basePower = 0;
        i3_3.targetType = "Self"; i3_3.isEnchantment = true; i3_3.enchantTurns = 5; i3_3.prerequisites = {"ICE_GLACIAL_ARMOR_2"}; element.spells[i3_3.id] = i3_3;

        i3_4.id = "ICE_AVALANCHE_CALL_3"; i3_4.name = "Call Avalanche"; i3_4.description = "Memanggil longsoran salju dahsyat yang menghantam satu target dengan kekuatan alam, damage masif.";
        i3_4.elementType = "Ice"; i3_4.tier = 3; i3_4.manaCost = 65; i3_4.basePower = 120;
        i3_4.targetType = "SingleEnemy"; i3_4.isEnchantment = false; i3_4.prerequisites = {"ICE_DEEP_FREEZE_2", "ICE_FROZEN_GROUND_1"}; element.spells[i3_4.id] = i3_4;

        i3_5.id = "ICE_ABSOLUTE_ZERO_3"; i3_5.name = "Absolute Zero"; i3_5.description = "Menciptakan zona suhu nol absolut di sekitar target, damage es masif dan berpeluang besar membekukan total (stun lama).";
        i3_5.elementType = "Ice"; i3_5.tier = 3; i3_5.manaCost = 85; i3_5.basePower = 100;
        i3_5.targetType = "SingleEnemy"; i3_5.isEnchantment = false; i3_5.prerequisites = {"ICE_DIAMOND_DUST_3", "ICE_WINTERS_MANTLE_3"}; element.spells[i3_5.id] = i3_5;
    }
    
    else if (element.name == "Thunder") {
        element.description = "An element that wields the devastating power of lightning, striking with blinding speed.";
        MagicSpell t1_1, t1_2, t1_3, t1_4, t1_5;
        t1_1.id = "THUNDER_SPARK_1"; t1_1.name = "Spark"; t1_1.description = "Serangan listrik minor ke satu target.";
        t1_1.elementType = "Thunder"; t1_1.tier = 1; t1_1.manaCost = 11; t1_1.basePower = 21;
        t1_1.targetType = "SingleEnemy"; t1_1.isEnchantment = false; element.spells[t1_1.id] = t1_1;

        t1_2.id = "THUNDER_JOLT_1"; t1_2.name = "Jolt"; t1_2.description = "Kejutan listrik cepat, damage kecil, sedikit mengurangi kecepatan target (Agility Debuff).";
        t1_2.elementType = "Thunder"; t1_2.tier = 1; t1_2.manaCost = 6; t1_2.basePower = 13;
        t1_2.targetType = "SingleEnemy"; t1_2.isEnchantment = false; element.spells[t1_2.id] = t1_2;

        t1_3.id = "THUNDER_STATIC_FIELD_1"; t1_3.name = "Static Field"; t1_3.description = "Menciptakan medan listrik statis di sekitar target, damage kecil per giliran (DoT).";
        t1_3.elementType = "Thunder"; t1_3.tier = 1; t1_3.manaCost = 13; t1_3.basePower = 6; 
        t1_3.targetType = "SingleEnemy"; t1_3.isEnchantment = false; element.spells[t1_3.id] = t1_3;

        t1_4.id = "THUNDER_CHARGE_WEAPON_1"; t1_4.name = "Charged Weapon"; t1_4.description = "Memberi muatan listrik pada senjata, menambah sedikit thunder damage.";
        t1_4.elementType = "Thunder"; t1_4.tier = 1; t1_4.manaCost = 16; t1_4.basePower = 0;
        t1_4.targetType = "Self"; t1_4.isEnchantment = true; t1_4.enchantTurns = 3; t1_4.enchantAttackBonus = 9; element.spells[t1_4.id] = t1_4;

        t1_5.id = "THUNDER_QUICKEN_REFLEX_1"; t1_5.name = "Quicken Reflexes"; t1_5.description = "Meningkatkan sedikit kegesitan (Agility) diri sendiri untuk sementara.";
        t1_5.elementType = "Thunder"; t1_5.tier = 1; t1_5.manaCost = 9; t1_5.basePower = 0;
        t1_5.targetType = "Self"; t1_5.isEnchantment = true; t1_5.enchantTurns = 4; element.spells[t1_5.id] = t1_5;

        MagicSpell t2_1, t2_2, t2_3, t2_4, t2_5;
        t2_1.id = "THUNDER_LIGHTNING_STRIKE_2"; t2_1.name = "Lightning Strike"; t2_1.description = "Sambaran kilat kuat ke satu musuh, damage sedang dengan peluang stun.";
        t2_1.elementType = "Thunder"; t2_1.tier = 2; t2_1.manaCost = 23; t2_1.basePower = 42;
        t2_1.targetType = "SingleEnemy"; t2_1.isEnchantment = false; t2_1.prerequisites = {"THUNDER_SPARK_1"}; element.spells[t2_1.id] = t2_1;

        t2_2.id = "THUNDER_THUNDERCLAP_2"; t2_2.name = "Thunderclap"; t2_2.description = "Sambaran petir menggelegar ke satu target, memberikan damage dan berpeluang tinggi menyebabkan stun singkat.";
        t2_2.elementType = "Thunder"; t2_2.tier = 2; t2_2.manaCost = 28; t2_2.basePower = 38;
        t2_2.targetType = "SingleEnemy"; t2_2.isEnchantment = false; t2_2.prerequisites = {"THUNDER_JOLT_1"}; element.spells[t2_2.id] = t2_2;

        t2_3.id = "THUNDER_MAGNETIC_OVERLOAD_2"; t2_3.name = "Magnetic Overload"; t2_3.description = "Menghantam target dengan energi listrik terkonsentrasi, memberikan damage dan menurunkan pertahanan sihirnya sementara.";
        t2_3.elementType = "Thunder"; t2_3.tier = 2; t2_3.manaCost = 26; t2_3.basePower = 35;
        t2_3.targetType = "SingleEnemy"; t2_3.isEnchantment = false; t2_3.prerequisites = {"THUNDER_STATIC_FIELD_1"}; element.spells[t2_3.id] = t2_3;

        t2_4.id = "THUNDER_VOLTAIC_EDGE_2"; t2_4.name = "Voltaic Edge"; t2_4.description = "Menyalurkan listrik kuat ke senjata, menambah damage listrik signifikan dan meningkatkan kecepatan serangan (agility).";
        t2_4.elementType = "Thunder"; t2_4.tier = 2; t2_4.manaCost = 24; t2_4.basePower = 0;
        t2_4.targetType = "Self"; t2_4.isEnchantment = true; t2_4.enchantTurns = 4; t2_4.enchantAttackBonus = 20; t2_4.prerequisites = {"THUNDER_CHARGE_WEAPON_1"}; element.spells[t2_4.id] = t2_4;

        t2_5.id = "THUNDER_SPEED_OF_LIGHTNING_2"; t2_5.name = "Speed of Lightning"; t2_5.description = "Meningkatkan drastis kegesitan dan jumlah aksi per giliran untuk sementara waktu.";
        t2_5.elementType = "Thunder"; t2_5.tier = 2; t2_5.manaCost = 20; t2_5.basePower = 0;
        t2_5.targetType = "Self"; t2_5.isEnchantment = true; t2_5.enchantTurns = 3; t2_5.prerequisites = {"THUNDER_QUICKEN_REFLEX_1"}; element.spells[t2_5.id] = t2_5;

        MagicSpell t3_1, t3_2, t3_3, t3_4, t3_5;
        t3_1.id = "THUNDER_JUDGEMENT_BOLT_3"; t3_1.name = "Judgement Bolt"; t3_1.description = "Petir masif dari langit menghantam satu musuh, damage sangat besar dan stun lama.";
        t3_1.elementType = "Thunder"; t3_1.tier = 3; t3_1.manaCost = 48; t3_1.basePower = 95;
        t3_1.targetType = "SingleEnemy"; t3_1.isEnchantment = false; t3_1.prerequisites = {"THUNDER_LIGHTNING_STRIKE_2"}; element.spells[t3_1.id] = t3_1;

        t3_2.id = "THUNDER_STORM_CONDUIT_3"; t3_2.name = "Thunderstorm Conduit"; t3_2.description = "Pengguna menjadi saluran badai petir, menyambar musuh dengan petir kuat beberapa kali.";
        t3_2.elementType = "Thunder"; t3_2.tier = 3; t3_2.manaCost = 68; t3_2.basePower = 30; 
        t3_2.targetType = "SingleEnemy"; t3_2.isEnchantment = false; t3_2.prerequisites = {"THUNDER_THUNDERCLAP_2", "THUNDER_MAGNETIC_OVERLOAD_2"}; element.spells[t3_2.id] = t3_2;

        t3_3.id = "THUNDER_MJOLNIR_AWAKENING_3"; t3_3.name = "Mjolnir's Awakening"; t3_3.description = "Menyihir senjata dengan kekuatan Mjolnir, damage listrik ekstrem, dan serangan berpeluang stun musuh.";
        t3_3.elementType = "Thunder"; t3_3.tier = 3; t3_3.manaCost = 60; t3_3.basePower = 0;
        t3_3.targetType = "Self"; t3_3.isEnchantment = true; t3_3.enchantTurns = 5; t3_3.enchantAttackBonus = 50; t3_3.prerequisites = {"THUNDER_VOLTAIC_EDGE_2"}; element.spells[t3_3.id] = t3_3;

        t3_4.id = "THUNDER_RIDE_THE_LIGHTNING_3"; t3_4.name = "Ride the Lightning"; t3_4.description = "Pengguna bergerak secepat kilat, sangat meningkatkan evasion dan dapat menyerang berkali-kali dalam satu giliran.";
        t3_4.elementType = "Thunder"; t3_4.tier = 3; t3_4.manaCost = 50; t3_4.basePower = 0;
        t3_4.targetType = "Self"; t3_4.isEnchantment = true; t3_4.enchantTurns = 3; t3_4.prerequisites = {"THUNDER_SPEED_OF_LIGHTNING_2"}; element.spells[t3_4.id] = t3_4;

        t3_5.id = "THUNDER_SKY_SOVEREIGNS_FURY_3"; t3_5.name = "Sky Sovereign's Fury"; t3_5.description = "Menghantam target dengan murka langit, damage listrik kolosal dan melumpuhkan pertahanan musuh sementara.";
        t3_5.elementType = "Thunder"; t3_5.tier = 3; t3_5.manaCost = 90; t3_5.basePower = 140;
        t3_5.targetType = "SingleEnemy"; t3_5.isEnchantment = false; t3_5.prerequisites = {"THUNDER_JUDGEMENT_BOLT_3", "THUNDER_STORM_CONDUIT_3"}; element.spells[t3_5.id] = t3_5;
    }
    
    else if (element.name == "Wind") {
        element.description = "An element that manipulates gusts of wind and storms, prioritizing speed and agility.";
        MagicSpell w1_1, w1_2, w1_3, w1_4, w1_5;
        w1_1.id = "WIND_CUTTER_1"; w1_1.name = "Wind Cutter"; w1_1.description = "Serangan angin tajam ke satu target.";
        w1_1.elementType = "Wind"; w1_1.tier = 1; w1_1.manaCost = 9; w1_1.basePower = 18;
        w1_1.targetType = "SingleEnemy"; w1_1.isEnchantment = false; element.spells[w1_1.id] = w1_1;

        w1_2.id = "WIND_AIR_BULLET_1"; w1_2.name = "Air Bullet"; w1_2.description = "Tembakan udara terkompresi, cepat dan berbiaya rendah.";
        w1_2.elementType = "Wind"; w1_2.tier = 1; w1_2.manaCost = 4; w1_2.basePower = 10;
        w1_2.targetType = "SingleEnemy"; w1_2.isEnchantment = false; element.spells[w1_2.id] = w1_2;

        w1_3.id = "WIND_GUST_1"; w1_3.name = "Gust"; w1_3.description = "Hembusan angin kuat yang dapat mengganggu konsentrasi musuh (chance interrupt).";
        w1_3.elementType = "Wind"; w1_3.tier = 1; w1_3.manaCost = 10; w1_3.basePower = 5;
        w1_3.targetType = "SingleEnemy"; w1_3.isEnchantment = false; element.spells[w1_3.id] = w1_3;

        w1_4.id = "WIND_FEATHER_STEP_1"; w1_4.name = "Feather Step"; w1_4.description = "Meringankan langkah pengguna, sedikit meningkatkan evasion.";
        w1_4.elementType = "Wind"; w1_4.tier = 1; w1_4.manaCost = 12; w1_4.basePower = 0;
        w1_4.targetType = "Self"; w1_4.isEnchantment = true; w1_4.enchantTurns = 4; element.spells[w1_4.id] = w1_4;

        w1_5.id = "WIND_AERO_BLADE_1"; w1_5.name = "Aero Blade"; w1_5.description = "Menyelimuti senjata dengan bilah angin tajam, menambah sedikit wind damage.";
        w1_5.elementType = "Wind"; w1_5.tier = 1; w1_5.manaCost = 14; w1_5.basePower = 0;
        w1_5.targetType = "Self"; w1_5.isEnchantment = true; w1_5.enchantTurns = 3; w1_5.enchantAttackBonus = 7; element.spells[w1_5.id] = w1_5;

        MagicSpell w2_1, w2_2, w2_3, w2_4, w2_5;
        w2_1.id = "WIND_GALE_FORCE_2"; w2_1.name = "Gale Force"; w2_1.description = "Serangkaian tebasan angin kuat ke satu target.";
        w2_1.elementType = "Wind"; w2_1.tier = 2; w2_1.manaCost = 20; w2_1.basePower = 40;
        w2_1.targetType = "SingleEnemy"; w2_1.isEnchantment = false; w2_1.prerequisites = {"WIND_CUTTER_1", "WIND_AIR_BULLET_1"}; element.spells[w2_1.id] = w2_1;

        w2_2.id = "WIND_CYCLONE_SHIELD_2"; w2_2.name = "Cyclone Shield"; w2_2.description = "Menciptakan perisai angin berputar yang meningkatkan defense dan evasion.";
        w2_2.elementType = "Wind"; w2_2.tier = 2; w2_2.manaCost = 18; w2_2.basePower = 0;
        w2_2.targetType = "Self"; w2_2.isEnchantment = true; w2_2.enchantTurns = 4; w2_2.prerequisites = {"WIND_FEATHER_STEP_1"}; element.spells[w2_2.id] = w2_2;

        w2_3.id = "WIND_DISORIENTING_GUST_2"; w2_3.name = "Disorienting Gust"; w2_3.description = "Hembusan angin kuat yang merusak dan berpotensi membuat serangan musuh berikutnya kurang akurat.";
        w2_3.elementType = "Wind"; w2_3.tier = 2; w2_3.manaCost = 24; w2_3.basePower = 30;
        w2_3.targetType = "SingleEnemy"; w2_3.isEnchantment = false; w2_3.prerequisites = {"WIND_GUST_1"}; element.spells[w2_3.id] = w2_3;

        w2_4.id = "WIND_TEMPEST_BLADES_2"; w2_4.name = "Tempest Blades"; w2_4.description = "Senjata diselimuti bilah angin ganas, meningkatkan damage serangan dan kecepatan serangan (agility).";
        w2_4.elementType = "Wind"; w2_4.tier = 2; w2_4.manaCost = 22; w2_4.basePower = 0;
        w2_4.targetType = "Self"; w2_4.isEnchantment = true; w2_4.enchantTurns = 3; w2_4.enchantAttackBonus = 19; w2_4.prerequisites = {"WIND_AERO_BLADE_1"}; element.spells[w2_4.id] = w2_4;

        w2_5.id = "WIND_SILENCING_GUST_2"; w2_5.name = "Silencing Gust"; w2_5.description = "Hembusan angin kuat yang berpeluang membungkam (Silence) target, mencegah penggunaan sihir untuk sementara.";
        w2_5.elementType = "Wind"; w2_5.tier = 2; w2_5.manaCost = 20; w2_5.basePower = 10;
        w2_5.targetType = "SingleEnemy"; w2_5.isEnchantment = false; w2_5.prerequisites = {"WIND_GUST_1"}; element.spells[w2_5.id] = w2_5;

        MagicSpell w3_1, w3_2, w3_3, w3_4, w3_5;
        w3_1.id = "WIND_TORNADO_OF_DESTRUCTION_3"; w3_1.name = "Tornado of Destruction"; w3_1.description = "Memanggil tornado yang menghantam target dengan damage besar berkelanjutan (DoT).";
        w3_1.elementType = "Wind"; w3_1.tier = 3; w3_1.manaCost = 60; w3_1.basePower = 50; 
        w3_1.targetType = "SingleEnemy"; w3_1.isEnchantment = false; w3_1.prerequisites = {"WIND_GALE_FORCE_2", "WIND_DISORIENTING_GUST_2"}; element.spells[w3_1.id] = w3_1;

        w3_2.id = "WIND_EYE_OF_THE_STORM_3"; w3_2.name = "Eye of the Storm"; w3_2.description = "Menciptakan zona tenang di sekitar pengguna, sangat meningkatkan evasion dan membalas serangan jarak dekat.";
        w3_2.elementType = "Wind"; w3_2.tier = 3; w3_2.manaCost = 50; w3_2.basePower = 0;
        w3_2.targetType = "Self"; w3_2.isEnchantment = true; w3_2.enchantTurns = 4; w3_2.prerequisites = {"WIND_CYCLONE_SHIELD_2"}; element.spells[w3_2.id] = w3_2;

        w3_3.id = "WIND_SKY_LORDS_WRATH_3"; w3_3.name = "Sky Lord's Wrath"; w3_3.description = "Senjata diberkati kekuatan dewa langit, serangan menjadi sangat cepat, kuat, dan berpeluang kritikal tinggi.";
        w3_3.elementType = "Wind"; w3_3.tier = 3; w3_3.manaCost = 55; w3_3.basePower = 0;
        w3_3.targetType = "Self"; w3_3.isEnchantment = true; w3_3.enchantTurns = 5; w3_3.enchantAttackBonus = 48; w3_3.prerequisites = {"WIND_TEMPEST_BLADES_2"}; element.spells[w3_3.id] = w3_3;

        w3_4.id = "WIND_GALE_STEP_3"; w3_4.name = "Gale Step"; w3_4.description = "Pengguna bergerak secepat badai, meningkatkan agility dan evasion secara drastis.";
        w3_4.elementType = "Wind"; w3_4.tier = 3; w3_4.manaCost = 45; w3_4.basePower = 0;
        w3_4.targetType = "Self"; w3_4.isEnchantment = true; w3_4.enchantTurns = 3; w3_4.prerequisites = {"WIND_FEATHER_STEP_1", "WIND_SILENCING_GUST_2"}; element.spells[w3_4.id] = w3_4;

        w3_5.id = "WIND_ZEPHYRS_DANCE_3"; w3_5.name = "Zephyr's Dance"; w3_5.description = "Pengguna melancarkan serangkaian tebasan angin mematikan ke satu target dengan kecepatan tak terhindarkan.";
        w3_5.elementType = "Wind"; w3_5.tier = 3; w3_5.manaCost = 88; w3_5.basePower = 130; 
        w3_5.targetType = "SingleEnemy"; w3_5.isEnchantment = false; w3_5.prerequisites = {"WIND_TORNADO_OF_DESTRUCTION_3", "WIND_SKY_LORDS_WRATH_3"}; element.spells[w3_5.id] = w3_5;
    }
    
    else if (element.name == "Dark") {
        element.description = "An element that harnesses mysterious and potent dark energies, focusing on draining and weakening foes.";
        MagicSpell d1_1, d1_2, d1_3, d1_4, d1_5;
        d1_1.id = "DARK_SHADOW_BOLT_1"; d1_1.name = "Shadow Bolt"; d1_1.description = "Proyektil energi gelap ke satu target.";
        d1_1.elementType = "Dark"; d1_1.tier = 1; d1_1.manaCost = 10; d1_1.basePower = 19;
        d1_1.targetType = "SingleEnemy"; d1_1.isEnchantment = false; element.spells[d1_1.id] = d1_1;

        d1_2.id = "DARK_MINOR_DRAIN_1"; d1_2.name = "Minor Drain"; d1_2.description = "Menyerap sedikit HP dari target.";
        d1_2.elementType = "Dark"; d1_2.tier = 1; d1_2.manaCost = 12; d1_2.basePower = 10;
        d1_2.targetType = "SingleEnemy"; d1_2.isEnchantment = false; element.spells[d1_2.id] = d1_2;

        d1_3.id = "DARK_CURSE_OF_FATIGUE_1"; d1_3.name = "Curse of Fatigue"; d1_3.description = "Membuat target lebih lambat (Agility Debuff) dan lemah serangannya (Attack Debuff).";
        d1_3.elementType = "Dark"; d1_3.tier = 1; d1_3.manaCost = 9; d1_3.basePower = 0;
        d1_3.targetType = "SingleEnemy"; d1_3.isEnchantment = false; element.spells[d1_3.id] = d1_3;

        d1_4.id = "DARK_SHROUD_1"; d1_4.name = "Shroud"; d1_4.description = "Menyelimuti diri dalam bayangan, meningkatkan evasion sementara.";
        d1_4.elementType = "Dark"; d1_4.tier = 1; d1_4.manaCost = 11; d1_4.basePower = 0;
        d1_4.targetType = "Self"; d1_4.isEnchantment = true; d1_4.enchantTurns = 3; element.spells[d1_4.id] = d1_4;

        d1_5.id = "DARK_INFUSED_BLADE_1"; d1_5.name = "Infused Blade"; d1_5.description = "Menyuntikkan energi gelap ke senjata, menambah sedikit dark damage.";
        d1_5.elementType = "Dark"; d1_5.tier = 1; d1_5.manaCost = 15; d1_5.basePower = 0;
        d1_5.targetType = "Self"; d1_5.isEnchantment = true; d1_5.enchantTurns = 3; d1_5.enchantAttackBonus = 8; element.spells[d1_5.id] = d1_5;

        MagicSpell d2_1, d2_2, d2_3, d2_4, d2_5;
        d2_1.id = "DARK_NIGHTMARE_BLAST_2"; d2_1.name = "Nightmare Blast"; d2_1.description = "Ledakan energi gelap kuat yang berpotensi menyebabkan ketakutan (Fear - chance musuh gagal aksi).";
        d2_1.elementType = "Dark"; d2_1.tier = 2; d2_1.manaCost = 24; d2_1.basePower = 38;
        d2_1.targetType = "SingleEnemy"; d2_1.isEnchantment = false; d2_1.prerequisites = {"DARK_SHADOW_BOLT_1"}; element.spells[d2_1.id] = d2_1;

        d2_2.id = "DARK_LIFE_TAP_2"; d2_2.name = "Life Tap"; d2_2.description = "Menyerap HP target secara signifikan untuk memulihkan diri.";
        d2_2.elementType = "Dark"; d2_2.tier = 2; d2_2.manaCost = 28; d2_2.basePower = 30;
        d2_2.targetType = "SingleEnemy"; d2_2.isEnchantment = false; d2_2.prerequisites = {"DARK_MINOR_DRAIN_1"}; element.spells[d2_2.id] = d2_2;

        d2_3.id = "DARK_CURSE_OF_VULNERABILITY_2"; d2_3.name = "Curse of Vulnerability"; d2_3.description = "Membuat target sangat rentan terhadap semua jenis damage (Defense Debuff kuat).";
        d2_3.elementType = "Dark"; d2_3.tier = 2; d2_3.manaCost = 22; d2_3.basePower = 0;
        d2_3.targetType = "SingleEnemy"; d2_3.isEnchantment = false; d2_3.prerequisites = {"DARK_CURSE_OF_FATIGUE_1"}; element.spells[d2_3.id] = d2_3;

        d2_4.id = "DARK_SHADOW_WALK_2"; d2_4.name = "Shadow Walk"; d2_4.description = "Menghilang ke bayangan dan muncul kembali untuk serangan mendadak dengan bonus damage.";
        d2_4.elementType = "Dark"; d2_4.tier = 2; d2_4.manaCost = 18; d2_4.basePower = 0;
        d2_4.targetType = "Self"; d2_4.isEnchantment = false; d2_4.prerequisites = {"DARK_SHROUD_1"}; element.spells[d2_4.id] = d2_4;

        d2_5.id = "DARK_SOUL_EATER_WEAPON_2"; d2_5.name = "Soul Eater Weapon"; d2_5.description = "Senjata diselimuti energi penguras jiwa, menambah dark damage dan menyerap MP saat menyerang.";
        d2_5.elementType = "Dark"; d2_5.tier = 2; d2_5.manaCost = 26; d2_5.basePower = 0;
        d2_5.targetType = "Self"; d2_5.isEnchantment = true; d2_5.enchantTurns = 4; d2_5.enchantAttackBonus = 15; d2_5.prerequisites = {"DARK_INFUSED_BLADE_1"}; element.spells[d2_5.id] = d2_5;

        MagicSpell d3_1, d3_2, d3_3, d3_4, d3_5;
        d3_1.id = "DARK_OBLITERATION_RAY_3"; d3_1.name = "Obliteration Ray"; d3_1.description = "Sinar energi gelap yang melenyapkan sebagian pertahanan target dan memberikan damage masif.";
        d3_1.elementType = "Dark"; d3_1.tier = 3; d3_1.manaCost = 50; d3_1.basePower = 80;
        d3_1.targetType = "SingleEnemy"; d3_1.isEnchantment = false; d3_1.prerequisites = {"DARK_NIGHTMARE_BLAST_2"}; element.spells[d3_1.id] = d3_1;

        d3_2.id = "DARK_FIELD_OF_DESPAIR_3"; d3_2.name = "Field of Despair"; d3_2.description = "Menciptakan aura gelap pada target yang menguras HP & MP perlahan dan menurunkan semua statnya.";
        d3_2.elementType = "Dark"; d3_2.tier = 3; d3_2.manaCost = 65; d3_2.basePower = 20;
        d3_2.targetType = "SingleEnemy"; d3_2.isEnchantment = false; d3_2.prerequisites = {"DARK_LIFE_TAP_2", "DARK_CURSE_OF_VULNERABILITY_2"}; element.spells[d3_2.id] = d3_2;

        d3_3.id = "DARK_FORM_OF_THE_VOID_3"; d3_3.name = "Form of the Void"; d3_3.description = "Pengguna berubah menjadi makhluk bayangan, kebal damage fisik & sihir gelap diserap untuk memulihkan MP.";
        d3_3.elementType = "Dark"; d3_3.tier = 3; d3_3.manaCost = 58; d3_3.basePower = 0;
        d3_3.targetType = "Self"; d3_3.isEnchantment = true; d3_3.enchantTurns = 3; d3_3.prerequisites = {"DARK_SHADOW_WALK_2"}; element.spells[d3_3.id] = d3_3;

        d3_4.id = "DARK_ETERNAL_NIGHT_CURSE_3"; d3_4.name = "Eternal Night Curse"; d3_4.description = "Menyelimuti target dalam kegelapan abadi, DoT kuat, kebutaan (Acc Debuff), dan kelemahan ekstrem (All Stat Debuff).";
        d3_4.elementType = "Dark"; d3_4.tier = 3; d3_4.manaCost = 52; d3_4.basePower = 40;
        d3_4.targetType = "SingleEnemy"; d3_4.isEnchantment = false; d3_4.prerequisites = {"DARK_CURSE_OF_VULNERABILITY_2"}; element.spells[d3_4.id] = d3_4;

        d3_5.id = "DARK_SOUL_ANNIHILATION_3"; d3_5.name = "Soul Annihilation"; d3_5.description = "Energi kegelapan pekat menghancurkan jiwa target, damage bayangan masif dan menguras sebagian besar mana musuh.";
        d3_5.elementType = "Dark"; d3_5.tier = 3; d3_5.manaCost = 95; d3_5.basePower = 120;
        d3_5.targetType = "SingleEnemy"; d3_5.isEnchantment = false; d3_5.prerequisites = {"DARK_OBLITERATION_RAY_3", "DARK_SOUL_EATER_WEAPON_2"}; element.spells[d3_5.id] = d3_5;
    }
    
    else if (element.name == "Light") {
        element.description = "An element that radiates holy light, offering healing and protection to the worthy.";
        MagicSpell l1_1, l1_2, l1_3, l1_4, l1_5;
        l1_1.id = "LIGHT_MINOR_HEAL_1"; l1_1.name = "Minor Heal"; l1_1.description = "Memulihkan sedikit HP diri sendiri.";
        l1_1.elementType = "Light"; l1_1.tier = 1; l1_1.manaCost = 10; l1_1.basePower = 30;
        l1_1.targetType = "Self"; l1_1.isEnchantment = false; element.spells[l1_1.id] = l1_1;

        l1_2.id = "LIGHT_SACRED_FLAME_1"; l1_2.name = "Sacred Flame"; l1_2.description = "Serangan api suci kecil ke satu target, efektif melawan Undead/Dark.";
        l1_2.elementType = "Light"; l1_2.tier = 1; l1_2.manaCost = 12; l1_2.basePower = 18;
        l1_2.targetType = "SingleEnemy"; l1_2.isEnchantment = false; element.spells[l1_2.id] = l1_2;

        l1_3.id = "LIGHT_BLESS_1"; l1_3.name = "Bless"; l1_3.description = "Memberkati diri sendiri, sedikit meningkatkan semua stat dasar sementara.";
        l1_3.elementType = "Light"; l1_3.tier = 1; l1_3.manaCost = 15; l1_3.basePower = 0;
        l1_3.targetType = "Self"; l1_3.isEnchantment = true; l1_3.enchantTurns = 3; element.spells[l1_3.id] = l1_3;

        l1_4.id = "LIGHT_PURIFICATION_1"; l1_4.name = "Purification"; l1_4.description = "Menghilangkan efek status negatif minor dari diri sendiri.";
        l1_4.elementType = "Light"; l1_4.tier = 1; l1_4.manaCost = 8; l1_4.basePower = 0;
        l1_4.targetType = "Self"; l1_4.isEnchantment = false; element.spells[l1_4.id] = l1_4;

        l1_5.id = "LIGHT_RADIANT_WEAPON_1"; l1_5.name = "Radiant Weapon"; l1_5.description = "Menyelimuti senjata dengan cahaya suci, menambah sedikit light damage.";
        l1_5.elementType = "Light"; l1_5.tier = 1; l1_5.manaCost = 16; l1_5.basePower = 0;
        l1_5.targetType = "Self"; l1_5.isEnchantment = true; l1_5.enchantTurns = 3; l1_5.enchantAttackBonus = 7; element.spells[l1_5.id] = l1_5;

        MagicSpell l2_1, l2_2, l2_3, l2_4, l2_5;
        l2_1.id = "LIGHT_HEALING_LIGHT_2"; l2_1.name = "Healing Light"; l2_1.description = "Memulihkan HP diri sendiri secara signifikan.";
        l2_1.elementType = "Light"; l2_1.tier = 2; l2_1.manaCost = 18; l2_1.basePower = 60;
        l2_1.targetType = "Self"; l2_1.isEnchantment = false; l2_1.prerequisites = {"LIGHT_MINOR_HEAL_1"}; element.spells[l2_1.id] = l2_1;

        l2_2.id = "LIGHT_SMITE_2"; l2_2.name = "Smite"; l2_2.description = "Serangan cahaya kuat ke satu target, sangat efektif melawan makhluk gelap dan undead.";
        l2_2.elementType = "Light"; l2_2.tier = 2; l2_2.manaCost = 22; l2_2.basePower = 40;
        l2_2.targetType = "SingleEnemy"; l2_2.isEnchantment = false; l2_2.prerequisites = {"LIGHT_SACRED_FLAME_1"}; element.spells[l2_2.id] = l2_2;

        l2_3.id = "LIGHT_BARRIER_OF_FAITH_2"; l2_3.name = "Barrier of Faith"; l2_3.description = "Menciptakan perisai cahaya yang meningkatkan pertahanan diri sendiri secara signifikan.";
        l2_3.elementType = "Light"; l2_3.tier = 2; l2_3.manaCost = 25; l2_3.basePower = 0;
        l2_3.targetType = "Self"; l2_3.isEnchantment = true; l2_3.enchantTurns = 4; l2_3.prerequisites = {"LIGHT_BLESS_1"}; element.spells[l2_3.id] = l2_3;

        l2_4.id = "LIGHT_CONSECRATED_STRIKE_2"; l2_4.name = "Consecrated Strike"; l2_4.description = "Serangan cahaya suci yang merusak musuh dan memulihkan sedikit HP diri sendiri.";
        l2_4.elementType = "Light"; l2_4.tier = 2; l2_4.manaCost = 30; l2_4.basePower = 35;
        l2_4.targetType = "SingleEnemy"; l2_4.isEnchantment = false; l2_4.prerequisites = {"LIGHT_PURIFICATION_1"}; element.spells[l2_4.id] = l2_4;

        l2_5.id = "LIGHT_DIVINE_EDGE_2"; l2_5.name = "Divine Edge"; l2_5.description = "Memberkati senjata dengan kekuatan ilahi, menambah light damage besar dan sedikit meningkatkan pertahanan diri.";
        l2_5.elementType = "Light"; l2_5.tier = 2; l2_5.manaCost = 26; l2_5.basePower = 0;
        l2_5.targetType = "Self"; l2_5.isEnchantment = true; l2_5.enchantTurns = 4; l2_5.enchantAttackBonus = 22; l2_5.prerequisites = {"LIGHT_RADIANT_WEAPON_1"}; element.spells[l2_5.id] = l2_5;

        MagicSpell l3_1, l3_2, l3_3, l3_4, l3_5;
        l3_1.id = "LIGHT_DIVINE_RENEWAL_3"; l3_1.name = "Divine Renewal"; l3_1.description = "Memulihkan HP diri sendiri secara masif dan menghilangkan semua efek status negatif dari diri sendiri.";
        l3_1.elementType = "Light"; l3_1.tier = 3; l3_1.manaCost = 50; l3_1.basePower = 100;
        l3_1.targetType = "Self"; l3_1.isEnchantment = false; l3_1.prerequisites = {"LIGHT_HEALING_LIGHT_2", "LIGHT_CONSECRATED_STRIKE_2"}; element.spells[l3_1.id] = l3_1;

        l3_2.id = "LIGHT_JUDGEMENT_DAY_3"; l3_2.name = "Judgement Day"; l3_2.description = "Memanggil pilar cahaya surgawi yang menghantam satu musuh, damage sangat besar terutama pada makhluk jahat.";
        l3_2.elementType = "Light"; l3_2.tier = 3; l3_2.manaCost = 70; l3_2.basePower = 120;
        l3_2.targetType = "SingleEnemy"; l3_2.isEnchantment = false; l3_2.prerequisites = {"LIGHT_SMITE_2"}; element.spells[l3_2.id] = l3_2;

        l3_3.id = "LIGHT_GUARDIAN_ANGEL_3"; l3_3.name = "Guardian Angel"; l3_3.description = "Memberikan diri sendiri perisai suci yang menyerap sejumlah besar damage dan kebal terhadap status negatif sementara.";
        l3_3.elementType = "Light"; l3_3.tier = 3; l3_3.manaCost = 55; l3_3.basePower = 0;
        l3_3.targetType = "Self"; l3_3.isEnchantment = true; l3_3.enchantTurns = 3; l3_3.prerequisites = {"LIGHT_BARRIER_OF_FAITH_2"}; element.spells[l3_3.id] = l3_3;

        l3_4.id = "LIGHT_SANCTUARY_3"; l3_4.name = "Sanctuary"; l3_4.description = "Menciptakan area suci di sekitar diri sendiri yang memberikan regenerasi HP kuat setiap giliran.";
        l3_4.elementType = "Light"; l3_4.tier = 3; l3_4.manaCost = 60; l3_4.basePower = 0;
        l3_4.targetType = "Self"; l3_4.isEnchantment = true; l3_4.enchantTurns = 5; l3_4.prerequisites = {"LIGHT_HEALING_LIGHT_2", "LIGHT_PURIFICATION_1"}; element.spells[l3_4.id] = l3_4;

        l3_5.id = "LIGHT_CELESTIAL_AEGIS_3"; l3_5.name = "Celestial Aegis"; l3_5.description = "Diri sendiri diselimuti perisai cahaya ilahi yang menyerap sejumlah besar damage dan memulihkan HP secara berkala.";
        l3_5.elementType = "Light"; l3_5.tier = 3; l3_5.manaCost = 100; l3_5.basePower = 0;
        l3_5.targetType = "Self"; l3_5.isEnchantment = true; l3_5.enchantTurns = 4; l3_5.prerequisites = {"LIGHT_JUDGEMENT_DAY_3", "LIGHT_DIVINE_EDGE_2"}; element.spells[l3_5.id] = l3_5;
    }
}


void initializeMagicSystem() {
    allMagicElements.clear(); 

    vector<string> elementNames = {"Fire", "Thunder", "Ice", "Wind", "Dark", "Light"};
    for (const string& name : elementNames) {
        MagicElement element;
        element.name = name;
        initializeSpellsForElement(element); 
        allMagicElements[name] = element;
    }
    wcout << L"Sistem magic telah diinisialisasi dengan " << allMagicElements.size() << L" elemen." << endl;
}


void initializeCompanions() {
    companions.clear(); // Pastikan list companions kosong sebelum diisi ulang

    Companion masha;
    masha.name = "Masha";
    masha.initialLoyalty = 10;
    masha.personality = "Putri Bangsawan Dingin";
    masha.description = "Seorang putri dari keluarga bangsawan Aurora yang dikenal sangat menjaga sikap dan perkataannya. Sering terlihat di Taman Norelia, Puncak Arcadia.";
    masha.coreAbilitiesOrTraits = {"Observatif Tajam", "Pemikir Kritis", "Pengetahuan Filsafat"};
    masha.met = true;

    masha.detailedInfoPerLevel[1] = L"Pertemuan pertama terasa sangat formal dan dingin. Dia tampak tidak tertarik berbasa-basi dan lebih suka menyendiri.";
    masha.traitsRevealedPerLevel[1] = {L"Menjaga Jarak", L"Formal"};
    masha.detailedInfoPerLevel[2] = L"Meskipun masih dingin, dia menunjukkan sedikit ketertarikan pada topik intelektual (filsafat Xantus). Mungkin ada sisi lain di balik sikapnya.";
    masha.traitsRevealedPerLevel[2] = {L"Tertarik Filsafat (Tersembunyi)"};
    masha.detailedInfoPerLevel[3] = L"Mulai mau terlibat dalam diskusi filosofis yang lebih dalam. Mengungkapkan bahwa ia menghargai pemikiran yang mendalam ketimbang gosip bangsawan.";
    masha.traitsRevealedPerLevel[3] = {L"Intelektual", L"Menghargai Diskusi Serius"};
    masha.detailedInfoPerLevel[4] = L"Terungkap memiliki minat dan pengetahuan tersembunyi dalam herbologi, terutama pada tanaman langka seperti Edelweiss. Tampak sedikit defensif saat hobinya diketahui.";
    masha.traitsRevealedPerLevel[4] = {L"Ahli Herbologi (Amatir)", L"Menyukai Tanaman Langka"};
    masha.detailedInfoPerLevel[5] = L"Menunjukkan sisi rapuhnya terkait tekanan perjodohan dari keluarganya. Mulai sedikit terbuka tentang perasaannya sebagai 'aset' keluarga.";
    masha.traitsRevealedPerLevel[5] = {L"Merasa Tertekan Ekspektasi", L"Menentang Perjodohan (Dalam Hati)"};
    masha.detailedInfoPerLevel[6] = L"Terlihat antusias membahas proyek Anggrek Bulan Salju dengan pelayannya, menunjukkan gairah tersembunyi. Kembali dingin saat Weiss muncul, namun sisi lainnya telah terlihat.";
    masha.traitsRevealedPerLevel[6] = {L"Ambisius (Proyek Botani)", L"Bersemangat (Tersembunyi)"};
    masha.detailedInfoPerLevel[7] = L"Terlibat dalam perdebatan filosofis yang lebih mendalam, menunjukkan kecerdasan dan kemampuannya berargumen. Mulai menghargai Weiss sebagai lawan diskusi yang sepadan.";
    masha.traitsRevealedPerLevel[7] = {L"Debater Ulung", L"Rasional"};
    masha.detailedInfoPerLevel[8] = L"Secara terbuka mengungkapkan frustrasinya terhadap perjodohan. Saat kamu menawarkan dukungan tulus, ada kehangatan yang langka dalam tatapannya, seolah menemukan seseorang yang akhirnya mengerti bebannya.";
    masha.traitsRevealedPerLevel[8] = {L"Berani Mengungkapkan Keresahan", L"Menghargai Dukungan Weiss", L"Mulai Membuka Hati"};
    masha.detailedInfoPerLevel[9] = L"Saat kalian berdua menyelamatkan mawar 'Aurora Dawn' kesayangannya, ia menunjukkan sisi yang sangat berbeda: peduli, lembut, dan bahkan sedikit ceria. Tawaran teh herbal buatannya terasa lebih dari sekadar ucapan terima kasih; ada harapan dan kelembutan dalam caranya memandangmu yang membuat hatimu sedikit berdebar.";
    masha.traitsRevealedPerLevel[9] = {L"Sangat Peduli (pada hal berharga)", L"Menunjukkan Kehangatan Sejati", L"Gestur Penuh Perhatian (pada Weiss)", L"Tatapan Berbeda"};
    masha.detailedInfoPerLevel[10] = L"Keberhasilannya menunda perjodohan adalah kemenangan besar, dan ia mengakuinya sebagai buah dari keberanian yang kamu inspirasikan. Saat memberikan bros Edelweiss, ada rona merah di pipinya dan getaran dalam suaranya yang menyiratkan perasaan lebih dalam dari sekadar persahabatan. Aliansi keluarga Aurora kini terasa seperti ikatan personal antara kamu dan dia, seorang 'Putri Es' yang hatinya mungkin telah mencair untukmu.";
    masha.traitsRevealedPerLevel[10] = {L"Mandiri & Percaya Diri", L"Sahabat yang Sangat Setia", L"Menyimpan Perasaan Khusus (pada Weiss)", L"Berani Berharap"};
    companions.push_back(masha);


    Companion kinich;
    kinich.name = "Kinich";
    kinich.initialLoyalty = 15;
    kinich.personality = "Penjaga Tambang Keras dan Berpengalaman";
    kinich.description = "Seorang pria tangguh yang menjaga keamanan di sekitar Goa Avernix. Tidak banyak bicara dan sangat waspada terhadap orang asing, terutama bangsawan.";
    kinich.coreAbilitiesOrTraits = {"Pengetahuan Tambang Luas", "Insting Tajam", "Keahlian Bertahan Hidup"};
    kinich.met = true;

    kinich.detailedInfoPerLevel[1] = L"Sangat skeptis dan formal. Menganggap kunjungan bangsawan hanya sebagai 'tur wisata'. Menjelaskan bahaya goa dengan singkat.";
    kinich.traitsRevealedPerLevel[1] = {L"Waspada", L"Profesional Kaku"};
    kinich.detailedInfoPerLevel[2] = L"Sedikit terkejut saat Weiss menanyakan kesejahteraan penambang. Masih sinis terhadap janji bangsawan, tapi mulai melihat keseriusan Weiss.";
    kinich.traitsRevealedPerLevel[2] = {L"Peduli Nasib Penambang (Tersembunyi)", L"Sinis terhadap Otoritas"};
    kinich.detailedInfoPerLevel[3] = L"Mulai berbagi cerita tentang bahaya goa yang lebih mistis ('Guncangan Besar', 'Roh Penunggu Goa') dan tradisi penambang. Menunjukkan sisi spiritualnya.";
    kinich.traitsRevealedPerLevel[3] = {L"Percaya Takhayul Tambang", L"Menghormati Alam Goa"};
    kinich.detailedInfoPerLevel[4] = L"Mau berbagi pengetahuan spesifik tentang lokasi di goa ('Gua Kunang-Kunang') dan jenis kristal. Bahkan sedikit bercanda, menunjukkan sisi yang lebih hangat.";
    kinich.traitsRevealedPerLevel[4] = {L"Ahli Peta Goa", L"Memiliki Sisi Humoris (Langka)"};
    kinich.detailedInfoPerLevel[5] = L"Sangat terkesan dengan tindakan nyata Weiss yang membantu menyediakan makanan dan berjanji mengatasi masalah lampu karbit. Memberikan hadiah kecil sebagai tanda terima kasih.";
    kinich.traitsRevealedPerLevel[5] = {L"Menghargai Tindakan Nyata", L"Mulai Percaya pada Weiss"};
    kinich.detailedInfoPerLevel[6] = L"Berbagi cerita tentang persaudaraan penambang dan keyakinannya pada 'Roh Goa'. Mengungkapkan kekhawatiran jika goa tidak dijaga dengan benar.";
    kinich.traitsRevealedPerLevel[6] = {L"Menjunjung Persaudaraan", L"Spiritual (Goa)"};
    kinich.detailedInfoPerLevel[7] = L"Menunjukkan rasa terima kasih yang besar atas bantuan peralatan baru. Memanggil Weiss dengan nama tanpa gelar di depan umum sebagai tanda hormat.";
    kinich.traitsRevealedPerLevel[7] = {L"Sangat Menghargai Bantuan", L"Loyal pada Penambang"};
    kinich.detailedInfoPerLevel[8] = L"Membagikan kisah tragis tentang kehilangan sahabatnya, Kael, di tambang. Mengungkapkan sumpahnya untuk selalu melindungi anak buahnya.";
    kinich.traitsRevealedPerLevel[8] = {L"Penuh Dedikasi (Keselamatan)", L"Memiliki Luka Batin"};
    kinich.detailedInfoPerLevel[9] = L"Bekerja sama dengan Weiss dalam situasi krisis kebocoran gas, menunjukkan kepercayaan penuh dan mengakui Weiss sebagai pemimpin sejati.";
    kinich.traitsRevealedPerLevel[9] = {L"Tenang dalam Krisis", L"Mempercayai Weiss Sepenuhnya"};
    kinich.detailedInfoPerLevel[10] = L"Menunjukkan 'Jantung Goa' kepada Weiss dan memberikan 'Air Mata Avernix' sebagai simbol persahabatan abadi dan kesetiaan. Menganggap Weiss sebagai saudara.";
    kinich.traitsRevealedPerLevel[10] = {L"Sahabat Sejati", L"Penjaga Rahasia Goa", L"Sangat Loyal"};
    companions.push_back(kinich);


    Companion irene;
    irene.name = "Irene";
    irene.initialLoyalty = 25;
    irene.personality = "Maid Setia dan Lembut";
    irene.description = "Pelayan baru di Mansion Astra yang rajin dan perhatian. Awalnya pemalu dan gugup, namun memiliki hati yang baik.";
    irene.coreAbilitiesOrTraits = {"Merawat Taman dengan Baik", "Perhatian pada Detail"};
    irene.met = true; 

    irene.detailedInfoPerLevel[1] = L"Sangat gugup dan canggung saat pertama kali diajak bicara. Menunjukkan kesukaannya pada taman sebagai tempat yang menenangkan.";
    irene.traitsRevealedPerLevel[1] = {L"Pemalu", L"Menyukai Ketenangan Taman"};
    irene.detailedInfoPerLevel[2] = L"Sedikit lebih santai. Mengungkapkan rasa syukurnya bisa bekerja di mansion dan dibimbing oleh senior.";
    irene.traitsRevealedPerLevel[2] = {L"Bersyukur", L"Rajin Belajar"};
    irene.detailedInfoPerLevel[3] = L"Mulai terbuka tentang hobinya membaca buku fantasi dan sedikit menyulam. Antusias saat Weiss menawarkan bertukar rekomendasi buku.";
    irene.traitsRevealedPerLevel[3] = {L"Suka Membaca Fantasi", L"Bisa Menyulam (Dasar)"};
    irene.detailedInfoPerLevel[4] = L"Berbagi momen ringan mengamati kupu-kupu langka bersama Weiss. Tidak lagi kaku dan bisa tertawa lepas.";
    irene.traitsRevealedPerLevel[4] = {L"Menghargai Keindahan Alam", L"Mulai Akrab"};
    irene.detailedInfoPerLevel[5] = L"Menunjukkan perhatian tulus saat melihat Weiss pucat. Berinisiatif menawarkan teh herbal buatannya.";
    irene.traitsRevealedPerLevel[5] = {L"Sangat Perhatian", L"Berinisiatif Membantu"};
    irene.detailedInfoPerLevel[6] = L"Berbagi perasaannya tentang rindu kampung halaman, namun juga menganggap Mansion Astra sebagai rumah kedua.";
    irene.traitsRevealedPerLevel[6] = {L"Penyayang Keluarga", L"Mulai Merasa Betah"};
    irene.detailedInfoPerLevel[7] = L"Sangat antusias berdiskusi tentang buku yang direkomendasikan Weiss, menunjukkan kesamaan selera dan kenyamanan dalam berpendapat.";
    irene.traitsRevealedPerLevel[7] = {L"Kritis terhadap Cerita", L"Teman Diskusi yang Baik"};
    irene.detailedInfoPerLevel[8] = L"Dengan tulus mengungkapkan rasa syukurnya atas perubahan positif dalam diri Weiss dan bagaimana itu dirasakan oleh semua staf.";
    irene.traitsRevealedPerLevel[8] = {L"Jujur", L"Mengapresiasi Kebaikan"};
    irene.detailedInfoPerLevel[9] = L"Menawarkan dukungan emosional saat Weiss merasa terbebani. Menegaskan kesetiaannya sebagai teman.";
    irene.traitsRevealedPerLevel[9] = {L"Pendengar yang Baik", L"Sangat Setia"};
    irene.detailedInfoPerLevel[10] = L"Memberikan jam saku pusaka keluarganya sebagai simbol persahabatan dan kesetiaan abadi. Menganggap Weiss sebagai keluarga.";
    irene.traitsRevealedPerLevel[10] = {L"Sangat Loyal dan Berbakti", L"Menganggap Weiss Keluarga"};
    companions.push_back(irene);


    Companion ruigerd;
    ruigerd.name = "Ruigerd";
    ruigerd.initialLoyalty = 30;
    ruigerd.personality = "Chef Bijaksana Keluarga Astra";
    ruigerd.description = "Kepala Koki Mansion Astra yang telah lama mengabdi. Dikenal karena keahlian memasaknya yang luar biasa dan kearifannya.";
    ruigerd.coreAbilitiesOrTraits = {"Ahli Memasak Hidangan Kerajaan", "Pengetahuan Bahan Makanan Luas"};
    ruigerd.met = true;

    ruigerd.detailedInfoPerLevel[1] = L"Profesional dan sedikit terkejut dengan kunjungan Weiss ke dapur. Menjelaskan menu makan malam dengan formal.";
    ruigerd.traitsRevealedPerLevel[1] = {L"Profesional", L"Menjaga Standar Tinggi"};
    ruigerd.detailedInfoPerLevel[2] = L"Mulai terbuka menjelaskan teknik memasak (penggunaan kayu bakar). Menunjukkan kesabaran sebagai kunci memasak.";
    ruigerd.traitsRevealedPerLevel[2] = {L"Detail dalam Memasak", L"Sabar"};
    ruigerd.detailedInfoPerLevel[3] = L"Bangga saat masakannya (sup jamur Morel) dipuji. Menjelaskan pentingnya bahan musiman.";
    ruigerd.traitsRevealedPerLevel[3] = {L"Mencintai Bahan Musiman", L"Antusias pada Keahliannya"};
    ruigerd.detailedInfoPerLevel[4] = L"Menunjukkan sisi mentor saat mengajari juru masak muda. Berbagi filosofi tentang kesabaran dalam belajar dan memasak (saus hollandaise).";
    ruigerd.traitsRevealedPerLevel[4] = {L"Bijaksana", L"Mentor yang Baik"};
    ruigerd.detailedInfoPerLevel[5] = L"Senang atas apresiasi Weiss terhadap pesta teh. Menawarkan kue cokelat spesial buatannya, menunjukkan kebanggaan seorang seniman kuliner.";
    ruigerd.traitsRevealedPerLevel[5] = {L"Kreatif dalam Resep", L"Bangga akan Karyanya"};
    ruigerd.detailedInfoPerLevel[6] = L"Berbagi kenangan sentimental tentang kakek dan ayah Weiss, serta hidangan favorit mereka. Menunjukkan kesetiaan lamanya pada keluarga Astra.";
    ruigerd.traitsRevealedPerLevel[6] = {L"Sangat Loyal pada Keluarga Astra", L"Penjaga Kenangan"};
    ruigerd.detailedInfoPerLevel[7] = L"Memberikan nasihat bijak tentang tanggung jawab dan menghadapi tekanan, menggunakan analogi dari dunia dapur. Menawarkan dukungan moral.";
    ruigerd.traitsRevealedPerLevel[7] = {L"Pemberi Nasihat Ulung", L"Berpengalaman Luas"};
    ruigerd.detailedInfoPerLevel[8] = L"Mengakui dan memuji perubahan positif serta kedewasaan Weiss. Menyatakan dukungannya dan melihat potensi besar dalam diri Weiss.";
    ruigerd.traitsRevealedPerLevel[8] = {L"Observatif terhadap Perubahan", L"Mendukung Penuh Weiss"};
    ruigerd.detailedInfoPerLevel[9] = L"Menunjukkan perhatian kebapakan saat Weiss merasa terbebani. Menawarkan cokelat hangat dan dukungan emosional yang mendalam.";
    ruigerd.traitsRevealedPerLevel[9] = {L"Perhatian seperti Ayah", L"Pendengar yang Empatik"};
    ruigerd.detailedInfoPerLevel[10] = L"Menciptakan hidangan 'Simfoni Astra' dan mewariskan buku resep pribadinya sebagai simbol kepercayaan tertinggi dan kesetiaan abadi.";
    ruigerd.traitsRevealedPerLevel[10] = {L"Sangat Setia dan Berdedikasi", L"Menganggap Weiss Keluarga"};
    companions.push_back(ruigerd);


    Companion ella;
    ella.name = "Ella";
    ella.initialLoyalty = 5;
    ella.personality = "Pemilik Cross Guild yang Tegas dan Pragmatis";
    ella.description = "Wanita tangguh yang mengelola Cross Guild di Kota Arcadia dengan tangan besi. Tidak suka basa-basi dan sangat berorientasi pada hasil.";
    ella.coreAbilitiesOrTraits = {"Manajemen Guild yang Efisien", "Jaringan Informasi Luas di Dunia Bawah"};
    ella.met = true;

    ella.detailedInfoPerLevel[1] = L"Sangat profesional dan sedikit sinis terhadap kunjungan bangsawan. Menjelaskan fungsi guild secara to-the-point.";
    ella.traitsRevealedPerLevel[1] = {L"Tegas", L"Praktis", L"Skeptis terhadap Bangsawan"};
    ella.detailedInfoPerLevel[2] = L"Menjelaskan cara kerja guild dalam menangani kasus 'kecil' yang tidak terjangkamu aparat. Menunjukkan pemahamannya tentang 'aturan main' di dunia bawah.";
    ella.traitsRevealedPerLevel[2] = {L"Memahami Realitas Lapangan", L"Transparan (dengan caranya)"};
    ella.detailedInfoPerLevel[3] = L"Mengungkapkan bahwa guild adalah 'keluarga besar yang kacau balau' baginya, menunjukkan sisi sentimentil di balik sikap kerasnya.";
    ella.traitsRevealedPerLevel[3] = {L"Dedikasi pada Guild", L"Melindungi Anggotanya"};
    ella.detailedInfoPerLevel[4] = L"Menyelesaikan sengketa antar petualang dengan cepat dan tegas. Menunjukkan sisi humor sarkastisnya saat berbincang dengan Weiss.";
    ella.traitsRevealedPerLevel[4] = {L"Pemimpin yang Tegas", L"Humoris (Sarkastis)"};
    ella.detailedInfoPerLevel[5] = L"Terkesan dengan masukan praktis Weiss tentang formulir quest. Mulai melihat Weiss sebagai individu yang cerdas, bukan hanya bangsawan.";
    ella.traitsRevealedPerLevel[5] = {L"Menghargai Ide Bagus", L"Mulai Terbuka"};
    ella.detailedInfoPerLevel[6] = L"Berbagi kisah tentang quest sulit di masa lalu (wabah di Pegunungan Naga Merah), menunjukkan esensi guild yang sebenarnya: membantu orang.";
    ella.traitsRevealedPerLevel[6] = {L"Menjunjung Tinggi Misi Guild", L"Berpengalaman dalam Krisis"};
    ella.detailedInfoPerLevel[7] = L"Memberikan nasihat praktis dan informasi sensitif tentang penyelundupan di dermaga, menunjukkan kepercayaannya pada Weiss.";
    ella.traitsRevealedPerLevel[7] = {L"Memiliki Jaringan Intelijen", L"Berani Mengambil Risiko (Terukur)"};
    ella.detailedInfoPerLevel[8] = L"Mengakui bahwa Weiss berbeda dari bangsawan kebanyakan karena kepedulian dan tindakannya. Menunjukkan rasa hormat yang tulus.";
    ella.traitsRevealedPerLevel[8] = {L"Menilai Orang dari Tindakan", L"Mulai Menghormati Weiss"};
    ella.detailedInfoPerLevel[9] = L"Menyatakan kesamaan tujuan dengan Weiss dalam memberantas premanisme di pasar malam. Menawarkan kerjasama dan menunjukkan sisi protektifnya.";
    ella.traitsRevealedPerLevel[9] = {L"Berjiwa Keadilan", L"Siap Bekerja Sama"};
    ella.detailedInfoPerLevel[10] = L"Menganugerahkan Lencana Kehormatan Guild Tertinggi kepada Weiss sebagai simbol kepercayaan penuh dan aliansi. Mengungkap motivasi pribadinya menjalankan guild.";
    ella.traitsRevealedPerLevel[10] = {L"Sangat Mempercayai Weiss", L"Visioner", L"Mitra Setia"};
    companions.push_back(ella);


    Companion charlotte;
    charlotte.name = "Charlotte";
    charlotte.initialLoyalty = 5;
    charlotte.personality = "Wartawan Gigih Arcadia Chronicle";
    charlotte.description = "Jurnalis muda yang idealis dan bersemangat dari Harian Arcadia Chronicle. Selalu mencari kebenaran dan tidak mudah menyerah.";
    charlotte.coreAbilitiesOrTraits = {"Keahlian Investigasi Mendalam", "Menulis Artikel yang Tajam"};
    charlotte.met = true;

    charlotte.detailedInfoPerLevel[1] = L"Energik dan langsung ke pokok permasalahan. Mengajukan pertanyaan tajam tentang motivasi Weiss terlibat dalam urusan kota.";
    charlotte.traitsRevealedPerLevel[1] = {L"Gigih", L"Profesional", L"Analitis"};
    charlotte.detailedInfoPerLevel[2] = L"Mengungkapkan tantangan pekerjaannya dalam memilah fakta dari desas-desus (kasus dermaga). Menunjukkan idealismenya tentang hak publik untuk tahu.";
    charlotte.traitsRevealedPerLevel[2] = {L"Idealis", L"Memiliki Jaringan Luas (Potensial)"};
    charlotte.detailedInfoPerLevel[3] = L"Sedang menginvestigasi keluhan pedagang pasar. Terkejut namun menghargai 'tip' dari Weiss, mulai melihat potensi kerjasama.";
    charlotte.traitsRevealedPerLevel[3] = {L"Peduli pada Rakyat Kecil", L"Mulai Percaya (Sedikit)"};
    charlotte.detailedInfoPerLevel[4] = L"Terlihat frustrasi menghadapi jalan buntu dalam investigasinya. Menunjukkan semangat juangnya yang tak mau menyerah demi kebenaran.";
    charlotte.traitsRevealedPerLevel[4] = {L"Pantang Menyerah", L"Berdedikasi Tinggi"};
    charlotte.detailedInfoPerLevel[5] = L"Mulai bertukar informasi secara lebih terbuka dengan Weiss terkait penyelidikan di dermaga dan catatan properti lama. Kemitraan mulai terbentuk.";
    charlotte.traitsRevealedPerLevel[5] = {L"Kolaboratif", L"Menghargai Informasi Akurat"};
    charlotte.detailedInfoPerLevel[6] = L"Bekerja hingga larut malam menyusun artikel investigasi. Berbagi kekhawatiran tentang risiko dan serangan balik dari pihak yang merugi.";
    charlotte.traitsRevealedPerLevel[6] = {L"Berani Mengambil Risiko (Jurnalistik)", L"Teliti"};
    charlotte.detailedInfoPerLevel[7] = L"Menghadapi dilema etis terkait penggunaan bukti sensitif dan keselamatan sumber. Memutuskan untuk mengambil risiko bersama Weiss.";
    charlotte.traitsRevealedPerLevel[7] = {L"Memegang Teguh Etika", L"Berani Bertindak"};
    charlotte.detailedInfoPerLevel[8] = L"Mengakui bahwa Weiss berbeda dari bangsawan kebanyakan karena kepedulian dan tindakannya. Menunjukkan rasa terima kasih atas dukungan dan keberanian Weiss.";
    charlotte.traitsRevealedPerLevel[8] = {L"Menghargai Integritas Weiss", L"Rekan yang Solid"};
    charlotte.detailedInfoPerLevel[9] = L"Melakukan pengintaian berbahaya bersama Weiss untuk mendapatkan bukti final. Menunjukkan keberanian fisik dan ikatan kuat sebagai tim.";
    charlotte.traitsRevealedPerLevel[9] = {L"Sangat Berani", L"Rekan Seperjuangan"};
    charlotte.detailedInfoPerLevel[10] = L"Berhasil menerbitkan berita skandal besar. Mengungkap motivasi pribadinya melanjutkan perjuangan ayahnya. Memberikan 'Pena Saksi Kebenaran' sebagai simbol persahabatan abadi.";
    charlotte.traitsRevealedPerLevel[10] = {L"Pembawa Perubahan", L"Sahabat Setia", L"Sangat Idealistis"};
    companions.push_back(charlotte);


    Companion mars;
    mars.name = "Mars";
    mars.initialLoyalty = 10;
    mars.personality = "Penjaga Pos Hutan yang Tangguh dan Bijaksana";
    mars.description = "Seorang pria bertubuh tegap yang menjaga Hutan Merah dengan penuh dedikasi. Awalnya pendiam dan waspada, namun memiliki kearifan alam.";
    mars.coreAbilitiesOrTraits = {"Pengetahuan Hutan Mendalam", "Keahlian Bertahan Hidup Unggul", "Insting Alam Tajam"};
    mars.met = true;

    mars.detailedInfoPerLevel[1] = L"Sangat formal dan waspada terhadap bangsawan. Menjelaskan tugasnya dengan singkat dan mengingatkan bahaya hutan.";
    mars.traitsRevealedPerLevel[1] = {L"Tegas", L"Profesional", L"Menghormati Hutan"};
    mars.detailedInfoPerLevel[2] = L"Sedikit melunak saat Weiss menunjukkan ketertarikan pada masalah perburuan liar. Mulai berbagi informasi tentang tantangan pekerjaannya.";
    mars.traitsRevealedPerLevel[2] = {L"Peduli Ekosistem", L"Praktis"};
    mars.detailedInfoPerLevel[3] = L"Mulai berbagi anekdot tentang hutan (babi hutan besar, pencari jamur tersesat). Menunjukkan sisi humor langka dan pengetahuannya tentang tanda-tanda alam.";
    mars.traitsRevealedPerLevel[3] = {L"Berpengalaman Luas (Hutan)", L"Observatif"};
    mars.detailedInfoPerLevel[4] = L"Menghargai hadiah apel dari Weiss. Berbagi pengetahuan tentang tanaman obat (Daun Jantung Ungu) dan legenda Bunga Bulan Perak.";
    mars.traitsRevealedPerLevel[4] = {L"Ahli Tanaman Obat (Dasar)", L"Menyimpan Cerita Hutan"};
    mars.detailedInfoPerLevel[5] = L"Terkesan dengan kesediaan Weiss membantu memperbaiki pagar. Mulai melihat Weiss berbeda dari rumor dan bangsawan lain. Memberikan air mata air hutan.";
    mars.traitsRevealedPerLevel[5] = {L"Menilai dari Tindakan", L"Mulai Terbuka"};
    mars.detailedInfoPerLevel[6] = L"Berbagi kekhawatiran tentang bencana alam di sekitar hutan saat terjebak hujan bersama Weiss. Menunjukkan harapan saat Weiss menawarkan bantuan.";
    mars.traitsRevealedPerLevel[6] = {L"Peduli Masyarakat Sekitar Hutan", L"Bertanggung Jawab"};
    mars.detailedInfoPerLevel[7] = L"Sangat berterima kasih atas bantuan Weiss dalam meloloskan proposal peralatan baru. Mengakui Weiss sebagai sahabat sejati hutan.";
    mars.traitsRevealedPerLevel[7] = {L"Sangat Menghargai Bantuan Nyata", L"Pemimpin yang Dihormati Penjaga Lain"};
    mars.detailedInfoPerLevel[8] = L"Berbagi kisah pribadi yang mendalam tentang pengalamannya berhadapan dengan Beruang Cakar Besi dan filosofinya tentang menghormati alam.";
    mars.traitsRevealedPerLevel[8] = {L"Memiliki Ikatan Spiritual dengan Alam", L"Pemberani (dengan Kearifan)"};
    mars.detailedInfoPerLevel[9] = L"Bekerja sama dengan Weiss dalam operasi penyelamatan tim patroli yang hilang. Mengakui bakat kepemimpinan dan ketenangan Weiss dalam krisis.";
    mars.traitsRevealedPerLevel[9] = {L"Rekan yang Andal dalam Krisis", L"Mempercayai Weiss"};
    mars.detailedInfoPerLevel[10] = L"Menunjukkan tempat favoritnya di Hutan Merah dan memberikan 'Taring Serigala Penjaga' sebagai simbol persahabatan abadi dan pengakuan Weiss sebagai 'Penjaga Hutan dalam hati'.";
    mars.traitsRevealedPerLevel[10] = {L"Sahabat dan Saudara Setia", L"Pelindung Warisan Alam"};
    companions.push_back(mars);


    
    socialLinks.clear();
    companionRelations.clear(); 
    for(const auto& comp : companions) {
        socialLinks[comp.name] = {comp.name, 1, false}; 
        socialLinkStories[comp.name].lockedLevels.clear(); 
        companionRelations[comp.name] = comp.initialLoyalty;
    }
   
    socialLinkStories["Masha"].lockedLevels = {1}; 
    socialLinkStories["Kinich"].lockedLevels = {1};
    socialLinkStories["Ella"].lockedLevels = {1};
    socialLinkStories["Charlotte"].lockedLevels = {1};
    socialLinkStories["Mars"].lockedLevels = {1};

}

// Fungsi baru untuk menginisialisasi data dungeons
void initializeDungeons() {
    allDungeons.clear(); // Pastikan map dungeons kosong sebelum diisi ulang
    enemyDatabase.clear(); // Pastikan enemyDatabase juga bersih
    defeatedBosses.clear(); // Pastikan defeatedBosses juga bersih

    // Inisialisasi Enemy Database (ini harus selalu diinisialisasi ulang untuk memastikan data musuh lengkap)
    enemyDatabase["Slime"] =                 {"Slime", 1, 30, 30, 10, 2, 10, 5, 2, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GiantRat"] =              {"Giant Rat", 1, 25, 25, 8, 1, 8, 4, 2, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["FeralGoblinGrunt"] =      {"Feral Goblin Grunt", 1, 35, 35, 12, 2, 12, 6, 2, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["StoneSprite"] =           {"Stone Sprite", 2, 30, 30, 12, 8, 12, 5, 4, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GiantCaveCricket"] =      {"Giant Cave Cricket", 2, 28, 28, 10, 5, 10, 4, 4, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["TempleRatSwarm"] =        {"Temple Rat Swarm", 3, 50, 50, 15, 3, 15, 7, 6, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["KoboldScavenger"] =       {"Kobold Scavenger", 3, 45, 45, 16, 4, 18, 8, 6, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GlowShroomCluster"] =     {"Glow Shroom Cluster", 4, 60, 60, 10, 10, 20, 8, 8, false, false, 0, 0, 0, 0, 0, "Plant", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["TempleGuardDog"] =        {"Temple Guard Dog", 4, 55, 55, 18, 6, 22, 11, 8, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DustMephit"] =            {"Dust Mephit", 5, 45, 45, 18, 5, 25, 10, 8, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LostPilgrimSpirit"] =     {"Lost Pilgrim Spirit", 5, 40, 40, 20, 3, 28, 12, 8, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["KoboldPathguard"] =       {"Kobold Pathguard", 6, 60, 60, 22, 8, 30, 15, 10, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CaveLurker"] =            {"Cave Lurker", 6, 55, 55, 24, 6, 32, 16, 10, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AnimatedSword"] =         {"Animated Sword", 7, 70, 70, 28, 12, 40, 20, 10, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["UmbralCrawler"] =         {"Umbral Crawler", 8, 65, 65, 30, 7, 42, 20, 10, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AncientSentryFragment"] = {"Ancient Sentry Fragment", 9, 80, 80, 32, 15, 50, 25, 10, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ShadowPup"] =             {"Shadow Pup" , 9, 60, 60, 35, 8, 48, 24, 14, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["GuardianOrb"] =           {"Guardian Orb", 11, 80, 80, 35, 12, 65, 30, 15, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GoblinRockthrower"] =     {"Goblin Rockthrower", 11, 75, 75, 33, 10, 68, 32, 15, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["TempleAcolyte"] =         {"Temple Acolyte", 12, 90, 90, 38, 14, 70, 35, 17, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["YoungCaveTroll"] =        {"Young Cave Troll", 12, 130, 130, 40, 10, 75, 38, 17, false, false, 0, 0, 0, 0, 0, "Giant", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LesserImp"] =             {"Lesser Imp", 13, 70, 70, 36, 9, 72, 36, 18, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DarkCultInitiate"] =      {"Dark Cult Initiate", 13, 85, 85, 37, 11, 80, 35,18, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["TempleKnightAspirant"] =  {"Temple Knight Aspirant", 14, 110, 110, 42, 18, 90, 40, 19, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["WildBoarStrong"] =        {"Wild Boar (Strong)", 14, 100, 100, 40, 12, 85, 39, 21, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["RuneGuardian"] =          {"Rune Guardian", 15, 120, 120, 40, 20, 100, 50, 16, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["BroodCavernSpider"] =     {"Brood Cavern Spider", 15, 110, 110, 43, 16, 110, 50, 21, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["CorruptedCherub"] =       {"Corrupted Cherub", 16, 90, 90, 40, 12, 120, 55, 24, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["KoboldDigger"] =          {"Kobold Digger", 17, 100, 100, 42, 16, 130, 60, 23, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ObsidianRazorfiend"] =    {"Obsidian Razorfiend", 18, 90, 90, 42, 12, 150, 70, 24, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["PhantomWarrior"] =        {"Phantom Warrior", 19, 140, 140, 45, 15, 160, 75, 23, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AltarGuardian"] =         {"Altar Guardian", 19, 150, 150, 48, 22, 170, 80, 26, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["CharredSalamander"] =     {"Charred Salamander", 21, 150, 150, 50, 20, 200, 90, 28, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ForestSpider"] =          {"Forest Spider", 21, 140, 140, 48, 18, 190, 85, 28, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["StoneLionCub"] =          {"Stone Lion Cub", 22, 160, 160, 55, 25, 220, 100, 30, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["RiverSerpent"] =          {"River Serpent", 23, 170, 170, 52, 20, 230, 105, 30, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SkeletonSoldierElite"] =  {"Skeleton Soldier Elite", 24, 180, 180, 58, 30, 250, 115, 30, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LesserGargoyle"] =        {"Lesser Gargoyle", 25, 180, 180, 55, 25, 280, 130, 32, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DeepDwellerBrute"] =      {"Deep Dweller Brute", 25, 200, 200, 60, 28, 270, 125, 34, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["HieroglyphicAnimator"] =  {"Hieroglyphic Animator", 26, 190, 190, 50, 30, 290, 135, 36, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LeaderBanditThug"] =      {"Leader Bandit Thug", 27, 210, 210, 62, 26, 310, 140, 36, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["FearHound"] =             {"Fear Hound", 28, 180, 180, 58, 22, 330, 150, 39, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["FallenTempleJusticar"] =  {"Fallen Temple Justicar", 29, 220, 220, 65, 35, 350, 160, 39, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["OrcGruntElite"] =         {"Orc Grunt Elite", 30, 250, 250, 70, 30, 380, 170, 42, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["RockGolemShard"] =        {"Rock Golem Shard", 30, 230, 230, 60, 40, 370, 165, 42, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["MoltenCoreElemental"] =   {"Molten Core Elemental", 31, 280, 280, 65, 40, 410, 180, 44, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ShadowedSunCleric"] =     {"Shadowed Sun Cleric", 32, 240, 240, 60, 30, 430, 190, 44, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GuardianSpirit"] =        {"Guardian Spirit", 33, 250, 250, 65, 30, 450, 200, 48, false, false, 0, 0, 0, 0, 0, "Magical", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AbyssalRitualist"] =      {"Abyssal Ritualist", 34, 250, 250, 70, 32, 520, 240, 48, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CrystalGolemCore"] =      {"Crystal Golem Core", 35, 300, 300, 70, 45, 550, 250, 50, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["HarpyMatriarch"] =        {"Harpy Matriarch", 35, 260, 260, 68, 28, 500, 230, 50, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["LavaBehemothWhelp"] =     {"Lava Behemoth Whelp", 36, 320, 320, 75, 42, 600, 270, 52, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["HellishDevilBat"] =       {"Hellish Devil Bat", 37, 220, 220, 72, 30, 620, 280, 52, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SeraphicEcho"] =          {"Seraphic Echo", 38, 280, 280, 75, 38, 650, 290,54, false, false, 0, 0, 0, 0, 0, "Celestial", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AncientCarnivorousPlant"]={"Ancient Carnivorous Plant", 39, 340, 340, 78, 35, 680, 300, 54, false, false, 0, 0, 0, 0, 0, "Plant", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CorruptedArchonAcolyte"]={"Corrupted Archon Acolyte", 40, 300, 300, 80, 40, 720, 310, 55, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["AbyssalWatcher"] =        {"Abyssal Watcher", 41, 330, 330, 75, 38, 650, 300, 57, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["InfernalVanguard"] =      {"Infernal Vanguard", 42, 360, 360, 82, 48, 780, 340, 58, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SunstoneSentinel"] =      {"Sunstone Sentinel", 42, 350, 350, 80, 40, 700, 320,58, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DivineConstructSentry"] = {"Divine Construct Sentry", 43, 380, 380, 85, 50, 800, 350, 57, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DarkWolfAlpha"] =         {"Dark Wolf Alpha", 44, 370, 370, 88, 40, 850, 370, 59, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SoulLeechWisp"] =         {"Soul Leech Wisp", 45, 330, 330, 78, 42, 920, 400,60, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["EchoOfALostSaint"] =      {"Echo of a Lost Saint", 46, 350, 350, 80, 45, 950, 420, 61, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["YoungPitFiend"] =         {"Young Pit Fiend", 47, 400, 400, 90, 50, 1000, 450, 61, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["TimelessTempleSentinel"] ={"Timeless Temple Sentinel", 49, 450, 450, 95, 55, 1100, 500, 63, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AvernusDeathKnight"] =    {"Avernus Death Knight", 49, 460, 460, 98, 58, 1150, 520, 63, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // Bosses
    enemyDatabase["AncientGolemSentry"] =    {"Ancient Golem Sentry", 12, 300, 300, 50, 20, 250, 120, 18, true, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GreaterSkeletonLord"] =   {"Greater Skeleton Lord", 24, 600, 600, 70, 30, 700, 300, 36, true, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["StoneColossusFragment"] = {"Stone Colossus Fragment", 36, 1000, 1000, 90, 45, 1500, 600, 40, true, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CorruptedArchon"] =       {"Corrupted Archon", 48, 1500, 1500, 120, 55, 3000, 1000, 53, true, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GiantCaveCrawler"] =      {"Giant Cave Crawler", 12, 280, 280, 55, 18, 240, 110, 18, true, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["UnderdarkOverseer"] =     {"Underdark Overseer", 24, 550, 550, 75, 28, 680, 290, 36, true, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LavaBehemothSpawn"] =     {"Lava Behemoth Spawn", 36, 950, 950, 95, 42, 1450, 580, 40, true, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["HeraldOfTheAbyss"] =      {"Herald of the Abyss", 48, 1400, 1400, 125, 52, 2900, 950, 53, true, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    
    enemyDatabase["AvatarOfTheForgottenDeity"] = {"Avatar of the Forgotten Deity", 60, 5000, 5000, 200, 80, 10000, 5000, 80, true, false, 0, 0, 0, 0, 0, "Divine", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AvernusCoreGuardian"] =      {"Avernus Core Guardian", 60, 4800, 4800, 210, 75, 9800, 4800, 80, true, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};


    enemyDatabase["Allain Ragna"] = Enemy("Allain Ragna", 1, 100, 100, 20, 10, 0, 0, 5, true, false, 0, 0, 0, 0, 0, "Humanoid");
    enemyDatabase["Azazel the Fallen Wing"] = Enemy("Azazel the Fallen Wing", 1, 200, 200, 30, 15, 0, 0, 10, true, false, 0, 0, 0, 0, 0, "Demon");
    enemyDatabase["Bael the Iron Fist"] = Enemy("Bael the Iron Fist", 1, 300, 300, 40, 20, 0, 0, 10, true, false, 0, 0, 0, 0, 0, "Demon");
    enemyDatabase["Vorlag, Wujud Awal Bencana"] = Enemy("Vorlag, Wujud Awal Bencana", 1, 500, 500, 50, 25, 0, 0, 15, true, false, 0, 0, 0, 0, 0, "Demon Lord (Form 1)");
    enemyDatabase["Vorlag, Wujud Sempurna Bencana"] = Enemy("Vorlag, Wujud Sempurna Bencana", 1, 700, 700, 60, 30, 0, 0, 20, true, false, 0, 0, 0, 0, 0, "True Demon Sovereign");
    enemyDatabase["Allain Ragna, Cahaya Pengharapan Terakhir"] = Enemy("Allain Ragna, Cahaya Pengharapan Terakhir", 1, 400, 400, 45, 25, 0, 0, 20, true, false, 0, 0, 0, 0, 0, "Heroic Spirit");

    // Dungeon Ancient Temple
    Dungeon ancientTemple;
    ancientTemple.exploredOnceFloors.clear();
    ancientTemple.name = "Ancient Temple";
    ancientTemple.type = "ascending";
    ancientTemple.printAsBasement = false;
    ancientTemple.storyLockedFloors = {11, 21, 31, 41}; 
    for (int i : {5, 15, 25, 35, 45}) { ancientTemple.campAreas[i] = CampArea{i}; }

    for (int i = 1; i <= 50; ++i) {
        ancientTemple.floorEnemies[i].clear(); 
        
        if (i >= 1 && i <= 3) {     
            ancientTemple.floorEnemies[i] = {"Slime", "GiantRat", "StoneSprite"};
        } else if (i >= 4 && i <= 6) { 
            ancientTemple.floorEnemies[i] = {"TempleRatSwarm", "TempleGuardDog", "DustMephit"};
        } else if (i >= 7 && i <= 9) { 
            ancientTemple.floorEnemies[i] = {"AnimatedSword", "AncientSentryFragment","LostPilgrimSpirit", "ShadowPup"};
        } else if (i == 10) { ancientTemple.miniBosses[i] = "AncientGolemSentry"; }

        
        else if (i >= 11 && i <= 13) { 
            ancientTemple.floorEnemies[i] = {"GuardianOrb", "GoblinRockthrower", "TempleAcolyte", "LesserImp"};
        } else if (i >= 14 && i <= 16) { 
            ancientTemple.floorEnemies[i] = {"DarkCultInitiate", "TempleKnightAspirant", "WildBoarStrong", "CorruptedCherub"};
        } else if (i >= 17 && i <= 19) { 
            ancientTemple.floorEnemies[i] = {"KoboldDigger", "ObsidianRazorfiend", "PhantomWarrior", "AltarGuardian"};
        } else if (i == 20) { ancientTemple.miniBosses[i] = "GreaterSkeletonLord"; }

        
        else if (i >= 21 && i <= 23) { 
            ancientTemple.floorEnemies[i] = {"CharredSalamander", "ForestSpider", "StoneLionCub", "RiverSerpent"};
        } else if (i >= 24 && i <= 26) { 
            ancientTemple.floorEnemies[i] = {"SkeletonSoldierElite", "LesserGargoyle", "DeepDwellerBrute", "HieroglyphicAnimator"};
        } else if (i >= 27 && i <= 29) { 
            ancientTemple.floorEnemies[i] = {"LeaderBanditThug", "FearHound", "FallenTempleJusticar"};
        } else if (i == 30) { ancientTemple.miniBosses[i] = "StoneColossusFragment"; }

        
        else if (i >= 31 && i <= 33) { 
            ancientTemple.floorEnemies[i] = {"OrcGruntElite", "RockGolemShard", "MoltenCoreElemental", "ShadowedSunCleric", "GuardianSpirit"};
        } else if (i >= 34 && i <= 36) { 
            ancientTemple.floorEnemies[i] = {"AbyssalRitualist", "CrystalGolemCore", "HarpyMatriarch", "LavaBehemothWhelp"};
        } else if (i >= 37 && i <= 39) { 
            ancientTemple.floorEnemies[i] = {"HellishDevilBat", "SeraphicEcho", "AncientCarnivorousPlant"};
        } else if (i == 40) { ancientTemple.miniBosses[i] = "CorruptedArchon"; }

        
        else if (i >= 41 && i <= 43) { 
            ancientTemple.floorEnemies[i] = {"CorruptedArchonAcolyte", "AbyssalWatcher", "InfernalVanguard", "DivineConstructSentry"};
        } else if (i >= 44 && i <= 46) { 
            ancientTemple.floorEnemies[i] = {"DarkWolfAlpha", "SoulLeechWisp", "EchoOfALostSaint"};
        } else if (i >= 47 && i <= 49) { 
            ancientTemple.floorEnemies[i] = {"YoungPitFiend", "TimelessTempleSentinel", "AvernusDeathKnight"}; 
        } else if (i == 50) { ancientTemple.finalBoss[i] = "AvatarOfTheForgottenDeity"; }
    }
    allDungeons["Ancient Temple"] = ancientTemple;


    // Dungeon Goa Avernix
    Dungeon goaAvernix;
    goaAvernix.exploredOnceFloors.clear();
    goaAvernix.name = "Goa Avernix";
    goaAvernix.type = "ascending";
    goaAvernix.printAsBasement = true;
    goaAvernix.storyLockedFloors = {11, 21, 31, 41}; 
    for (int i : {5, 15, 25, 35, 45}) { goaAvernix.campAreas[i] = CampArea{i}; }

    for (int i = 1; i <= 50; ++i) {
        goaAvernix.floorEnemies[i].clear(); 
        
        if (i >= 1 && i <= 3) {     
            goaAvernix.floorEnemies[i] = {"GiantRat", "FeralGoblinGrunt", "GiantCaveCricket"};
        } else if (i >= 4 && i <= 6) { 
            goaAvernix.floorEnemies[i] = {"KoboldScavenger", "GlowShroomCluster", "CaveLurker", "KoboldPathguard"};
        } else if (i >= 7 && i <= 9) { 
            goaAvernix.floorEnemies[i] = {"UmbralCrawler", "ShadowPup", "KoboldPathguard"}; 
        } else if (i == 10) { goaAvernix.miniBosses[i] = "GiantCaveCrawler"; }

        
        else if (i >= 11 && i <= 13) { 
            goaAvernix.floorEnemies[i] = {"GoblinRockthrower", "YoungCaveTroll", "LesserImp", "DarkCultInitiate"};
        } else if (i >= 14 && i <= 16) { 
            goaAvernix.floorEnemies[i] = {"WildBoarStrong", "BroodCavernSpider", "CorruptedCherub" }; 
        } else if (i >= 17 && i <= 19) { 
            goaAvernix.floorEnemies[i] = {"KoboldDigger", "ObsidianRazorfiend", "BroodCavernSpider"};
        } else if (i == 20) { goaAvernix.miniBosses[i] = "UnderdarkOverseer"; }

        
        else if (i >= 21 && i <= 23) { 
            goaAvernix.floorEnemies[i] = {"CharredSalamander", "ForestSpider", "StoneLionCub"}; 
        } else if (i >= 24 && i <= 26) { 
            goaAvernix.floorEnemies[i] = {"SkeletonSoldierElite", "DeepDwellerBrute", "LeaderBanditThug"};
        } else if (i >= 27 && i <= 29) { 
            goaAvernix.floorEnemies[i] = {"FearHound", "OrcGruntElite", "RockGolemShard"};
        } else if (i == 30) { goaAvernix.miniBosses[i] = "LavaBehemothSpawn"; }

        
        else if (i >= 31 && i <= 33) { 
            goaAvernix.floorEnemies[i] = {"MoltenCoreElemental", "AbyssalRitualist", "DeepDwellerBrute"};
        } else if (i >= 34 && i <= 36) { 
            goaAvernix.floorEnemies[i] = {"AbyssalRitualist", "LavaBehemothWhelp", "HellishDevilBat"};
        } else if (i >= 37 && i <= 39) { 
            goaAvernix.floorEnemies[i] = {"HellishDevilBat", "AncientCarnivorousPlant", "YoungPitFiend" }; 
        } else if (i == 40) { goaAvernix.miniBosses[i] = "HeraldOfTheAbyss"; }

        
        else if (i >= 41 && i <= 43) { 
            goaAvernix.floorEnemies[i] = {"AbyssalWatcher", "InfernalVanguard", "DarkWolfAlpha"};
        } else if (i >= 44 && i <= 46) { 
            goaAvernix.floorEnemies[i] = {"DarkWolfAlpha", "SoulLeechWisp", "YoungPitFiend"}; 
        } else if (i >= 47 && i <= 49) { 
            goaAvernix.floorEnemies[i] = {"YoungPitFiend", "AvernusDeathKnight", "SoulLeechWisp"};
        } else if (i == 50) { goaAvernix.finalBoss[i] = "AvernusCoreGuardian"; }
    }
    allDungeons["Goa Avernix"] = goaAvernix;
    loadEnemyASCIIFromFile("enemy.txt");
}

void initializeItems() {
    allItems = {
        {"Health Potion", "consumable", 25, "Memulihkan 50 HP.", 0, 100},
        {"Mana Potion", "consumable", 20, "Memulihkan 30 Mana.", 0, 100},
        {"Big Health Potion", "consumable", 60, "Memulihkan 300 HP dengan cepat.", 0, 275},
        {"Big Mana Potion", "consumable", 50, "Memulihkan 150 Mana dengan cepat.", 0, 275},
        {"Earl Grey Tea", "consumable", 10, "Secangkir teh yang nikmat. Akhirnya!", 0, 50},
        {"Minor Strength Elixir", "consumable", 60, "Sedikit meningkatkan Kekuatan untuk sementara.", 0, 250},
        {"Minor Focus Elixir", "consumable", 60, "Sedikit meningkatkan Int untuk sementara.", 0, 250}
    };
    
    itemDatabase.clear();
    for(auto& item : allItems) {
        itemDatabase[item.name] = &item;
    }
}

void initializeWeapons() {
    allWeapons = {
        {"Noble's Sword", 25, 5, 0, "Pedang turun temurun keluarga Weiss, lebih untuk pertarungan.", false, 750, "spesific_quest_completed", 0},
        {"Rusty Shortsword", 12, 5, 0, "Bilah terlupakan, lebih baik daripada tangan kosong.", false, 150, "no_flag", 0},
        {"Training Sword", 18, 8, 0, "Pedang standar untuk berlatih tebasan dasar.", false, 300, "no_flag", 0},
        {"Steel Dagger", 15, 3, 0, "Belati baja tajam dan ringan, cocok untuk serangan cepat.", false, 250, "no_flag", 0},
        {"Iron Kukri", 19, 7, 0, "Pedang melengkung dari besi, tebasannya cukup baik.", false, 350, "no_flag", 0},
        {"Light War Hammer", 20, 10, 0, "Palu tumpul ringan, efektif melawan armor sederhana.", false, 400, "no_flag", 0},
        {"Iron Longsword", 30, 12, 0, "Pedang panjang dari besi yang kokoh dan dapat diandalkan.", false, 1200, "blacksmith_tier1_unlocked", 1},
        {"Steel Kite Shield (Weapon)", 10, 15, 0, "Perisai yang juga bisa digunakan untuk memukul. (Dihitung sebagai senjata)", false, 1000, "blacksmith_tier1_unlocked", 1},
        {"Reinforced Staff", 28, 0, 20, "Tongkat yang diperkuat dengan lilitan logam.", false, 1100, "blacksmith_tier1_unlocked", 1},
        {"Cavalry Sword", 32, 14, 0, "Pedang lurus yang biasa digunakan pasukan berkuda.", false, 1500, "blacksmith_tier1_unlocked", 1},
        {"Steel War Axe", 35, 16, 0, "Kapak dari baja, membutuhkan kekuatan lebih untuk ayunan kuat.", false, 1700, "blacksmith_tier1_unlocked", 1},
        {"Knight's Arming Sword", 45, 18, 5, "Pedang seimbang yang pantas untuk seorang kesatria.", false, 3500, "blacksmith_tier2_unlocked", 1},
        {"Elven Thinblade", 40, 15, 10, "Bilah ringan dan cepat buatan peri, meningkatkan kelincahan.", false, 4000, "blacksmith_tier2_unlocked", 1},
        {"Battlemage's Rod", 38, 5, 25, "Gada dirancang untuk penyihir yang bertarung di garis depan.", false, 3200, "blacksmith_tier2_unlocked", 1},
        {"Bastard Flamberge", 48, 20, 0, "Pedang dengan bilah bergelombang, menakutkan dan mematikan.", false, 5000, "blacksmith_tier2_unlocked", 1},
        {"Moonlit Spellblade", 42, 17, 22, "Pedang yang bersinar lembut, dialiri energi bulan.", false, 5500, "blacksmith_tier2_unlocked", 1},
        {"Executioner's Greatsword", 70, 28, 0, "Pedang raksasa yang dirancang untuk kekuatan mentah.", false, 10000, "blacksmith_tier3_unlocked", 1},
        {"Crystal-Core Blade", 60, 22, 15, "Bilah dengan inti kristal yang dialiri sihir.", false, 12000, "blacksmith_tier3_unlocked", 1},
        {"Archmage's War Staff", 55, 10, 40, "Tongkat ampuh untuk sihir ofensif kuat dan pertarungan jarak dekat.", false, 9000, "blacksmith_tier3_unlocked", 1},
        {"Rune-Shatterer Claymore", 65, 25, 20, "Ditempa khusus untuk menetralkan atau menghancurkan sihir.", false, 15000, "blacksmith_tier3_unlocked", 1},
        {"Stormbringer Replica", 75, 30, 10, "Pedang legendaris yang konon bisa memanggil petir.", false, 18000, "blacksmith_tier3_unlocked", 1},
        {"Lumanaire MoonSword", 99, 70, 50, "Pedang sihir kuat, hanya sang pahlawan yang bisa mendapatkannya.", false, 20000, "specific_quest_completed", 1},
        {"Aurora's Thorned Blossom", 75, 15, 45, "Rapier elegan, bilahnya dingin menyimpan kehangatan tak terduga. Diberikan dengan tatapan yang jarang terlihat di Puncak Arcadia.", false, 0, "MASHA_LV10_COMPLETE", 1},
        {"Heartstone Pickaxe", 88, 60, 5, "Beliung penambang kokoh, ditempa dari inti bijih Avernix. Sebuah simbol ketahanan dari penjaga goa yang tak banyak bicara.", false, 0, "KINICH_LV10_COMPLETE", 1},
        {"Gardener's Gentle Thorn", 68, 10, 30, "Belati berukir lili, selembut tangan perawat taman namun setajam duri tersembunyi. Hadiah dari hati yang tulus di Mansion Astra.", false, 0, "IRENE_LV10_COMPLETE", 1},
        {"Chef's Honor Cleaver", 92, 65, 10, "Golok dapur raksasa yang seimbang sempurna, warisan dari seorang master chef yang telah melihat generasi Astra tumbuh.", false, 0, "RUIGERD_LV10_COMPLETE", 1},
        {"Guildmaster's Ledger Blade", 80, 40, 25, "Pedang panjang berhias lencana Cross Guild, tajam dan adil layaknya kontrak yang mengikat. Tanda kemitraan dari pemimpinnya.", false, 0, "ELLA_LV10_COMPLETE", 1},
        {"Truthseeker's Quillpoint", 72, 12, 35, "Rapier ramping setajam ujung pena seorang jurnalis pemberani, dirancang untuk mengungkap kelemahan dan memperjuangkan kebenaran.", false, 0, "CHARLOTTE_LV10_COMPLETE", 1},
        {"Warden's Silent Fang (Knife)", 85, 25, 10, "Pisau berburu senyap dari kayu Hutan Merah terliat, berukir jejak serigala. Tanda persaudaraan dari penjaga hutan yang setia.", false, 0, "MARS_LV10_COMPLETE", 1}
    };
    
    weaponDatabase.clear();
    for(auto& weapon : allWeapons) {
        weaponDatabase[weapon.name] = &weapon;
    }
    
    if (weaponDatabase.count("Noble's Sword")) {
        Weapon* noblesSwordPtr = weaponDatabase["Noble's Sword"];
        if (noblesSwordPtr) {
            player.weapons.push_back(noblesSwordPtr); 
            player.equippedWeapon = noblesSwordPtr;  
            noblesSwordPtr->equipped = true;         
        }
    }
}

void initializeStoryFlags() {
    storyFlags["duel_persahabatan"] = 0; 
    storyFlags["invasi_mansion"] = 0;
    storyFlags["invasi_arcadia"] = 0;
    storyFlags["pedang_pahlawan"] = 0; 
    storyFlags["pedang_pahlawan_weiss_chosen"] = 0;
    storyFlags["pedang_pahlawan_allain_chosen"] = 0;
    storyFlags["raja_iblis_final"] = 0; 
    storyFlags["ruigerd_weapon_given"] = 0;
    storyFlags["irene_book_given"] = 0;
    storyFlags["ella_contract_signed"] = 0;
    storyFlags["charlotte_scoop_shared"] = 0;
    storyFlags["mars_oath_taken"] = 0;
    storyFlags["kinich_map_received"] = 0;
    storyFlags["masha_flower_bloomed"] = 0;

    storyFlags["blacksmith_tier1_unlocked"] = 0;
    storyFlags["blacksmith_tier2_unlocked"] = 0;
    storyFlags["blacksmith_tier3_unlocked"] = 0;
}

void initializeScheduledEvents() {
    while (!scheduledEvents.empty()) {
        scheduledEvents.pop();
    }
    scheduledEvents.push({"Undangan Tak Terduga", "Sebuah panggilan kehormatan akan menentukan langkah awalmu.", 15, false});
    scheduledEvents.push({"Bayangan di Kediaman", "Sesuatu mengusik ketenangan Mansion Astra di kegelapan malam.", 25, false});
    scheduledEvents.push({"Gema Perang di Ibukota", "Nasib Arcadia berada di ujung tanduk, suara pertempuran menggema.", 35, false});
    scheduledEvents.push({"Cahaya Legenda Bangkit", "Sebuah artefak kuno akan muncul, mencari tuannya yang terpilih.", 50, false});
    scheduledEvents.push({"Fajar Terakhir atau Awal Baru?", "Hari perhitungan terakhir akan tiba, menentukan nasib dunia.", 60, false});
}

void initializeGame() {
    srand(time(nullptr));   
    setupWorldAreas();
    setupConnections();

    
    player.level = 1; 
    player.exp = 0;
    player.expToNextLevel = calculateExpToNextLevel(player.level);
    player.skillPoints = 1;
    player.unlockedMagicElements.clear();
    player.knownSpells.clear();
    player.activeEnchantments.clear();
    player.hp = player.maxHp = 100;
    player.mana = player.maxMana = 50;
    player.strength = 15;
    player.intelligence = 20;
    player.agility = 12;
    player.defense = 5; 
    player.gold = 1000;
    player.equippedWeapon = nullptr;
    player.activeHoTs.clear();
    player.inventory.clear(); 
    player.weapons.clear();
    
    // Panggil fungsi inisialisasi companions dan dungeons
    initializeCompanions(); 
    initializeDungeons();
    initializeItems();
    initializeWeapons();
    initializeStoryFlags();
    initializeScheduledEvents();
    initializeAllQuests();
    generateDailyQuests();


    initializeMagicSystem();
}

bool sudahBertemuCompanion(const string& namaCompanion) {
    if (socialLinks.count(namaCompanion)) {
        return socialLinks[namaCompanion].currentLevel > 0; 
    }
    return false;
}

void applyItemEffect(const string& itemName) {
    if (itemName == "Health Potion") {
        int heal = 50;
        player.hp = min(player.maxHp, player.hp + heal);
        delayPrint(L"✓ Kamu memulihkan " + to_wstring(heal) + L" HP!", 20);
    } else if (itemName == "Big Health Potion") {
        int heal = 150;
        player.hp = min(player.maxHp, player.hp + heal);
        delayPrint(L"✓ Kamu memulihkan " + to_wstring(heal) + L" HP!", 20);
    } else if (itemName == "Mana Potion") {
        int restore = 30;
        player.mana = min(player.maxMana, player.mana + restore);
        delayPrint(L"✓ Kamu memulihkan " + to_wstring(restore) + L" Mana!", 20);
    } else if (itemName == "Big Mana Potion") {
        int restore = 100;
        player.mana = min(player.maxMana, player.mana + restore);
        delayPrint(L"✓ Kamu memulihkan " + to_wstring(restore) + L" Mana!", 20);
    } else if (itemName == "Earl Grey Tea") {
        int heal = 50;
        player.hp = min(player.maxHp, player.hp + heal);
        delayPrint(L"✓ Kamu memulihkan " + to_wstring(heal) + L" HP!", 20);
    } else if (itemName == "Minor Strength Elixir") {
        delayPrint(L"✓ Kekuatanmu meningkat sementara!", 20);
        player.temporaryStrengthBuff += 5; 
    } else if (itemName == "Minor Focus Elixir") {
        delayPrint(L"✓ Konsentrasimu meningkat sementara!", 20);
        player.temporaryIntelligenceBuff += 5; 
    } else {
        delayPrint(L"Efek item tidak dikenali.", 20);
    }
}


void showItemShop() {
    int choice;
    vector<Item*> shopStock;

    
    for (auto const& [name, itemPtr] : itemDatabase) {
        if (itemPtr->price > 0) { 
            shopStock.push_back(itemPtr);
        }
    }
    
    sort(shopStock.begin(), shopStock.end(), [](Item* a, Item* b){
        if (a->type != b->type) return a->type < b->type; 
        return a->name < b->name; 
    });

    do {
        system("cls");
        printLine();
        centerText(L"✦✦✦ ITEM SHOP - 'Emporium Kelana' ✦✦✦");
        printLine();
        wcout << L"Selamat datang! Ada yang bisa kubantu?" << endl;
        wcout << L"Emas Anda: " << player.gold << L" 💰" << endl;
        printLine(60, L'─');

        if (shopStock.empty()) {
            wcout << L"Maaf, kami sedang kehabisan stok hari ini." << endl;
        } else {
            for (size_t i = 0; i < shopStock.size(); ++i) {
                wcout << L" ❖ " << (i + 1) << L". " << padRight(utf8_to_wstring(shopStock[i]->name), 25)
                      << L" (" << padRight(utf8_to_wstring(shopStock[i]->type), 10) << L")"
                      << L" - Harga: " << setw(4) << right << shopStock[i]->price << L" G" << endl;
                wcout << L"      └─ " << utf8_to_wstring(shopStock[i]->description) << endl;
            }
        }
        printLine(60, L'─');
        wcout << L" ❖ 0. Keluar Toko" << endl;
        printLine(60, L'─');
        wcout << L"Pilih item untuk dibeli ✦: ";

        choice = getValidatedChoice(1, 10); 

        if (cin.fail() || choice < 0 || choice > static_cast<int>(shopStock.size())) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            choice = -1;
        }

        if (choice > 0 && choice <= static_cast<int>(shopStock.size())) {
            Item* selectedItem = shopStock[choice - 1];
            system("cls");
            printLine();
            centerText(L"KONFIRMASI PEMBELIAN");
            printLine();
            wcout << L"Anda ingin membeli: " << utf8_to_wstring(selectedItem->name) << endl;
            wcout << L"Deskripsi         : " << utf8_to_wstring(selectedItem->description) << endl;
            wcout << L"Harga             : " << selectedItem->price << L" G" << endl;
            wcout << L"Emas Anda         : " << player.gold << L" G" << endl;
            printLine(50, L'-');

            if (player.gold >= selectedItem->price) {
                wcout << L"Beli item ini? (y/n) ✦: ";
                char confirm_char; 
                cin >> confirm_char;
                if (tolower(confirm_char) == 'y') {
                    player.gold -= selectedItem->price;
                    player.inventory.push_back(selectedItem);
                    delayPrint(L"✅ Pembelian berhasil! " + utf8_to_wstring(selectedItem->name) + L" ditambahkan ke inventory.", 20);
                } else {
                    delayPrint(L"Pembelian dibatalkan.", 20);
                }
            } else {
                delayPrint(L"❌ Emas Anda tidak cukup.", 20);
            }
            waitForEnter(L"Tekan Enter untuk kembali ke toko...");
            
        } else if (choice != 0) {
            delayPrint(L"Pilihan tidak valid.", 20);
            waitForEnter(L"Tekan Enter untuk melanjutkan...");
            
        }
         
        if (choice != 0) {
            if(cin.peek() != '\n') { 
                 cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            } else { 
                 cin.ignore();
            }
        }


    } while (choice != 0);
    delayPrint(L"Terima kasih sudah berkunjung!", 20);
    waitForEnter();
    
}

void showBlacksmith() {
    int choice;
    vector<Weapon*> availableWeapons;

    do {
        availableWeapons.clear();
        for (auto& weapon : allWeapons) { 
            bool isUnlocked = false;
            if (weapon.requiredStoryFlagKey == "no_flag" || weapon.requiredStoryFlagKey.empty()) {
                isUnlocked = true;
            } else if (storyFlags.count(weapon.requiredStoryFlagKey) && storyFlags.at(weapon.requiredStoryFlagKey) >= weapon.requiredStoryFlagValue) {
                isUnlocked = true;
            }

            if (isUnlocked && weapon.price > 0) {
                availableWeapons.push_back(&weapon); 
            }
        }
        sort(availableWeapons.begin(), availableWeapons.end(), [](Weapon* a, Weapon* b){
            if (a->price != b->price) return a->price < b->price;
            return a->name < b->name;
        });

        system("cls");
        printLine();
        centerText(L"✦✦✦ PENEMPA BESI 'Palu Membara' ✦✦✦");
        printLine();
        wcout << L"Butuh senjata baru, Tuan Muda? Lihatlah koleksiku!" << endl;
        wcout << L"Emas Anda: " << player.gold << L" 💰" << endl;
        printLine(80, L'─'); 

        if (availableWeapons.empty()) {
            wcout << L"Maaf, sepertinya belum ada senjata yang cocok untuk Anda saat ini." << endl;
            wcout << L"Kembalilah lagi nanti jika sudah lebih berpengalaman." << endl;
        } else {
            for (size_t i = 0; i < availableWeapons.size(); ++i) {
                wcout << L" ❖ " << (i + 1) << L". " << padRight(utf8_to_wstring(availableWeapons[i]->name), 28) 
                      << L" ATK: " << setw(3) << availableWeapons[i]->attackPower
                      << L" | STR Req: " << setw(2) << availableWeapons[i]->strengthRequired
                      << L" | INT Req: " << setw(2) << availableWeapons[i]->intelligenceRequired
                      << L" - Harga: " << setw(5) << right << availableWeapons[i]->price << L" G" << endl; 
                wcout << L"      └─ " << utf8_to_wstring(availableWeapons[i]->description) << endl;
            }
        }
        printLine(80, L'─');
        wcout << L" ❖ 0. Keluar dari Penempa" << endl;
        printLine(80, L'─');
        wcout << L"Pilih senjata untuk dibeli ✦: ";

        choice = getValidatedChoice(1, 10); 

         if (cin.fail() || choice < 0 || choice > static_cast<int>(availableWeapons.size())) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            choice = -1;
        }

        if (choice > 0 && choice <= static_cast<int>(availableWeapons.size())) {
            Weapon* selectedWeapon = availableWeapons[choice - 1];
            system("cls");
            printLine();
            centerText(L"KONFIRMASI PEMBELIAN SENJATA");
            printLine();
            wcout << L"Anda ingin membeli : " << utf8_to_wstring(selectedWeapon->name) << endl;
            wcout << L"Attack Power     : " << selectedWeapon->attackPower << endl;
            wcout << L"Strength Req.    : " << selectedWeapon->strengthRequired << endl;
            wcout << L"Intelligence Req.: " << selectedWeapon->intelligenceRequired << endl;
            wcout << L"Harga            : " << selectedWeapon->price << L" G" << endl;
            wcout << L"Emas Anda        : " << player.gold << L" G" << endl;
            printLine(50, L'-');

            bool alreadyOwned = false;
            for (const auto* pWeapon : player.weapons) {
                if (pWeapon->name == selectedWeapon->name) {
                    alreadyOwned = true;
                    break;
                }
            }

            if (alreadyOwned) {
                delayPrint(L"⚠️ Anda sudah memiliki senjata ini.", 20);
            } else if (player.gold >= selectedWeapon->price) {
                wcout << L"Beli senjata ini? (y/n) ✦: ";
                char confirm_char_weapon; 
                cin >> confirm_char_weapon;
                if (tolower(confirm_char_weapon) == 'y') {
                    player.gold -= selectedWeapon->price;
                    player.weapons.push_back(selectedWeapon); 
                    delayPrint(L"✅ Pembelian berhasil! " + utf8_to_wstring(selectedWeapon->name) + L" ditambahkan ke gudang senjata Anda.", 20);
                } else {
                    delayPrint(L"Pembelian dibatalkan.", 20);
                }
            } else {
                delayPrint(L"❌ Emas Anda tidak cukup untuk membeli senjata ini.", 20);
            }
            waitForEnter(L"Tekan Enter untuk kembali ke penempa...");
            
        } else if (choice != 0) {
            delayPrint(L"Pilihan tidak valid.", 20);
            waitForEnter();
            
        }
        
        if (choice != 0) {
             if(cin.peek() != '\n') {
                 waitForEnter();
            } else {
                 cin.ignore();
            }
        }

    } while (choice != 0);
    delayPrint(L"Hati-hati di jalan, Tuan Muda!", 20);
    waitForEnter();
    
}


void unlockNewMagicElementIfNeeded(Character& character) {
    for (int milestoneLevel : MAGIC_ELEMENT_UNLOCK_LEVELS) {
        if (character.level == milestoneLevel) {
            vector<string> availableElements;
            for (const auto& pair : allMagicElements) {
                bool alreadyUnlocked = false;
                for (const string& unlockedElem : character.unlockedMagicElements) {
                    if (unlockedElem == pair.first) {
                        alreadyUnlocked = true;
                        break;
                    }
                }
                if (!alreadyUnlocked) {
                    availableElements.push_back(pair.first);
                }
            }

            if (!availableElements.empty()) {
                int randomIndex = rand() % availableElements.size();
                string newElement = availableElements[randomIndex];
                character.unlockedMagicElements.push_back(newElement);
                delayPrint(L"✨ Selamat! Kamu telah membuka akses ke elemen magic baru: " + utf8_to_wstring(newElement) + L"!", 30);

                
                if (allMagicElements.count(newElement)) {
                    for (const auto& spellPair : allMagicElements[newElement].spells) {
                        const MagicSpell& spell = spellPair.second;
                        if (spell.tier == 1) {
                            bool alreadyKnown = false;
                            for(const string& knownId : character.knownSpells){
                                if(knownId == spell.id) {
                                    alreadyKnown = true;
                                    break;
                                }
                            }
                            if(!alreadyKnown) {
                                character.knownSpells.push_back(spell.id);
                                delayPrint(L"  ➤ Kamu mempelajari: " + utf8_to_wstring(spell.name) + L"!", 20);
                            }
                        }
                    }
                }
                
                character.skillPoints++;
                delayPrint(L"  Kamu mendapatkan 1 Skill Point tambahan!", 20);
                break; 
            }
        }
    }
}

void levelUpCharacter(Character& character) {
    character.level++;
    centerText(L" ");
    printLine(); 
    centerText(L"✦ LEVEL UP! ✦");
    printLine();

    delayPrint(L"📈 Selamat! Kamu mencapai Level " + to_wstring(character.level) + L"!", 30);
    delayPrint(L"═══════════════════════════════════════════════", 5);

    
    int hpGain = 5 + rand() % 6;       
    int manaGain = 5 + rand() % 4;     
    character.maxHp += hpGain;
    character.maxMana += manaGain;
    character.strength += 1;
    character.intelligence += 1;
    character.defense += 1;
    character.agility += 1;

    delayPrint(L"✦ Max HP +" + to_wstring(hpGain) + L", 🔷 Max Mana +" + to_wstring(manaGain), 20);
    delayPrint(L"✦ Strength +1", 20);
    delayPrint(L"✦ Intelligence +1", 20);
    delayPrint(L"✦ Defense +1", 20);
    delayPrint(L"✦ Agility +1", 20);

    if (character.level % 5 == 0) {
        character.skillPoints += 1;
        delayPrint(L"✦ Kamu mendapatkan 1 Skill Point!", 25);
    }

    character.expToNextLevel = calculateExpToNextLevel(character.level);
    delayPrint(L"✦ EXP ke Level berikutnya: " + to_wstring(character.expToNextLevel), 20);

    unlockNewMagicElementIfNeeded(character); 

    printLine(); 
}


void handleExperienceAndLevelUp(Character& character, int expGained) {
    if (expGained <= 0) return;
    system("cls");
    character.exp += expGained;
    bool leveledUp = false;
    while (character.exp >= character.expToNextLevel) {
        character.exp -= character.expToNextLevel;
        levelUpCharacter(character);
        leveledUp = true; 
    }

    if (!leveledUp) { 
        printLine();
        delayPrint(L"Total EXP: " + to_wstring(character.exp) + L"/" + to_wstring(character.expToNextLevel), 20);
    }
}

bool canLearnSpell(const Character& character, const MagicSpell& spell) {
    
    if (spell.tier == 2 && character.level < 30) return false; 
    if (spell.tier == 3 && character.level < 60) return false; 

    
    for (const string& prereqId : spell.prerequisites) {
        bool found = false;
        for (const string& knownSpellId : character.knownSpells) {
            if (knownSpellId == prereqId) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

void learnSpell(Character& character, const string& spellIdToLearn) {
    const MagicSpell* spellToLearn = nullptr;

    for (const auto& elemPair : allMagicElements) {
        if (elemPair.second.spells.count(spellIdToLearn)) {
            spellToLearn = &elemPair.second.spells.at(spellIdToLearn);
            
            break;
        }
    }

    if (!spellToLearn) {
        delayPrint(L"❌ Spell tidak ditemukan!", 20);
        return;
    }

    bool elementUnlocked = false;
    for (const string& unlockedElem : character.unlockedMagicElements) {
        if (unlockedElem == spellToLearn->elementType) {
            elementUnlocked = true;
            break;
        }
    }
    if (!elementUnlocked) {
        delayPrint(L"❌ Kamu belum membuka elemen " + utf8_to_wstring(spellToLearn->elementType) + L"!", 20);
        return;
    }

    
    for (const string& knownSpellId : character.knownSpells) {
        if (knownSpellId == spellIdToLearn) {
            delayPrint(L"❌ Kamu sudah mempelajari spell ini!", 20);
            return;
        }
    }

    if (!canLearnSpell(character, *spellToLearn)) {
        delayPrint(L"❌ Persyaratan untuk mempelajari spell ini belum terpenuhi (level atau prerequisite spell).", 20);
        return;
    }

    if (character.skillPoints < 1) { 
        delayPrint(L"❌ Skill Point tidak cukup!", 20);
        return;
    }
    PlayerSpellUndoState currentStateSnapshot;
    currentStateSnapshot.skillPoints = character.skillPoints;
    currentStateSnapshot.knownSpells = character.knownSpells; 
    spellLearnUndoStack.push(currentStateSnapshot);

 
    character.knownSpells.push_back(spellIdToLearn);
    character.skillPoints -= 1; 
    delayPrint(L"✨ Selamat! Kamu telah mempelajari: " + utf8_to_wstring(spellToLearn->name) + L"!", 20);
    delayPrint(L"  Sisa Skill Point: " + to_wstring(character.skillPoints), 20);
    waitForEnter(); 
}

void undoLearnLastSpell(Character& character) {
    system("cls"); 
    printLine();
    centerText(L"✦ UNDO PEMBELAJARAN SIHIR ✦");
    printLine();

    if (!spellLearnUndoStack.empty()) {
        PlayerSpellUndoState previousState = spellLearnUndoStack.top();
        spellLearnUndoStack.pop();

        string unlearnedSpellName = "Sihir Tak Dikenal";
        if (character.knownSpells.size() > previousState.knownSpells.size()) {
            string unlearnedSpellId = character.knownSpells.back(); 
             const MagicSpell* spellDetails = nullptr;
            for (const auto& elemPair : allMagicElements) {
                if (elemPair.second.spells.count(unlearnedSpellId)) {
                    spellDetails = &elemPair.second.spells.at(unlearnedSpellId);
                    break;
                }
            }
            if(spellDetails) unlearnedSpellName = spellDetails->name;
        }


        character.skillPoints = previousState.skillPoints;
        character.knownSpells = previousState.knownSpells; 

        delayPrint(L"Pembelajaran sihir '" + utf8_to_wstring(unlearnedSpellName) + L"' telah dibatalkan.", 30);
        delayPrint(L"Skill Point Anda telah dikembalikan menjadi: " + to_wstring(character.skillPoints), 30);
    } else {
        delayPrint(L"Tidak ada aksi pembelajaran sihir yang bisa dibatalkan dari sesi ini.", 30);
    }
    printLine();
    waitForEnter();
}

void displayElementSkillTree(Character& character, const string& elementName) {
    if (!allMagicElements.count(elementName)) return;
    const MagicElement& element = allMagicElements.at(elementName);

    map<int, vector<const MagicSpell*>> spellsByTier;
    for(const auto& spellPair : element.spells) {
        spellsByTier[spellPair.second.tier].push_back(&spellPair.second);
    }
    
    for (auto& tierPair : spellsByTier) {
        sort(tierPair.second.begin(), tierPair.second.end(), [](const MagicSpell* a, const MagicSpell* b){
            return a->id < b->id; 
        });
    }


    vector<const MagicSpell*> learnableSpellsList; 

    int spellDisplayIndex = 1;
    bool canGoBack = false;

    while(!canGoBack) {
        system("cls");
        printLine();
        centerText(L"✦✦✦ SKILL TREE - ELEMEN " + utf8_to_wstring(elementName) + L" ✦✦✦");
        printLine();
        wcout << L"Level Karakter: " << character.level << L"   Skill Points: " << character.skillPoints << endl;
        wcout << utf8_to_wstring(element.description) << endl;
        printLine(60, L'-');

        learnableSpellsList.clear();
        spellDisplayIndex = 1;

        for (int tier = 1; tier <= 3; ++tier) { 
            if (spellsByTier.count(tier)) {
                bool tierAccessible = (tier == 1 && character.level >=1) ||
                                      (tier == 2 && character.level >=15) ||
                                      (tier == 3 && character.level >=30);
                wstring tierHeader = L"--- Tier " + to_wstring(tier) + L" ---";
                if (!tierAccessible) {
                    tierHeader += L" (Terbuka di Lv. " + to_wstring(tier == 2 ? 15 : 30) + L")";
                }
                wcout << tierHeader << endl;

                for (const MagicSpell* spell : spellsByTier.at(tier)) {
                    bool known = false;
                    for (const string& knownId : character.knownSpells) {
                        if (knownId == spell->id) {
                            known = true;
                            break;
                        }
                    }

                    wstring displayStr = L"  ";
                    bool currentlyLearnable = tierAccessible && !known && canLearnSpell(character, *spell) && character.skillPoints > 0;

                    if (currentlyLearnable) {
                         displayStr += L"❖ " + to_wstring(spellDisplayIndex) + L". ";
                         learnableSpellsList.push_back(spell);
                         spellDisplayIndex++;
                    } else {
                        displayStr += L"    "; 
                    }

                    displayStr += utf8_to_wstring(spell->name) + L" (MP: " + to_wstring(spell->manaCost) + L", Power: " + to_wstring(spell->basePower) + L")";
                    if (known) {
                        displayStr += L" [Dikuasai]";
                    } else if (!tierAccessible) {
                         displayStr += L" [Terkunci Level]";
                    } else if (!canLearnSpell(character, *spell)) {
                         displayStr += L" [Prerequisite Belum]";
                    } else if (character.skillPoints == 0 && !known) {
                         displayStr += L" [SP Kurang]";
                    }


                    wcout << displayStr << endl;
                    wcout << L"      Desc: " << utf8_to_wstring(spell->description) << endl;
                    if (!spell->prerequisites.empty()) {
                        wcout << L"      Prerequisites: ";
                        for (size_t k = 0; k < spell->prerequisites.size(); ++k) {
                            string prereqName = "Unknown";
                            
                            for(const auto& elPair : allMagicElements){
                                if(elPair.second.spells.count(spell->prerequisites[k])){
                                    prereqName = elPair.second.spells.at(spell->prerequisites[k]).name;
                                    break;
                                }
                            }
                            wcout << utf8_to_wstring(prereqName) << (k == spell->prerequisites.size() - 1 ? L"" : L", ");
                        }
                        wcout << endl;
                    }
                }
                wcout << endl;
            }
        }
        printLine(60, L'-');
        wcout << L"Pilih spell untuk dipelajari (nomor) atau 0 untuk kembali: ";
        int choice;
        choice = getValidatedChoice(1, 20 ); 


        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; 
        }

        if (choice == 0) {
            canGoBack = true;
        } else if (choice > 0 && choice <= learnableSpellsList.size()) {
            learnSpell(character, learnableSpellsList[choice-1]->id);
            waitForEnter(L" Tekan enter untuk lanjut" ); 
        } else {
            waitForEnter(L"Pilihan tidak valid. Tekan Enter...");
        }
    }
}

bool showSpellDetailAndMaybeUnlock(Character& character, const MagicSpell& spell) {
    
    system("cls");
    printLine(); 
    centerText(L"✦ DETAIL SKILL: " + utf8_to_wstring(spell.name) + L" ✦"); 
    printLine();

    wcout << L"Elemen      : " << utf8_to_wstring(spell.elementType) << endl;
    wcout << L"Tier        : " << spell.tier << endl;
    wcout << L"MP Cost     : " << spell.manaCost << endl;
    wcout << L"Power       : " << spell.basePower << endl;
    wcout << L"Deskripsi   : " << utf8_to_wstring(spell.description) << endl;

    if (!spell.prerequisites.empty()) {
        wcout << L"Prasyarat   : ";
        for (size_t i = 0; i < spell.prerequisites.size(); ++i) {
            const MagicSpell* prereqSpell = getSpellDetails(spell.prerequisites[i]); 
            if (prereqSpell) {
                wcout << utf8_to_wstring(prereqSpell->name) << (i < spell.prerequisites.size() - 1 ? L", " : L"");
            } else {
                wcout << utf8_to_wstring(spell.prerequisites[i]) << L" (Detail Tidak Ditemukan)" << (i < spell.prerequisites.size() - 1 ? L", " : L"");
            }
        }
        wcout << endl;
    }

    bool alreadyKnown = false;
    for (const string& knownId : character.knownSpells) {
        if (knownId == spell.id) {
            alreadyKnown = true;
            break;
        }
    }

    wcout << L"Status      : " << (alreadyKnown ? L"✅ Dimiliki" : L"🔒 Belum dimiliki") << endl;
    bool learnedThisTurn = false; 

    if (!alreadyKnown) {
        wcout << L"Skill Point Tersisa: " << character.skillPoints << endl; 

        bool canCurrentlyLearnCheck = canLearnSpell(character, spell); 

        if (canCurrentlyLearnCheck && character.skillPoints > 0) {
            wcout << L"\nKamu bisa mempelajari skill ini. Gunakan 1 Skill Point? (y/n) ✦: ";
            char input;
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            if (input == 'y' || input == 'Y') {
                learnSpell(character, spell.id); 
                                                 
                learnedThisTurn = true; 
            } else {
                delayPrint(L"Pembelajaran dibatalkan.", 20);
            }
        } else if (!canCurrentlyLearnCheck) {
            delayPrint(L"\n❌ Belum memenuhi prasyarat atau level untuk mempelajari skill ini.", 20);
        } else { 
            delayPrint(L"\n❌ Skill Point tidak mencukupi.", 20);
        }
    }

    if (!learnedThisTurn) { 
         waitForEnter();
    }
    
    
    


    return learnedThisTurn; 
}


void displaySpellRecursive(const MagicSpell& spell, const map<string, MagicSpell>& allSpells,
                            const unordered_set<string>& knownSpells,
                            vector<const MagicSpell*>& selectableList,
                            int indent, int& counter) {
    wstring prefix(indent * 4, L' ');
    bool unlocked = knownSpells.count(spell.id);

    wcout << prefix << counter << L". " << (unlocked ? L"✅ " : L"🔒 ")
          << utf8_to_wstring(spell.name)
          << L" (MP: " << spell.manaCost << L", Power: " << spell.basePower << L")" << endl;

    selectableList.push_back(&spell);
    int current = counter;
    counter++;

    for (const auto& [id, s] : allSpells) {
        if (find(s.prerequisites.begin(), s.prerequisites.end(), spell.id) != s.prerequisites.end()) {
            displaySpellRecursive(s, allSpells, knownSpells, selectableList, indent + 1, counter);
        }
    }
}

void showSkillTreeMenu(Character& character) {
    int mainChoice; 
    do {
        system("cls");
        printLine();
        centerText(L"✦✦✦ SKILL TREE UTAMA ✦✦✦");
        printLine();
        wcout << L"Pilih elemen untuk melihat skill tree:" << endl;

        vector<string> unlockedElementsSorted = character.unlockedMagicElements;
        
        if (unlockedElementsSorted.empty() && character.name.find("Weiss von Astra") != string::npos && character.unlockedMagicElements.empty()) {
            delayPrint(L"(DEBUG: Menambahkan elemen Fire & Ice untuk tes karena belum ada elemen terbuka)");
            character.unlockedMagicElements.push_back("Fire");
            if(character.level >=1) character.unlockedMagicElements.push_back("Ice"); 
            unlockedElementsSorted = character.unlockedMagicElements; 
            waitForEnter();
        }

        if (unlockedElementsSorted.empty()){
            wcout << L"  Belum ada elemen magic yang terbuka." << endl;
            wcout << L"  (Elemen akan terbuka seiring kenaikan level atau melalui progres cerita)" << endl;
        } else {
            sort(unlockedElementsSorted.begin(), unlockedElementsSorted.end());
            for (size_t i = 0; i < unlockedElementsSorted.size(); ++i) {
                wcout << L"  ❖ " << (i + 1) << L". " << utf8_to_wstring(unlockedElementsSorted[i]) << endl;
            }
        }
        wcout << L"  ❖ 0. Kembali ke Diary" << endl;
        printLine(50, L'─');
        wcout << L"Pilih menu ✦: ";

        cin >> mainChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            delayPrint(L"Pilihan tidak valid. Masukkan angka.", 20);
            waitForEnter();
            mainChoice = -1; 
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (mainChoice > 0 && (size_t)mainChoice <= unlockedElementsSorted.size()) {
            string selectedElement = unlockedElementsSorted[mainChoice - 1];
            
            bool stayInElementView = true;
            while(stayInElementView) { 
                if (!allMagicElements.count(selectedElement)) {
                    delayPrint(L"Error: Data elemen " + utf8_to_wstring(selectedElement) + L" tidak ditemukan!", 20);
                    waitForEnter();
                    stayInElementView = false; 
                    break;
                }
                const auto& elementData = allMagicElements.at(selectedElement); 
                unordered_set<string> known(character.knownSpells.begin(), character.knownSpells.end()); 
                vector<const MagicSpell*> selectableList; 
                int counter = 1; 

                system("cls");
                printLine();
                centerText(L"✦ SKILL TREE: " + utf8_to_wstring(selectedElement) + L" ✦ SP: " + to_wstring(character.skillPoints) + L" ✦");
                printLine();
                wcout << utf8_to_wstring(elementData.description) << endl;
                printLine(60, L'-');


                for (const auto& spellPair : elementData.spells) {
                    if (spellPair.second.prerequisites.empty()) { 
                        displaySpellRecursive(spellPair.second, elementData.spells, known, selectableList, 0, counter);
                    }
                }

                printLine(60, L'-');
                wcout << L"Pilih spell (nomor dari daftar di atas) untuk melihat detail/mempelajari." << endl;
                wcout << L"Ketik '0' untuk kembali ke pemilihan elemen." << endl;
                if (!spellLearnUndoStack.empty()) {
                    wcout << L"Ketik 'U' atau 'u' untuk membatalkan pembelajaran sihir terakhir." << endl;
                }
                wcout << L"Pilihan Anda ✦: ";

                string inputSpellChoiceStr;
                
                if (cin.peek() == '\n') {
                     cin.ignore(); 
                }
                getline(cin, inputSpellChoiceStr);

                if (inputSpellChoiceStr == "U" || inputSpellChoiceStr == "u") {
                    if (!spellLearnUndoStack.empty()) {
                        undoLearnLastSpell(character); 
                    } else {
                        delayPrint(L"Tidak ada yang bisa di-undo saat ini.", 20);
                        waitForEnter();
                    }
                } else {
                    int spellChoiceNum = -1;
                    bool isValidNumericInput = true;
                    try {
                        spellChoiceNum = stoi(inputSpellChoiceStr);
                    } catch (const std::invalid_argument& ia) {
                        isValidNumericInput = false;
                    } catch (const std::out_of_range& oor) {
                        isValidNumericInput = false;
                    }

                    if (!isValidNumericInput && !inputSpellChoiceStr.empty()) { 
                        delayPrint(L"Pilihan tidak valid. Masukkan nomor, '0', atau 'U'.", 20);
                        waitForEnter();
                    } else if (inputSpellChoiceStr.empty()){
                        
                        
                        delayPrint(L"Tidak ada input. Coba lagi.", 20);
                        waitForEnter();
                    } else { 
                        if (spellChoiceNum == 0) {
                            stayInElementView = false; 
                        } else if (spellChoiceNum > 0 && (size_t)spellChoiceNum <= selectableList.size()) {
                            
                            
                            
                            showSpellDetailAndMaybeUnlock(character, *selectableList[spellChoiceNum - 1]);
                        } else if (spellChoiceNum != -1) { 
                            delayPrint(L"Nomor spell tidak ada dalam daftar.", 20);
                            waitForEnter();
                        }
                        
                    }
                }
            } 
        } else if (mainChoice != 0) { 
             delayPrint(L"Pilihan elemen tidak valid.", 20);
             waitForEnter();
        }
    } while (mainChoice != 0); 
}


void setupWorldAreas() {
    
    WorldArea mansion;
    mansion.name = "Mansion Astra";
    mansion.startSubArea = "Kamar Weiss";
    mansion.subAreas = {
        {"Kamar Weiss", { "Kamar Weiss", {"Cek Sekitar", "Membuka Diary", "Pilih Lokasi", "Istirahat"} }},
        {"Dapur Mansion", { "Dapur Mansion", {"Cek Sekitar", "Bicara dengan Ruigerd", "Membuka Diary", "Pilih Lokasi"} }},
        {"Taman Floresia", { "Taman Floresia", {"Cek Sekitar", "Bicara dengan Irene", "Membuka Diary", "Pilih Lokasi"} }},
        {"Lorong Panjang", { "Lorong Panjang", {"Cek Sekitar", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Mansion Astra"] = mansion;

    
    WorldArea arcadia;
    arcadia.name = "Kota Arcadia";
    arcadia.startSubArea = "Balai Kota";
    arcadia.subAreas = {
        {"Cross Guild", { "Cross Guild", {"Cek Sekitar", "Quest Board", "Bicara dengan Ella", "Buka Diary", "Pilih Lokasi"} }},
        {"Perbelanjaan", { "Perbelanjaan", {"Cek Sekitar", "Item Shop", "Penempa Besi", "Buka Diary", "Pilih Lokasi"} }},
        {"Balai Kota", { "Balai Kota", {"Cek Sekitar", "Cek Berita Kota", "Bicara dengan Charlotte", "Buka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Kota Arcadia"] = arcadia;

    
    WorldArea hutan;
    hutan.name = "Hutan Merah";
    hutan.startSubArea = "Pos Hutan";
    hutan.subAreas = {
        {"Pos Hutan", { "Pos Hutan", {"Cek Sekitar", "Bicara dengan Mars", "Membuka Diary", "Pilih Lokasi"} }},
        {"Reruntuhan Kuno", { "Reruntuhan Kuno", {"Cek Sekitar", "Masuk ke Ancient Temple (Dungeon)", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Hutan Merah"] = hutan;

    
    WorldArea goa;
    goa.name = "Goa Avernix";
    goa.startSubArea = "Camp Avernix";
    goa.subAreas = {
        {"Camp Avernix", { "Camp Avernix", {"Cek Sekitar", "Masuk ke Goa Avernix (Dungeon)", "Bicara dengan Kinich", "Membuka Diary", "Pilih Lokasi"} }},
        {"Tambang Terbengkalai", { "Tambang Terbengkalai", {"Cek Sekitar", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Goa Avernix"] = goa;

    
    WorldArea puncak;
    puncak.name = "Puncak Arcadia";
    puncak.startSubArea = "Taman Norelia";
    puncak.subAreas = {
        {"Taman Norelia", { "Taman Norelia", {"Cek Sekitar", "Bicara dengan Masha", "Membuka Diary", "Pilih Lokasi"} }},
        {"Bendungan", { "Bukit Myriad", {"Cek Sekitar", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Puncak Arcadia"] = puncak;
    
}

void setupConnections() {
    
    if (allWorlds.count("Mansion Astra")) {
        vector<pair<string, string>> koneksiMansion = {
            {"Kamar Weiss", "Lorong Panjang"},
            {"Lorong Panjang", "Taman Floresia"},
            {"Lorong Panjang", "Dapur Mansion"}
        };
        for (const auto& conn : koneksiMansion) {
            locationGraph[conn.first].push_back(conn.second);
            locationGraph[conn.second].push_back(conn.first);
        }
    }

    
    if (allWorlds.count("Kota Arcadia")) {
        vector<pair<string, string>> koneksiKotaArcadia = {
            {"Balai Kota", "Cross Guild"},
            {"Balai Kota", "Perbelanjaan"}
        };
        for (const auto& conn : koneksiKotaArcadia) {
            locationGraph[conn.first].push_back(conn.second);
            locationGraph[conn.second].push_back(conn.first);
        }
    }

    
    if (allWorlds.count("Hutan Merah")) {
        vector<pair<string, string>> koneksiHutanMerah = {
            {"Pos Hutan", "Reruntuhan Kuno"}
        };
        for (const auto& conn : koneksiHutanMerah) {
            locationGraph[conn.first].push_back(conn.second);
            locationGraph[conn.second].push_back(conn.first);
        }
    }

    
    if (allWorlds.count("Goa Avernix")) {
        vector<pair<string, string>> koneksiGoaAvernix = {
            {"Camp Avernix", "Tambang Terbengkalai"}
        };
        for (const auto& conn : koneksiGoaAvernix) {
            locationGraph[conn.first].push_back(conn.second);
            locationGraph[conn.second].push_back(conn.first);
        }
    }

    
    if (allWorlds.count("Puncak Patung Pahlawan Negara")) {
        vector<pair<string, string>> koneksiPuncak = {
            {"Taman Norelia", "Bendungan"}
        };
        for (const auto& conn : koneksiPuncak) {
            locationGraph[conn.first].push_back(conn.second);
            locationGraph[conn.second].push_back(conn.first);
        }
    }
}


void initializeAllQuests() {
    allDailyQuestPool.clear();

    
    
    
    
    allDailyQuestPool.push_back({"Perburuan Slime Dasar", "Bunuh 1 monster Slime.", "kill", "Slime", 0, "", false, false, 30, 20, "C"});
    allDailyQuestPool.push_back({"Ancaman Tikus Biasa", "Kalahkan 1 Giant Rat.", "kill", "GiantRat", 0, "", false, false, 35, 25, "C"});
    allDailyQuestPool.push_back({"Masalah Goblin Grunt", "Habisi 1 Feral Goblin Grunt.", "kill", "FeralGoblinGrunt", 2, "Goa Avernix", false, false, 40, 30, "C"});
    allDailyQuestPool.push_back({"Penjinakan Sprite Batu", "Hancurkan 1 Stone Sprite.", "kill", "StoneSprite", 0, "", false, false, 45, 35, "C"});
    allDailyQuestPool.push_back({"Serangga Gua Mengganggu", "Basmi 1 Giant Cave Cricket.", "kill", "GiantCaveCricket", 1, "Goa Avernix", false, false, 50, 40, "C"});
    allDailyQuestPool.push_back({"Gerombolan Tikus Kuil", "Singkirkan 1 Temple Rat Swarm.", "kill", "TempleRatSwarm", 3, "Ancient Temple", false, false, 55, 45, "C"});
    allDailyQuestPool.push_back({"Pencuri Kobold", "Kalahkan 1 Kobold Scavenger.", "kill", "KoboldScavenger", 4, "Goa Avernix", false, false, 60, 50, "C"});
    allDailyQuestPool.push_back({"Jamur Aneh", "Selidiki dan kalahkan 1 Glow Shroom Cluster.", "kill", "GlowShroomCluster", 0, "", false, false, 65, 55, "C"});
    
    allDailyQuestPool.push_back({"Kunjungan ke Dapur", "Kunjungi Dapur Mansion.", "travel", "Dapur Mansion", 0, "Mansion Astra", false, false, 20, 15, "C"});
    allDailyQuestPool.push_back({"Menikmati Taman Floresia", "Jalan-jalan santai di Taman Floresia.", "travel", "Taman Floresia", 0, "Mansion Astra", false, false, 25, 20, "C"});
    allDailyQuestPool.push_back({"Menyusuri Lorong Kediaman", "Periksa Lorong Panjang di Mansion Astra.", "travel", "Lorong Panjang", 0, "Mansion Astra", false, false, 20, 15, "C"});
    allDailyQuestPool.push_back({"Ke Balai Kota Arcadia", "Kunjungi Balai Kota di Kota Arcadia.", "travel", "Balai Kota", 0, "Kota Arcadia", false, false, 30, 25, "C"});
    allDailyQuestPool.push_back({"Mampir ke Pos Hutan", "Laporkan diri di Pos Hutan, Hutan Merah.", "travel", "Pos Hutan", 0, "Hutan Merah", false, false, 35, 30, "C"});
    allDailyQuestPool.push_back({"Dasar Kuil Kuno", "Jelajahi hingga Lantai 2 Ancient Temple.", "travel", "Ancient Temple Lt.2", 2, "Ancient Temple", false, false, 70, 60, "C"});
    allDailyQuestPool.push_back({"Pintu Masuk Goa Avernix", "Capai Lantai B1 (lantai 1) di Goa Avernix.", "travel", "Goa Avernix Lt.B1", 1, "Goa Avernix", false, false, 75, 65, "C"});
    allDailyQuestPool.push_back({"Debu Misterius", "Kalahkan 1 Dust Mephit.", "kill", "DustMephit", 0, "", false, false, 80, 70, "C"});
    allDailyQuestPool.push_back({"Anjing Penjaga", "Hadapi 1 Temple Guard Dog.", "kill", "TempleGuardDog", 6, "Ancient Temple", false, false, 90, 75, "C"});


    
    
    
    
    allDailyQuestPool.push_back({"Kobold Penjaga Jalur", "Kalahkan 1 Kobold Pathguard.", "kill", "KoboldPathguard", 8, "Goa Avernix", false, false, 150, 100, "B"});
    allDailyQuestPool.push_back({"Pengintai Gua", "Hadapi 1 Cave Lurker.", "kill", "CaveLurker", 0, "", false, false, 160, 110, "B"});
    allDailyQuestPool.push_back({"Pedang Animasi", "Hancurkan 1 Animated Sword di reruntuhan.", "kill", "AnimatedSword", 11, "Ancient Temple", false, false, 170, 120, "B"});
    allDailyQuestPool.push_back({"Perayap Kegelapan", "Singkirkan 1 Umbral Crawler.", "kill", "UmbralCrawler", 13, "Goa Avernix", false, false, 180, 130, "B"});
    allDailyQuestPool.push_back({"Fragmen Penjaga Kuno", "Nonaktifkan 1 Ancient Sentry Fragment.", "kill", "AncientSentryFragment", 14, "Ancient Temple", false, false, 190, 140, "B"});
    allDailyQuestPool.push_back({"Anak Anjing Bayangan", "Tenangkan 1 Shadow Pup.", "kill", "ShadowPup", 0, "", false, false, 200, 150, "B"});
    allDailyQuestPool.push_back({"Orb Penjaga", "Hancurkan 1 Guardian Orb.", "kill", "GuardianOrb", 11, "Ancient Temple", false, false, 210, 160, "B"});
    allDailyQuestPool.push_back({"Pelempar Batu Goblin", "Lumpuhkan 1 Goblin Rockthrower.", "kill", "GoblinRockthrower", 12, "Goa Avernix", false, false, 220, 170, "B"});
    
    allDailyQuestPool.push_back({"Jelajah Reruntuhan Kuno", "Kunjungi area Reruntuhan Kuno di Hutan Merah.", "travel", "Reruntuhan Kuno", 0, "Hutan Merah", false, false, 100, 80, "B"});
    allDailyQuestPool.push_back({"Ke Distrik Perbelanjaan", "Cari barang di Perbelanjaan, Kota Arcadia.", "travel", "Perbelanjaan", 0, "Kota Arcadia", false, false, 110, 90, "B"});
    allDailyQuestPool.push_back({"Menemui Informan Guild", "Datangi Cross Guild di Kota Arcadia.", "travel", "Cross Guild", 0, "Kota Arcadia", false, false, 120, 100, "B"});
    allDailyQuestPool.push_back({"Menjelajah Kuil Tengah", "Capai Lantai 15 di Ancient Temple.", "travel", "Ancient Temple Lt.15", 15, "Ancient Temple", false, false, 250, 180, "B"});
    allDailyQuestPool.push_back({"Turuni Goa Avernix (Mid)", "Capai Lantai B14 (lantai 14) di Goa Avernix.", "travel", "Goa Avernix Lt.B14", 14, "Goa Avernix", false, false, 260, 190, "B"});
    allDailyQuestPool.push_back({"Akolit Kuil Sesat", "Kalahkan 1 Temple Acolyte.", "kill", "TempleAcolyte", 16, "Ancient Temple", false, false, 230, 175, "B"});
    allDailyQuestPool.push_back({"Troll Gua Muda", "Hadapi 1 Young Cave Troll.", "kill", "YoungCaveTroll", 17, "Goa Avernix", false, false, 240, 185, "B"});
    allDailyQuestPool.push_back({"Imp Pengganggu", "Usir 1 Lesser Imp.", "kill", "LesserImp", 0, "", false, false, 200, 150, "B"});
    allDailyQuestPool.push_back({"Inisiat Kultus Gelap", "Hentikan 1 Dark Cult Initiate.", "kill", "DarkCultInitiate", 0, "", false, false, 215, 165, "B"});


    
    
    
    
    allDailyQuestPool.push_back({"Ksatria Kuil Aspiran", "Ujilah kekuatan 1 Temple Knight Aspirant.", "kill", "TempleKnightAspirant", 22, "Ancient Temple", false, false, 400, 250, "A"});
    allDailyQuestPool.push_back({"Babi Hutan Perkasa", "Burulah 1 Wild Boar (Strong).", "kill", "WildBoarStrong", 0, "", false, false, 420, 260, "A"});
    allDailyQuestPool.push_back({"Penjaga Rune Aktif", "Nonaktifkan 1 Rune Guardian.", "kill", "RuneGuardian", 25, "Ancient Temple", false, false, 440, 270, "A"});
    allDailyQuestPool.push_back({"Induk Laba-laba Gua", "Kalahkan 1 Brood Cavern Spider.", "kill", "BroodCavernSpider", 23, "Goa Avernix", false, false, 460, 280, "A"});
    allDailyQuestPool.push_back({"Cherub Terkorupsi", "Sucikan 1 Corrupted Cherub.", "kill", "CorruptedCherub", 0, "", false, false, 480, 290, "A"});
    allDailyQuestPool.push_back({"Penggali Kobold Ahli", "Hentikan 1 Kobold Digger.", "kill", "KoboldDigger", 21, "Goa Avernix", false, false, 500, 300, "A"});
    allDailyQuestPool.push_back({"Iblis Pisau Obsidian", "Lawan 1 Obsidian Razorfiend.", "kill", "ObsidianRazorfiend", 0, "", false, false, 520, 310, "A"});
    allDailyQuestPool.push_back({"Prajurit Hantu", "Tenangkan arwah 1 Phantom Warrior.", "kill", "PhantomWarrior", 28, "Ancient Temple", false, false, 540, 320, "A"});
    allDailyQuestPool.push_back({"Penjaga Altar Kuno", "Kalahkan 1 Altar Guardian.", "kill", "AltarGuardian", 29, "Ancient Temple", false, false, 560, 330, "A"});
    
    allDailyQuestPool.push_back({"Inspeksi Tambang Terbengkalai", "Selidiki Tambang Terbengkalai di Goa Avernix.", "travel", "Tambang Terbengkalai", 0, "Goa Avernix", false, false, 200, 150, "A"});
    allDailyQuestPool.push_back({"Menjelajahi Kuil Dalam", "Capai Lantai 25 di Ancient Temple.", "travel", "Ancient Temple Lt.25", 25, "Ancient Temple", false, false, 600, 350, "A"});
    allDailyQuestPool.push_back({"Menerobos Goa Avernix (Dalam)", "Capai Lantai B28 (lantai 28) di Goa Avernix.", "travel", "Goa Avernix Lt.B28", 28, "Goa Avernix", false, false, 620, 360, "A"});
    allDailyQuestPool.push_back({"Salamander Hangus", "Kalahkan 1 Charred Salamander.", "kill", "CharredSalamander", 0, "", false, false, 570, 340, "A"});
    allDailyQuestPool.push_back({"Laba-laba Hutan Belantara", "Singkirkan 1 Forest Spider.", "kill", "ForestSpider", 0, "", false, false, 580, 350, "A"});
    allDailyQuestPool.push_back({"Singa Batu Muda", "Hadapi 1 Stone Lion Cub.", "kill", "StoneLionCub", 0, "", false, false, 590, 360, "A"});
    allDailyQuestPool.push_back({"Ular Sungai Berbisa", "Lumpuhkan 1 River Serpent.", "kill", "RiverSerpent", 0, "", false, false, 600, 370, "A"});


    
    
    
    
    allDailyQuestPool.push_back({"Elite Prajurit Tengkorak", "Musnahkan 1 Skeleton Soldier Elite.", "kill", "SkeletonSoldierElite", 31, "Ancient Temple", false, false, 800, 500, "S"});
    allDailyQuestPool.push_back({"Gargoyle Penjaga", "Kalahkan 1 Lesser Gargoyle.", "kill", "LesserGargoyle", 33, "Ancient Temple", false, false, 830, 520, "S"});
    allDailyQuestPool.push_back({"Brute Penghuni Kedalaman", "Hadapi 1 Deep Dweller Brute.", "kill", "DeepDwellerBrute", 32, "Goa Avernix", false, false, 860, 540, "S"});
    allDailyQuestPool.push_back({"Animator Hieroglif", "Hentikan 1 Hieroglyphic Animator.", "kill", "HieroglyphicAnimator", 35, "Ancient Temple", false, false, 890, 560, "S"});
    allDailyQuestPool.push_back({"Pemimpin Bandit Kejam", "Tangkap atau kalahkan 1 Leader Bandit Thug.", "kill", "LeaderBanditThug", 0, "", false, false, 920, 580, "S"});
    allDailyQuestPool.push_back({"Anjing Pengejar Ketakutan", "Lawan 1 Fear Hound.", "kill", "FearHound", 36, "Goa Avernix", false, false, 950, 600, "S"});
    allDailyQuestPool.push_back({"Justicar Kuil Terkutuk", "Adili 1 Fallen Temple Justicar.", "kill", "FallenTempleJusticar", 38, "Ancient Temple", false, false, 980, 620, "S"});
    allDailyQuestPool.push_back({"Suku Orc Elit", "Kalahkan 1 Orc Grunt Elite.", "kill", "OrcGruntElite", 0, "", false, false, 1010, 640, "S"});
    allDailyQuestPool.push_back({"Pecahan Golem Batu Raksasa", "Hancurkan 1 Rock Golem Shard.", "kill", "RockGolemShard", 39, "Goa Avernix", false, false, 1040, 660, "S"});
    
    allDailyQuestPool.push_back({"Menjelajahi Jantung Kuil", "Capai Lantai 35 di Ancient Temple.", "travel", "Ancient Temple Lt.35", 35, "Ancient Temple", false, false, 1100, 700, "S"});
    allDailyQuestPool.push_back({"Menuruni Inti Avernix", "Capai Lantai B38 (lantai 38) di Goa Avernix.", "travel", "Goa Avernix Lt.B38", 38, "Goa Avernix", false, false, 1150, 720, "S"});
    allDailyQuestPool.push_back({"Elemental Inti Cair", "Taklukkan 1 Molten Core Elemental.", "kill", "MoltenCoreElemental", 31, "Goa Avernix", false, false, 1050, 670, "S"});
    allDailyQuestPool.push_back({"Klerik Matahari Bayangan", "Hadapi 1 Shadowed Sun Cleric.", "kill", "ShadowedSunCleric", 0, "", false, false, 1060, 680, "S"});
    allDailyQuestPool.push_back({"Roh Penjaga Agung", "Lawan 1 Guardian Spirit.", "kill", "GuardianSpirit", 33, "Ancient Temple", false, false, 1070, 690, "S"});
    allDailyQuestPool.push_back({"Ritualis Jurang Maut", "Gagalkan ritual 1 Abyssal Ritualist.", "kill", "AbyssalRitualist", 34, "Ancient Temple", false, false, 1080, 700, "S"});
    allDailyQuestPool.push_back({"Inti Golem Kristal", "Ambil inti dari 1 Crystal Golem Core.", "kill", "CrystalGolemCore", 35, "Goa Avernix", false, false, 1090, 710, "S"});


    
    
    
    
    allDailyQuestPool.push_back({"Matriark Harpy Penguasa", "Kalahkan 1 Harpy Matriarch.", "kill", "HarpyMatriarch", 0, "", false, false, 1500, 1000, "SS"});
    allDailyQuestPool.push_back({"Anakan Behemoth Lava", "Lumpuhkan 1 Lava Behemoth Whelp.", "kill", "LavaBehemothWhelp", 41, "Goa Avernix", false, false, 1550, 1050, "SS"});
    allDailyQuestPool.push_back({"Kelelawar Iblis Neraka", "Basmi 1 Hellish Devil Bat.", "kill", "HellishDevilBat", 0, "", false, false, 1600, 1100, "SS"});
    allDailyQuestPool.push_back({"Gema Seraphim", "Hadapi 1 Seraphic Echo.", "kill", "SeraphicEcho", 43, "Ancient Temple", false, false, 1650, 1150, "SS"});
    allDailyQuestPool.push_back({"Tanaman Karnivora Purba", "Tebang 1 Ancient Carnivorous Plant.", "kill", "AncientCarnivorousPlant", 0, "", false, false, 1700, 1200, "SS"});
    allDailyQuestPool.push_back({"Akolit Archon Terkorupsi", "Hentikan 1 Corrupted Archon Acolyte.", "kill", "CorruptedArchonAcolyte", 45, "Ancient Temple", false, false, 1750, 1250, "SS"});
    allDailyQuestPool.push_back({"Pengintai Jurang Neraka", "Kalahkan 1 Abyssal Watcher.", "kill", "AbyssalWatcher", 42, "Goa Avernix", false, false, 1800, 1300, "SS"});
    allDailyQuestPool.push_back({"Barisan Depan Inferno", "Hadapi 1 Infernal Vanguard.", "kill", "InfernalVanguard", 44, "Goa Avernix", false, false, 1850, 1350, "SS"});
    allDailyQuestPool.push_back({"Benteng Batu Matahari", "Hancurkan 1 Sunstone Sentinel.", "kill", "SunstoneSentinel", 0, "", false, false, 1900, 1400, "SS"});
    allDailyQuestPool.push_back({"Penjaga Konstruk Ilahi", "Nonaktifkan 1 Divine Construct Sentry.", "kill", "DivineConstructSentry", 46, "Ancient Temple", false, false, 1950, 1450, "SS"});
    
    allDailyQuestPool.push_back({"Menaklukkan Puncak Kuil Suci", "Capai Lantai 45 Ancient Temple.", "travel", "Ancient Temple Lt.45", 45, "Ancient Temple", false, false, 2000, 1500, "SS"});
    allDailyQuestPool.push_back({"Menuruni Dasar Avernix", "Capai Lantai B48 (lantai 48) Goa Avernix.", "travel", "Goa Avernix Lt.B48", 48, "Goa Avernix", false, false, 2100, 1550, "SS"});
    allDailyQuestPool.push_back({"Alfa Serigala Kegelapan", "Burulah pemimpin Dark Wolf Alpha.", "kill", "DarkWolfAlpha", 0, "", false, false, 2200, 1600, "SS"});
    allDailyQuestPool.push_back({"Wisp Penyerap Jiwa", "Musnahkan 1 Soul Leech Wisp.", "kill", "SoulLeechWisp", 47, "Ancient Temple", false, false, 2300, 1650, "SS"});
    allDailyQuestPool.push_back({"Gema Orang Suci yang Hilang", "Tenangkan 1 Echo of a Lost Saint.", "kill", "EchoOfALostSaint", 0, "", false, false, 2400, 1700, "SS"});
    allDailyQuestPool.push_back({"Iblis Muda dari Jurang", "Kalahkan 1 Young Pit Fiend.", "kill", "YoungPitFiend", 49, "Goa Avernix", false, false, 2500, 1750, "SS"});
    allDailyQuestPool.push_back({"Penjaga Kuil Abadi", "Hadapi 1 Timeless Temple Sentinel.", "kill", "TimelessTempleSentinel", 50, "Ancient Temple", false, false, 3000, 2000, "SS"}); 
}

void generateDailyQuests() {
    dailyQuests.clear();
    unordered_set<int> chosen;
    string playerRank = getQuestRankLetter();
    vector<DailyQuest> filtered;

    map<string, int> rankValue = {{"C", 1}, {"B", 2}, {"A", 3}, {"S", 4}, {"SS", 5}};

    for (const auto& q : allDailyQuestPool) {
        if (rankValue[q.rank] <= rankValue[playerRank]) {
            filtered.push_back(q);
        }
    }

    while (dailyQuests.size() < 3 && chosen.size() < filtered.size()) {
        int idx = rand() % filtered.size();
        if (!chosen.count(idx)) {
            chosen.insert(idx);
            dailyQuests.push_back(filtered[idx]);
        }
    }
}



void showQuestBoard() {
    while (true) {
        system("cls");
        printLine();
        centerText(L"✦✦✦ PAPAN QUEST CROSS GUILD ✦✦✦");
        centerText(L"» RANK QUEST HARI INI: " + utf8_to_wstring(getQuestRankLetter()));
        printLine();

        int index = 1;
        vector<int> visibleQuestIndices;

        for (size_t i = 0; i < dailyQuests.size(); ++i) {
            const DailyQuest& q = dailyQuests[i];
            if (q.completed) continue; 

            wcout << L"❖ " << index++ << L". " << utf8_to_wstring(q.title);

            bool isTaken = false;
            ActiveDailyQuestNode* current = activeDailyQuestsHead;
            while (current != nullptr) {
                if (current->data.title == q.title) {
                    isTaken = true;
                    wcout << (current->data.completed ? L" [Selesai]" : L" [Diambil]");
                    break;
                }
                current = current->next;
            }

            if (!isTaken && q.taken) {
                wcout << L" [Diambil - Belum di List Aktif?]";
            }

            wcout << endl;
            visibleQuestIndices.push_back(i); 
        }

        if (visibleQuestIndices.empty()) {
            wcout << L"~ Tidak ada quest tersedia saat ini." << endl;
        }

        printLine();
        wcout << L"❖ Pilih nomor untuk lihat detail quest, atau 0 untuk kembali: ";
        int qchoice;
        cin >> qchoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            delayPrint(L"Pilihan tidak valid. Masukkan angka.", 20);
            waitForEnter();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (qchoice == 0) break;
        if (qchoice < 1 || qchoice > visibleQuestIndices.size()) {
            delayPrint(L"Nomor quest tidak valid.", 20);
            waitForEnter();
            continue;
        }

        
        DailyQuest& selectedQuest = dailyQuests[visibleQuestIndices[qchoice - 1]];

        
        system("cls");
        printLine();
        centerText(L"✦ DETAIL QUEST ✦");
        printLine();
        wcout << L"✦ Judul     : " << utf8_to_wstring(selectedQuest.title) << endl;
        wcout << L"✦ Deskripsi : " << utf8_to_wstring(selectedQuest.description) << endl;
        wcout << L"✦ Target    : " << utf8_to_wstring(selectedQuest.target);
        if (selectedQuest.type == "kill" && selectedQuest.dungeonFloor > 0 && !selectedQuest.dungeonName.empty()) {
            wcout << L" (di " << utf8_to_wstring(selectedQuest.dungeonName)
                  << L" Lt." << formatDungeonFloor(allDungeons[selectedQuest.dungeonName], selectedQuest.dungeonFloor) << L")";
        } else if (selectedQuest.type == "travel" && selectedQuest.dungeonFloor > 0 && !selectedQuest.dungeonName.empty()) {
            wcout << L" (Area: " << utf8_to_wstring(selectedQuest.dungeonName)
                  << L", Lantai: " << formatDungeonFloor(allDungeons[selectedQuest.dungeonName], selectedQuest.dungeonFloor) << L")";
        }
        wcout << endl;
        wcout << L"✦ Rank      : " << utf8_to_wstring(selectedQuest.rank) << endl;
        wcout << L"✦ Reward    : " << selectedQuest.expReward << L" EXP, " << selectedQuest.goldReward << L" Gold" << endl;
        printLine();

        
        bool alreadyTaken = false;
        for (ActiveDailyQuestNode* node = activeDailyQuestsHead; node != nullptr; node = node->next) {
            if (node->data.title == selectedQuest.title) {
                alreadyTaken = true;
                break;
            }
        }

        if (!alreadyTaken) {
            wcout << L"Ambil quest ini? (y/n) ✦: ";
            char confirm;
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirm == 'y' || confirm == 'Y') {
                selectedQuest.taken = true;

                
                ActiveDailyQuestNode* newNode = new ActiveDailyQuestNode();
                newNode->data = selectedQuest;
                newNode->data.taken = true;
                newNode->data.completed = false;
                newNode->next = nullptr;

                if (!activeDailyQuestsHead) {
                    activeDailyQuestsHead = newNode;
                } else {
                    ActiveDailyQuestNode* last = activeDailyQuestsHead;
                    while (last->next != nullptr) last = last->next;
                    last->next = newNode;
                }

                delayPrint(L"✓ Quest '" + utf8_to_wstring(selectedQuest.title) + L"' berhasil diambil!", 20);
            }
        } else {
            delayPrint(L"Kamu sudah mengambil quest ini dan sedang aktif.", 20);
        }

        waitForEnter();
    }
}



void showActiveQuestsInDiary() {
    bool stayInQuestView = true; 
    ActiveDailyQuestNode* selectedNode = nullptr; 

    while (stayInQuestView) {
        system("cls");
        printLine();
        centerText(L"✦✦✦ QUEST AKTIF ✦✦✦");
        printLine();

        if (activeDailyQuestsHead == nullptr) {
            wcout << L"Belum ada quest aktif yang diambil." << endl;
            printLine();
            waitForEnter();
            stayInQuestView = false; 
            break; 
        }

        vector<ActiveDailyQuestNode*> activeNodes; 
        ActiveDailyQuestNode* current = activeDailyQuestsHead;
        int i = 0;
        while (current != nullptr) {
            wcout << L"❖ " << i + 1 << L". " << utf8_to_wstring(current->data.title);
            if (current->data.completed) {
                wcout << L" [✅ Selesai]";
            } else if (current->data.taken) { 
                wcout << L" [⏳ Berlangsung]";
            }
            wcout << endl;
            activeNodes.push_back(current); 
            current = current->next;
            i++;
        }

        printLine();
        wcout << L"Pilih nomor quest untuk detail, atau 0 untuk kembali ke Diary Menu: ";
        int qsel;
        cin >> qsel;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            delayPrint(L"Pilihan tidak valid. Masukkan angka.", 20);
            waitForEnter();
            continue; 
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        if (qsel == 0) {
            stayInQuestView = false; 
            break;
        }

        if (qsel > 0 && (size_t)qsel <= activeNodes.size()) {
            selectedNode = activeNodes[qsel - 1]; 

            
            system("cls");
            printLine();
            centerText(L"✦ DETAIL QUEST DIARY ✦");
            printLine();
            wcout << L"✦ Judul     : " << utf8_to_wstring(selectedNode->data.title) << endl;
            wcout << L"✦ Deskripsi : " << utf8_to_wstring(selectedNode->data.description) << endl;
            wcout << L"✦ Target    : " << utf8_to_wstring(selectedNode->data.target);
            if (selectedNode->data.type == "kill" && selectedNode->data.dungeonFloor > 0 && !selectedNode->data.dungeonName.empty()) {
                 wcout << L" (di " << utf8_to_wstring(selectedNode->data.dungeonName) << L" Lt." << formatDungeonFloor(allDungeons[selectedNode->data.dungeonName],selectedNode->data.dungeonFloor) << L")";
            } else if (selectedNode->data.type == "travel" && selectedNode->data.dungeonFloor > 0 && !selectedNode->data.dungeonName.empty()) {
                 wcout << L" (Area: " << utf8_to_wstring(selectedNode->data.dungeonName) << L", Lantai: " << formatDungeonFloor(allDungeons[selectedNode->data.dungeonName],selectedNode->data.dungeonFloor) << L")";
            }
            wcout << endl;
            wcout << L"✦ Rank      : " << utf8_to_wstring(selectedNode->data.rank) << endl;
            wcout << L"✦ Hadiah    : " << selectedNode->data.expReward << L" EXP, " << selectedNode->data.goldReward << L" Gold" << endl;
            wcout << L"Status      : " << (selectedNode->data.completed ? L"✅ Selesai" : (selectedNode->data.taken ? L"⏳ Berlangsung" : L"Belum Diambil")) << endl;
            printLine();
            waitForEnter(L"Tekan Enter untuk kembali ke daftar quest aktif..."); 
            
        } else {
            delayPrint(L"Pilihan quest tidak valid.", 20);
            waitForEnter();
            
        }
    }
}






void loadEnemyASCIIFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        wcout << L"❌ Gagal membuka file ASCII enemy: " << utf8_to_wstring(filename).c_str() << endl;
        
        
        
        return;
    }

    string line;
    string currentNameKey = "";       
    vector<wstring> currentArtLines; 

    while (getline(file, line)) {
        string trimmedLineForTag = trim(line); 

        if (trimmedLineForTag.length() > 1 && trimmedLineForTag.front() == '[' && trimmedLineForTag.back() == ']') {
            

            
            if (!currentNameKey.empty() && !currentArtLines.empty()) {
                asciiArtMap[currentNameKey] = currentArtLines;
                
            }

            
            currentArtLines.clear(); 
            string extractedName = trimmedLineForTag.substr(1, trimmedLineForTag.length() - 2);
            currentNameKey = trim(extractedName); 
            

        } else { 
            
            if (!currentNameKey.empty()) { 
                
                
                
                
                currentArtLines.push_back(utf8_to_wstring(line));
            }
            
            
        }
    }

    
    if (!currentNameKey.empty() && !currentArtLines.empty()) {
        asciiArtMap[currentNameKey] = currentArtLines;
        
    }

    file.close();
    
}

void displayEnemyASCII(const string& enemyName) {
    const int totalWidth = 100;
    if (asciiArtMap.count(enemyName)) {
        for (const auto& line : asciiArtMap[enemyName]) {
            int padding = (totalWidth - static_cast<int>(line.length())) / 2;
            wcout << wstring(max(0, padding), L' ') << line << endl;
        }
    } else {
        centerText(L"(⚠ ASCII musuh tidak ditemukan)", totalWidth);
    }
}


void processEndOfPlayerTurn(Character& character) {
    for (auto it = character.activeEnchantments.begin(); it != character.activeEnchantments.end(); ) {
        it->remainingTurns--;
        if (it->remainingTurns <= 0) {
            delayPrint(L"Efek '" + utf8_to_wstring(it->spellName) + L"' telah berakhir.", 20);
            it = character.activeEnchantments.erase(it);
        } else {
            ++it;
        }
    }
}


void drawBattleScreen(const Enemy& enemy, const Character& character, const vector<wstring>& battleLog) {
    const int totalWidth = 100;
    system("cls");

    
    wcout << L"╔" << wstring(totalWidth - 2, L'═') << L"╗" << endl;
    centerText(L"✦✦✦  PERTARUNGAN DIMULAI  ✦✦✦", totalWidth);
    wcout << L"╚" << wstring(totalWidth - 2, L'═') << L"╝" << endl;

    
    wcout << L"👤 Kamu  ♥ HP: " << character.hp << L"/" << character.maxHp
          << L"  ♦ Mana: " << character.mana << L"/" << character.maxMana
          << setw(15) << L""
          << L"☠ " << utf8_to_wstring(enemy.name)
          << L"  ♥ HP: " << enemy.hp << L"/" << enemy.maxHp << endl;

    
    if (!character.activeEnchantments.empty()) {
        wcout << L"  🔮 Buffs: ";
        for (size_t i = 0; i < character.activeEnchantments.size(); ++i) {
            wcout << utf8_to_wstring(character.activeEnchantments[i].spellName)
                  << L"(" << character.activeEnchantments[i].remainingTurns << L")";
            if (i < character.activeEnchantments.size() - 1) wcout << L", ";
        }
        wcout << endl;
    }

    
    displayEnemyASCII(enemy.name);

    
    wcout << L"╟" << wstring(totalWidth - 2, L'─') << L"╢" << endl;
    if (battleLog.empty()) {
        centerText(L"» Apa yang ingin kamu lakukan?", totalWidth);
    } else {
        for (const auto& line : battleLog) {
            centerText(L"» " + line, totalWidth);
        }
    }

    
    wcout << L"╟" << wstring(totalWidth - 2, L'─') << L"╢" << endl;
    centerText(L"❖ 1. ⚔ Serang   ❖ 2. ✹ Magic   ❖ 3. ⊕ Item   ❖ 4. 🛡 Bertahan   ❖ 5. ➤ Kabur", totalWidth);
    printLine();
}

void processPlayerHoTs(Character& character, vector<wstring>& battleLogMessages) {
    if (!character.activeHoTs.empty()) {
        bool processedHot = false;
        for (auto it = character.activeHoTs.begin(); it != character.activeHoTs.end(); ) {
            if (character.hp < character.maxHp) { 
                int actualHeal = min(it->healPerTurn, character.maxHp - character.hp);
                character.hp += actualHeal;
                if (!processedHot) { 
                     battleLogMessages.push_back(L"-- Regenerasi HP Aktif --");
                     processedHot = true;
                }
                battleLogMessages.push_back(L"✨ " + utf8_to_wstring(it->spellName) + L" memulihkan " + to_wstring(actualHeal) + L" HP.");
            }
            it->remainingTurns--;
            if (it->remainingTurns <= 0) {
                battleLogMessages.push_back(L"Efek regenerasi " + utf8_to_wstring(it->spellName) + L" berakhir.");
                it = character.activeHoTs.erase(it);
            } else {
                ++it;
            }
        }
    }
}


void processEndOfPlayerTurn(Character& character, vector<wstring>& battleLogMessages) { 
    
    for (auto it = character.activeEnchantments.begin(); it != character.activeEnchantments.end(); ) {
        it->remainingTurns--;
        if (it->remainingTurns <= 0) {
            wstring enchEndLog = L"Efek '" + utf8_to_wstring(it->spellName) + L"' telah berakhir.";
            delayPrint(enchEndLog, 20); 
            battleLogMessages.push_back(enchEndLog);
            it = character.activeEnchantments.erase(it);
        } else {
            ++it;
        }
    }
    
    processPlayerHoTs(character, battleLogMessages); 
}



BattleResult startBattle(Enemy& baseEnemy, const string& currentDungeonName = "") {
    Enemy enemy = baseEnemy;
    
    enemy.isStunned = false; enemy.stunDuration = 0;
    enemy.attackDebuffValue = 0; enemy.attackDebuffDuration = 0;
    enemy.accuracyDebuffValue = 0; enemy.accuracyDebuffDuration = 0;
    enemy.physicalDefenseDebuffValue = 0; enemy.physicalDefenseDebuffDuration = 0;
    enemy.magicDefenseDebuffValue = 0; enemy.magicDefenseDebuffDuration = 0;
    enemy.isFeared = false; enemy.fearDuration = 0;
    enemy.isSilenced = false; enemy.silenceDuration = 0;
    enemy.activeDoTs.clear();
    enemy.activeRunes.clear();

    system("cls");
    vector<wstring> battleLogMessages;
    bool playerRevivedThisBattle = false; 

    while (player.hp > 0 && enemy.hp > 0) {
        battleLogMessages.clear();

        
        if (enemy.hp > 0) {
            bool processedPersistentEffectHeader = false;
            
            if (!enemy.activeDoTs.empty()) {
                for (auto it = enemy.activeDoTs.begin(); it != enemy.activeDoTs.end(); ) {
                    if (it->remainingTurns > 0) {
                        if (!processedPersistentEffectHeader) { battleLogMessages.push_back(L"--- Efek Berkelanjutan pada Musuh ---"); processedPersistentEffectHeader = true; }
                        int dotDamage = it->damagePerTurn;
                        enemy.hp -= dotDamage;
                        battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" menerima " + to_wstring(dotDamage) + L" " + utf8_to_wstring(it->elementType) + L" damage dari " + it->spellName + L".");
                        it->remainingTurns--;
                        if (it->remainingTurns <= 0) { battleLogMessages.push_back(L"Efek " + it->spellName + L" pada " + utf8_to_wstring(enemy.name) + L" berakhir."); it = enemy.activeDoTs.erase(it); }
                        else { ++it; }
                    } else { it = enemy.activeDoTs.erase(it); }
                }
            }
            
            if (!enemy.activeRunes.empty()) {
                for (auto it = enemy.activeRunes.begin(); it != enemy.activeRunes.end(); ) {
                    it->turnsUntilTrigger--;
                    if (it->turnsUntilTrigger <= 0) {
                        if (!processedPersistentEffectHeader) { battleLogMessages.push_back(L"--- Rune Meledak! ---"); processedPersistentEffectHeader = true; }
                        int runeDamage = it->damageOnTrigger;
                        enemy.hp -= runeDamage;
                        battleLogMessages.push_back(L"💥 Rune " + utf8_to_wstring(it->spellName) + L" meledak pada " + utf8_to_wstring(enemy.name) + L", " + to_wstring(runeDamage) + L" " + utf8_to_wstring(it->elementType) + L" damage!");
                        it = enemy.activeRunes.erase(it);
                    } else {
                        battleLogMessages.push_back(L"  ⏳ Rune " + utf8_to_wstring(it->spellName) + L" akan meledak dalam " + to_wstring(it->turnsUntilTrigger) + L" giliran.");
                        ++it;
                    }
                }
            }
            if (enemy.hp <= 0) { enemy.hp = 0; }
        }
        if (enemy.hp <= 0) break;

        drawBattleScreen(enemy, player, battleLogMessages);
        battleLogMessages.clear();

        int choice;
        wcout << L"Aksi ✦: ";
        choice = getValidatedChoice(1, 5); 

        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); choice = 99; }

        
        int playerBaseAttackPower = player.strength + player.temporaryStrengthBuff + (player.equippedWeapon ? player.equippedWeapon->attackPower : 0);
        int totalPlayerAttackBonus = 0, totalPlayerDefenseBonus = 0, totalPlayerEvasionBonus = 0, totalPlayerIntelligenceBonus = 0, totalPlayerAgilityBonus = 0;
        double totalPlayerCritChanceBonus = 0.0;
        bool playerIsPhysicallyImmune = false;
        int playerRetaliateDamage = 0;

        for (const auto& ench : player.activeEnchantments) {
            totalPlayerAttackBonus += ench.attackBonus;
            totalPlayerDefenseBonus += ench.defenseBonus;
            totalPlayerEvasionBonus += ench.evasionBonus;
            totalPlayerIntelligenceBonus += ench.intelligenceBonus;
            totalPlayerAgilityBonus += ench.agilityBonus;
            totalPlayerCritChanceBonus += ench.criticalChanceBonus;
            if (ench.isPhysicallyImmune) playerIsPhysicallyImmune = true;
            if (ench.retaliateDamage > 0) playerRetaliateDamage = max(playerRetaliateDamage, ench.retaliateDamage);
        }
        int finalPlayerAttackPower = playerBaseAttackPower + totalPlayerAttackBonus;
        int finalPlayerDefense = player.defense + totalPlayerDefenseBonus;
        int finalPlayerAgility = player.agility + totalPlayerAgilityBonus;
        int finalPlayerEvasion = finalPlayerAgility + totalPlayerEvasionBonus;
        int finalPlayerIntelligence = player.intelligence + player.temporaryIntelligenceBuff + totalPlayerIntelligenceBonus;

        double finalPlayerCritChance = 0.05 + totalPlayerCritChanceBonus; 

        
        int currentEnemyAttack = enemy.attack;
        if (enemy.attackDebuffDuration > 0) { currentEnemyAttack = max(0, enemy.attack - enemy.attackDebuffValue); }
        int finalEnemyPhysicalDefense = max(0, enemy.defense - enemy.physicalDefenseDebuffValue);
        int finalEnemyMagicDefense = max(0, enemy.magicDefense - enemy.magicDefenseDebuffValue);

        int baseDamageToPlayer = max(0, currentEnemyAttack - finalPlayerDefense);
        int enemyBaseAccuracy = 95;
        int enemyHitChance = max(40, min(95, enemyBaseAccuracy - finalPlayerEvasion - enemy.accuracyDebuffValue));

        wstring turnActionLog;

        switch (choice) {
            case 1: { 
                bool isCriticalHit = (rand() % 100 < (finalPlayerCritChance * 100));
                int damageToEnemy = max(0, finalPlayerAttackPower - finalEnemyPhysicalDefense);
                if (isCriticalHit) {
                    damageToEnemy = static_cast<int>(damageToEnemy * 1.5);
                    battleLogMessages.push_back(L"✨ CRITICAL HIT! ✨");
                }
                enemy.hp -= damageToEnemy;
                turnActionLog = L"➤ Kamu menyerang " + utf8_to_wstring(enemy.name) + L"! Damage: " + to_wstring(damageToEnemy);
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);

                if (totalPlayerAttackBonus > 0) { battleLogMessages.push_back(L"  (Bonus ATK dari enchantment: +" + to_wstring(totalPlayerAttackBonus) + L")"); }

                
                for(const auto& ench : player.activeEnchantments) {
                    if (ench.spellId == "THUNDER_MJOLNIR_AWAKENING_3" && !enemy.isStunned && rand() % 100 < 30) {
                        enemy.isStunned = true; enemy.stunDuration = 1;
                        battleLogMessages.push_back(L"  ⚡ Palu Mjolnir menyetrum " + utf8_to_wstring(enemy.name) + L" (STUN)!");
                    }
                    if (ench.spellId == "DARK_SOUL_EATER_WEAPON_2" && rand() % 100 < 40) {
                        int mpDrained = 5 + finalPlayerIntelligence / 10;
                        player.mana = min(player.maxMana, player.mana + mpDrained);
                        battleLogMessages.push_back(L"  ☠ Senjata Pemakan Jiwa menyerap " + to_wstring(mpDrained) + L" MP untukmu!");
                    }
                    if (ench.spellId == "ICE_FROSTBITE_WEAPON_2" && rand() % 100 < 50) {
                        bool dotExists = false; int dotDmg = 5 + finalPlayerIntelligence / 8;
                        for (auto& dot : enemy.activeDoTs) {
                            if (dot.spellId == ench.spellId + "_HIT") { dot.remainingTurns = 2; dot.damagePerTurn = dotDmg; dotExists = true; battleLogMessages.push_back(L"  ❄️ Efek Frostbite diperbarui!"); break; }
                        }
                        if (!dotExists) { enemy.activeDoTs.push_back({ench.spellId + "_HIT", utf8_to_wstring(ench.spellName) + L" (Gigitan Dingin)", "Ice", dotDmg, 2}); battleLogMessages.push_back(L"  ❄️ Seranganmu menyebabkan Frostbite!"); }
                    }
                }
                break;
            }
            case 2: { 
                if (player.knownSpells.empty()) {
                    battleLogMessages.push_back(L"Kamu tidak tahu spell apapun!");
                    continue; 
                }

                wcout << L"\n═════════════════════════════════════════════════════════════\n";
                wcout << L"                  ✹✹✹ PILIHAN MAGIC ✹✹✹                     \n";
                wcout << L"═════════════════════════════════════════════════════════════\n";
                int spellIdx_display = 1;
                vector<const MagicSpell*> displayedSpells_battle; 

                for (const string& spellId : player.knownSpells) {
                    const MagicSpell* spell = getSpellDetails(spellId); 
                    if (spell) {
                        displayedSpells_battle.push_back(spell); 
                        wcout << L" " << setw(2) << left << spellIdx_display++ << L". ✧ " << padRight(utf8_to_wstring(spell->name), 25)
                              << L" ✦ MP: " << setw(3) << spell->manaCost;
                        if (player.mana < spell->manaCost) {
                            wcout << L" [✖ MP Kurang]";
                        }
                        wcout << endl;
                    }
                }
                wcout << L"─────────────────────────────────────────────────────────────\n";
                wcout << L"  0. ❌ Batal\n";
                wcout << L"─────────────────────────────────────────────────────────────\n";
                wcout << L"Pilih magic ✦: ";

                int magicChoice_input;
                cin >> magicChoice_input;

                if (cin.fail() || magicChoice_input < 0 || magicChoice_input > displayedSpells_battle.size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    battleLogMessages.push_back(L"Pilihan magic tidak valid.");
                    
                    break;    
                }
                if (magicChoice_input == 0) { 
                    
                    break;    
                }

                
                const MagicSpell* chosenSpell = displayedSpells_battle[magicChoice_input - 1];

                if (chosenSpell && player.mana >= chosenSpell->manaCost) {
                    player.mana -= chosenSpell->manaCost;
                    
                    turnActionLog = L"➤ Kamu menggunakan " + utf8_to_wstring(chosenSpell->name) + L"!";
                    delayPrint(turnActionLog, 20); 
                    battleLogMessages.push_back(turnActionLog); 

                    
                       if (chosenSpell->isEnchantment) {
                            bool alreadyActive = false; int enchIndex = -1;
                            for(size_t i=0; i < player.activeEnchantments.size(); ++i){ if(player.activeEnchantments[i].spellId == chosenSpell->id){ enchIndex = i; alreadyActive = true; break; }}
                            ActiveEnchantment newEnch(chosenSpell->id, chosenSpell->name, chosenSpell->enchantTurns, chosenSpell->enchantAttackBonus);
                            
                            if(chosenSpell->id == "FIRE_FLAME_WEAPON_1") newEnch.attackBonus = 8; 
                            else if(chosenSpell->id == "ICE_ICY_EDGE_1") newEnch.attackBonus = 9;
                            else if(chosenSpell->id == "THUNDER_CHARGE_WEAPON_1") newEnch.attackBonus = 9;
                            else if(chosenSpell->id == "WIND_AERO_BLADE_1") newEnch.attackBonus = 7;
                            else if(chosenSpell->id == "DARK_INFUSED_BLADE_1") newEnch.attackBonus = 8;
                            else if(chosenSpell->id == "LIGHT_RADIANT_WEAPON_1") newEnch.attackBonus = 7;
                            else if(chosenSpell->id == "THUNDER_VOLTAIC_EDGE_2") { newEnch.attackBonus = 20; newEnch.agilityBonus = 10 + finalPlayerAgility/15; }
                            else if(chosenSpell->id == "WIND_TEMPEST_BLADES_2") { newEnch.attackBonus = 19; newEnch.agilityBonus = 8 + finalPlayerAgility/18;}
                            else if(chosenSpell->id == "DARK_SOUL_EATER_WEAPON_2") newEnch.attackBonus = 15; 
                            else if(chosenSpell->id == "LIGHT_DIVINE_EDGE_2") { newEnch.attackBonus = 22; newEnch.defenseBonus = 5 + player.level/5; }
                            else if(chosenSpell->id == "THUNDER_MJOLNIR_AWAKENING_3") newEnch.attackBonus = 50; 
                            else if(chosenSpell->id == "WIND_SKY_LORDS_WRATH_3") { newEnch.attackBonus = 48; newEnch.criticalChanceBonus = 0.15 + (double)finalPlayerAgility / 150.0; battleLogMessages.push_back(L"  🌪️ Seranganmu menjadi lebih mematikan!");}

                            else if(chosenSpell->id == "ICE_FROST_ARMOR_1") newEnch.defenseBonus = 10;
                            else if(chosenSpell->id == "LIGHT_BARRIER_OF_FAITH_2") newEnch.defenseBonus = 20;
                            else if(chosenSpell->id == "ICE_GLACIAL_ARMOR_2") newEnch.defenseBonus = 25;
                            else if(chosenSpell->id == "WIND_FEATHER_STEP_1") newEnch.evasionBonus = 10;
                            else if(chosenSpell->id == "DARK_SHROUD_1") newEnch.evasionBonus = 15;
                            else if(chosenSpell->id == "WIND_CYCLONE_SHIELD_2") { newEnch.defenseBonus = 10; newEnch.evasionBonus = 10; }
                            else if(chosenSpell->id == "FIRE_BLAZING_SOUL_2") { newEnch.intelligenceBonus = 10 + finalPlayerIntelligence/10; battleLogMessages.push_back(L"  🔥 Kekuatan sihir apimu bergelora!");}
                            else if(chosenSpell->id == "THUNDER_QUICKEN_REFLEX_1") { newEnch.agilityBonus = 8 + finalPlayerAgility/10; newEnch.evasionBonus = 5 + finalPlayerAgility/20; battleLogMessages.push_back(L"  ⚡ Refleksmu menajam!");}
                            else if(chosenSpell->id == "THUNDER_SPEED_OF_LIGHTNING_2") { newEnch.agilityBonus = 15 + finalPlayerAgility/8; newEnch.evasionBonus = 10 + finalPlayerAgility/15; battleLogMessages.push_back(L"  ⚡ Kecepatanmu meningkat drastis!");}
                            else if(chosenSpell->id == "WIND_GALE_STEP_3") { newEnch.agilityBonus = 12 + finalPlayerAgility/8; newEnch.evasionBonus = 15 + finalPlayerAgility/10; battleLogMessages.push_back(L"  🌬️ Gerakanmu secepat badai!");}
                            else if(chosenSpell->id == "LIGHT_BLESS_1") { newEnch.attackBonus += (3 + player.level/6); newEnch.defenseBonus = (3+player.level/6); newEnch.intelligenceBonus = (3+player.level/6); newEnch.agilityBonus = (3+player.level/6); newEnch.evasionBonus =(2+player.level/8); battleLogMessages.push_back(L"  🌟 Berkat Cahaya menyelimutimu!");}
                            else if (chosenSpell->id == "DARK_FORM_OF_THE_VOID_3") { newEnch.isPhysicallyImmune = true; battleLogMessages.push_back(L"  🌑 Kamu berubah menjadi makhluk bayangan, kebal serangan fisik!"); }
                            else if (chosenSpell->id == "ICE_WINTERS_MANTLE_3") { newEnch.defenseBonus = 30; newEnch.retaliateDamage = 10 + finalPlayerIntelligence / 4; battleLogMessages.push_back(L"  ❄️ Mantel Musim Dingin melindungimu dan membalas penyerang!");}
                            else if (chosenSpell->id == "WIND_EYE_OF_THE_STORM_3") { newEnch.evasionBonus = 25; newEnch.retaliateDamage = 8 + finalPlayerAgility / 4; battleLogMessages.push_back(L"  🌀 Kamu dikelilingi Mata Badai!");}
                            else if (chosenSpell->id == "FIRE_PHOENIX_BLESSING_3") { newEnch.hasRevive = true; battleLogMessages.push_back(L"  🔥 Berkat Phoenix memberimu kesempatan kedua!");}
                            else if (chosenSpell->id == "LIGHT_GUARDIAN_ANGEL_3") { newEnch.shieldHp = 75 + finalPlayerIntelligence * 2; battleLogMessages.push_back(L"  🛡️ Perisai Malaikat Pelindung aktif!"); }
                            else if (chosenSpell->id == "LIGHT_CELESTIAL_AEGIS_3") { newEnch.shieldHp = 100 + finalPlayerIntelligence * 2.5; battleLogMessages.push_back(L"  🛡️ Aegis Surgawi melindungimu!"); }
                            else if (chosenSpell->id == "ICE_ICE_CLONE_2") {newEnch.evasionBonus = 15 + finalPlayerAgility/10; battleLogMessages.push_back(L"  ❄️ Klon es meningkatkan evasionmu!");}
                            else if (chosenSpell->id == "THUNDER_RIDE_THE_LIGHTNING_3") {newEnch.evasionBonus = 30 + finalPlayerAgility/5; newEnch.agilityBonus = 20 + finalPlayerAgility/5; battleLogMessages.push_back(L"  ⚡ Kamu bergerak secepat kilat!");}


                            if(alreadyActive && enchIndex != -1) { player.activeEnchantments[enchIndex] = newEnch; battleLogMessages.push_back(L"  Durasi " + utf8_to_wstring(chosenSpell->name) + L" diperbarui!");}
                            else { player.activeEnchantments.push_back(newEnch); /*Pesan sudah ditambahkan di atas*/ }

                            if (chosenSpell->id == "FIRE_PHOENIX_BLESSING_3" || chosenSpell->id == "LIGHT_SANCTUARY_3" || chosenSpell->id == "LIGHT_CELESTIAL_AEGIS_3") {
                                int healVal=0; if(chosenSpell->id == "FIRE_PHOENIX_BLESSING_3") healVal = 10 + finalPlayerIntelligence/5; if(chosenSpell->id == "LIGHT_SANCTUARY_3") healVal = 15 + finalPlayerIntelligence/4; if(chosenSpell->id == "LIGHT_CELESTIAL_AEGIS_3") healVal = (newEnch.shieldHp > 0 ? 10 : 20) + finalPlayerIntelligence/4;
                                bool hotExists = false; for(auto& hot : player.activeHoTs) if(hot.spellId == chosenSpell->id) {hot.remainingTurns = chosenSpell->enchantTurns; hot.healPerTurn=healVal; hotExists=true; battleLogMessages.push_back(L"  ✨ Regenerasi " + utf8_to_wstring(chosenSpell->name) + L" diperbarui!"); break;}
                                if(!hotExists && healVal > 0) {player.activeHoTs.push_back({chosenSpell->id, chosenSpell->name, healVal, chosenSpell->enchantTurns}); battleLogMessages.push_back(L"  ✨ Kamu merasakan energi penyembuhan berkala!");}
                            }

                        } else { 
                            float defenseMultiplier = 1.0f;
                            if (chosenSpell->id == "DARK_OBLITERATION_RAY_3") { defenseMultiplier = 0.3f; battleLogMessages.push_back(L"  💥 Sinar Pemusnahan menembus pertahanan sihir!"); }
                            int baseMagicDmgCalc = chosenSpell->basePower + finalPlayerIntelligence + player.level * 1.5;
                            int effectiveEnemyMagicDefense = static_cast<int>(finalEnemyMagicDefense * defenseMultiplier);
                            int magicDamage = max(0, (int)(baseMagicDmgCalc - effectiveEnemyMagicDefense));

                            if (chosenSpell->targetType == "SingleEnemy" || chosenSpell->targetType == "AllEnemies") {
                                if (chosenSpell->basePower > 0 || chosenSpell->id == "DARK_CURSE_OF_FATIGUE_1" || chosenSpell->id == "FIRE_SCORCHING_HAZE_1" || chosenSpell->id == "WIND_DISORIENTING_GUST_2" || chosenSpell->id == "THUNDER_MAGNETIC_OVERLOAD_2" || chosenSpell->id == "DARK_CURSE_OF_VULNERABILITY_2" || chosenSpell->id == "ICE_CRYSTAL_PRISON_3" || chosenSpell->id == "WIND_SILENCING_GUST_2" || chosenSpell->id == "FIRE_EXPLOSIVE_RUNE_2") {
                                    if (chosenSpell->basePower > 0) {
                                        int bonusDamage = 0;
                                        if ((chosenSpell->id == "LIGHT_SACRED_FLAME_1" || chosenSpell->id == "LIGHT_SMITE_2" || chosenSpell->id == "LIGHT_JUDGEMENT_DAY_3") && (enemy.enemyType == "Undead" || enemy.enemyType == "Dark")) {
                                            bonusDamage = static_cast<int>(baseMagicDmgCalc * 0.5); battleLogMessages.push_back(L"  ✨ Sangat efektif melawan " + utf8_to_wstring(enemy.enemyType) + L"!");
                                        }
                                        int totalDamageToEnemy = magicDamage + bonusDamage;
                                        if (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" || chosenSpell->id == "WIND_ZEPHYRS_DANCE_3") { 
                                            int hits = (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" ? (2 + rand()%3) : (3 + rand()%2) ); 
                                            int damagePerHitCalc = (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" ? chosenSpell->basePower + finalPlayerIntelligence/2 : chosenSpell->basePower/2 + finalPlayerIntelligence/3);
                                            int damagePerHit = max(0,(int)(damagePerHitCalc - effectiveEnemyMagicDefense));
                                            totalDamageToEnemy = 0;
                                            battleLogMessages.push_back(L"  " + utf8_to_wstring(chosenSpell->name) + L" mengenai " + to_wstring(hits) + L" kali!");
                                            for(int i=0; i<hits; ++i) { enemy.hp -= damagePerHit; totalDamageToEnemy += damagePerHit; battleLogMessages.push_back(L"    ↳ Serangan ke-" + to_wstring(i+1) + L": " + to_wstring(damagePerHit) + L" damage!"); if(enemy.hp <= 0) break;}
                                            magicDamage = totalDamageToEnemy; 
                                        } else { enemy.hp -= totalDamageToEnemy; battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" terkena " + to_wstring(totalDamageToEnemy) + L" magic damage!");}
                                    if (totalDamageToEnemy > 0 && !(chosenSpell->id == "FIRE_IGNITE_1" || chosenSpell->id == "THUNDER_STATIC_FIELD_1" /*spell DoT murni lainnya*/)) {
                                        enemy.hp -= totalDamageToEnemy; 
                                        battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" terkena " + to_wstring(totalDamageToEnemy) + L" " + utf8_to_wstring(chosenSpell->elementType) + L" damage!");
                                    } else if (totalDamageToEnemy == 0 && chosenSpell->basePower > 0) {
                                        battleLogMessages.push_back(L"  Serangan " + utf8_to_wstring(chosenSpell->name) + L" tidak memberikan damage (mungkin di-resist atau defense terlalu tinggi).");
                            }
                                    }
                                
                                bool applyStun = false; int stunTurns = 1;
                                if (chosenSpell->id == "ICE_FROZEN_LANCE_2" && rand() % 100 < 50) { applyStun = true; stunTurns = 1;}
                                else if (chosenSpell->id == "THUNDER_THUNDERCLAP_2" && rand() % 100 < 70) { applyStun = true; stunTurns = 1;}
                                else if (chosenSpell->id == "ICE_DEEP_FREEZE_2" && rand() % 100 < 60) { applyStun = true; stunTurns = 2;}
                                else if (chosenSpell->id == "ICE_DIAMOND_DUST_3" && rand() % 100 < 75) { applyStun = true; stunTurns = 1;}
                                else if (chosenSpell->id == "ICE_ABSOLUTE_ZERO_3" && rand() % 100 < 85) { applyStun = true; stunTurns = 2; battleLogMessages.push_back(L"  ❄❄❄ " + utf8_to_wstring(enemy.name) + L" membeku total!");}
                                else if (chosenSpell->id == "ICE_CRYSTAL_PRISON_3") { applyStun = true; stunTurns = 3; battleLogMessages.push_back(L"  ❄️⛓ " + utf8_to_wstring(enemy.name) + L" terperangkap!"); enemy.physicalDefenseDebuffValue = 25 + finalPlayerIntelligence/7; enemy.physicalDefenseDebuffDuration = stunTurns; battleLogMessages.push_back(L"  ❄️ Pertahanan fisiknya hancur!");}
                                else if (chosenSpell->id == "THUNDER_LIGHTNING_STRIKE_2" && rand() % 100 < 40) { applyStun = true; stunTurns = 1;}
                                else if (chosenSpell->id == "THUNDER_JUDGEMENT_BOLT_3" && rand() % 100 < 90) { applyStun = true; stunTurns = 2; battleLogMessages.push_back(L"  ⚡⚡ " + utf8_to_wstring(enemy.name) + L" tersambar Petir Penghakiman!");}

                                if (applyStun && !enemy.isStunned) { enemy.isStunned = true; enemy.stunDuration = stunTurns; battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" terkena STUN (" + to_wstring(stunTurns) + L" giliran)!");}
                                else if (applyStun && enemy.isStunned) { battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" sudah STUN.");}
                                

                                
                                if (chosenSpell->id == "DARK_NIGHTMARE_BLAST_2" && !enemy.isFeared && rand()%100 < 40) { 
                                    enemy.isFeared = true; enemy.fearDuration = 2; 
                                    battleLogMessages.push_back(L"  👻 " + utf8_to_wstring(enemy.name) + L" diliputi ketakutan!");
                                }
                                
                                if (chosenSpell->id == "WIND_SILENCING_GUST_2" && !enemy.isSilenced && rand()%100 < 60) { 
                                    enemy.isSilenced = true; enemy.silenceDuration = 2; 
                                    battleLogMessages.push_back(L"  🔇 " + utf8_to_wstring(enemy.name) + L" terkena Silence!");
                                }
                                
                                if (chosenSpell->id == "DARK_CURSE_OF_FATIGUE_1") {
                                    enemy.attackDebuffValue = max(enemy.attackDebuffValue, 5 + finalPlayerIntelligence/10); 
                                    enemy.attackDebuffDuration = max(enemy.attackDebuffDuration, 3); 
                                    battleLogMessages.push_back(L"  ⚔ Serangan " + utf8_to_wstring(enemy.name) + L" melemah!");
                                }
                                
                                if (chosenSpell->id == "FIRE_SCORCHING_HAZE_1") {
                                    enemy.accuracyDebuffValue = max(enemy.accuracyDebuffValue, 15 + finalPlayerIntelligence / 10);
                                    enemy.accuracyDebuffDuration = max(enemy.accuracyDebuffDuration, 3);
                                    battleLogMessages.push_back(L"  ♨️ Kabut panas mengganggu pandangan " + utf8_to_wstring(enemy.name) + L"!");
                                } else if (chosenSpell->id == "WIND_DISORIENTING_GUST_2" || chosenSpell->id == "DARK_ETERNAL_NIGHT_CURSE_3") {
                                    int accDebuffVal = (chosenSpell->id == "WIND_DISORIENTING_GUST_2" ? 20 : 25) + finalPlayerIntelligence / 10;
                                    int accDebuffDur = (chosenSpell->id == "WIND_DISORIENTING_GUST_2" ? 2 : 4);
                                    enemy.accuracyDebuffValue = max(enemy.accuracyDebuffValue, accDebuffVal);
                                    enemy.accuracyDebuffDuration = max(enemy.accuracyDebuffDuration, accDebuffDur);
                                    battleLogMessages.push_back(L"  🌬️ " + utf8_to_wstring(enemy.name) + L" kesulitan melihat dengan jelas!");
                                }
                                
                                if (chosenSpell->id == "THUNDER_MAGNETIC_OVERLOAD_2" || chosenSpell->id == "THUNDER_SKY_SOVEREIGNS_FURY_3") {
                                    int mDefDebuffVal = (chosenSpell->id == "THUNDER_MAGNETIC_OVERLOAD_2" ? 15 : 20) + finalPlayerIntelligence / 8;
                                    int mDefDebuffDur = (chosenSpell->id == "THUNDER_MAGNETIC_OVERLOAD_2" ? 3 : 4);
                                    enemy.magicDefenseDebuffValue = max(enemy.magicDefenseDebuffValue, mDefDebuffVal);
                                    enemy.magicDefenseDebuffDuration = max(enemy.magicDefenseDebuffDuration, mDefDebuffDur);
                                    battleLogMessages.push_back(L"  🧲 Pertahanan sihir " + utf8_to_wstring(enemy.name) + L" melemah!");
                                    if (chosenSpell->id == "THUNDER_SKY_SOVEREIGNS_FURY_3") { 
                                        enemy.physicalDefenseDebuffValue = max(enemy.physicalDefenseDebuffValue, 15 + finalPlayerIntelligence / 8);
                                        enemy.physicalDefenseDebuffDuration = max(enemy.physicalDefenseDebuffDuration, 4);
                                    }
                                } else if (chosenSpell->id == "DARK_CURSE_OF_VULNERABILITY_2" || chosenSpell->id == "DARK_ETERNAL_NIGHT_CURSE_3") {
                                    enemy.physicalDefenseDebuffValue = max(enemy.physicalDefenseDebuffValue, (chosenSpell->id == "DARK_CURSE_OF_VULNERABILITY_2" ? 20 : 25) + finalPlayerIntelligence / 8);
                                    enemy.physicalDefenseDebuffDuration = max(enemy.physicalDefenseDebuffDuration, 4);
                                    enemy.magicDefenseDebuffValue = max(enemy.magicDefenseDebuffValue, (chosenSpell->id == "DARK_CURSE_OF_VULNERABILITY_2" ? 10 : 15) + finalPlayerIntelligence / 10);
                                    enemy.magicDefenseDebuffDuration = max(enemy.magicDefenseDebuffDuration, 4);
                                    battleLogMessages.push_back(L"  ☠️ " + utf8_to_wstring(enemy.name) + L" menjadi sangat rentan!");
                                    if (chosenSpell->id == "DARK_ETERNAL_NIGHT_CURSE_3") { 
                                        enemy.attackDebuffValue = max(enemy.attackDebuffValue, 10 + finalPlayerIntelligence/8);
                                        enemy.attackDebuffDuration = max(enemy.attackDebuffDuration, 4);
                                        battleLogMessages.push_back(L"  ☠️ Kekuatan dan kegesitannya juga menurun drastis!");
                                    }
                                }

                                
                                if (chosenSpell->id == "FIRE_IGNITE_1" || chosenSpell->id == "THUNDER_STATIC_FIELD_1" || chosenSpell->id == "FIRE_ENGULFING_FLAMES_2" || chosenSpell->id == "FIRE_VOLCANIC_ERUPTION_3" || chosenSpell->id == "WIND_TORNADO_OF_DESTRUCTION_3") {                                 bool dotExists = false;
                                int dotDmg = chosenSpell->basePower; 
                                int dotTurns = 3; 

                                if (chosenSpell->id == "FIRE_IGNITE_1") { dotDmg = 5 + finalPlayerIntelligence / 5; dotTurns = 3;}
                                else if (chosenSpell->id == "THUNDER_STATIC_FIELD_1") { dotDmg = 6 + finalPlayerIntelligence / 5; dotTurns = 4;}
                                else if (chosenSpell->id == "FIRE_ENGULFING_FLAMES_2") { dotDmg = (magicDamage > 0 ? magicDamage/3 : 10) + 8 + finalPlayerIntelligence/3; dotTurns = 3;}
                                else if (chosenSpell->id == "FIRE_VOLCANIC_ERUPTION_3") { dotDmg = (magicDamage > 0 ? magicDamage/3 : 15) + 12 + finalPlayerIntelligence/3; dotTurns = 4;}
                                else if (chosenSpell->id == "WIND_TORNADO_OF_DESTRUCTION_3") { dotDmg = (magicDamage > 0 ? magicDamage/3 : 20) + 15 + finalPlayerIntelligence/3; dotTurns = 3;}
                                else if (chosenSpell->id == "DARK_FIELD_OF_DESPAIR_3") { dotDmg = 10 + finalPlayerIntelligence/4; dotTurns = 4; /* MP Drain & stat debuff juga */ battleLogMessages.push_back(L"  Aura keputusasaan menguras MP musuh!"); }
                                else if (chosenSpell->id == "DARK_ETERNAL_NIGHT_CURSE_3") { dotDmg = 15 + finalPlayerIntelligence/4; dotTurns = 4; /* Efek lain sudah di atas */ }

                                for (auto& dot : enemy.activeDoTs) {
                                    if (dot.spellId == chosenSpell->id) { 
                                        dot.remainingTurns = max(dot.remainingTurns, dotTurns); 
                                        dot.damagePerTurn = max(dot.damagePerTurn, dotDmg);     
                                        dotExists = true;
                                        battleLogMessages.push_back(L"  Efek " + utf8_to_wstring(chosenSpell->name) + L" pada " + utf8_to_wstring(enemy.name) + L" diperkuat/diperbarui!");
                                        break;
                                    }
                                }
                                if (!dotExists) {
                                    enemy.activeDoTs.push_back({chosenSpell->id, utf8_to_wstring(chosenSpell->name), chosenSpell->elementType, dotDmg, dotTurns});
                                    battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" mulai menerima damage berkelanjutan dari " + utf8_to_wstring(chosenSpell->name) + L"!");
                                }
                            }
                                
                                if (chosenSpell->id == "FIRE_EXPLOSIVE_RUNE_2") { int runeDamage = chosenSpell->basePower + finalPlayerIntelligence/2; 
                                int runeTurns = 2 + rand()%2; 
                                bool runeExists = false;
                                for(auto& r : enemy.activeRunes) {
                                    if(r.spellId == chosenSpell->id) {
                                        r.turnsUntilTrigger = runeTurns; 
                                        r.damageOnTrigger = max(r.damageOnTrigger, runeDamage); 
                                        runeExists=true;
                                        battleLogMessages.push_back(L"  ⏳ Rune " + utf8_to_wstring(chosenSpell->name) + L" pada " + utf8_to_wstring(enemy.name) + L" diperbarui!");
                                        break;
                                    }
                                }
                                if(!runeExists) {
                                    enemy.activeRunes.push_back({chosenSpell->id, chosenSpell->name, chosenSpell->elementType, runeDamage, runeTurns});
                                    battleLogMessages.push_back(L"  ⏳ Rune " + utf8_to_wstring(chosenSpell->name) + L" ditanam pada " + utf8_to_wstring(enemy.name) + L"!");
                                }
                            }
                                
                                if (chosenSpell->id == "DARK_MINOR_DRAIN_1" || chosenSpell->id == "DARK_LIFE_TAP_2" || chosenSpell->id == "LIGHT_CONSECRATED_STRIKE_2") {
                                int totalDamageDealt = magicDamage; 
                                if (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" || chosenSpell->id == "WIND_ZEPHYRS_DANCE_3") {
                                }
                                int drainedHp = 0;
                                if(chosenSpell->id == "DARK_MINOR_DRAIN_1") drainedHp = totalDamageDealt / 2;
                                else if(chosenSpell->id == "DARK_LIFE_TAP_2") drainedHp = totalDamageDealt; 
                                else if(chosenSpell->id == "LIGHT_CONSECRATED_STRIKE_2") drainedHp = totalDamageDealt / 3;

                                if (drainedHp > 0 && enemy.hp > 0) { 
                                    player.hp = min(player.maxHp, player.hp + drainedHp);
                                    battleLogMessages.push_back(L"  Kamu menyerap " + to_wstring(drainedHp) + L" HP dari " + utf8_to_wstring(enemy.name) + L"!");
                                }
                            }
                                if (chosenSpell->id == "DARK_SOUL_ANNIHILATION_3") {                             if (chosenSpell->id == "DARK_SOUL_ANNIHILATION_3" || chosenSpell->id == "DARK_FIELD_OF_DESPAIR_3") {
                                int mpDrainedToPlayer = (chosenSpell->id == "DARK_SOUL_ANNIHILATION_3" ? magicDamage/3 : 5 + finalPlayerIntelligence/10);
                                player.mana = min(player.maxMana, player.mana + mpDrainedToPlayer);
                                battleLogMessages.push_back(L"  💀 Kamu menyerap " + to_wstring(mpDrainedToPlayer) + L" MP dari jiwa musuh!");
                            }
                        }
                            }
                        } else if (chosenSpell->targetType == "Self") { 
                        if (chosenSpell->basePower > 0 && chosenSpell->id != "LIGHT_DIVINE_RENEWAL_3" && chosenSpell->id != "LIGHT_PURIFICATION_1") {
                            int healAmount = chosenSpell->basePower + finalPlayerIntelligence / 2;
                            player.hp = min(player.maxHp, player.hp + healAmount);
                            battleLogMessages.push_back(L"  Kamu memulihkan " + to_wstring(healAmount) + L" HP!");
                        }
                        if (chosenSpell->id == "DARK_SHADOW_WALK_2"){
                                bool shadowWalkActive = false;
                                int bonusDmgAmount = 30 + finalPlayerIntelligence/2; 
                                for(auto& ench : player.activeEnchantments){
                                    if(ench.spellId == "SHADOW_WALK_BONUS"){ 
                                        ench.remainingTurns = 1;
                                        ench.attackBonus = max(ench.attackBonus, bonusDmgAmount); 
                                        shadowWalkActive = true;
                                        battleLogMessages.push_back(L"  Efek Shadow Walk diperbarui!");
                                        break;
                                    }
                                }
                                if(!shadowWalkActive) {
                                    player.activeEnchantments.push_back({"SHADOW_WALK_BONUS", "Shadow Walk Attack", 1, bonusDmgAmount});
                                }
                                battleLogMessages.push_back(L"  Kamu menghilang ke bayangan, serangan fisik berikutnya akan lebih kuat!");
                            }
                        if (chosenSpell->id == "LIGHT_PURIFICATION_1" || chosenSpell->id == "LIGHT_DIVINE_RENEWAL_3") {
                            
                            battleLogMessages.push_back(L"  ✨ Semua efek negatif ringan telah dimurnikan darimu!");
                            if (chosenSpell->id == "LIGHT_DIVINE_RENEWAL_3") { 
                                int healAmount = chosenSpell->basePower + finalPlayerIntelligence;
                                player.hp = min(player.maxHp, player.hp + healAmount);
                                battleLogMessages.push_back(L"  Dan kamu memulihkan " + to_wstring(healAmount) + L" HP secara masif!");
                            }
                        }
                    }
                        }
                    
                    if (!battleLogMessages.empty() && turnActionLog != battleLogMessages.back() && battleLogMessages.back().find(L"➤ Kamu menggunakan") == wstring::npos ) {
                         delayPrint(battleLogMessages.back(), 20);
                    }

                } else if (chosenSpell) { 
                    battleLogMessages.push_back(L"MP tidak cukup untuk " + utf8_to_wstring(chosenSpell->name) + L"!");
                    continue;
                } else { 
                     battleLogMessages.push_back(L"Pilihan magic tidak valid (internal error).");
                     continue;
                }
                break;
            }
            case 3: {
                if (player.inventory.empty()) {
                    battleLogMessages.push_back(L"Tidak ada item untuk digunakan!");
                    break;
                }

                wcout << L"\n❖ INVENTORY:\n";
                for (size_t i = 0; i < player.inventory.size(); ++i) {
                    wcout << L"❖ " << (i + 1) << L". " << utf8_to_wstring(player.inventory[i]->name)
                        << L" - " << utf8_to_wstring(player.inventory[i]->description) << endl;
                }
                wcout << L"❖ 0. Batal" << endl;
                wcout << L"Pilih item: ";
                int itemChoice;
                cin >> itemChoice;

                if (itemChoice <= 0 || itemChoice > player.inventory.size()) {
                    battleLogMessages.push_back(L"Kamu batal menggunakan item.");
                    break;
                }

                Item* selectedItem = player.inventory[itemChoice - 1];
                applyItemEffect(selectedItem->name);
                player.inventory.erase(player.inventory.begin() + itemChoice - 1);
                battleLogMessages.push_back(L"Kamu menggunakan " + utf8_to_wstring(selectedItem->name) + L"!");
                break;
            }


            case 4: { 
                turnActionLog = L"➤ Kamu memilih untuk bertahan. Damage musuh berikutnya akan dikurangi!";
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                break;
            }
            case 5: { 
                if (enemy.isBoss) {
                    turnActionLog = L"➤ Tidak bisa kabur dari Boss!";
                } else if (rand() % 100 < (50 + finalPlayerAgility / 2) ) { 
                    turnActionLog = L"➤ Kamu berhasil kabur!";
                    delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                    processEndOfPlayerTurn(player, battleLogMessages);
                    drawBattleScreen(enemy, player, battleLogMessages);
                    waitForEnter(L"Tekan enter untuk lanjut.....");
                    return PLAYER_ESCAPED;
                } else {
                    turnActionLog = L"➤ Gagal kabur!";
                }
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                break;
            }
            default:
                turnActionLog = L"Aksi tidak valid.";
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                continue; 
        } 

        if (enemy.hp <= 0) { enemy.hp = 0; }
        else { 
            if (choice >=1 && choice <=5 && choice !=3) { 
                if (enemy.isStunned && enemy.stunDuration > 0) {
                    battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" masih STUN!");
                    enemy.stunDuration--;
                    if (enemy.stunDuration == 0) { enemy.isStunned = false; battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" pulih dari STUN."); }
                } else if (enemy.isFeared && enemy.fearDuration > 0) {
                    if (rand() % 100 < 50) { 
                        battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" terlalu takut untuk bergerak!");
                    } else { 
                        if (rand() % 100 < enemyHitChance) {
                            int actualDamageToPlayer = baseDamageToPlayer;
                            if (choice == 4) { actualDamageToPlayer /= 2; } 
                            
                            if (playerIsPhysicallyImmune) {
                                 battleLogMessages.push_back(L"  🛡️ Serangan fisik " + utf8_to_wstring(enemy.name) + L" tidak berpengaruh (Immune)!");
                                 actualDamageToPlayer = 0;
                            } else {
                                for(auto& ench : player.activeEnchantments) {
                                    if (ench.shieldHp > 0) {
                                        if (ench.shieldHp >= actualDamageToPlayer) { ench.shieldHp -= actualDamageToPlayer; battleLogMessages.push_back(L"  🛡️ Perisaimu menyerap " + to_wstring(actualDamageToPlayer) + L" damage! Sisa: " + to_wstring(ench.shieldHp)); actualDamageToPlayer = 0; }
                                        else { actualDamageToPlayer -= ench.shieldHp; battleLogMessages.push_back(L"  🛡️ Perisaimu hancur setelah menyerap " + to_wstring(ench.shieldHp) + L" damage!"); ench.shieldHp = 0; }
                                        break;
                                    }
                                }
                            }
                            if (actualDamageToPlayer > 0) { player.hp -= actualDamageToPlayer; }
                            battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" menyerangmu! Damage diterima: " + to_wstring(actualDamageToPlayer));
                            if (playerRetaliateDamage > 0 && !playerIsPhysicallyImmune && baseDamageToPlayer > 0 ) { 
                                enemy.hp -= playerRetaliateDamage;
                                battleLogMessages.push_back(L"  ⚔️ " + utf8_to_wstring(enemy.name) + L" terkena damage balasan " + to_wstring(playerRetaliateDamage) + L"!");
                                if (enemy.hp <= 0) { enemy.hp = 0; }
                            }
                        } else { battleLogMessages.push_back(L"➤ Serangan " + utf8_to_wstring(enemy.name) + L" meleset!"); }
                    }
                } else if (enemy.isSilenced && enemy.silenceDuration > 0) {
                    battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" terbungkam dan tidak bisa menggunakan sihir!");
                    if (rand() % 100 < enemyHitChance) {
                        int actualDamageToPlayer = baseDamageToPlayer;
                        if (playerIsPhysicallyImmune) { battleLogMessages.push_back(L"  🛡️ Serangan fisik " + utf8_to_wstring(enemy.name) + L" tidak berpengaruh (Immune)!"); actualDamageToPlayer = 0; }
                        else { for(auto& ench : player.activeEnchantments) { if (ench.shieldHp > 0) { if (ench.shieldHp >= actualDamageToPlayer) { ench.shieldHp -= actualDamageToPlayer; battleLogMessages.push_back(L"  🛡️ Perisaimu menyerap " + to_wstring(actualDamageToPlayer) + L" damage! Sisa: " + to_wstring(ench.shieldHp)); actualDamageToPlayer = 0;} else { actualDamageToPlayer -= ench.shieldHp; battleLogMessages.push_back(L"  🛡️ Perisaimu hancur menyerap " + to_wstring(ench.shieldHp) + L" damage!"); ench.shieldHp = 0;} break;}}}
                        if (actualDamageToPlayer > 0) { player.hp -= actualDamageToPlayer; }
                        battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" menyerangmu (fisik)! Damage diterima: " + to_wstring(actualDamageToPlayer));
                        if (playerRetaliateDamage > 0 && !playerIsPhysicallyImmune && baseDamageToPlayer > 0 && enemy.hp > 0) { enemy.hp -= playerRetaliateDamage; battleLogMessages.push_back(L"  ⚔️ " + utf8_to_wstring(enemy.name) + L" terkena damage balasan " + to_wstring(playerRetaliateDamage) + L"!"); if (enemy.hp <= 0) { enemy.hp = 0;}}
                    } else { battleLogMessages.push_back(L"➤ Serangan " + utf8_to_wstring(enemy.name) + L" meleset!"); }
                } else { 
                    if (rand() % 100 < enemyHitChance) {
                        int actualDamageToPlayer = baseDamageToPlayer;
                        if (playerIsPhysicallyImmune) { actualDamageToPlayer = 0; battleLogMessages.push_back(L"  🛡️ Serangan fisik " + utf8_to_wstring(enemy.name) + L" tidak berpengaruh (Immune)!");}
                        else { for(auto& ench : player.activeEnchantments) { if (ench.shieldHp > 0) { if (ench.shieldHp >= actualDamageToPlayer) { ench.shieldHp -= actualDamageToPlayer; actualDamageToPlayer = 0; battleLogMessages.push_back(L"  🛡️ Perisaimu menyerap semua damage! Sisa: " + to_wstring(ench.shieldHp));} else { actualDamageToPlayer -= ench.shieldHp; ench.shieldHp = 0; battleLogMessages.push_back(L"  🛡️ Perisaimu hancur! Sisa damage: " + to_wstring(actualDamageToPlayer));} break;}}}
                        if (actualDamageToPlayer > 0) { player.hp -= actualDamageToPlayer; }
                        battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" menyerangmu! Damage diterima: " + to_wstring(actualDamageToPlayer));
                        if (playerRetaliateDamage > 0 && !playerIsPhysicallyImmune && baseDamageToPlayer > 0 && enemy.hp > 0) { enemy.hp -= playerRetaliateDamage; battleLogMessages.push_back(L"  ⚔️ " + utf8_to_wstring(enemy.name) + L" terkena damage balasan " + to_wstring(playerRetaliateDamage) + L"!"); if (enemy.hp <= 0) { enemy.hp = 0;}}
                    } else { battleLogMessages.push_back(L"➤ Serangan " + utf8_to_wstring(enemy.name) + L" meleset!"); }
                }
            }
        }
        if (player.hp <= 0) { player.hp = 0; }

        
        if (player.hp > 0 && (choice >=1 && choice <=5 && choice !=3) ) {
             processEndOfPlayerTurn(player, battleLogMessages); 
        }
        
        if (enemy.attackDebuffDuration > 0) { enemy.attackDebuffDuration--; if (enemy.attackDebuffDuration == 0) { enemy.attackDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" serangannya normal kembali."); }}
        if (enemy.accuracyDebuffDuration > 0) { enemy.accuracyDebuffDuration--; if (enemy.accuracyDebuffDuration == 0) { enemy.accuracyDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" pandangannya normal kembali."); }}
        if (enemy.physicalDefenseDebuffDuration > 0) { enemy.physicalDefenseDebuffDuration--; if (enemy.physicalDefenseDebuffDuration == 0) { enemy.physicalDefenseDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" pertahanan fisiknya normal kembali."); }}
        if (enemy.magicDefenseDebuffDuration > 0) { enemy.magicDefenseDebuffDuration--; if (enemy.magicDefenseDebuffDuration == 0) { enemy.magicDefenseDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" pertahanan sihirnya normal kembali."); }}
        if (enemy.fearDuration > 0) { enemy.fearDuration--; if (enemy.fearDuration == 0) { enemy.isFeared = false; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" tidak lagi ketakutan."); }}
        if (enemy.silenceDuration > 0) { enemy.silenceDuration--; if (enemy.silenceDuration == 0) { enemy.isSilenced = false; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" tidak lagi terbungkam."); }}
        
        

        if (player.hp <= 0 || enemy.hp <= 0) { /* Loop akan berhenti */ }
        else {
            drawBattleScreen(enemy, player, battleLogMessages);
            waitForEnter(L"<<<< Tekan Enter Untuk Melanjutkan Ke Turn Selanjutnya >>>> ");
        }
    } 

    
    if (player.hp <= 0 && !playerRevivedThisBattle) { 
        for (auto it = player.activeEnchantments.begin(); it != player.activeEnchantments.end(); ) {
            if (it->hasRevive) {
                player.hp = player.maxHp / 2; 
                battleLogMessages.push_back(L"✨ Dengan kekuatan " + utf8_to_wstring(it->spellName) + L", kamu bangkit kembali!");
                playerRevivedThisBattle = true; 
                it = player.activeEnchantments.erase(it); 
                
                
                break; 
            } else {
                ++it;
            }
        }
    }

    drawBattleScreen(enemy, player, battleLogMessages); 
    if (player.hp <= 0) {
            system("cls");
            printLine(); 
            centerText(L"⚔️ PERTEMPURAN SELESAI! ⚔️");
            printLine();
            delayPrint(L"",10); delayPrint(L"❌ Kamu telah mati dan gagal mengubah segalanya...", 50);
            printLine();
            waitForEnter(L" Tekan enter untuk keluar");
            gameRunning = false; 
            return PLAYER_DEAD;   
    } else {
        if (enemy.hp <=0) {
            printLine(); 
            centerText(L"⚔️ PERTEMPURAN SELESAI! ⚔️");
            printLine();
            wcout << L"✅ Musuh " << utf8_to_wstring(enemy.name) << L" telah dikalahkan!\n";
            wcout << L"🎉 Kamu mendapatkan: " << to_wstring(enemy.goldDrop) << L" Gold 💰 dan " << to_wstring(enemy.expReward) << L" EXP 📚.\n";
            printLine();
            player.gold += enemy.goldDrop;
            waitForEnter();
            handleExperienceAndLevelUp(player, enemy.expReward);
            waitForEnter();
            ActiveDailyQuestNode* currentQuestNode = activeDailyQuestsHead;
            ActiveDailyQuestNode* prevQuestNode = nullptr;
            int expFromCompletedQuests = 0; 

            while (currentQuestNode != nullptr) {
                DailyQuest& quest = currentQuestNode->data; 
                bool wasThisQuestCompleted = false;

                if (!quest.completed && quest.taken && quest.type == "kill" && enemy.name == quest.target) {
                    bool dungeonRequirementMet = true; 

                    if (!quest.dungeonName.empty()) { 
                        if (quest.dungeonName != currentDungeonName) {
                            dungeonRequirementMet = false;
                        }
                    }

                    if (dungeonRequirementMet) {
                        quest.completed = true; 
                        expFromCompletedQuests += quest.expReward;
                        player.gold += quest.goldReward;
                        delayPrint(L"✓ Quest Harian Selesai: " + utf8_to_wstring(quest.title) + L"!", 20);
                        delayPrint(L"  Reward: +" + to_wstring(quest.expReward) + L" EXP, +" + to_wstring(quest.goldReward) + L" Gold", 20);
                        
                        wasThisQuestCompleted = true;
                    }   
                    }
                    ActiveDailyQuestNode* nodeToDelete = nullptr;
                    if (wasThisQuestCompleted) {
                        nodeToDelete = currentQuestNode;
                        if (prevQuestNode == nullptr) { 
                            activeDailyQuestsHead = currentQuestNode->next;
                            currentQuestNode = activeDailyQuestsHead; 
                            
                        } else { 
                            prevQuestNode->next = currentQuestNode->next;
                            currentQuestNode = prevQuestNode->next; 
                            
                        }
                        delete nodeToDelete; 
                    } else {
                        
                        prevQuestNode = currentQuestNode;
                        currentQuestNode = currentQuestNode->next;
                    }
                    handleExperienceAndLevelUp(player, expFromCompletedQuests);
                }

            printLine();
        } else if (playerRevivedThisBattle && enemy.hp > 0) {
            delayPrint(L" Kamu bangkit, namun musuh masih berdiri. Pertarungan berakhir untuk saat ini.", 40);
        }
    }
    if (player.hp <= 0) {
    return PLAYER_DEAD;
}
return ENEMY_DEAD;

}



void showInventoryCategory() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ TAS INVENTORY ✦✦✦");
    printLine();
    
    wcout << L"❖ 1. Item" << endl;
    wcout << L"❖ 2. Senjata" << endl;
    wcout << L"❖ 3. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih kategori ✦: ";
}

void showItemList() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ DAFTAR ITEM ✦✦✦");
    printLine();
    
    if(player.inventory.empty()) {
        wcout << L"    Tidak ada item dalam inventory." << endl;
    } else {
        for(int i = 0; i < player.inventory.size(); i++) {
            wcout << L"    ❖ " << i+1 << L". " << player.inventory[i]->name.c_str() << endl;
        }
    }
    wcout << L"    ❖ 0. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih item ✦: ";
}

void showItemDetail(Item* item) {
    system("cls");
    printLine();
    centerText(L"✦✦✦ DETAIL ITEM ✦✦✦");
    printLine();
    
    wcout << L"Nama: " << item->name.c_str() << endl;
    wcout << L"Tipe: " << item->type.c_str() << endl;
    wcout << L"Nilai: " << item->value << endl;
    wcout << L"Deskripsi: " << item->description.c_str() << endl;
    
    if(item->type == "consumable") {
        wcout << L"    ❖ 1. Gunakan" << endl;
    }
    wcout << L"    ❖ 2. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih aksi ✦: ";
}

void showWeaponList() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ DAFTAR SENJATA ✦✦✦");
    printLine();
    
    if(player.weapons.empty()) {
        wcout << L"    Tidak ada senjata dalam inventory." << endl;
    } else {
        for(int i = 0; i < player.weapons.size(); i++) {
            wcout << L"    ❖ " << i+1 << L". " << player.weapons[i]->name.c_str();
            if(player.weapons[i]->equipped) {
                wcout << L" [EQUIPPED]";
            }
            wcout << endl;
        }
    }
    wcout << L"    ❖ 0. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih senjata ✦: ";
}

void showWeaponDetail(Weapon* weapon) {
    system("cls");
    printLine();
    centerText(L"✦✦✦ DETAIL SENJATA ✦✦✦");
    printLine();
    
    wcout << L"Nama: " << weapon->name.c_str() << endl;
    wcout << L"Attack Power: " << weapon->attackPower << endl;
    wcout << L"Strength Required: " << weapon->strengthRequired << endl;
    wcout << L"Intelligence Required: " << weapon->intelligenceRequired << endl;
    wcout << L"Deskripsi: " << weapon->description.c_str() << endl;
    
    if(!weapon->equipped) {
        wcout << L"    ❖ 1. Gunakan (Equip)" << endl;
    } else {
        wcout << L"    ❖ 1. Lepas (Unequip)" << endl;
    }
    wcout << L"    ❖ 2. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih aksi ✦: ";
}

void showCompanionListScreen() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ DAFTAR REKANAN (COMPANION) ✦✦✦");
    printLine();

    if (companions.empty()) {
        wcout << L"    Anda belum menjalin hubungan dengan siapa pun." << endl;
    } else {
        wcout << L"    Pilih rekanan untuk melihat detail:" << endl;
        for (size_t i = 0; i < companions.size(); ++i) {
            const Companion& comp = companions[i]; 
            wcout << L"    ❖ " << (i + 1) << L". " << utf8_to_wstring(comp.name);
            if (comp.met) {
                int currentSocialLevel = 0;
                if (socialLinks.count(comp.name)) {
                    currentSocialLevel = socialLinks[comp.name].currentLevel;
                }
                wcout << L" [Sudah Bertemu | Hubungan Lv.: " << currentSocialLevel << L" | Loyalitas: " << companionRelations[comp.name] << L"]";
            } else {
                wcout << L" [Belum Dikenal]";
            }
            wcout << endl;
        }
    }
    printLine(70, L'─');
    wcout << L"    ❖ 0. Kembali ke Diary" << endl;
    printLine(70, L'─');
    wcout << L"Pilihan Anda ✦: ";
}



void showCompanionDetailScreen(const Companion& companion) { 
    
    
        system("cls");
        printLine();
        centerText(L"✦✦✦ DETAIL REKANAN - " + utf8_to_wstring(companion.name) + L" ✦✦✦");
        printLine();

        if (companion.met) {
            int currentSocialLevel = 0;
            bool isMaxLevel = false; 

            if (socialLinks.count(companion.name)) {
                currentSocialLevel = socialLinks[companion.name].currentLevel;
                if (socialLinks[companion.name].completed) { 
                    isMaxLevel = true;
                    
                    
                    
                    currentSocialLevel = 10;
                }
            } else {
                 wcout << L"    Belum ada progres hubungan sosial dengan " << utf8_to_wstring(companion.name) << L"." << endl;
            }

            wcout << L" Nama         : " << utf8_to_wstring(companion.name) << endl;
            wcout << L" Kepribadian  : " << utf8_to_wstring(companion.personality) << endl;
            wcout << L" Loyalitas    : " << companionRelations[companion.name] << L"/100" << endl;
            wcout << L" Level Hub.   : " << currentSocialLevel << (isMaxLevel ? L" (MAX)" : L"") << endl; 
            wcout << endl;
            wcout << L" Deskripsi Awal:" << endl;
            wcout << L"   " << utf8_to_wstring(companion.description) << endl;
            wcout << endl;

            wcout << L" Sifat & Keahlian Inti:" << endl;
            if (companion.coreAbilitiesOrTraits.empty()) {
                wcout << L"   - Belum ada yang diketahui secara jelas." << endl;
            } else {
                for (const auto& ability : companion.coreAbilitiesOrTraits) {
                    wcout << L"   - " << utf8_to_wstring(ability) << endl;
                }
            }
            wcout << endl;

            wcout << L" Informasi & Sifat Terungkap (Seiring Hubungan):" << endl;
            bool infoRevealedThisSession = false; 
            
            int displayUpToLevel = currentSocialLevel;
            if (isMaxLevel) { 
                displayUpToLevel = 10;
            }


            for (int i = 1; i <= displayUpToLevel; ++i) { 
                bool levelInfoDisplayed = false;
                wstring tempLevelInfo = L"";

                if (companion.detailedInfoPerLevel.count(i)) {
                    tempLevelInfo += L"\n   ✧ Level " + to_wstring(i) + L": " + companion.detailedInfoPerLevel.at(i);
                    levelInfoDisplayed = true;
                    infoRevealedThisSession = true;
                }
                if (companion.traitsRevealedPerLevel.count(i)) {
                    if (!levelInfoDisplayed) { 
                        tempLevelInfo += L"\n   ✧ Level " + to_wstring(i) + L":";
                        levelInfoDisplayed = true;
                    }
                    for (const auto& trait : companion.traitsRevealedPerLevel.at(i)) {
                        tempLevelInfo += L"\n     └─ Sifat/Keahlian Baru: " + trait;
                    }
                    infoRevealedThisSession = true;
                }
                if (levelInfoDisplayed) {
                    wcout << tempLevelInfo << endl;
                }
            }

            if (!infoRevealedThisSession && currentSocialLevel > 0) { 
                 wcout << L"   Belum ada informasi detail tambahan yang terungkap pada level hubungan ini." << endl;
            } else if (currentSocialLevel == 0 && companion.met) { 
                 wcout << L"   Mulailah berinteraksi untuk mengenal mereka lebih dalam!" << endl;
            } else if (!infoRevealedThisSession && currentSocialLevel == 0 && !companion.met) {
                 
            }


            printLine(70, L'─');
            
            
            
            waitForEnter(L"Tekan Enter untuk kembali ke Daftar Rekanan.");
        } else {
            wcout << L" Nama         : ???" << endl;
            wcout << L" Status       : Belum Dikenal" << endl;
            wcout << L" Informasi    : Anda belum bertemu dengan individu ini." << endl;
            printLine(70, L'─');
            waitForEnter(L"Tekan Enter untuk kembali ke Daftar Rekanan."); 
        }
        printLine(70, L'─');

        
    
}

void enterDungeon(string dungeonName) {
    if (!allDungeons.count(dungeonName)) {
        delayPrint(L"Error: Dungeon '" + utf8_to_wstring(dungeonName) + L"' tidak ditemukan.", 20);
        waitForEnter();
        return;
    }
    
    Dungeon& dungeon = allDungeons.at(dungeonName); 

    bool firstTimeEnteringThisSpecificDungeonRun = true; 
    if (dungeon.currentFloor == 1 && dungeon.visitedCampAreas.empty() && dungeon.exploredOnceFloors.empty()) {
        firstTimeEnteringThisSpecificDungeonRun = true;
    } else if (!dungeon.visitedCampAreas.empty()){
        firstTimeEnteringThisSpecificDungeonRun = false;
    }


    if (!firstTimeEnteringThisSpecificDungeonRun) {
        system("cls"); printLine();
        centerText(L"MELANJUTKAN EKSPLORASI " + utf8_to_wstring(dungeon.name)); printLine();
        wcout << L"Kamu pernah mencapai Camp Area di Lantai " << formatDungeonFloor(dungeon, dungeon.visitedCampAreas.back()) << L".\n";
        wcout << L"❖ 1. Mulai dari Lantai " << formatDungeonFloor(dungeon, 1) << endl;
        wcout << L"❖ 2. Mulai dari Camp Area terakhir (Lantai " << formatDungeonFloor(dungeon, dungeon.visitedCampAreas.back()) << L")" << endl;
        wcout << L"Pilih opsi ✦: ";
        int startChoice = getValidatedChoice(1, 2);

        if (startChoice == 2) {
            dungeon.currentFloor = dungeon.visitedCampAreas.back();  
        } else {
            dungeon.currentFloor = 1;  
        }
    } else {
        dungeon.currentFloor = 1; 
    }
    
    consumeAction(); 
    bool inDungeon = true;

    while (inDungeon && gameRunning) {
        system("cls");
        printLine();
        wstring title = L"🏛️  " + utf8_to_wstring(dungeon.name) +
                        L" - Lantai " + formatDungeonFloor(dungeon, dungeon.currentFloor);
        centerText(title); 
        if (dungeon.campAreas.count(dungeon.currentFloor)) {
            centerText(L"🏕️  CAMP AREA");
        } else {
            centerText(L"⚔️  AREA BERBAHAYA");
        }
        printLine();

        ActiveDailyQuestNode* currentQuestNode = activeDailyQuestsHead;
        ActiveDailyQuestNode* prevQuestNode = nullptr;
        int expFromCompletedQuestsThisTurn = 0;

        while (currentQuestNode != nullptr) {
            DailyQuest& quest = currentQuestNode->data;
            ActiveDailyQuestNode* nextNode = currentQuestNode->next; 
            bool wasThisQuestCompletedThisCheck = false;

            if (quest.type == "travel" && quest.taken && !quest.completed &&
                !quest.dungeonName.empty() && quest.dungeonName == dungeon.name && 
                quest.dungeonFloor > 0 && quest.dungeonFloor == dungeon.currentFloor) {
                
                quest.completed = true; 
                expFromCompletedQuestsThisTurn += quest.expReward;
                player.gold += quest.goldReward;
                
                system("cls"); 
                printLine();
                centerText(L"🎉 QUEST SELESAI! 🎉");
                printLine();
                delayPrint(L"✓ kamu telah menyelesaikan Quest Harian: " + utf8_to_wstring(quest.title) + L"!", 20);
                delayPrint(L"  Hadiah: +" + to_wstring(quest.expReward) + L" EXP, +" + to_wstring(quest.goldReward) + L" Gold", 20);
                printLine();
                waitForEnter();
                wasThisQuestCompletedThisCheck = true;

                if (prevQuestNode == nullptr) { 
                    activeDailyQuestsHead = nextNode;
                } else { 
                    prevQuestNode->next = nextNode;
                }
                delete currentQuestNode; 
            }

            if (!wasThisQuestCompletedThisCheck) {
                prevQuestNode = currentQuestNode;
            }
            currentQuestNode = nextNode;
        }

        if (expFromCompletedQuestsThisTurn > 0) {
            handleExperienceAndLevelUp(player, expFromCompletedQuestsThisTurn);
            waitForEnter(); 
        }

        if (find(dungeon.storyLockedFloors.begin(), dungeon.storyLockedFloors.end(), dungeon.currentFloor) != dungeon.storyLockedFloors.end() && 
            !storyFlags.count(dungeon.name + "_Floor_" + to_string(dungeon.currentFloor) + "_Unlocked")) {
            centerText(L"❌ Jalan menuju lantai ini disegel oleh kekuatan misterius atau membutuhkan progres cerita tertentu.");
            printLine();
            waitForEnter(L"Tekan enter untuk kembali ke lantai sebelumnya....");
            if (dungeon.currentFloor > 1) {
                dungeon.currentFloor--;
            } else {
                 waitForEnter(L"Tekan Enter untuk keluar dari dungeon...");
                 return;
            }
            continue; 
        }

        if (dungeon.campAreas.count(dungeon.currentFloor)) {
            CampArea& camp = dungeon.campAreas.at(dungeon.currentFloor);
            if (find(dungeon.visitedCampAreas.begin(), dungeon.visitedCampAreas.end(), camp.floor) == dungeon.visitedCampAreas.end()) {
                dungeon.visitedCampAreas.push_back(camp.floor);
                sort(dungeon.visitedCampAreas.begin(), dungeon.visitedCampAreas.end()); 
            }
            camp.visited = true;

            wcout << L"kamu tiba di Camp Area di Lantai " << formatDungeonFloor(dungeon, camp.floor) << L". Tempat ini aman untuk beristirahat." << endl;
            printLine(60, L'─');
            wcout << L"❖ 1. Istirahat (Sisa: " << (camp.diaryAccessible ? (2 - camp.restUsed) : 0) << L" kali)" << endl;
            wcout << L"❖ 2. Lanjut ke lantai berikutnya" << endl;
            wcout << L"❖ 3. Kembali ke lantai sebelumnya" << endl;
            if (camp.diaryAccessible) {
                wcout << L"❖ 4. Buka Diary" << endl;
            }
            wcout << L"❖ 0. Keluar dari dungeon" << endl;
            printLine(60, L'─');
            wcout << L"Pilih aksi ✦: ";

            int campChoice = getValidatedChoice(0, (camp.diaryAccessible ? 4 : 3));

            switch (campChoice) {
                case 1:
                    if (camp.diaryAccessible && camp.restUsed < 2) {
                        player.hp = player.maxHp;
                        player.mana = player.maxMana;
                        camp.restUsed++;
                        delayPrint(L"kamu beristirahat di dekat api unggun. Semua HP dan Mana dipulihkan.", 20);
                    } else if (!camp.diaryAccessible) {
                        delayPrint(L"Istirahat tidak tersedia di camp ini saat ini.", 20);
                    } else {
                        delayPrint(L"kamu sudah menggunakan semua jatah istirahat di camp ini.", 20);
                    }
                    waitForEnter();
                    break;
                case 2:
                    dungeon.currentFloor++;
                    if (dungeon.currentFloor > dungeon.maxUnlockedFloor) dungeon.maxUnlockedFloor = dungeon.currentFloor;
                    break;
                case 3:
                    if (dungeon.currentFloor > 1) {
                        dungeon.currentFloor--;
                    } else {
                        delayPrint(L"Ini adalah lantai teratas/pintu masuk.", 20);
                    }
                    break;
                case 4:
                    if (camp.diaryAccessible) {
                        showDiaryMenu();
                    } else {
                        delayPrint(L"Pilihan tidak valid.", 20);
                        waitForEnter();
                    }
                    break;
                case 0:
                    inDungeon = false;
                    delayPrint(L"kamu memutuskan untuk keluar dari " + utf8_to_wstring(dungeon.name) + L".", 20);
                    break;
                default:
                    delayPrint(L"Aksi tidak dikenali.", 20);
                    waitForEnter();
                    break;
            }
        } else {
            wcout << L"Pilihan aksi di Lantai " << formatDungeonFloor(dungeon, dungeon.currentFloor) << L":" << endl;
            printLine(60, L'─');
            wcout << L"❖ 1. Eksplorasi lantai" << endl;
            wcout << L"❖ 2. Lanjut ke lantai berikutnya" << endl;
            wcout << L"❖ 3. Kembali ke lantai sebelumnya" << endl;
            wcout << L"❖ 4. Gunakan item dari inventory" << endl;
            printLine(60, L'─');
            wcout << L"Pilih aksi ✦: ";

            int actionChoice = getValidatedChoice(0, 4);

            switch (actionChoice) {
                case 1: {
                    if (dungeon.exploredOnceFloors.count(dungeon.currentFloor)) {
                        system("cls");
                        printLine();
                        centerText(L"🔎 EKSPLORASI LANTAI 🔎");
                        printLine();
                        delayPrint(L"kamu sudah menjelajahi lantai " + formatDungeonFloor(dungeon, dungeon.currentFloor) + L" ini dengan saksama sebelumnya.", 20);
                        delayPrint(L"Tidak ada lagi yang bisa ditemukan di sini.", 20);
                        printLine();
                        waitForEnter();
                        break; 
                    }

                    system("cls");
                    printLine();
                    centerText(L"🔎 MENJELAJAHI LANTAI " + formatDungeonFloor(dungeon, dungeon.currentFloor) + L" 🔍");
                    printLine();
                    delayPrint(L"kamu dengan seksama mengamati setiap sudut dan celah di lantai ini...", 30);
                    
                    int outcomeRoll = rand() % 100;

                    if (outcomeRoll < 10) { 
                        int foundGold = 3 + rand() % 13;
                        player.gold += foundGold;
                        delayPrint(L"Matamu menangkap kilauan samar di antara bebatuan.", 20);
                        delayPrint(L"Itu beberapa koin emas yang tercecer! kamu mengambilnya.", 20);
                        delayPrint(L"💰 Gold +" + to_wstring(foundGold) + L"!", 20);
                    } else if (outcomeRoll < 15) { 
                        delayPrint(L"Di sudut yang terlupakan, kamu menemukan sebuah kantong usang.", 20);
                        Item* foundItem = nullptr;
                        if (rand() % 3 == 0 && itemDatabase.count("Mana Potion")) {
                            foundItem = itemDatabase.at("Mana Potion");
                        } else if (itemDatabase.count("Health Potion")) {
                            foundItem = itemDatabase.at("Health Potion");
                        }
                        
                        if (foundItem) {
                            player.inventory.push_back(foundItem);
                            delayPrint(L"Isinya adalah sebuah " + utf8_to_wstring(foundItem->name) + L"! Berguna sekali.", 20);
                            delayPrint(L"✨ Item '" + utf8_to_wstring(foundItem->name) + L"' ditambahkan ke inventory!", 20);
                        } else {
                            delayPrint(L"Sayangnya, kantong itu sudah kosong dan robek.", 20);
                        }
                    } else if (outcomeRoll < 25) { 
                        delayPrint(L"kamu menemukan jejak-jejak aneh di lantai berdebu, sepertinya dari makhluk yang belum pernah kamu lihat.", 20);
                        delayPrint(L"Mempelajarinya memberimu sedikit pemahaman baru tentang ekosistem tempat ini.", 20);
                        int foundExp = 4 + rand() % 5;
                        player.exp += foundExp;
                        delayPrint(L"📚 EXP +" + to_wstring(foundExp) + L"!", 20);
                    } else if (outcomeRoll < 40) { 
                        if (dungeon.name == "Ancient Temple") {
                            delayPrint(L"kamu mendengar suara gemericik air samar dari balik dinding batu, namun tak terlihat sumbernya.", 20);
                            delayPrint(L"Udara terasa sangat tua dan sedikit berbau dupa yang telah lama padam.", 20);
                        } else if (dungeon.name == "Goa Avernix") {
                            delayPrint(L"Sebuah stalaktit besar menjuntai dari langit-langit goa, meneteskan air perlahan.", 20);
                            delayPrint(L"kamu melihat beberapa kristal kecil berkilauan redup di dinding yang lembap.", 20);
                        } else {
                            delayPrint(L"Angin dingin berhembus melalui lorong sempit di depanmu, membawa suara yang tak jelas.", 20);
                            delayPrint(L"kamu merasa sedikit merinding.", 20);
                        }
                    } else if (outcomeRoll < 55) { 
                        if (dungeon.name == "Ancient Temple") {
                            delayPrint(L"Dinding di sini dipenuhi ukiran rumit yang hampir tak terbaca karena usia.", 20);
                            delayPrint(L"kamu mencoba memahami artinya, namun hanya bisa menebak-nebak kisah para pendahulu.", 20);
                        } else if (dungeon.name == "Goa Avernix") {
                            delayPrint(L"Jejak cakar besar terlihat jelas di tanah berlumpur. Makhluk apa yang sebesar ini?", 20);
                            delayPrint(L"kamu meningkatkan kewaspadaanmu.", 20);
                        } else {
                            delayPrint(L"Sebuah obor yang sudah lama padam tergeletak di sudut, meninggalkan noda jelaga di dinding.", 20);
                            delayPrint(L"Siapapun yang terakhir di sini, sepertinya pergi dengan tergesa-gesa.", 20);
                        }
                    } else if (outcomeRoll < 70) { 
                        if (dungeon.name == "Ancient Temple") {
                            delayPrint(L"kamu menemukan sisa-sisa perapian kecil yang sudah dingin. Petualang lain pernah berkemah di sini.", 20);
                            delayPrint(L"Namun tidak ada barang berharga yang tertinggal.", 20);
                        } else if (dungeon.name == "Goa Avernix") {
                            delayPrint(L"Terdengar suara gemuruh samar dari kedalaman goa. Apakah itu hanya angin, atau sesuatu yang lebih besar?", 20);
                            delayPrint(L"kamu memutuskan untuk tidak mencari tahu lebih jauh untuk saat ini.", 20);
                        } else {
                            delayPrint(L"Lorong di depanmu bercabang dua. Keduanya tampak sama-sama gelap dan misterius.", 20);
                            delayPrint(L"Untuk saat ini, kamu memilih untuk tetap di jalur utama lantai ini.", 20);
                        }
                    } else if (outcomeRoll < 85) {
                         delayPrint(L"Keheningan di lantai ini terasa menekan. Hanya suara langkah kakimu sendiri yang bergema.", 20);
                         delayPrint(L"kamu merasa seolah ada ratusan mata tak terlihat yang mengawasimu dari kegelapan.", 20);
                    } else if (outcomeRoll < 90) {
                        delayPrint(L"kamu menemukan sebuah tulisan aneh yang tergores di dinding menggunakan bahasa yang tidak kamu kenali.", 20);
                        delayPrint(L"Mungkin suatu saat kamu akan menemukan artinya. Untuk sekarang, itu hanyalah simbol misterius.", 20);
                    }
                    else { 
                        delayPrint(L"Setelah berkeliling dengan hati-hati, kamu tidak menemukan sesuatu yang benar-benar menonjol.", 20);
                        delayPrint(L"Lantai ini tampak biasa saja, jika kata 'biasa' bisa digunakan untuk menggambarkan dungeon.", 20);
                    }
                    dungeon.exploredOnceFloors.insert(dungeon.currentFloor);
                    printLine();
                    waitForEnter();
                    break;
                }
                case 2: {
                    string enemyName;
                    bool battleTriggered = false;
                    string floorKeyForBoss = dungeon.name + "_F" + to_string(dungeon.currentFloor);

                    if (dungeon.miniBosses.count(dungeon.currentFloor) && !defeatedBosses[floorKeyForBoss + "_MB"]) {
                        enemyName = dungeon.miniBosses.at(dungeon.currentFloor);
                        battleTriggered = true;
                        delayPrint(L"kamu merasakan aura kuat di depan! Sesosok Entitas Kuat menghalangi jalan menuju lantai berikutnya!", 30);
                        waitForEnter(L"Tekan Enter untuk menghadapi Mini Boss...");
                    } else if (dungeon.finalBoss.count(dungeon.currentFloor) && !defeatedBosses[dungeon.name + "_FB"]) {
                        enemyName = dungeon.finalBoss.at(dungeon.currentFloor);
                        battleTriggered = true;
                        delayPrint(L"Aura yang sangat menindas datang dari ruangan di depan! Sang penjaga terakhir dungeon ini, telah menantimu!", 30);
                        waitForEnter(L"Tekan Enter untuk menghadapi Final Boss Dungeon...");
                    } else if (dungeon.floorEnemies.count(dungeon.currentFloor) && !dungeon.floorEnemies.at(dungeon.currentFloor).empty()) {
                        enemyName = dungeon.floorEnemies.at(dungeon.currentFloor)[rand() % dungeon.floorEnemies.at(dungeon.currentFloor).size()];
                        battleTriggered = true;
                        delayPrint(L"Saat mencoba ke lantai berikutnya, seekor musuh menghadangmu!", 30);
                        waitForEnter(L"Tekan Enter untuk bertarung...");
                    }

                    if (battleTriggered && enemyDatabase.count(enemyName)) {
                        Enemy enemyToFight = enemyDatabase.at(enemyName);
                        BattleResult result = startBattle(enemyToFight, dungeon.name);
                        if (result == PLAYER_DEAD) { if (!gameRunning) return; inDungeon = false; } 
                        else if (result == ENEMY_DEAD) {
                            if (dungeon.miniBosses.count(dungeon.currentFloor) && dungeon.miniBosses.at(dungeon.currentFloor) == enemyName) {
                                defeatedBosses[floorKeyForBoss + "_MB"] = true;
                            } else if (dungeon.finalBoss.count(dungeon.currentFloor) && dungeon.finalBoss.at(dungeon.currentFloor) == enemyName) {
                                defeatedBosses[dungeon.name + "_FB"] = true;
                                delayPrint(L"kamu telah menaklukkan " + utf8_to_wstring(dungeon.name) + L"!", 30);
                                inDungeon = false; 
                                break; 
                            }
                            dungeon.currentFloor++;
                            if (dungeon.currentFloor > dungeon.maxUnlockedFloor) dungeon.maxUnlockedFloor = dungeon.currentFloor;
                            delayPrint(L"Setelah mengalahkan musuh, kamu melanjutkan ke Lantai " + formatDungeonFloor(dungeon, dungeon.currentFloor) + L"...", 20);
                        }
                        else if (result == PLAYER_ESCAPED) { 
                            delayPrint(L"Kamu berhasil kabur, tapi kembali ke lantai ini.", 20);
                        }
                    } else if (!battleTriggered) { 
                        dungeon.currentFloor++;
                        if (dungeon.currentFloor > dungeon.maxUnlockedFloor) dungeon.maxUnlockedFloor = dungeon.currentFloor;
                        delayPrint(L"Kamu melanjutkan ke Lantai " + formatDungeonFloor(dungeon, dungeon.currentFloor) + L" tanpa halangan.", 20);
                    } else { 
                        delayPrint(L"Data musuh tidak ditemukan. Kamu melanjutkan dengan hati-hati.", 20);
                        dungeon.currentFloor++;
                        if (dungeon.currentFloor > dungeon.maxUnlockedFloor) dungeon.maxUnlockedFloor = dungeon.currentFloor;
                    }
                    break; 
                }
                case 3: 
                    if (dungeon.currentFloor > 1) {
                        dungeon.currentFloor--;
                        delayPrint(L"kamu kembali ke Lantai " + formatDungeonFloor(dungeon, dungeon.currentFloor) + L"...", 20);
                    } else {
                        delayPrint(L"Ini adalah lantai teratas/pintu masuk.", 20);
                    }
                    break;
                case 4: { 
                    if (player.inventory.empty()) {
                        delayPrint(L"Inventaris kamu kosong.", 20);
                        waitForEnter();
                        break;
                    }
                    int itemChoice = -1;
                    bool itemUsedOrCancelled = false;
                    while (!itemUsedOrCancelled) {
                        system("cls");
                        printLine();
                        centerText(L"✦ GUNAKAN ITEM DI DUNGEON ✦");
                        printLine();
                        for (size_t i = 0; i < player.inventory.size(); ++i) {
                            wcout << L"❖ " << (i + 1) << L". " << utf8_to_wstring(player.inventory[i]->name)
                                << L" - " << utf8_to_wstring(player.inventory[i]->description) << endl;
                        }
                        wcout << L"❖ 0. Batal" << endl;
                        printLine();
                        wcout << L"Pilih item untuk digunakan ✦: ";
                        itemChoice = getValidatedChoice(0, static_cast<int>(player.inventory.size()));

                        if (itemChoice == 0) {
                            delayPrint(L"Batal menggunakan item.", 20);
                            itemUsedOrCancelled = true; 
                        } else if (itemChoice > 0 && static_cast<size_t>(itemChoice) <= player.inventory.size()) {
                            Item* selectedItem = player.inventory[itemChoice - 1];
                            if (selectedItem->type == "consumable") {
                                applyItemEffect(selectedItem->name);
                                player.inventory.erase(player.inventory.begin() + itemChoice - 1);
                                itemUsedOrCancelled = true;
                            } else {
                                delayPrint(L"Item ini tidak bisa digunakan saat ini.", 20);
                            }
                        } else {
                            delayPrint(L"Pilihan tidak valid.", 20);
                        }
                        if (itemUsedOrCancelled) waitForEnter();
                    }
                    break;
                }
                default:
                    delayPrint(L"Aksi tidak valid.", 20);
                    waitForEnter();
                    break;
            }
        }
        if (player.hp <= 0 && gameRunning) { 
            delayPrint(L"Nyawamu habis... Kegelapan menelanmu...", 50);
            gameRunning = false; 
            inDungeon = false;
        }
    }
    waitForEnter();
}


void showCalendar() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ KALENDER PERUBAHAN ✦✦✦");
    printLine();
    
    wcout << L"Hari Sekarang: " << currentDay << endl;
    wcout << L"Event yang Dijadwalkan:" << endl;
    
    queue<GameEvent> tempQueue = scheduledEvents;
    while(!tempQueue.empty()) {
        GameEvent event = tempQueue.front();
        tempQueue.pop();
        
        wcout << L"    ❖ Hari " << event.dayTrigger << L": " << event.eventName.c_str();
        if(!event.triggered) {
            wcout << L" [UPCOMING]";
        } else {
            wcout << L" [COMPLETED]";
        }
        wcout << endl;
        wcout << L"      " << event.description.c_str() << endl;
    }
    
    printLine();
    wcout << L"    ❖ 1. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih aksi ✦: ";
}

void populateSaveSlotData(SaveSlot& slot) {
    slot.isUsed = true;
    slot.saveTime = time(0); // Waktu saat ini

    // Data Pemain
    slot.playerName = player.name;
    slot.playerLevel = player.level;
    slot.playerHp = player.hp;
    slot.playerMaxHp = player.maxHp;
    slot.playerMana = player.mana;
    slot.playerMaxMana = player.maxMana;
    slot.playerStrength = player.strength;
    slot.playerDefense = player.defense;
    slot.playerIntelligence = player.intelligence;
    slot.playerAgility = player.agility;
    slot.playerExp = player.exp;
    slot.playerExpToNextLevel = player.expToNextLevel;
    slot.playerGold = player.gold;
    slot.playerSkillPoints = player.skillPoints;
    slot.playerUnlockedMagicElements = player.unlockedMagicElements;
    slot.playerKnownSpells = player.knownSpells;
    slot.playerEquippedWeaponName = player.equippedWeapon ? player.equippedWeapon->name : "";

    slot.playerInventoryItemNames.clear();
    for (const auto* item : player.inventory) {
        if (item) slot.playerInventoryItemNames.push_back(item->name);
    }
    slot.playerWeaponNames.clear();
    for (const auto* weapon : player.weapons) {
        if (weapon) slot.playerWeaponNames.push_back(weapon->name);
    }

    // Progres Cerita & Dunia
    slot.currentDay = currentDay;
    slot.currentActionsRemaining = currentActionsRemaining;
    slot.currentWorld = currentWorld;
    slot.currentSubArea = currentSubArea;
    slot.storyFlagsData = storyFlags; // Langsung copy map

    slot.scheduledEventsVector.clear();
    queue<GameEvent> tempScheduledEvents = scheduledEvents; // Salin queue
    while(!tempScheduledEvents.empty()) {
        slot.scheduledEventsVector.push_back(tempScheduledEvents.front());
        tempScheduledEvents.pop();
    }

    // Progres Companion
    slot.companionNamesMet.clear();
    slot.companionRelationsData.clear();
    slot.companionSocialLinkLevels.clear();
    slot.companionSocialLinkCompleted.clear();
    for(const auto& comp : companions) {
        if(comp.met) slot.companionNamesMet.push_back(comp.name);
        if(companionRelations.count(comp.name)) slot.companionRelationsData[comp.name] = companionRelations.at(comp.name);
        if(socialLinks.count(comp.name)) {
            slot.companionSocialLinkLevels[comp.name] = socialLinks.at(comp.name).currentLevel;
            slot.companionSocialLinkCompleted[comp.name] = socialLinks.at(comp.name).completed;
        }
    }
        slot.companionCurrentLocations.clear();
    for (const auto& pair : companionCurrentLocations) {
        slot.companionCurrentLocations[pair.first] = pair.second;
    }


    // Progres Dungeon
    slot.dungeonVisitedCampAreasData.clear();
    slot.dungeonExploredOnceFloorsData.clear();
    for(const auto& pair_dungeon : allDungeons) {
        slot.dungeonVisitedCampAreasData[pair_dungeon.first] = pair_dungeon.second.visitedCampAreas;
        slot.dungeonExploredOnceFloorsData[pair_dungeon.first] = pair_dungeon.second.exploredOnceFloors;
    }
    slot.defeatedBossesData = defeatedBosses;

    // Quest Aktif
    slot.activeDailyQuestsData.clear();
    ActiveDailyQuestNode* currentQuestNode = activeDailyQuestsHead;
    while(currentQuestNode != nullptr) {
        slot.activeDailyQuestsData.push_back(currentQuestNode->data);
        currentQuestNode = currentQuestNode->next;
    }

    // Nama slot bisa dibuat otomatis atau diminta dari pemain
    char timeBuffer[80];
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localtime(&slot.saveTime));
    slot.slotName = player.name + " - Hari " + to_string(currentDay) + " (" + timeBuffer + ")";
}

void writeSaveDataToFile() {
    ofstream outFile(SAVE_FILE_NAME, ios::binary | ios::trunc);
    if (!outFile) {
        return;
    }

    for (int i = 0; i < MAX_SAVE_SLOTS; ++i) {
        const SaveSlot& slot = saveSlots[i];
        outFile.write(reinterpret_cast<const char*>(&slot.isUsed), sizeof(slot.isUsed));
        if (slot.isUsed) {
            size_t slotNameLen = slot.slotName.length();
            outFile.write(reinterpret_cast<const char*>(&slotNameLen), sizeof(slotNameLen));
            outFile.write(slot.slotName.c_str(), slotNameLen);
            outFile.write(reinterpret_cast<const char*>(&slot.saveTime), sizeof(slot.saveTime));

            size_t playerNameLen = slot.playerName.length();
            outFile.write(reinterpret_cast<const char*>(&playerNameLen), sizeof(playerNameLen));
            outFile.write(slot.playerName.c_str(), playerNameLen);
            outFile.write(reinterpret_cast<const char*>(&slot.playerLevel), sizeof(slot.playerLevel));
            outFile.write(reinterpret_cast<const char*>(&slot.playerHp), sizeof(slot.playerHp));
            outFile.write(reinterpret_cast<const char*>(&slot.playerMaxHp), sizeof(slot.playerMaxHp));
            outFile.write(reinterpret_cast<const char*>(&slot.playerMana), sizeof(slot.playerMana));
            outFile.write(reinterpret_cast<const char*>(&slot.playerMaxMana), sizeof(slot.playerMaxMana));
            outFile.write(reinterpret_cast<const char*>(&slot.playerStrength), sizeof(slot.playerStrength));
            outFile.write(reinterpret_cast<const char*>(&slot.playerDefense), sizeof(slot.playerDefense));
            outFile.write(reinterpret_cast<const char*>(&slot.playerIntelligence), sizeof(slot.playerIntelligence));
            outFile.write(reinterpret_cast<const char*>(&slot.playerAgility), sizeof(slot.playerAgility));
            outFile.write(reinterpret_cast<const char*>(&slot.playerExp), sizeof(slot.playerExp));
            outFile.write(reinterpret_cast<const char*>(&slot.playerExpToNextLevel), sizeof(slot.playerExpToNextLevel));
            outFile.write(reinterpret_cast<const char*>(&slot.playerGold), sizeof(slot.playerGold));
            outFile.write(reinterpret_cast<const char*>(&slot.playerSkillPoints), sizeof(slot.playerSkillPoints));

            size_t unlockedElementsSize = slot.playerUnlockedMagicElements.size();
            outFile.write(reinterpret_cast<const char*>(&unlockedElementsSize), sizeof(unlockedElementsSize));
            for (const string& elem : slot.playerUnlockedMagicElements) {
                size_t elemLen = elem.length();
                outFile.write(reinterpret_cast<const char*>(&elemLen), sizeof(elemLen));
                outFile.write(elem.c_str(), elemLen);
            }

            size_t knownSpellsSize = slot.playerKnownSpells.size();
            outFile.write(reinterpret_cast<const char*>(&knownSpellsSize), sizeof(knownSpellsSize));
            for (const string& spellId : slot.playerKnownSpells) {
                size_t idLen = spellId.length();
                outFile.write(reinterpret_cast<const char*>(&idLen), sizeof(idLen));
                outFile.write(spellId.c_str(), idLen);
            }
            
            size_t equippedWeaponNameLen = slot.playerEquippedWeaponName.length();
            outFile.write(reinterpret_cast<const char*>(&equippedWeaponNameLen), sizeof(equippedWeaponNameLen));
            outFile.write(slot.playerEquippedWeaponName.c_str(), equippedWeaponNameLen);


            size_t inventorySize = slot.playerInventoryItemNames.size();
            outFile.write(reinterpret_cast<const char*>(&inventorySize), sizeof(inventorySize));
            for (const string& itemName : slot.playerInventoryItemNames) {
                size_t nameLen = itemName.length();
                outFile.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
                outFile.write(itemName.c_str(), nameLen);
            }

            size_t weaponsSize = slot.playerWeaponNames.size();
            outFile.write(reinterpret_cast<const char*>(&weaponsSize), sizeof(weaponsSize));
            for (const string& weaponName : slot.playerWeaponNames) {
                size_t nameLen = weaponName.length();
                outFile.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
                outFile.write(weaponName.c_str(), nameLen);
            }

            outFile.write(reinterpret_cast<const char*>(&slot.currentDay), sizeof(slot.currentDay));
            outFile.write(reinterpret_cast<const char*>(&slot.currentActionsRemaining), sizeof(slot.currentActionsRemaining));
            
            size_t currentWorldLen = slot.currentWorld.length();
            outFile.write(reinterpret_cast<const char*>(&currentWorldLen), sizeof(currentWorldLen));
            outFile.write(slot.currentWorld.c_str(), currentWorldLen);

            size_t currentSubAreaLen = slot.currentSubArea.length();
            outFile.write(reinterpret_cast<const char*>(&currentSubAreaLen), sizeof(currentSubAreaLen));
            outFile.write(slot.currentSubArea.c_str(), currentSubAreaLen);

            size_t storyFlagsSize = slot.storyFlagsData.size();
            outFile.write(reinterpret_cast<const char*>(&storyFlagsSize), sizeof(storyFlagsSize));
            for (const auto& flagPair : slot.storyFlagsData) {
                size_t keyLen = flagPair.first.length();
                outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
                outFile.write(flagPair.first.c_str(), keyLen);
                outFile.write(reinterpret_cast<const char*>(&flagPair.second), sizeof(flagPair.second));
            }

            size_t scheduledEventsVecSize = slot.scheduledEventsVector.size();
            outFile.write(reinterpret_cast<const char*>(&scheduledEventsVecSize), sizeof(scheduledEventsVecSize));
            for(const auto& ev : slot.scheduledEventsVector){
                size_t eventNameLen = ev.eventName.length();
                outFile.write(reinterpret_cast<const char*>(&eventNameLen), sizeof(eventNameLen));
                outFile.write(ev.eventName.c_str(), eventNameLen);
                size_t descLen = ev.description.length();
                outFile.write(reinterpret_cast<const char*>(&descLen), sizeof(descLen));
                outFile.write(ev.description.c_str(), descLen);
                outFile.write(reinterpret_cast<const char*>(&ev.dayTrigger), sizeof(ev.dayTrigger));
                outFile.write(reinterpret_cast<const char*>(&ev.triggered), sizeof(ev.triggered));
            }
            
            size_t compMetSize = slot.companionNamesMet.size();
            outFile.write(reinterpret_cast<const char*>(&compMetSize), sizeof(compMetSize));
            for(const string& cn : slot.companionNamesMet){
                size_t cnLen = cn.length();
                outFile.write(reinterpret_cast<const char*>(&cnLen), sizeof(cnLen));
                outFile.write(cn.c_str(), cnLen);
            }

            size_t compRelSize = slot.companionRelationsData.size();
            outFile.write(reinterpret_cast<const char*>(&compRelSize), sizeof(compRelSize));
            for(const auto& crPair : slot.companionRelationsData){
                size_t keyLen = crPair.first.length();
                outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
                outFile.write(crPair.first.c_str(), keyLen);
                outFile.write(reinterpret_cast<const char*>(&crPair.second), sizeof(crPair.second));
            }
            
            size_t compSlLvlSize = slot.companionSocialLinkLevels.size();
            outFile.write(reinterpret_cast<const char*>(&compSlLvlSize), sizeof(compSlLvlSize));
            for(const auto& slPair : slot.companionSocialLinkLevels){
                size_t keyLen = slPair.first.length();
                outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
                outFile.write(slPair.first.c_str(), keyLen);
                outFile.write(reinterpret_cast<const char*>(&slPair.second), sizeof(slPair.second));
            }

            size_t compSlCompSize = slot.companionSocialLinkCompleted.size();
            outFile.write(reinterpret_cast<const char*>(&compSlCompSize), sizeof(compSlCompSize));
            for(const auto& slCompPair : slot.companionSocialLinkCompleted){
                size_t keyLen = slCompPair.first.length();
                outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
                outFile.write(slCompPair.first.c_str(), keyLen);
                outFile.write(reinterpret_cast<const char*>(&slCompPair.second), sizeof(slCompPair.second));
            }

            size_t dungeonVisitedSize = slot.dungeonVisitedCampAreasData.size();
            outFile.write(reinterpret_cast<const char*>(&dungeonVisitedSize), sizeof(dungeonVisitedSize));
            for(const auto& dPair : slot.dungeonVisitedCampAreasData) {
                size_t dNameLen = dPair.first.length();
                outFile.write(reinterpret_cast<const char*>(&dNameLen), sizeof(dNameLen));
                outFile.write(dPair.first.c_str(), dNameLen);
                size_t vecSize = dPair.second.size();
                outFile.write(reinterpret_cast<const char*>(&vecSize), sizeof(vecSize));
                for(int floorNum : dPair.second) {
                    outFile.write(reinterpret_cast<const char*>(&floorNum), sizeof(floorNum));
                }
            }
            
            size_t dungeonExploredSize = slot.dungeonExploredOnceFloorsData.size();
            outFile.write(reinterpret_cast<const char*>(&dungeonExploredSize), sizeof(dungeonExploredSize));
            for(const auto& dPair : slot.dungeonExploredOnceFloorsData) {
                size_t dNameLen = dPair.first.length();
                outFile.write(reinterpret_cast<const char*>(&dNameLen), sizeof(dNameLen));
                outFile.write(dPair.first.c_str(), dNameLen);
                size_t setSize = dPair.second.size();
                outFile.write(reinterpret_cast<const char*>(&setSize), sizeof(setSize));
                for(int floorNum : dPair.second) {
                    outFile.write(reinterpret_cast<const char*>(&floorNum), sizeof(floorNum));
                }
            }

            size_t defeatedBossesSize = slot.defeatedBossesData.size();
            outFile.write(reinterpret_cast<const char*>(&defeatedBossesSize), sizeof(defeatedBossesSize));
            for(const auto& bossPair : slot.defeatedBossesData) {
                size_t keyLen = bossPair.first.length();
                outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
                outFile.write(bossPair.first.c_str(), keyLen);
                outFile.write(reinterpret_cast<const char*>(&bossPair.second), sizeof(bossPair.second));
            }

            size_t activeQuestsSize = slot.activeDailyQuestsData.size();
            outFile.write(reinterpret_cast<const char*>(&activeQuestsSize), sizeof(activeQuestsSize));
            for(const auto& q : slot.activeDailyQuestsData){
                size_t titleLen = q.title.length(); outFile.write(reinterpret_cast<const char*>(&titleLen), sizeof(titleLen)); outFile.write(q.title.c_str(), titleLen);
                size_t descLen = q.description.length(); outFile.write(reinterpret_cast<const char*>(&descLen), sizeof(descLen)); outFile.write(q.description.c_str(), descLen);
                size_t typeLen = q.type.length(); outFile.write(reinterpret_cast<const char*>(&typeLen), sizeof(typeLen)); outFile.write(q.type.c_str(), typeLen);
                size_t targetLen = q.target.length(); outFile.write(reinterpret_cast<const char*>(&targetLen), sizeof(targetLen)); outFile.write(q.target.c_str(), targetLen);
                outFile.write(reinterpret_cast<const char*>(&q.dungeonFloor), sizeof(q.dungeonFloor));
                size_t dNameLen = q.dungeonName.length(); outFile.write(reinterpret_cast<const char*>(&dNameLen), sizeof(dNameLen)); outFile.write(q.dungeonName.c_str(), dNameLen);
                outFile.write(reinterpret_cast<const char*>(&q.taken), sizeof(q.taken));
                outFile.write(reinterpret_cast<const char*>(&q.completed), sizeof(q.completed));
                outFile.write(reinterpret_cast<const char*>(&q.expReward), sizeof(q.expReward));
                outFile.write(reinterpret_cast<const char*>(&q.goldReward), sizeof(q.goldReward));
                size_t rankLen = q.rank.length(); outFile.write(reinterpret_cast<const char*>(&rankLen), sizeof(rankLen)); outFile.write(q.rank.c_str(), rankLen);
            }
        }
    }
    outFile.close();
}

void saveGame() {
    system("cls");
    printLine();
    centerText(L"✦ SIMPAN PERMAINAN ✦");
    printLine();
    wcout << L"Pilih slot untuk menyimpan:" << endl;
    for (int i = 0; i < MAX_SAVE_SLOTS; ++i) {
        wcout << L" " << (i + 1) << L". Slot " << (i + 1) << ": ";
        if (saveSlots[i].isUsed) {
            wcout << utf8_to_wstring(saveSlots[i].slotName) << endl;
        } else {
            wcout << L"[Kosong]" << endl;
        }
    }
    wcout << L" 0. Batal" << endl;
    printLine();
    wcout << L"Pilihanmu ✦: ";
    int slotChoice = getValidatedChoice(0, MAX_SAVE_SLOTS);

    if (slotChoice == 0) {
        delayPrint(L"Penyimpanan dibatalkan.", 20);
        waitForEnter();
        return;
    }

    int slotIndex = slotChoice - 1;
    if (saveSlots[slotIndex].isUsed) {
        wcout << L"Slot ini sudah terisi. Timpa data simpanan ini? (y/n) ✦: ";
        char overwriteChoice;
        cin >> overwriteChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(overwriteChoice) != 'y') {
            delayPrint(L"Penyimpanan dibatalkan.", 20);
            waitForEnter();
            return;
        }
    }

    populateSaveSlotData(saveSlots[slotIndex]);
    writeSaveDataToFile();
    delayPrint(L"✅ Permainan berhasil disimpan di Slot " + to_wstring(slotChoice) + L"!", 20);
    waitForEnter();
}

void applySaveSlotData(const SaveSlot& slot) {
    initializeItems();
    initializeWeapons();
    initializeMagicSystem();
    player.name = slot.playerName;
    player.level = slot.playerLevel;
    player.hp = slot.playerHp;
    player.maxHp = slot.playerMaxHp;
    player.mana = slot.playerMana;
    player.maxMana = slot.playerMaxMana;
    player.strength = slot.playerStrength;
    player.defense = slot.playerDefense;
    player.intelligence = slot.playerIntelligence;
    player.agility = slot.playerAgility;
    player.exp = slot.playerExp;
    player.expToNextLevel = slot.playerExpToNextLevel;
    player.gold = slot.playerGold;
    player.skillPoints = slot.playerSkillPoints;
    player.unlockedMagicElements = slot.playerUnlockedMagicElements;
    player.knownSpells = slot.playerKnownSpells;
    
    player.inventory.clear();
    for (const string& itemName : slot.playerInventoryItemNames) {
        if (itemDatabase.count(itemName)) {
            player.inventory.push_back(itemDatabase.at(itemName));
        }
    }
    player.weapons.clear();
    player.equippedWeapon = nullptr; 
    for (const string& weaponName : slot.playerWeaponNames) {
        if (weaponDatabase.count(weaponName)) {
            Weapon* weaponToAdd = weaponDatabase.at(weaponName);
            player.weapons.push_back(weaponToAdd);
            if (weaponName == slot.playerEquippedWeaponName) {
                player.equippedWeapon = weaponToAdd;
                if (player.equippedWeapon) player.equippedWeapon->equipped = true;
            } else {
                 if(weaponToAdd) weaponToAdd->equipped = false;
            }
        }
    }
    if (player.equippedWeapon && player.weapons.empty()){ 
        player.equippedWeapon = nullptr;
    }


    currentDay = slot.currentDay;
    currentActionsRemaining = slot.currentActionsRemaining;
    currentWorld = slot.currentWorld;
    currentSubArea = slot.currentSubArea;
    storyFlags = slot.storyFlagsData; 

    while(!scheduledEvents.empty()) scheduledEvents.pop(); 
    for(const auto& ev : slot.scheduledEventsVector){
        scheduledEvents.push(ev);
    }

    initializeCompanions(); 
    companionRelations = slot.companionRelationsData;
    for(auto& comp : companions) { 
        bool foundInSave = false;
        for(const auto& savedCompName : slot.companionNamesMet) {
            if (comp.name == savedCompName) {
                comp.met = true;
                foundInSave = true;
                break;
            }
        }
        if (!foundInSave) {
            comp.met = false;
        }

        if(socialLinks.count(comp.name)){ 
            if(slot.companionSocialLinkLevels.count(comp.name)){
                socialLinks[comp.name].currentLevel = slot.companionSocialLinkLevels.at(comp.name);
            } else {
                socialLinks[comp.name].currentLevel = 1; 
            }
            if(slot.companionSocialLinkCompleted.count(comp.name)){
                socialLinks[comp.name].completed = slot.companionSocialLinkCompleted.at(comp.name);
            } else {
                socialLinks[comp.name].completed = false;
            }
        }
    }
    
    companionCurrentLocations = slot.companionCurrentLocations;
    if (companionCurrentLocations.empty()) { // Fallback for old saves or if not explicitly saved
        for (auto& comp : companions) {
            if (comp.name == "Charlotte") {
                companionCurrentLocations[comp.name] = "Balai Kota";
            } else if (comp.name == "Masha") {
                companionCurrentLocations[comp.name] = "Taman Norelia";
            } else if (comp.name == "Mars") {
                companionCurrentLocations[comp.name] = "Pos Hutan";
            } else if (comp.name == "Kinich") {
                companionCurrentLocations[comp.name] = "Camp Avernix";
            } else if (comp.name == "Ruigerd") {
                companionCurrentLocations[comp.name] = "Dapur Mansion";
            } else if (comp.name == "Irene") {
                companionCurrentLocations[comp.name] = "Taman Floresia";
            } else if (comp.name == "Ella") {
                companionCurrentLocations[comp.name] = "Cross Guild";
            }
        }
    }
    

    initializeDungeons(); 
    for(const auto& pair_dungeon_data : slot.dungeonVisitedCampAreasData) {
        if(allDungeons.count(pair_dungeon_data.first)){
            allDungeons.at(pair_dungeon_data.first).visitedCampAreas = pair_dungeon_data.second;
        }
    }
    for(const auto& pair_dungeon_data : slot.dungeonExploredOnceFloorsData) {
         if(allDungeons.count(pair_dungeon_data.first)){
            allDungeons.at(pair_dungeon_data.first).exploredOnceFloors = pair_dungeon_data.second;
        }
    }
    defeatedBosses = slot.defeatedBossesData;

    ActiveDailyQuestNode* temp = activeDailyQuestsHead;
    while(temp != nullptr){
        ActiveDailyQuestNode* next = temp->next;
        delete temp;
        temp = next;
    }
    activeDailyQuestsHead = nullptr;
    for(const auto& qData : slot.activeDailyQuestsData){
        ActiveDailyQuestNode* newNode = new ActiveDailyQuestNode();
        newNode->data = qData;
        newNode->next = activeDailyQuestsHead;
        activeDailyQuestsHead = newNode;
    }
    
    initializeAllQuests();
    generateDailyQuests();

    player.activeEnchantments.clear();
    player.activeHoTs.clear();
    player.temporaryStrengthBuff = 0;
    player.temporaryIntelligenceBuff = 0;

    setupWorldAreas();
    setupConnections();
    
    talkedToday.clear();

}

void readSaveDataFromFile() {
    ifstream inFile(SAVE_FILE_NAME, ios::binary);
    if (!inFile) {
        delayPrint(L"File save tidak ditemukan atau tidak bisa dibuka. Mungkin belum ada game yang disimpan?", 20);
        
        for(int i=0; i<MAX_SAVE_SLOTS; ++i) saveSlots[i].isUsed = false;
        waitForEnter();
        return;
    }

    for (int i = 0; i < MAX_SAVE_SLOTS; ++i) {
        SaveSlot& slot = saveSlots[i];
        inFile.read(reinterpret_cast<char*>(&slot.isUsed), sizeof(slot.isUsed));
        if (slot.isUsed && !inFile.eof()) { // Tambahkan pengecekan eof
            size_t slotNameLen;
            inFile.read(reinterpret_cast<char*>(&slotNameLen), sizeof(slotNameLen));
            slot.slotName.resize(slotNameLen);
            inFile.read(&slot.slotName[0], slotNameLen);
            inFile.read(reinterpret_cast<char*>(&slot.saveTime), sizeof(slot.saveTime));

            size_t playerNameLen;
            inFile.read(reinterpret_cast<char*>(&playerNameLen), sizeof(playerNameLen));
            slot.playerName.resize(playerNameLen);
            inFile.read(&slot.playerName[0], playerNameLen);
            inFile.read(reinterpret_cast<char*>(&slot.playerLevel), sizeof(slot.playerLevel));
            inFile.read(reinterpret_cast<char*>(&slot.playerHp), sizeof(slot.playerHp));
            inFile.read(reinterpret_cast<char*>(&slot.playerMaxHp), sizeof(slot.playerMaxHp));
            inFile.read(reinterpret_cast<char*>(&slot.playerMana), sizeof(slot.playerMana));
            inFile.read(reinterpret_cast<char*>(&slot.playerMaxMana), sizeof(slot.playerMaxMana));
            inFile.read(reinterpret_cast<char*>(&slot.playerStrength), sizeof(slot.playerStrength));
            inFile.read(reinterpret_cast<char*>(&slot.playerDefense), sizeof(slot.playerDefense));
            inFile.read(reinterpret_cast<char*>(&slot.playerIntelligence), sizeof(slot.playerIntelligence));
            inFile.read(reinterpret_cast<char*>(&slot.playerAgility), sizeof(slot.playerAgility));
            inFile.read(reinterpret_cast<char*>(&slot.playerExp), sizeof(slot.playerExp));
            inFile.read(reinterpret_cast<char*>(&slot.playerExpToNextLevel), sizeof(slot.playerExpToNextLevel));
            inFile.read(reinterpret_cast<char*>(&slot.playerGold), sizeof(slot.playerGold));
            inFile.read(reinterpret_cast<char*>(&slot.playerSkillPoints), sizeof(slot.playerSkillPoints));
            
            size_t unlockedElementsSize;
            inFile.read(reinterpret_cast<char*>(&unlockedElementsSize), sizeof(unlockedElementsSize));
            slot.playerUnlockedMagicElements.resize(unlockedElementsSize);
            for (size_t j = 0; j < unlockedElementsSize; ++j) {
                size_t elemLen; inFile.read(reinterpret_cast<char*>(&elemLen), sizeof(elemLen));
                slot.playerUnlockedMagicElements[j].resize(elemLen);
                inFile.read(&slot.playerUnlockedMagicElements[j][0], elemLen);
            }

            size_t knownSpellsSize;
            inFile.read(reinterpret_cast<char*>(&knownSpellsSize), sizeof(knownSpellsSize));
            slot.playerKnownSpells.resize(knownSpellsSize);
            for (size_t j = 0; j < knownSpellsSize; ++j) {
                size_t idLen; inFile.read(reinterpret_cast<char*>(&idLen), sizeof(idLen));
                slot.playerKnownSpells[j].resize(idLen);
                inFile.read(&slot.playerKnownSpells[j][0], idLen);
            }
            
            size_t equippedWeaponNameLen;
            inFile.read(reinterpret_cast<char*>(&equippedWeaponNameLen), sizeof(equippedWeaponNameLen));
            slot.playerEquippedWeaponName.resize(equippedWeaponNameLen);
            inFile.read(&slot.playerEquippedWeaponName[0], equippedWeaponNameLen);


            size_t inventorySize;
            inFile.read(reinterpret_cast<char*>(&inventorySize), sizeof(inventorySize));
            slot.playerInventoryItemNames.resize(inventorySize);
            for (size_t j = 0; j < inventorySize; ++j) {
                size_t nameLen; inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
                slot.playerInventoryItemNames[j].resize(nameLen);
                inFile.read(&slot.playerInventoryItemNames[j][0], nameLen);
            }

            size_t weaponsSize;
            inFile.read(reinterpret_cast<char*>(&weaponsSize), sizeof(weaponsSize));
            slot.playerWeaponNames.resize(weaponsSize);
            for (size_t j = 0; j < weaponsSize; ++j) {
                size_t nameLen; inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
                slot.playerWeaponNames[j].resize(nameLen);
                inFile.read(&slot.playerWeaponNames[j][0], nameLen);
            }

            inFile.read(reinterpret_cast<char*>(&slot.currentDay), sizeof(slot.currentDay));
            inFile.read(reinterpret_cast<char*>(&slot.currentActionsRemaining), sizeof(slot.currentActionsRemaining));
            
            size_t currentWorldLen; inFile.read(reinterpret_cast<char*>(&currentWorldLen), sizeof(currentWorldLen));
            slot.currentWorld.resize(currentWorldLen); inFile.read(&slot.currentWorld[0], currentWorldLen);
            
            size_t currentSubAreaLen; inFile.read(reinterpret_cast< char*>(&currentSubAreaLen), sizeof(currentSubAreaLen));
            slot.currentSubArea.resize(currentSubAreaLen); inFile.read(&slot.currentSubArea[0], currentSubAreaLen);

            size_t storyFlagsSize;
            inFile.read(reinterpret_cast<char*>(&storyFlagsSize), sizeof(storyFlagsSize));
            slot.storyFlagsData.clear();
            for (size_t j = 0; j < storyFlagsSize; ++j) {
                size_t keyLen; inFile.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
                string key; key.resize(keyLen); inFile.read(&key[0], keyLen);
                int value; inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
                slot.storyFlagsData[key] = value;
            }
            
            size_t scheduledEventsVecSize;
            inFile.read(reinterpret_cast<char*>(&scheduledEventsVecSize), sizeof(scheduledEventsVecSize));
            slot.scheduledEventsVector.resize(scheduledEventsVecSize);
            for(size_t j=0; j < scheduledEventsVecSize; ++j){
                GameEvent ev;
                size_t eventNameLen; inFile.read(reinterpret_cast<char*>(&eventNameLen), sizeof(eventNameLen));
                ev.eventName.resize(eventNameLen); inFile.read(&ev.eventName[0], eventNameLen);
                size_t descLen; inFile.read(reinterpret_cast<char*>(&descLen), sizeof(descLen));
                ev.description.resize(descLen); inFile.read(&ev.description[0], descLen);
                inFile.read(reinterpret_cast<char*>(&ev.dayTrigger), sizeof(ev.dayTrigger));
                inFile.read(reinterpret_cast<char*>(&ev.triggered), sizeof(ev.triggered));
                slot.scheduledEventsVector[j] = ev;
            }

            size_t compMetSize; inFile.read(reinterpret_cast<char*>(&compMetSize), sizeof(compMetSize));
            slot.companionNamesMet.resize(compMetSize);
            for(size_t j=0; j<compMetSize; ++j){
                size_t cnLen; inFile.read(reinterpret_cast<char*>(&cnLen), sizeof(cnLen));
                slot.companionNamesMet[j].resize(cnLen); inFile.read(&slot.companionNamesMet[j][0], cnLen);
            }

            size_t compRelSize; inFile.read(reinterpret_cast<char*>(&compRelSize), sizeof(compRelSize));
            slot.companionRelationsData.clear();
            for(size_t j=0; j<compRelSize; ++j){
                size_t keyLen; inFile.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
                string key; key.resize(keyLen); inFile.read(&key[0], keyLen);
                int value; inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
                slot.companionRelationsData[key] = value;
            }
            
            size_t compSlLvlSize; inFile.read(reinterpret_cast<char*>(&compSlLvlSize), sizeof(compSlLvlSize));
            slot.companionSocialLinkLevels.clear();
            for(size_t j=0; j<compSlLvlSize; ++j){
                size_t keyLen; inFile.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
                string key; key.resize(keyLen); inFile.read(&key[0], keyLen);
                int value; inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
                slot.companionSocialLinkLevels[key] = value;
            }

            size_t compSlCompSize; inFile.read(reinterpret_cast<char*>(&compSlCompSize), sizeof(compSlCompSize));
            slot.companionSocialLinkCompleted.clear();
            for(size_t j=0; j<compSlCompSize; ++j){
                size_t keyLen; inFile.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
                string key; key.resize(keyLen); inFile.read(&key[0], keyLen);
                bool value; inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
                slot.companionSocialLinkCompleted[key] = value;
            }
            
            size_t dungeonVisitedSize; inFile.read(reinterpret_cast<char*>(&dungeonVisitedSize), sizeof(dungeonVisitedSize));
            slot.dungeonVisitedCampAreasData.clear();
            for(size_t j=0; j<dungeonVisitedSize; ++j){
                size_t dNameLen; inFile.read(reinterpret_cast<char*>(&dNameLen), sizeof(dNameLen));
                string dNameKey; dNameKey.resize(dNameLen); inFile.read(&dNameKey[0], dNameLen);
                size_t vecSize; inFile.read(reinterpret_cast<char*>(&vecSize), sizeof(vecSize));
                vector<int> floors(vecSize);
                for(size_t k=0; k<vecSize; ++k) { inFile.read(reinterpret_cast<char*>(&floors[k]), sizeof(int)); }
                slot.dungeonVisitedCampAreasData[dNameKey] = floors;
            }
            
            size_t dungeonExploredSize; inFile.read(reinterpret_cast<char*>(&dungeonExploredSize), sizeof(dungeonExploredSize));
            slot.dungeonExploredOnceFloorsData.clear();
            for(size_t j=0; j<dungeonExploredSize; ++j){
                size_t dNameLen; inFile.read(reinterpret_cast<char*>(&dNameLen), sizeof(dNameLen));
                string dNameKey; dNameKey.resize(dNameLen); inFile.read(&dNameKey[0], dNameLen);
                size_t setSize; inFile.read(reinterpret_cast<char*>(&setSize), sizeof(setSize));
                unordered_set<int> floors;
                for(size_t k=0; k<setSize; ++k) { int floorNum; inFile.read(reinterpret_cast<char*>(&floorNum), sizeof(int)); floors.insert(floorNum); }
                slot.dungeonExploredOnceFloorsData[dNameKey] = floors;
            }

            size_t defeatedBossesSize; inFile.read(reinterpret_cast<char*>(&defeatedBossesSize), sizeof(defeatedBossesSize));
            slot.defeatedBossesData.clear();
            for(size_t j=0; j<defeatedBossesSize; ++j){
                size_t keyLen; inFile.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
                string key; key.resize(keyLen); inFile.read(&key[0], keyLen);
                bool value; inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
                slot.defeatedBossesData[key] = value;
            }
            
            size_t activeQuestsSize; inFile.read(reinterpret_cast<char*>(&activeQuestsSize), sizeof(activeQuestsSize));
            slot.activeDailyQuestsData.resize(activeQuestsSize);
            for(size_t j=0; j<activeQuestsSize; ++j){
                DailyQuest q;
                size_t titleLen; inFile.read(reinterpret_cast<char*>(&titleLen), sizeof(titleLen)); q.title.resize(titleLen); inFile.read(&q.title[0], titleLen);
                size_t descLen; inFile.read(reinterpret_cast<char*>(&descLen), sizeof(descLen)); q.description.resize(descLen); inFile.read(&q.description[0], descLen);
                size_t typeLen; inFile.read(reinterpret_cast<char*>(&typeLen), sizeof(typeLen)); q.type.resize(typeLen); inFile.read(&q.type[0], typeLen);
                size_t targetLen; inFile.read(reinterpret_cast<char*>(&targetLen), sizeof(targetLen)); q.target.resize(targetLen); inFile.read(&q.target[0], targetLen);
                inFile.read(reinterpret_cast<char*>(&q.dungeonFloor), sizeof(q.dungeonFloor));
                size_t dNameLen; inFile.read(reinterpret_cast<char*>(&dNameLen), sizeof(dNameLen)); q.dungeonName.resize(dNameLen); inFile.read(&q.dungeonName[0], dNameLen);
                inFile.read(reinterpret_cast<char*>(&q.taken), sizeof(q.taken));
                inFile.read(reinterpret_cast<char*>(&q.completed), sizeof(q.completed));
                inFile.read(reinterpret_cast<char*>(&q.expReward), sizeof(q.expReward));
                inFile.read(reinterpret_cast<char*>(&q.goldReward), sizeof(q.goldReward));
                size_t rankLen; inFile.read(reinterpret_cast<char*>(&rankLen), sizeof(rankLen)); q.rank.resize(rankLen); inFile.read(&q.rank[0], rankLen);
                slot.activeDailyQuestsData[j] = q;
            }
        } else if (inFile.eof() && !slot.isUsed) {

        } else if (!inFile.eof()){
            slot.isUsed = false; 
        }
    }
    inFile.close();
}



void loadGame() {
    readSaveDataFromFile(); 
    system("cls");
    printLine();
    centerText(L"✦ MUAT PERMAINAN ✦");
    printLine();
    wcout << L"Pilih slot untuk dimuat:" << endl;
    bool hasSave = false;
    for (int i = 0; i < MAX_SAVE_SLOTS; ++i) {
        wcout << L" " << (i + 1) << L". Slot " << (i + 1) << ": ";
        if (saveSlots[i].isUsed) {
            wcout << utf8_to_wstring(saveSlots[i].slotName) << endl;
            hasSave = true;
        } else {
            wcout << L"[Kosong]" << endl;
        }
    }

    if (!hasSave) {
        delayPrint(L"Tidak ada data simpanan yang ditemukan.", 20);
        waitForEnter();
        return;
    }

    wcout << L" 0. Batal" << endl;
    printLine();
    wcout << L"Pilihanmu ✦: ";
    int slotChoice = getValidatedChoice(0, MAX_SAVE_SLOTS);

    if (slotChoice == 0) {
        delayPrint(L"Pemuatan dibatalkan.", 20);
        waitForEnter();
        return;
    }

    int slotIndex = slotChoice - 1;
    if (!saveSlots[slotIndex].isUsed) {
        delayPrint(L"Slot ini kosong. Tidak ada yang bisa dimuat.", 20);
        waitForEnter();
        return;
    }

    applySaveSlotData(saveSlots[slotIndex]);
    gameRunning = true;

    delayPrint(L"✅ Permainan berhasil dimuat dari Slot " + to_wstring(slotChoice) + L"!", 20);
    waitForEnter();

    while (gameRunning) {
        showGameMenu(); 
    }

}


void showDiaryMenu() {
    int choice;
    do {
        system("cls");
        printLine();
        centerText(L"✦✦✦ BUKA DIARY ✦✦✦");
        printLine();       
        wcout << L"❖ 1. Status Karakter" << endl;
        wcout << L"❖ 2. Tas Inventory" << endl;
        wcout << L"❖ 3. Quest List" << endl;
        wcout << L"❖ 4. Skill Tree" << endl;
        wcout << L"❖ 5. Companion List" << endl;
        wcout << L"❖ 6. Kalender Perubahan" << endl;
        wcout << L"❖ 7. Save Game" << endl;
        wcout << L"❖ 8. Load Game" << endl;
        wcout << L"❖ 9. Tutup Diary" << endl;
        wcout << L"❖ 0. Kembali ke Main Menu" << endl;
        printLine(50, L'─');
        wcout << L"Pilih menu ✦: ";
        
        choice = getValidatedChoice(0, 9); 

        
        switch(choice) {
            case 1: {
                
                system("cls");
                printLine();
                centerText(L"✦✦✦ STATUS KARAKTER ✦✦✦");
                printLine();
                wcout << L"Nama: " << player.name.c_str() << endl;
                wcout << L"Level: " << player.level << endl;
                wcout << L"HP: " << player.hp << L"/" << player.maxHp << endl;
                wcout << L"Mana: " << player.mana << L"/" << player.maxMana << endl;
                wcout << L"Strength: " << player.strength << endl;
                wcout << L"Intelligence: " << player.intelligence << endl;
                wcout << L"Agility: " << player.agility << endl;
                wcout << L"Experience: " << player.exp << endl;
                wcout << L"Gold: " << player.gold << endl;
                printLine();
                waitForEnter();
                break;
            }
            case 2: {
                
                int invChoice;
                do {
                    showInventoryCategory();
                    cin >> invChoice;
                    
                    if(invChoice == 1) {
                        
                        int itemChoice;
                        do {
                            showItemList();
                            cin >> itemChoice;
                            
                            if(itemChoice > 0 && itemChoice <= player.inventory.size()) {
                                Item* selectedItem = player.inventory[itemChoice-1];
                                int detailChoice;
                                do {
                                    showItemDetail(selectedItem);
                                    cin >> detailChoice;
                                    
                                    if (detailChoice == 1 && selectedItem->type == "consumable") {
                                    applyItemEffect(selectedItem->name);
                                    detailChoice = 2; 
                                    itemChoice = 0;   
                                }
                                } while(detailChoice != 2);
                            }
                        } while(itemChoice != 0);
                    } else if(invChoice == 2) {
                        
                        int weaponChoice;
                        do {
                            showWeaponList();
                            cin >> weaponChoice;
                            
                            if(weaponChoice > 0 && weaponChoice <= player.weapons.size()) {
                                Weapon* selectedWeapon = player.weapons[weaponChoice-1];
                                int detailChoice;
                                do {
                                    showWeaponDetail(selectedWeapon);
                                    cin >> detailChoice;
                                    
                                    if(detailChoice == 1) {
                                        if(!selectedWeapon->equipped) {
                                            
                                            if(player.strength >= selectedWeapon->strengthRequired && 
                                               player.intelligence >= selectedWeapon->intelligenceRequired) {
                                                
                                                if(player.equippedWeapon) {
                                                    player.equippedWeapon->equipped = false;
                                                }
                                                selectedWeapon->equipped = true;
                                                player.equippedWeapon = selectedWeapon;
                                                wcout << L"Senjata " << selectedWeapon->name.c_str() << L" berhasil dipasang!" << endl;
                                            } else {
                                                wcout << L"Persyaratan stat tidak terpenuhi!" << endl;
                                                wcout << L"Dibutuhkan Strength: " << selectedWeapon->strengthRequired;
                                                wcout << L", Intelligence: " << selectedWeapon->intelligenceRequired << endl;
                                            }
                                        } else {
                                            selectedWeapon->equipped = false;
                                            player.equippedWeapon = nullptr;
                                            wcout << L"Senjata " << selectedWeapon->name.c_str() << L" dilepas!" << endl;
                                        }
                                        waitForEnter();
                                    }
                                } while(detailChoice != 2);
                            }
                        } while(weaponChoice != 0);
                    }
                } while(invChoice != 3);
                break;
            }
            case 3: {
                showActiveQuestsInDiary();
                break;
            }
            case 5: {
                int compChoice;
                do {
                    showCompanionListScreen(); 
                    cin >> compChoice;

                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        delayPrint(L"Pilihan tidak valid. Coba lagi.", 20);
                        system("pause"); 
                        compChoice = -1; 
                        continue;
                    }
                    
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');


                    if (compChoice > 0 && compChoice <= static_cast<int>(companions.size())) {
                        
                        
                        showCompanionDetailScreen(companions[compChoice - 1]);
                        
                    } else if (compChoice != 0) {
                        delayPrint(L"Nomor pilihan tidak ada dalam daftar.", 20);
                        system("pause");
                    }
                } while (compChoice != 0);
                break;
            }
            case 6: {
                
                int calChoice;
                do {
                    showCalendar();
                    cin >> calChoice;
                } while(calChoice != 1);
                break;
            }
            case 4:
                showSkillTreeMenu(player);
                break;
            case 7: 
                saveGame();
                break;
            case 8:
                loadGame();
                break;
        }
    } while(choice != 9 && choice != 0);
    
    if(choice == 0) {
        gameRunning = false;
    }
}

void applySocialLinkBonus(const string& npcName) {
    system("cls"); 
    printLine();
    centerText(L"✦✦✦ IKATAN TELAH MENCAPAI PUNCAK ✦✦✦");
    printLine();
    delayPrint(L"Hubunganmu dengan " + utf8_to_wstring(npcName) + L" telah mencapai level tertinggi!", 30);
    delayPrint(L"Ikatan yang kuat ini memberimu kekuatan baru dan sebuah kenang-kenangan berharga.", 20);
    wcout << endl;

    string weaponNameToAdd = "";
    string uppercaseNpcName = npcName;
    transform(uppercaseNpcName.begin(), uppercaseNpcName.end(), uppercaseNpcName.begin(), ::toupper);
    string flagToSet = uppercaseNpcName + "_LV10_COMPLETE";

    if (npcName == "Masha") {
        weaponNameToAdd = "Aurora's Thorned Blossom";
        delayPrint(L"Kepercayaan dan pemahaman mendalam dengan Putri Masha telah membuka jalan baru bagimu.", 20);
    } else if (npcName == "Kinich") {
        weaponNameToAdd = "Heartstone Pickaxe";
        delayPrint(L"Para penambang Avernix kini menghormatimu setinggi Kinich menghargai batu permata.", 20);
    } else if (npcName == "Irene") {
        weaponNameToAdd = "Gardener's Gentle Thorn";
        delayPrint(L"Kehangatan dan kesetiaan tulus Irene memberimu semangat dan harapan baru.", 20);
    } else if (npcName == "Ruigerd") {
        weaponNameToAdd = "Chef's Honor Cleaver";
        delayPrint(L"Resep kehidupan dan kearifan Ruigerd kini terukir dalam jiwamu, setajam bilah kehormatannya.", 20);
    } else if (npcName == "Ella") {
        weaponNameToAdd = "Guildmaster's Ledger Blade";
        delayPrint(L"Cross Guild, di bawah kepemimpinan Ella, kini menjadi sekutu kuat yang tak tergoyahkan.", 20);
    } else if (npcName == "Charlotte") {
        weaponNameToAdd = "Truthseeker's Quillpoint";
        delayPrint(L"Pena kebenaran Charlotte yang tajam kini juga menjadi bagian dari persenjataanmu melawan ketidakadilan.", 20);
    } else if (npcName == "Mars") {
        weaponNameToAdd = "Warden's Silent Fang (Knife)"; 
        delayPrint(L"Roh Hutan Merah kini mengalir dalam dirimu, melindungimu melalui ikatan sucimu dengan Mars.", 20);
    }

  
    if (!flagToSet.empty()) {
        storyFlags[flagToSet] = 1; 
    }

    if (!weaponNameToAdd.empty() && weaponDatabase.count(weaponNameToAdd)) {
        Weapon* specialWeapon = weaponDatabase[weaponNameToAdd];

  
        bool alreadyOwned = false;
        for (const auto* pWeapon : player.weapons) {
            if (pWeapon && pWeapon->name == weaponNameToAdd) {
                alreadyOwned = true;
                break;
            }
        }

        if (!alreadyOwned && specialWeapon) { 
            player.weapons.push_back(specialWeapon);
            wcout << endl;
            delayPrint(L"✨ Kamu menerima sebuah senjata istimewa sebagai tanda ikatanmu: ✨", 30);
            printLine(40, L'-');
            centerText(L"📜 " + utf8_to_wstring(specialWeapon->name) + L" 📜", 40);
            printLine(40, L'-');
            delayPrint(L"   " + utf8_to_wstring(specialWeapon->description), 20);
            wcout << endl;
        } else if (alreadyOwned && specialWeapon) {
            delayPrint(L"Kamu sudah memiliki " + utf8_to_wstring(specialWeapon->name) + L", namun ikatanmu tetap menjadi yang terkuat.", 20);
        } else if (!weaponNameToAdd.empty() && !specialWeapon) {
             delayPrint(L"[ERROR INTERNAL] Senjata spesial '" + utf8_to_wstring(weaponNameToAdd) + L"' tidak ditemukan datanya di database!", 20);
        }
    } else if (!weaponNameToAdd.empty()) {
        delayPrint(L"[ERROR] Definisi senjata spesial '" + utf8_to_wstring(weaponNameToAdd) + L"' tidak ditemukan di database!", 20);
    }

    int bonusHp = 15 + rand() % 11; 
    int bonusMana = 10 + rand() % 6; 
    player.maxHp += bonusHp;
    player.hp += bonusHp; 
    player.maxMana += bonusMana;
    player.mana += bonusMana;

    wcout << endl;
    delayPrint(L"Ikatanmu yang tak terpatahkan memberimu kekuatan baru:", 20);
    delayPrint(L"   💖 Max HP +" + to_wstring(bonusHp), 20);
    delayPrint(L"   💠 Max Mana +" + to_wstring(bonusMana), 20);
    if (npcName == "Masha" || npcName == "Charlotte") player.intelligence +=1; 
    if (npcName == "Kinich" || npcName == "Mars") player.strength +=1;
    if (npcName == "Ruigerd" || npcName == "Ella") player.defense +=1;
    if (npcName == "Irene") player.agility +=1;


    printLine();

}

void sceneRuigerdLevel1() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 1 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Masuk ke dapur yang ramai namun teratur) \"Permisi, Kepala Koki Ruigerd. Apakah saya mengganggu?\"", 30);
    delayPrint(L"Ruigerd: (Menoleh dari panci besar yang mengepulkan uap, sedikit terkejut) \"Tuan Muda Weiss! Tidak sama sekali. Suatu kehormatan Anda mengunjungi dapur. Ada yang bisa saya bantu, Tuan Muda?\"", 30);
    delayPrint(L"Weiss: \"Tidak ada yang spesifik. Hanya ingin melihat-lihat. Aroma dari sini selalu luar biasa. Apa yang sedang Anda siapkan untuk makan malam nanti?\"", 30);
    delayPrint(L"Ruigerd: \"Malam ini menu utamanya adalah Daging Panggang Rempah ala Astra, Tuan Muda. Dengan saus jamur hutan dan beberapa hidangan pendamping sayuran musim semi.\"", 30);
    delayPrint(L"Weiss: \"Kedengarannya lezat. Saya selalu mengagumi bagaimana Anda dan tim Anda bisa menyajikan begitu banyak hidangan setiap hari dengan kualitas yang konsisten.\"", 30);
    delayPrint(L"Ruigerd: (Sedikit tersenyum, sebuah senyum profesional) \"Itu sudah menjadi tugas kami, Tuan Muda. Memastikan keluarga Astra mendapatkan yang terbaik. Apakah ada preferensi khusus untuk hidangan Anda malam ini?\"", 30);
    delayPrint(L"Weiss: \"Tidak ada. Saya percaya penuh pada keahlian Anda, Kepala Koki. Terima kasih atas waktunya. Saya tidak akan mengganggu lebih lama.\"", 30);
    delayPrint(L"Ruigerd: \"Sama-sama, Tuan Muda. Jika ada apapun, jangan ragu memberitahu saya.\"", 30);
    delayPrint(L"Weiss: \"Tentu. Selamat melanjutkan pekerjaan Anda.\"", 30);
    delayPrint(L"Ruigerd: \"Terima kasih, Tuan Muda.\"", 30);
    delayPrint(L"Ruigerd kembali fokus pada pekerjaannya, namun kamu merasa ada sedikit rasa ingin tahu dalam tatapannya. Kunjunganmu yang sopan mungkin sedikit mengejutkannya.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel2() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 2 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Kepala Koki Ruigerd, saya perhatikan Anda selalu menggunakan jenis kayu bakar tertentu untuk oven panggang. Apakah ada alasan khusus?\"", 30);
    delayPrint(L"Ruigerd: (Mengelap tangannya di celemek, menoleh ke Weiss) \"Pengamatan yang baik, Tuan Muda. Ya, saya lebih suka menggunakan kayu dari pohon apel atau ceri untuk memanggang daging. Asapnya memberikan aroma manis yang khas dan tidak terlalu kuat.\"", 30);
    delayPrint(L"Weiss: \"Menarik sekali. Saya tidak pernah tahu hal sedetail itu bisa mempengaruhi rasa. Apakah itu teknik umum atau rahasia dapur Astra?\"", 30);
    delayPrint(L"Ruigerd: (Tersenyum tipis) \"Kombinasi keduanya, Tuan Muda. Ada beberapa teknik dasar yang kami pelajari, tapi setiap koki biasanya punya sentuhan pribadi. Bagaimana sarapan Anda pagi ini? Apakah Roti Panggang Madu-Kayumanisnya sesuai selera?\"", 30);
    delayPrint(L"Weiss: \"Sangat lezat, Kepala Koki. Seperti biasa. Kehangatannya pas dan rasa manisnya tidak berlebihan. Apakah ada bahan rahasia di dalamnya?\"", 30);
    delayPrint(L"Ruigerd: \"Tidak ada rahasia besar, Tuan Muda. Hanya bahan-bahan segar berkualitas dan sedikit kesabaran dalam proses pemanggangan. Itu kunci utama dalam memasak.\"", 30);
    delayPrint(L"Weiss: \"Kesabaran, ya? Saya rasa itu berlaku untuk banyak hal, bukan hanya memasak. Terima kasih atas penjelasannya, Kepala Koki.\"", 30);
    delayPrint(L"Ruigerd: \"Dengan senang hati, Tuan Muda. Apakah Anda tertarik mempelajari lebih banyak tentang seni kuliner?\"", 30);
    delayPrint(L"Weiss: \"Mungkin suatu saat nanti. Untuk saat ini, saya cukup menikmati hasil karya Anda.\" (tersenyum)", 30);
    delayPrint(L"Ruigerd: \"Sebuah kehormatan bagi saya, Tuan Muda.\"", 30);
    delayPrint(L"Ruigerd tampak sedikit lebih terbuka hari ini, mungkin karena ketertarikanmu yang tulus pada keahliannya.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel3() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 3 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Kepala Koki Ruigerd, sup jamur yang disajikan semalam benar-benar istimewa. Rasanya sangat kaya dan... berbeda dari biasanya. Apa ada yang spesial?\"", 30);
    delayPrint(L"Ruigerd: (Wajahnya sedikit cerah mendengar pujian itu) \"Ah, Tuan Muda memperhatikan. Ya, saya menggunakan jamur Morel liar yang baru saja dikirim dari pemasok di pegunungan utara. Jenis itu hanya tumbuh di musim tertentu dan punya aroma tanah yang khas.\"", 30);
    delayPrint(L"Weiss: \"Jamur Morel liar? Pantas saja. Saya pernah membacanya di buku, tapi baru pertama kali mencicipinya. Apakah sulit untuk mengolahnya?\"", 30);
    delayPrint(L"Ruigerd: \"Membutuhkan penanganan yang hati-hati, Tuan Muda. Karena teksturnya yang lembut dan mudah hancur. Saya hanya menumisnya sebentar dengan bawang putih dan sedikit thyme segar sebelum dimasukkan ke dalam kaldu krim.\"", 30);
    delayPrint(L"Weiss: \"Kedengarannya sederhana, tapi hasilnya luar biasa. Apakah Anda sering bereksperimen dengan bahan-bahan musiman seperti itu?\"", 30);
    delayPrint(L"Ruigerd: \"Selalu, Tuan Muda. Menggunakan bahan musiman adalah cara terbaik untuk mendapatkan rasa yang optimal. Alam selalu menyediakan yang terbaik pada waktunya. Saya senang Anda menikmatinya.\"", 30);
    delayPrint(L"Weiss: \"Sangat menikmati. Itu mungkin sup terbaik yang pernah saya makan. Tolong sampaikan pujian saya kepada seluruh tim dapur juga.\"", 30);
    delayPrint(L"Ruigerd: (Mengangguk dengan bangga) \"Akan saya sampaikan, Tuan Muda. Pujian dari Anda sangat berarti bagi kami semua. Apakah ada hidangan lain yang ingin Anda coba dengan bahan musiman tertentu?\"", 30);
    delayPrint(L"Weiss: \"Saya serahkan pada keahlian Anda, Kepala Koki. Kejutan dari dapur Anda selalu menyenangkan.\"", 30);
    delayPrint(L"Ruigerd: \"Saya akan pastikan ada kejutan menyenangkan lainnya untuk Anda, Tuan Muda.\"", 30);
    delayPrint(L"Kamu melihat sedikit kilau antusiasme di mata Ruigerd saat berbicara tentang pekerjaannya. Sepertinya dia benar-benar mencintai apa yang dilakukannya.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel4() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 4 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Melihat Ruigerd sedang dengan sabar mengajari seorang juru masak muda cara memotong sayuran dengan benar) \"Kepala Koki Ruigerd, Anda terlihat sangat telaten mengajari staf baru.\"", 30);
    delayPrint(L"Ruigerd: (Menoleh sambil tersenyum tipis) \"Tuan Muda Weiss. Ya, regenerasi itu penting di setiap profesi, termasuk di dapur. Keterampilan dasar seperti ini adalah fondasi. Jika fondasinya kuat, bangunannya juga akan kokoh.\"", 30);
    delayPrint(L"Weiss: \"Sebuah filosofi yang bagus. Tapi tidakkah itu melelahkan, mengulang hal yang sama berulang kali? Saya perhatikan anak muda itu sudah beberapa kali salah memegang pisau.\"", 30);
    delayPrint(L"Ruigerd: \"Memasak itu seperti kehidupan, Tuan Muda. Butuh kesabaran dan ketekunan. Tidak ada yang langsung ahli. Kesalahan adalah bagian dari proses belajar. Yang penting, jangan menyerah dan terus mencoba memperbaiki diri. Sama seperti saat kita mencoba resep baru, terkadang gagal, tapi dari kegagalan itu kita belajar.\"", 30);
    delayPrint(L"Weiss: \"Kata-kata yang bijak, Kepala Koki. Saya jadi teringat, apakah ada hidangan yang menurut Anda paling sulit untuk dikuasai? Yang membutuhkan kesabaran paling ekstra?\"", 30);
    delayPrint(L"Ruigerd: (Berpikir sejenak) \"Mungkin membuat saus hollandaise yang sempurna, Tuan Muda. Keseimbangan antara mentega cair, kuning telur, dan lemon harus tepat. Terlalu panas, saus akan pecah. Terlalu dingin, tidak akan mengental. Butuh perasaan dan latihan bertahun-tahun.\"", 30);
    delayPrint(L"Weiss: \"Begitu rupanya. Saya jadi semakin menghargai setiap hidangan yang tersaji di meja makan. Ada begitu banyak usaha dan dedikasi di baliknya.\"", 30);
    delayPrint(L"Ruigerd: \"Kami senang jika usaha kami dihargai, Tuan Muda. Itu memberi kami semangat. Apakah Anda ingin mencoba memotong sayuran ini? Saya bisa ajari dasarnya.\"", 30);
    delayPrint(L"Weiss: (Tertawa kecil) \"Mungkin lain kali, Kepala Koki. Saya khawatir malah merusak bahan makanan Anda. Saya serahkan pada ahlinya saja.\"", 30);
    delayPrint(L"Ruigerd: \"Baiklah, Tuan Muda. Tapi tawaran saya selalu terbuka.\"", 30);
    delayPrint(L"Kamu merasa Ruigerd bukan hanya seorang koki, tapi juga seorang mentor yang bijaksana. Ada aura tenang dan berwibawa darinya.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel5() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 5 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Kepala Koki Ruigerd, saya datang secara khusus untuk mengucapkan terima kasih. Pesta teh kemarin sore benar-benar sukses besar. Semua tamu memuji hidangan kecil dan kue-kue yang Anda sajikan.\"", 30);
    delayPrint(L"Ruigerd: (Menghentikan sejenak pekerjaannya menguleni adonan, wajahnya menunjukkan sedikit kelegaan) \"Syukurlah jika semuanya berjalan lancar dan memuaskan para tamu, Tuan Muda. Kami semua bekerja keras untuk itu.\"", 30);
    delayPrint(L"Weiss: \"Saya tahu. Dan saya sangat menghargainya. Terutama Scone Cranberry dengan krim lemon itu, benar-benar luar biasa. Apakah itu resep baru?\"", 30);
    delayPrint(L"Ruigerd: \"Resep lama yang sedikit saya modifikasi, Tuan Muda. Saya menambahkan sedikit parutan kulit jeruk untuk aroma yang lebih segar. Saya senang Anda menyukainya. Sebenarnya, saya sudah menyiapkan sesuatu yang lain untuk Anda cicipi.\"", 30);
    delayPrint(L"Ruigerd mengambil sebuah piring kecil dari lemari pendingin, di atasnya ada sepotong kecil kue cokelat gelap yang terlihat sangat lembut.", 30);
    delayPrint(L"Ruigerd: \"Ini Kue Cokelat Lava Valrhona dengan inti raspberry. Saya baru saja mengujinya untuk menu pencuci mulut khusus nanti. Silakan dicoba, Tuan Muda.\"", 30);
    delayPrint(L"Weiss: (Matanya berbinar) \"Anda terlalu baik, Kepala Koki! Ini terlihat... sangat menggoda. Saya tidak bisa menolaknya.\"", 30);
    delayPrint(L"Weiss mencicipi kue itu. Rasanya benar-benar meleleh di mulut, kombinasi cokelat pahit dan raspberry asam manis yang sempurna.", 30);
    delayPrint(L"Weiss: \"Ini... ini adalah kesempurnaan, Kepala Koki! Luar biasa! Anda benar-benar seorang seniman.\"", 30);
    delayPrint(L"Ruigerd: (Tersenyum lebar, kali ini senyum yang tulus dan bangga) \"Pujian dari Anda adalah kehormatan terbesar, Tuan Muda. Saya senang bisa menciptakan sesuatu yang membawa kebahagiaan. Itulah tujuan utama seorang koki.\"", 30);
    delayPrint(L"Weiss: \"Anda telah berhasil, Kepala Koki. Lebih dari berhasil. Terima kasih untuk ini.\"", 30);
    delayPrint(L"Ruigerd: \"Kapan saja, Tuan Muda. Selalu ada sesuatu yang baru untuk dicicipi di dapur ini bagi Anda.\"", 30);
    delayPrint(L"Kamu merasa hubunganmu dengan Ruigerd semakin hangat. Dia mulai melihatmu bukan hanya sebagai Tuan Muda, tapi juga sebagai seseorang yang menghargai seninya.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel6() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 6 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Menemukan Ruigerd sedang duduk sendirian di sudut dapur, memandangi sebuah foto lama yang sudah usang) \"Kepala Koki? Apakah semuanya baik-baik saja? Maaf jika saya mengganggu momen pribadi Anda.\"", 30);
    delayPrint(L"Ruigerd: (Sedikit terkejut, lalu buru-buru menyimpan foto itu) \"Oh, Tuan Muda Weiss. Tidak apa-apa. Saya hanya sedang... bernostalgia sedikit. Ini foto lama saat saya pertama kali mulai bekerja untuk kakek Anda, Tuan Besar Alaric Astra.\"", 30);
    delayPrint(L"Weiss: \"Kakek Alaric? Saya tidak banyak mendengar cerita tentang beliau. Beliau yang mempekerjakan Anda pertama kali?\"", 30);
    delayPrint(L"Ruigerd: \"Benar, Tuan Muda. Saya masih sangat muda waktu itu, baru lulus dari akademi kuliner kecil di desa. Beliau melihat potensi dalam diri saya dan memberi saya kesempatan. Beliau adalah orang yang sangat tegas namun bijaksana, dan punya selera makan yang luar biasa.\"", 30);
    delayPrint(L"Weiss: \"Pasti banyak kenangan indah selama Anda mengabdi pada keluarga Astra. Apakah ada hidangan favorit Kakek yang sering Anda buatkan untuknya?\"", 30);
    delayPrint(L"Ruigerd: (Tersenyum mengenang) \"Oh, banyak sekali. Tapi yang paling beliau sukai adalah Sup Buntut Sapi Klasik dengan Roti Bawang Putih Panggang. Beliau bilang itu mengingatkannya pada masakan ibunya. Setiap kali saya membuatnya, saya merasa seperti sedang menghormati kenangan beliau.\"", 30);
    delayPrint(L"Weiss: \"Itu cerita yang sangat menyentuh, Kepala Koki. Saya bisa merasakan betapa Anda menghormati beliau. Apakah... apakah Ayah saya juga punya hidangan favorit tertentu dari Anda?\"", 30);
    delayPrint(L"Ruigerd: (Menghela napas pelan, ada sedikit kesedihan di matanya) \"Tuan Regulus... ayah Anda, Tuan Muda... beliau lebih menyukai hidangan yang sederhana namun penuh rasa. Ikan Salmon Panggang dengan Saus Dill Lemon adalah salah satu kesukaannya. Beliau sering memintanya saat sedang banyak pikiran.\"", 30);
    delayPrint(L"Weiss: \"Terima kasih sudah berbagi cerita ini, Kepala Koki. Ini membantu saya merasa... sedikit lebih dekat dengan mereka, dengan sejarah keluarga ini.\"", 30);
    delayPrint(L"Ruigerd: \"Suatu kehormatan bagi saya bisa berbagi kenangan ini dengan Anda, Tuan Muda. Anda adalah penerus mereka. Dan saya yakin, mereka akan bangga melihat Anda sekarang.\"", 30);
    delayPrint(L"Weiss: \"Saya harap begitu, Kepala Koki. Saya harap begitu.\"", 30);
    delayPrint(L"Ruigerd: \"Saya percaya Anda akan membawa nama Astra ke masa depan yang lebih baik, Tuan Muda.\"", 30);
    delayPrint(L"Percakapan ini terasa sangat personal. Kamu merasa Ruigerd bukan hanya pelayan setia, tapi juga penjaga kenangan keluarga Astra.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel7() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 7 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Kepala Koki Ruigerd, apakah Anda punya waktu sebentar? Ada sesuatu yang ingin saya diskusikan, tapi ini bukan tentang makanan.\"", 30);
    delayPrint(L"Ruigerd: (Menghentikan pekerjaannya memotong daging, lalu membersihkan tangannya) \"Tentu saja, Tuan Muda Weiss. Selalu ada waktu untuk Anda. Silakan, apa yang ada di pikiran Anda?\"", 30);
    delayPrint(L"Weiss: \"Ini tentang... tanggung jawab. Sebagai pewaris keluarga Astra, ada banyak ekspektasi dan tekanan. Terkadang saya merasa bingung bagaimana harus menyeimbangkan keinginan pribadi dengan tugas keluarga. Anda sudah lama mengabdi di sini, pasti Anda melihat banyak hal. Bagaimana Anda menghadapi tekanan dalam pekerjaan Anda sendiri?\"", 30);
    delayPrint(L"Ruigerd: (Tertegun sejenak, lalu mengangguk paham) \"Pertanyaan yang sangat bagus, Tuan Muda. Tekanan selalu ada di setiap pekerjaan, terutama di dapur besar seperti ini di mana setiap hidangan harus sempurna. Kuncinya, bagi saya, adalah fokus pada apa yang bisa saya kendalikan: kualitas bahan, ketepatan teknik, dan kerja tim yang solid.\"", 30);
    delayPrint(L"Ruigerd: \"Untuk hal-hal di luar kendali saya, saya belajar untuk menerimanya dan beradaptasi. Dan yang paling penting, jangan pernah takut meminta bantuan atau nasihat jika merasa buntu. Tidak ada orang yang bisa melakukan semuanya sendirian, Tuan Muda, bahkan seorang Kepala Koki atau pewaris keluarga sekalipun.\"", 30);
    delayPrint(L"Weiss: \"Fokus pada apa yang bisa dikendalikan... itu masuk akal. Tapi bagaimana jika ekspektasi itu datang dari orang-orang yang kita hormati? Bagaimana cara agar tidak mengecewakan mereka?\"", 30);
    delayPrint(L"Ruigerd: \"Lakukan yang terbaik dengan tulus, Tuan Muda. Itu saja. Orang yang benar-benar menghormati Anda akan menghargai usaha Anda, apapun hasilnya. Dan ingatlah, Tuan Muda, Anda tidak harus menjadi persis seperti ayah atau kakek Anda. Anda adalah diri Anda sendiri, dengan kekuatan dan jalan Anda sendiri. Temukan itu, dan pegang teguh.\"", 30);
    delayPrint(L"Weiss: \"Menemukan jalan sendiri... Itu nasihat yang sangat berharga, Kepala Koki. Anda selalu punya cara pandang yang bijaksana. Terima kasih banyak, ini sangat membantu saya.\"", 30);
    delayPrint(L"Ruigerd: \"Saya hanya berbagi pengalaman hidup yang sedikit ini, Tuan Muda. Saya senang jika bisa membantu Anda. Ingat, dapur ini selalu terbuka jika Anda butuh tempat untuk berpikir atau sekadar secangkir kopi hangat.\"", 30);
    delayPrint(L"Weiss: \"Akan saya ingat itu, Kepala Koki. Terima kasih sekali lagi.\"", 30);
    delayPrint(L"Ruigerd: \"Tidak masalah, Tuan Muda. Sekarang, jika Anda tidak keberatan, daging panggang ini tidak bisa menunggu lebih lama lagi.\"", 30);
    delayPrint(L"Kamu merasa sangat beruntung memiliki seseorang seperti Ruigerd di sisimu, yang bisa memberikan perspektif dan dukungan layaknya seorang ayah atau mentor.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel8() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 8 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Ruigerd: \"Tuan Muda Weiss, saya perhatikan Anda semakin sering menghabiskan waktu di perpustakaan dan berdiskusi dengan para penasihat keluarga. Apakah ada proyek besar yang sedang Anda kerjakan?\"", 30);
    delayPrint(L"Weiss: \"Ya, Kepala Koki. Saya sedang mencoba memahami lebih dalam tentang aset dan investasi keluarga Astra. Banyak hal yang rumit dan perlu dipelajari. Saya ingin memastikan bisa mengelolanya dengan baik di masa depan.\"", 30);
    delayPrint(L"Ruigerd: (Mengangguk dengan tatapan penuh hormat) \"Itu adalah sikap yang sangat bertanggung jawab, Tuan Muda. Saya harus mengatakan, saya sangat terkesan dengan perubahan dan kedewasaan yang Anda tunjukkan akhir-akhir ini.\"", 30);
    delayPrint(L"Weiss: \"Perubahan? Apakah saya terlihat sangat berbeda dari sebelumnya?\"", 30);
    delayPrint(L"Ruigerd: \"Sangat berbeda, Tuan Muda. Jika saya boleh jujur, dulu... Anda lebih sering terlihat acuh tak acuh dan mudah tersinggung. Tapi sekarang, Anda lebih bijaksana, lebih sabar, dan lebih peduli pada orang-orang di sekitar Anda, termasuk kami para staf. Itu bukan hanya pengamatan saya, tapi juga pembicaraan hangat di antara para pelayan senior.\"", 30);
    delayPrint(L"Weiss: (Sedikit terkejut namun juga lega) \"Benarkah? Saya... saya senang jika perubahan ini membawa dampak positif. Sejujurnya, saya sendiri merasa seperti... terbangun dari tidur panjang yang buruk.\"", 30);
    delayPrint(L"Ruigerd: \"Apapun yang telah membangunkan Anda, Tuan Muda, itu adalah berkah. Keluarga Astra membutuhkan pemimpin yang kuat dan berhati baik seperti Anda sekarang. Dan saya, bersama seluruh staf dapur, akan selalu mendukung Anda dengan segenap kemampuan kami.\"", 30);
    delayPrint(L"Weiss: \"Dukungan Anda sangat berarti bagi saya, Kepala Koki. Lebih dari yang Anda bayangkan. Terkadang, saya masih meragukan diri sendiri, tapi mengetahui ada orang-orang seperti Anda yang percaya pada saya, itu memberi saya kekuatan.\"", 30);
    delayPrint(L"Ruigerd: \"Jangan pernah ragu pada diri Anda, Tuan Muda. Anda memiliki potensi yang luar biasa. Saya sudah melihat banyak pemimpin datang dan pergi, dan saya melihat sesuatu yang istimewa dalam diri Anda. Sesuatu yang mengingatkan saya pada semangat Tuan Besar Alaric.\"", 30);
    delayPrint(L"Weiss: (Tersentuh) \"Disamakan dengan Kakek Alaric adalah pujian tertinggi bagi saya, Kepala Koki. Terima kasih.\"", 30);
    delayPrint(L"Ruigerd: \"Anda pantas mendapatkannya, Tuan Muda. Sekarang, bagaimana kalau saya siapkan minuman penambah energi? Sepertinya Anda akan membutuhkan banyak tenaga untuk mempelajari semua laporan itu.\"", 30);
    delayPrint(L"Weiss: \"Itu ide yang sangat bagus, Kepala Koki. Terima kasih.\"", 30);
    delayPrint(L"Pengakuan tulus dari Ruigerd, seseorang yang telah lama mengabdi pada keluarganya, terasa sangat memvalidasi usahamu untuk berubah.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel9() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 9 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Masuk ke dapur larut malam, menemukan Ruigerd masih di sana, sedang membersihkan peralatannya dengan teliti) \"Kepala Koki? Anda masih di sini selarut ini? Saya pikir semua orang sudah beristirahat.\"", 30);
    delayPrint(L"Ruigerd: (Menoleh, sedikit terkejut) \"Tuan Muda Weiss. Saya hanya menyelesaikan beberapa hal. Anda sendiri, kenapa belum tidur? Apakah ada yang mengganggu pikiran Anda? Anda terlihat sedikit... murung.\"", 30);
    delayPrint(L"Weiss: (Menghela napas, duduk di salah satu bangku) \"Hanya... banyak hal yang harus dipikirkan, Kepala Koki. Tentang masa depan, tentang tanggung jawab yang semakin besar. Terkadang rasanya sedikit membebani.\"", 30);
    delayPrint(L"Ruigerd: (Mengeringkan tangannya, lalu duduk di hadapan Weiss) \"Saya mengerti, Tuan Muda. Memikul beban sebesar itu di usia muda pasti tidak mudah. Tapi ingatlah, Anda tidak sendirian. Ada banyak orang yang peduli dan siap membantu Anda, termasuk saya.\"", 30);
    delayPrint(L"Weiss: \"Saya tahu, Kepala Koki. Dan saya sangat bersyukur untuk itu. Tapi ada kalanya saya merasa... takut gagal. Takut tidak bisa memenuhi harapan semua orang. Takut mengecewakan warisan keluarga ini.\"", 30);
    delayPrint(L"Ruigerd: \"Kegagalan adalah bagian dari kehidupan, Tuan Muda. Bahkan koki terbaik pun pernah membuat hidangan yang gosong atau salah bumbu. Yang penting bukan apakah kita pernah gagal, tapi bagaimana kita bangkit dan belajar dari kegagalan itu. Dan percayalah, Tuan Muda, harapan terbesar kami bukanlah kesempurnaan, tapi melihat Anda berusaha yang terbaik dengan hati yang tulus.\"", 30);
    delayPrint(L"Ruigerd: \"Saya sudah melihat Anda tumbuh dari seorang anak laki-laki yang sering membuat ulah menjadi seorang pemuda yang bertanggung jawab dan penuh pertimbangan. Perjalanan Anda sungguh luar biasa. Jangan biarkan ketakutan itu meredupkan cahaya yang sudah Anda pancarkan.\"", 30);
    delayPrint(L"Weiss: (Menatap Ruigerd dengan rasa terima kasih yang dalam) \"Anda selalu tahu apa yang harus dikatakan, Kepala Koki. Kata-kata Anda seperti... balsam yang menenangkan. Rasanya seperti berbicara dengan seorang ayah.\"", 30);
    delayPrint(L"Ruigerd: (Tersenyum hangat, ada sorot kebapakan di matanya) \"Saya mungkin tidak bisa menggantikan ayah Anda, Tuan Muda. Tapi saya akan selalu ada di sini untuk Anda, sebagai teman, sebagai penasihat, sebagai seseorang yang akan selalu mendoakan yang terbaik untuk Anda. Sekarang, bagaimana kalau saya buatkan cokelat hangat? Itu minuman terbaik untuk malam-malam perenungan seperti ini.\"", 30);
    delayPrint(L"Weiss: \"Itu... akan sangat menyenangkan, Kepala Koki. Terima kasih. Untuk segalanya.\"", 30);
    delayPrint(L"Ruigerd: \"Anggap saja ini tugas tambahan saya, Tuan Muda. Menjaga semangat Anda tetap menyala.\"", 30);
    delayPrint(L"Malam itu, di keheningan dapur, kamu merasa menemukan sosok ayah dalam diri Ruigerd. Seseorang yang bisa kamu andalkan dan percaya sepenuhnya.", 30);

    printLine();
    waitForEnter();
}

void sceneRuigerdLevel10() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ruigerd - Chef ✦ Level 10 ✦ Dapur Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Ruigerd: (Menyambut Weiss di pintu dapur dengan senyum lebar dan khidmat) \"Selamat datang, Tuan Muda Weiss. Saya sudah menyiapkan sesuatu yang sangat spesial untuk Anda hari ini. Anggap saja ini perayaan kecil kita atas semua pencapaian dan pertumbuhan Anda.\"", 30);
    delayPrint(L"Weiss: \"Perayaan? Untuk saya, Kepala Koki? Anda tidak perlu serepot ini. Tapi... saya sangat penasaran. Apa yang Anda siapkan? Aromanya saja sudah luar biasa.\"", 30);
    delayPrint(L"Ruigerd memimpin Weiss ke sebuah meja kecil yang telah ditata dengan indah di sudut dapur yang tenang. Di atasnya, tersaji hidangan yang tampak seperti sebuah mahakarya kuliner.", 30);
    delayPrint(L"Ruigerd: \"Ini adalah 'Simfoni Astra', Tuan Muda. Sebuah hidangan yang saya ciptakan khusus untuk Anda. Setiap elemen di piring ini melambangkan sesuatu. Daging Rusa Panggang Madu ini melambangkan kekuatan dan ketahanan Anda. Puree Ubi Ungu dengan Truffle melambangkan kebijaksanaan dan kedalaman karakter Anda. Dan Asparagus Panggang dengan Saus Lemon-Mentega ini melambangkan kesegaran dan harapan baru yang Anda bawa.\"", 30);
    delayPrint(L"Weiss: (Terpana, menatap hidangan itu dengan takjub dan haru) \"Kepala Koki... Ruigerd... saya... saya tidak tahu harus berkata apa. Ini... ini adalah hidangan terindah dan paling bermakna yang pernah saya lihat seumur hidup saya.\"", 30);
    delayPrint(L"Ruigerd: \"Ada satu hal lagi, Tuan Muda.\" (Mengeluarkan sebuah buku catatan kulit yang sudah tua namun terawat baik) \"Ini adalah buku resep pribadi saya. Di dalamnya, ada semua resep yang telah saya kumpulkan dan ciptakan selama bertahun-tahun mengabdi pada keluarga Astra, termasuk beberapa resep rahasia yang hanya diketahui oleh Kepala Koki.\"", 30);
    delayPrint(L"Ruigerd: \"Saya ingin mewariskan ini kepada Anda. Bukan agar Anda menjadi koki, Tuan Muda, tapi sebagai simbol kepercayaan saya yang penuh. Di dalamnya ada lebih dari sekadar resep; ada sejarah, ada cinta, ada dedikasi. Gunakanlah dengan bijak, mungkin suatu hari nanti Anda ingin membuatkan hidangan spesial untuk orang yang Anda sayangi, atau sekadar memahami lebih dalam tentang warisan kuliner keluarga ini.\"", 30);
    delayPrint(L"Weiss: (Menerima buku itu dengan tangan gemetar, air mata menggenang di pelupuk matanya) \"Kepala Koki... Ruigerd... ini... ini adalah kehormatan yang tak ternilai harganya. Saya bersumpah akan menjaga buku ini dan semua isinya dengan segenap jiwa saya. Anda... Anda lebih dari sekadar Kepala Koki bagi saya. Anda adalah guru, mentor, sahabat, dan sosok ayah yang telah membimbing saya.\"", 30);
    delayPrint(L"Ruigerd: (Menepuk bahu Weiss dengan hangat, matanya juga berkaca-kaca) \"Dan Anda, Tuan Muda Weiss, adalah harapan terbaik keluarga Astra. Saya telah mengabdi pada tiga generasi keluarga ini, dan saya bisa katakan dengan keyakinan penuh, Anda memiliki semua yang dibutuhkan untuk menjadi pemimpin yang hebat dan dicintai. Hati Anda ada di tempat yang benar.\"", 30);
    delayPrint(L"Ruigerd: \"Sekarang, silakan nikmati hidangannya selagi hangat. Dan ketahuilah, Tuan Muda, bahwa kesetiaan dan dukungan saya akan selalu menyertai Anda, sampai akhir hayat saya. Dapur ini, dan hati saya, akan selalu terbuka untuk Anda.\"", 30);
    delayPrint(L"Weiss: \"Terima kasih, Ruigerd. Terima kasih untuk segalanya. Saya tidak akan pernah melupakan ini. Anda adalah bagian tak terpisahkan dari keluarga Astra, dari hidup saya.\"", 30);
    delayPrint(L"Ruigerd: \"Suatu kehormatan terbesar bagi saya, Tuan Muda. Suatu kehormatan terbesar.\"", 30);
    delayPrint(L"Di tengah aroma masakan yang memikat dan kehangatan persahabatan yang tulus, kamu merasa ikatanmu dengan Ruigerd telah mencapai puncaknya. Sebuah hubungan yang ditempa oleh waktu, rasa hormat, dan kasih sayang yang tulus, layaknya hidangan terbaik yang membutuhkan kesabaran dan cinta untuk tercipta.", 30);

    waitForEnter(L" Kamu telah membentuk ikatan terkuat...... Tekan Enter untuk melihat detailnya");

    if (!socialLinks["Ruigerd"].completed) { 
        applySocialLinkBonus("Ruigerd"); 
        socialLinks["Ruigerd"].completed = true; 
    }


    printLine();
    waitForEnter();
}

void sceneIreneLevel1() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 1 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Permisi, apakah kamu Irene? Pelayan baru yang bertugas di area taman ini, bukan?\"", 30);
    delayPrint(L"Irene: (Terkejut dan sedikit membungkuk) \"I-iya, Tuan Muda Weiss. Sayalah Irene. Ada yang bisa saya bantu?\"", 30);
    delayPrint(L"Weiss: \"Tidak ada yang spesifik. Hanya ingin menyapa. kamu terlihat sangat serius merawat mawar itu. Indah sekali bunganya. Apakah itu jenis favorit seseorang di sini?\"", 30);
    delayPrint(L"Irene: \"Oh... t-terima kasih, Tuan Muda. Saya hanya mencoba melakukan yang terbaik. Mawar ini memang salah satu favorit Nyonya Astra. Beliau suka jika ada bunga segar di kamarnya setiap pagi.\"", 30);
    delayPrint(L"Weiss: \"Begitu. Pasti sebuah tanggung jawab besar memastikan bunganya selalu prima. Tidak perlu terlalu tegang begitu di dekatku. Anggap saja aku teman mengobrol di taman. Bagaimana kesan pertamamu bekerja di mansion ini?\"", 30);
    delayPrint(L"Irene: (Sedikit ragu) \"Mansion ini... sangat besar dan megah, Tuan Muda. Dan... semua orang tampak sangat sibuk dan profesional. Saya masih berusaha menyesuaikan diri dengan semua peraturannya.\"", 30);
    delayPrint(L"Weiss: \"Aku mengerti. Awalnya memang bisa terasa begitu. Tapi aku yakin kamu akan segera terbiasa. Nikmati saja prosesnya, dan keindahan taman ini selagi bisa. Ini tempat yang baik untuk menenangkan pikiran.\"", 30);
    delayPrint(L"Irene: (Mengangguk pelan, ada sedikit senyum di wajahnya) \"Baik, Tuan Muda. Terima kasih atas kata-kata Anda. Saya akan berusaha.\"", 30);
    delayPrint(L"Weiss: \"Bagus. Sampai jumpa lagi, Irene.\"", 30);
    delayPrint(L"Irene: \"S-sampai jumpa, Tuan Muda.\"", 30);
    delayPrint(L"Kamu melihat bahunya sedikit lebih rileks saat kamu berbalik. Setidaknya, dia tidak lagi terlihat ingin lari. Sebuah kemajuan kecil.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel2() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 2 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Irene, selamat pagi. Kebetulan sekali bertemu denganmu di sini lagi. Udara pagi ini sangat menyegarkan, bukan?\"", 30);
    delayPrint(L"Irene: (Menoleh, senyumnya lebih natural kali ini) \"Selamat pagi, Tuan Muda Weiss! Iya, sangat segar. Saya baru saja selesai menyiram anggrek di dekat paviliun. Mereka tampak sangat haus pagi ini.\"", 30);
    delayPrint(L"Weiss: \"Anggrek-anggrek itu memang butuh perhatian ekstra, ya? Aku dengar perawatannya cukup sulit. Apa kamu menikmati merawat tanaman secara umum?\"", 30);
    delayPrint(L"Irene: \"Sangat menikmati, Tuan Muda. Rasanya seperti merawat kehidupan. Selain anggrek, saya juga ditugaskan merapikan koleksi herbal Nyonya Astra. Itu cukup menantang tapi menarik.\"", 30);
    delayPrint(L"Weiss: \"Koleksi herbal? Itu terdengar menarik. Bagaimana sejauh ini pekerjaanmu di mansion secara keseluruhan? Apakah ada kesulitan yang kamu hadapi?\"", 30);
    delayPrint(L"Irene: \"Sejauh ini berjalan cukup baik, Tuan Muda. Para pelayan senior sangat membantu dan sabar. Kepala Pelayan Ruigerd juga sering memberikan arahan yang jelas. Saya paling menikmati saat ditugaskan di perpustakaan atau taman seperti ini, tempatnya lebih tenang.\"", 30);
    delayPrint(L"Weiss: \"Perpustakaan, ya? Tempat itu memang salah satu favoritku juga. Banyak buku menarik di sana. Syukurlah kalau kamu merasa nyaman. Jangan ragu memberitahu jika ada sesuatu yang mengganggumu. Kami ingin semua merasa betah.\"", 30);
    delayPrint(L"Irene: \"Terima kasih banyak atas perhatian Anda, Tuan Muda. Saya akan mengingatnya. Saya... saya senang bisa berkontribusi di mansion ini, sekecil apapun peran saya.\"", 30);
    delayPrint(L"Weiss: \"Setiap peran penting, Irene. Dan kamu melakukannya dengan baik. Lanjutkan kerja bagusmu.\"", 30);
    delayPrint(L"Irene: (Pipinya sedikit merona) \"Baik, Tuan Muda! Terima kasih!\"", 30);
    delayPrint(L"Dia tampak sedikit terkejut dengan pujian langsung itu, tapi rona bahagia terlihat jelas di wajahnya.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel3() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 3 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Irene: \"Permisi, Tuan Muda Weiss. Saya lihat Anda sedang membaca buku yang cukup tebal. Sepertinya sangat menarik? Sampulnya terlihat seperti peta dunia kuno.\"", 30);
    delayPrint(L"Weiss: (Menurunkan bukunya) \"Oh, Irene. Ya, ini salah satu seri fantasi klasik. Penuh dengan naga, sihir, dan kerajaan yang hilang. kamu sendiri, apa kamu juga suka membaca di waktu luang?\"", 30);
    delayPrint(L"Irene: \"S-saya sangat suka membaca, Tuan Muda! Terutama cerita-cerita petualangan dan legenda kuno. Itu seperti membawa saya ke dunia lain, melupakan sejenak rutinitas.\"", 30);
    delayPrint(L"Weiss: \"Benarkah? Genre apa yang paling kamu nikmati? Mungkin aku punya beberapa rekomendasi untukmu, atau sebaliknya. Aku selalu mencari judul baru.\"", 30);
    delayPrint(L"Irene: (Dengan antusias) \"Saya paling suka kisah-kisah tentang ksatria yang membela kebenaran, atau penyihir yang mempelajari rahasia alam semesta! Penulis seperti Master Valerius atau Lady Evangeline selalu jadi favorit saya! 'Balada Ksatria Fajar' karya Master Valerius sangat menginspirasi!\"", 30);
    delayPrint(L"Weiss: \"Lady Evangeline! 'The Starlight Chronicles' karyanya luar biasa! Aku tidak menyangka kamu juga membacanya. Kita benar-benar harus bertukar daftar bacaan kapan-kapan. Bagaimana menurutmu tentang akhir dari buku ketiganya? Agak menggantung, bukan?\"", 30);
    delayPrint(L"Irene: \"Sangat menggantung, Tuan Muda! Saya sampai tidak sabar menunggu kelanjutannya! Jika Anda tidak keberatan, saya akan sangat senang jika kita bisa berdiskusi lebih banyak tentang buku ini atau buku lainnya. Saya punya banyak pertanyaan tentang sistem sihir di 'Starlight Chronicles'.\"", 30);
    delayPrint(L"Weiss: \"Tentu saja, Irene! Aku justru mencari teman diskusi yang seantusias dirimu. Mungkin kita bisa mulai dengan buku itu? Aku punya beberapa teori menarik tentang artefak yang hilang itu.\"", 30);
    delayPrint(L"Irene: (Matanya berbinar) \"Dengan senang hati, Tuan Muda! Kapan saja Anda ada waktu! Saya juga penasaran dengan teori Anda!\"", 30);
    delayPrint(L"Weiss: \"Bagaimana kalau besok sore, di waktu istirahatmu? Kita bisa bertemu di gazebo ini lagi.\"", 30);
    delayPrint(L"Irene: \"Sempurna, Tuan Muda! Saya akan pastikan semua pekerjaan saya selesai tepat waktu!\"", 30);
    delayPrint(L"Kalian berdua tertawa ringan. Sepertinya hobi yang sama ini akan menjadi jembatan yang kuat untuk hubungan kalian.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel4() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 4 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Irene, lihat ke sana! Di atas bunga matahari itu!\" (Menunjuk dengan antusias)", 30);
    delayPrint(L"Irene: (Mengikuti arah pandang Weiss) \"Ada apa, Tuan Muda? Oh! Seekor kepik dengan tujuh bintang! Saya sudah lama tidak melihatnya! Cantik sekali warnanya!\"", 30);
    delayPrint(L"Weiss: \"Konon katanya membawa keberuntungan, bukan? Dia tampak nyaman sekali di sana, menikmati sinar matahari. Apa kamu percaya hal-hal seperti itu, Irene?\"", 30);
    delayPrint(L"Irene: \"Orang tua di desa saya dulu sering berkata begitu, Tuan Muda. Mereka bilang jika kepik hinggap padamu, itu pertanda baik. Saya tidak tahu pasti kebenarannya, tapi rasanya menyenangkan untuk mempercayai hal-hal kecil yang membawa harapan. Ah, dia terbang!\"", 30);
    delayPrint(L"Weiss: \"Sayang sekali. Tapi setidaknya kita sempat melihatnya. Hal-hal kecil seperti ini yang kadang membuat hari jadi lebih berwarna. kamu sendiri, apa ada pemandangan favoritmu di taman ini?\"", 30);
    delayPrint(L"Irene: (Tersenyum) \"Anda benar sekali, Tuan Muda. Keindahan seringkali tersembunyi dalam kesederhanaan. Saya paling suka melihat embun pagi di jaring laba-laba, berkilau seperti berlian. Terima kasih sudah menunjukkannya pada saya. Saya hampir melewatkannya karena terlalu fokus bekerja.\"", 30);
    delayPrint(L"Weiss: \"Tidak masalah, Irene. Terkadang kita semua butuh pengingat untuk berhenti sejenak dan menikmati sekitar. Apa kamu punya cerita menarik lain dari desamu tentang pertanda alam atau makhluk kecil lainnya?\"", 30);
    delayPrint(L"Irene: (Berpikir sejenak, matanya menerawang) \"Ada beberapa, Tuan Muda. Misalnya, jika burung layang-layang terbang rendah, itu tandanya akan segera turun hujan. Atau jika kunang-kunang berkumpul banyak di malam hari, itu pertanda udara akan sangat cerah keesokan harinya.\"", 30);
    delayPrint(L"Weiss: \"Menarik sekali. Kearifan lokal seperti itu selalu punya pesonanya sendiri. Terima kasih sudah berbagi, Irene.\"", 30);
    delayPrint(L"Irene: \"Sama-sama, Tuan Muda. Saya senang bisa berbincang dengan Anda.\"", 30);
    delayPrint(L"Percakapan ringan berlanjut, diwarnai cerita-cerita kecil yang membuat suasana semakin akrab. Kamu merasa senang bisa berbagi momen seperti ini dengannya.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel5() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 5 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Irene: (Menghampirimu yang sedang memijat pelipis di bangku taman) \"Permisi, Tuan Muda Weiss. Maaf mengganggu. Apakah Anda merasa tidak enak badan? Wajah Anda terlihat sedikit lelah dari biasanya.\"", 30);
    delayPrint(L"Weiss: \"Oh, Irene. Tidak apa-apa. Hanya sedikit pusing karena kurang tidur semalam. Terlalu banyak laporan keuangan yang harus kuperiksa dan pahami. Angka-angka itu membuat kepalaku berputar.\"", 30);
    delayPrint(L"Irene: \"Astaga, pasti sangat melelahkan. Saya bisa membayangkan betapa rumitnya. Emm... Tuan Muda, jika Anda tidak keberatan, saya bisa membuatkan minuman hangat. Mungkin teh herbal dengan campuran mint dan lavender? Itu sangat baik untuk meredakan sakit kepala dan membuat rileks.\"", 30);
    delayPrint(L"Weiss: \"Lavender? Aku belum pernah mencobanya dalam teh. Apakah rasanya tidak terlalu kuat atau seperti parfum?\"", 30);
    delayPrint(L"Irene: (Tersenyum menenangkan) \"Sama sekali tidak, Tuan Muda. Jika diracik dengan benar, aromanya justru sangat lembut dan menenangkan. Nenek saya di desa dulu sering membuatnya jika ada yang sulit tidur atau merasa cemas. Atau, jika Anda lebih suka, saya bisa mengambilkan air putih dingin dengan irisan lemon dan sedikit jahe untuk menyegarkan?\"", 30);
    delayPrint(L"Weiss: \"Hmm, penjelasanmu tentang teh herbal itu membuatku penasaran. Baiklah, jika tidak merepotkanmu, aku mau mencobanya. Siapa tahu memang bisa membantu.\"", 30);
    delayPrint(L"Irene: (Wajahnya berseri) \"Tentu saja tidak merepotkan, Tuan Muda! Saya akan segera menyiapkannya! Semoga bisa membantu meringankan pusing Anda. Saya akan tambahkan sedikit madu hutan, itu juga baik untuk stamina.\" Ia bergegas pergi.", 30);
    delayPrint(L"Kamu tersenyum sendiri. Perhatiannya yang tulus dan inisiatifnya untuk menawarkan bantuan spesifik benar-benar menghangatkan hati. Dia tidak lagi hanya melihatmu sebagai majikan, tapi sebagai seseorang yang benar-benar ia pedulikan.", 30);
    delayPrint(L"Tak lama, Irene kembali dengan secangkir teh yang aromanya memang sangat menenangkan. \"Silakan dicoba, Tuan Muda. Hati-hati, masih panas.\"", 30);
    delayPrint(L"Weiss: (Menyesapnya perlahan) \"Ini... ini sungguh nikmat, Irene. Aromanya unik dan rasanya... menenangkan. Terima kasih banyak. kamu benar, rasanya kepalaku sedikit lebih ringan.\"", 30);
    delayPrint(L"Irene: \"Syukurlah jika Anda menyukainya dan merasa lebih baik, Tuan Muda. Jika Anda membutuhkan sesuatu lagi, jangan ragu memanggil saya.\"", 30);
    delayPrint(L"Weiss: \"Akan kuingat itu. Terima kasih sekali lagi, Irene.\"", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel6() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 6 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Irene, kamu sedang melamun menatap air mancur itu? Pemandangan matahari terbenam yang terpantul di airnya memang indah, ya?\"", 30);
    delayPrint(L"Irene: (Sedikit tersentak dari lamunannya, lalu tersenyum) \"Ah, Tuan Muda Weiss. Maaf, saya tidak melihat Anda datang. Iya, sangat indah. Warna langitnya mengingatkan saya pada lukisan cat air yang pernah saya lihat di buku.\"", 30);
    delayPrint(L"Weiss: \"Kadang pemandangan seperti ini membuatku berpikir... Apa kamu sering merindukan kampung halamanmu, Irene? Bagaimana suasana di sana?\"", 30);
    delayPrint(L"Irene: \"Tentu, Tuan Muda. Hampir setiap hari. Desa saya kecil, dikelilingi perbukitan hijau dan sungai yang jernih tempat anak-anak sering bermain. Saya merindukan suara gemericik air, aroma masakan ibu saya yang sederhana namun lezat, dan tawa riang adik-adik saya.\"", 30);
    delayPrint(L"Weiss: \"Kedengarannya sangat damai. Pasti sebuah pengorbanan besar bagimu untuk bekerja jauh dari mereka.\"", 30);
    delayPrint(L"Irene: \"Memang, Tuan Muda. Tapi saya melakukannya demi masa depan mereka. Dan... sejujurnya, Mansion Astra ini, dengan segala kesibukannya, juga mulai memberikan rasa nyaman tersendiri. Terutama karena orang-orang di dalamnya.\"", 30);
    delayPrint(L"Weiss: \"Aku mengerti. Terkadang... aku juga merasa seperti jauh dari 'rumah' yang sesungguhnya, meskipun secara fisik aku berada di sini. Dunia ini terasa... berbeda dari yang kuingat, atau mungkin dari yang kuharapkan.\"", 30);
    delayPrint(L"Irene: (Menatapmu dengan penuh perhatian dan kelembutan) \"Saya mungkin tidak sepenuhnya mengerti apa yang Anda rasakan, Tuan Muda. Tapi saya percaya, 'rumah' bukan hanya tentang tempat fisik. Tapi juga tentang rasa aman, diterima, dan dipedulikan oleh orang-orang di sekitar kita. Dan saya lihat, Anda sedang berusaha menciptakan 'rumah' itu di sini.\"", 30);
    delayPrint(L"Weiss: \"kamu ada benarnya, Irene. Kata-katamu selalu menenangkan. Dan kamu adalah salah satu orang yang membuat mansion ini terasa lebih... bersahabat dan hangat bagiku.\"", 30);
    delayPrint(L"Irene: (Tersipu, namun senyumnya tulus) \"Saya... saya merasa terhormat mendengarnya, Tuan Muda. Saya juga merasa Mansion Astra ini sudah seperti rumah kedua, berkat kebaikan Anda dan yang lainnya. Kita semua adalah bagian dari keluarga besar di sini, bukan?\"", 30);
    delayPrint(L"Weiss: \"Ya, kamu benar. Keluarga besar yang terkadang rumit, tapi tetap keluarga.\" (Tersenyum kecil)", 30);
    delayPrint(L"Irene: \"Saya setuju, Tuan Muda.\"", 30);
    delayPrint(L"Percakapan ini terasa lebih dalam dan personal dari biasanya, sebuah tanda bahwa kepercayaan di antara kalian semakin menguat.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel7() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 7 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Irene: (Berlari kecil menghampirimu, wajahnya bersemu karena antusias dan napasnya sedikit terengah) \"Tuan Muda Weiss! Tuan Muda! Saya baru saja dari perpustakaan dan menemukan edisi terbatas dari 'Syair Para Bintang'! Ini buku yang kita diskusikan minggu lalu, bukan? Yang katanya sangat sulit dicari itu!\"", 30);
    delayPrint(L"Weiss: (Terkejut dan senang, langsung berdiri) \"Benarkah, Irene? Luar biasa! Aku sudah mencarinya di beberapa toko buku di kota tapi selalu kehabisan. Bagaimana kamu bisa menemukannya? Apa Pak Theodore yang membantumu?\"", 30);
    delayPrint(L"Irene: \"Betul, Tuan Muda! Saya bertanya pada Pak Theodore, pustakawan. Awalnya beliau bilang tidak ada. Tapi setelah saya bilang kita sering berdiskusi tentang buku dan sangat ingin membacanya, beliau teringat ada satu salinan yang disimpan khusus di ruang arsip! Beliau mengizinkan saya meminjamnya untuk Anda!\"", 30);
    delayPrint(L"Weiss: \"kamu luar biasa, Irene! Terima kasih banyak! Ini sangat berarti. Bagaimana kalau kita membacanya bersama di gazebo nanti sore, jika kamu tidak sibuk? Kita bisa mulai dari bab pertama.\"", 30);
    delayPrint(L"Irene: \"Ide yang sangat bagus, Tuan Muda! Saya akan pastikan semua pekerjaan saya selesai. Tapi, sebelum itu, saya penasaran, apa pendapat Anda tentang prolognya? Saya sudah sempat membacanya sekilas, ramalan tentang Pangeran Cahaya dan Putri Bayangan itu... sangat puitis sekaligus misterius!\"", 30);
    delayPrint(L"Weiss: \"Oh, prolog itu memang salah satu yang terbaik! Aku punya interpretasi sendiri tentang siapa sebenarnya Putri Bayangan itu. Banyak yang salah mengira. Aku pikir...\" Kalian pun langsung terlibat dalam diskusi yang seru dan panjang, saling melempar argumen dan teori dengan semangat.", 30);
    delayPrint(L"Irene: \"Wah, teori Anda sangat menarik, Tuan Muda! Saya tidak pernah terpikir dari sudut pandang itu! Tapi, bagaimana dengan simbol naga berkepala tiga yang disebut dalam ramalan? Apakah itu merujuk pada tiga kerajaan yang bertikai?\"", 30);
    delayPrint(L"Weiss: \"Bisa jadi! Atau mungkin itu metafora untuk tiga cobaan besar yang harus dihadapi Pangeran Cahaya. Lady Evangeline memang suka menggunakan simbolisme berlapis.\"", 30);
    delayPrint(L"Irene: (Tertawa riang) \"Sepertinya kita punya banyak bahan diskusi untuk nanti sore ya, Tuan Muda! Saya jadi semakin tidak sabar!\"", 30);
    delayPrint(L"Weiss: \"Tepat sekali! Aku sangat menikmati bertukar pikiran denganmu, Irene. kamu punya wawasan yang tajam dan antusiasme yang menular. Jadi, nanti sore di gazebo, ya? Aku akan membawa teh dan camilan spesial.\"", 30);
    delayPrint(L"Irene: \"Siap, Tuan Muda! Ini akan menjadi sore yang sangat menyenangkan! Terima kasih sekali lagi sudah mau berdiskusi dengan saya!\"", 30);
    delayPrint(L"Weiss: \"Akulah yang berterima kasih, Irene.\"", 30);
    delayPrint(L"Kegembiraan kalian berdua karena menemukan teman diskusi yang sepadan terasa begitu nyata, mempererat ikatan persahabatan kalian hingga ke level yang baru.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel8() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 8 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Irene: \"Tuan Muda Weiss, bolehkah saya duduk sebentar? Ada sesuatu yang ingin saya sampaikan secara pribadi, jika Anda tidak keberatan. Ini sudah lama ingin saya utarakan.\"", 30);
    delayPrint(L"Weiss: \"Tentu, Irene. Silakan. Ada apa? kamu terlihat lebih serius dari biasanya. Apakah ada masalah?\"", 30);
    delayPrint(L"Irene: (Menghela napas pelan, mengumpulkan kata-kata) \"Tidak ada masalah, Tuan Muda. Justru sebaliknya. Ini tentang... Anda. Dan perubahan besar yang saya, dan juga staf lain, lihat dalam diri Anda sejak saya mulai bekerja di sini.\"", 30);
    delayPrint(L"Weiss: \"Oh? Perubahan seperti apa yang kamu maksud? Aku harap ini perubahan ke arah yang baik.\"", 30);
    delayPrint(L"Irene: \"Sangat baik, Tuan Muda. Dulu, saat awal-awal, saya akui saya dan beberapa pelayan lain merasa sedikit... waspada dan, terus terang, takut. Rumor tentang sikap Tuan Muda yang terdahulu cukup membuat kami semua menjaga jarak dan hanya melakukan pekerjaan kami tanpa berani banyak bicara.\"", 30);
    delayPrint(L"Irene: \"Tetapi, semakin hari, kami melihat sisi yang sangat berbeda dari Anda. Anda mulai menyapa kami dengan ramah, menanyakan kabar kami, bahkan hal-hal kecil seperti mengingat nama anak-anak kami atau hari ulang tahun kami. Anda juga sering membantu saat ada kesulitan kecil tanpa diminta.\"", 30);
    delayPrint(L"Irene: \"Saya ingat dengan jelas suatu kali ketika salah satu pelayan dapur, Lily, tidak sengaja menjatuhkan nampan berisi porselen mahal milik Nyonya Astra. Kami semua sudah membayangkan dia akan dipecat atau setidaknya mendapat hukuman berat. Tapi Anda justru menghampirinya, menanyakan dengan tenang apakah dia terluka, dan mengatakan bahwa porselen bisa diganti, tapi keselamatan staf lebih utama. Anda bahkan membantu membereskannya tanpa sepatah kata marah pun. Momen itu... itu sangat mengejutkan dan menyentuh kami semua, Tuan Muda. Dengan cara yang sangat, sangat baik.\"", 30);
    delayPrint(L"Weiss: (Terdiam sejenak, mengingat kejadian itu dengan jelas. Saat itu, dia hanya bertindak berdasarkan naluri barunya) \"Aku... aku hanya melakukan apa yang kurasa benar pada saat itu, Irene. Tidak ada gunanya marah untuk kesalahan yang tidak disengaja. Lily pasti sudah cukup takut dan merasa bersalah waktu itu.\"", 30);
    delayPrint(L"Irene: \"Mungkin bagi Anda itu hal sederhana, Tuan Muda. Tapi bagi kami, itu adalah tanda kebesaran hati dan kepedulian yang tulus. Anda telah menunjukkan bahwa Anda menghargai kami bukan hanya sebagai pekerja, tapi sebagai manusia. Dan bukan hanya saya, tapi banyak staf lain yang merasakan hal yang sama. Suasana di mansion ini jadi jauh lebih hangat, lebih penuh senyum, dan lebih menyenangkan berkat Anda.\"", 30);
    delayPrint(L"Weiss: \"Mendengar itu darimu... sungguh sangat berarti, Irene. Sejujurnya, aku sendiri masih berjuang setiap hari untuk menjadi orang yang lebih baik dari diriku di masa lalu. Pengakuanmu ini memberiku semacam... validasi dan kekuatan bahwa aku berada di jalan yang benar, bahwa perubahanku ini bermakna.\"", 30);
    delayPrint(L"Irene: (Tersenyum tulus, matanya berkaca-kaca) \"Anda sudah lebih dari baik, Tuan Muda. Anda adalah inspirasi bagi kami. Dan kami semua, dengan tulus, mendukung Anda. Terima kasih telah menjadi Tuan Muda yang seperti ini.\"", 30);
    delayPrint(L"Weiss: \"Justru aku yang harus berterima kasih, Irene. Atas kejujuranmu, atas dukunganmu, dan atas persahabatanmu. Itu semua memberiku semangat.\"", 30);
    delayPrint(L"Irene: \"Kapan pun Anda butuh teman bicara atau sekadar didengarkan, saya selalu ada, Tuan Muda.\"", 30);
    delayPrint(L"Kepercayaan dan rasa hormat yang terpancar dari mata Irene membuat hatimu terasa hangat dan damai. Kamu merasa usahamu untuk berubah tidak sia-sia dan telah menyentuh banyak hati.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel9() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 9 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Kalian duduk di bangku taman langganan, menikmati semilir angin senja yang membawa aroma bunga melati dan suara jangkrik yang mulai terdengar. Keheningan di antara kalian terasa nyaman, bukan canggung, dipenuhi pemahaman.", 30);
    delayPrint(L"Weiss: \"Entah mengapa, Irene, akhir-akhir ini aku sering merenung. Tentang takdir, tentang pilihan-pilihan besar dalam hidup... tentang apakah kita benar-benar bisa mengubah alur cerita yang seolah sudah ditetapkan untuk kita.\"", 30);
    delayPrint(L"Irene: (Menatapmu dengan pandangan yang dalam dan penuh perhatian) \"Saya percaya kita semua memiliki peran penting dalam menentukan jalan hidup kita sendiri, Tuan Muda. Mungkin ada hal-hal besar di luar kendali kita, seperti badai atau musim. Tapi bagaimana kita merespons, bagaimana kita memilih untuk bertindak dalam situasi tersebut... itu sepenuhnya ada di tangan kita. Kita adalah nakhoda bagi kapal kita sendiri, meskipun lautan terkadang ganas.\"", 30);
    delayPrint(L"Weiss: \"Sebuah analogi yang indah, Irene. Tapi terkadang, menjadi nakhoda itu terasa sangat sepi dan bebannya berat. Apalagi jika masa lalu terus menciptakan gelombang yang mencoba menenggelamkan kapal itu.\"", 30);
    delayPrint(L"Irene: \"Masa lalu adalah pelajaran berharga, Tuan Muda, bukan sebuah jangkar yang harus terus menyeret kita ke dasar. Anda telah membuktikan bahwa perubahan itu mungkin, bahwa kapal bisa diarahkan ke tujuan yang baru dan lebih baik. Anda telah memilih jalan yang berbeda, jalan yang dipenuhi kebaikan dan keberanian. Dan lihatlah sekeliling Anda, lihatlah bagaimana pilihan itu membawa dampak positif bagi banyak orang, termasuk saya.\"", 30);
    delayPrint(L"Weiss: \"kamu selalu tahu cara membuatku melihat sisi terangnya, ya, Irene? Kata-katamu seperti mercusuar di tengah kabut. Persahabatanmu ini seperti oasis di tengah gurun yang tandus bagiku. Sesuatu yang tidak pernah kuduga akan kutemukan di kehidupan keduaku ini.\"", 30);
    delayPrint(L"Irene: (Tersenyum lembut, pipinya sedikit merona namun tatapannya mantap) \"Bagi saya pun begitu, Tuan Muda Weiss. Anda telah menunjukkan arti persahabatan yang tulus, yang melampaui batasan status atau latar belakang. Anda membuat saya merasa dihargai bukan hanya sebagai pelayan, tapi sebagai seorang individu, sebagai seorang teman yang setara. Itu adalah hadiah yang tak ternilai.\"", 30);
    delayPrint(L"Irene: \"Karena itu, ketahuilah, Tuan Muda, apapun yang terjadi di masa depan, serumit apapun tantangan yang mungkin menghadang, Anda tidak akan pernah menghadapinya sendirian. Kesetiaan dan dukungan saya akan selalu menyertai Anda. Saya akan menjadi perisai Anda jika perlu, dan penasihat Anda jika diminta.\"", 30);
    delayPrint(L"Weiss: (Menatap Irene dengan rasa terima kasih yang mendalam, suaranya sedikit bergetar) \"Kata-katamu itu... lebih berharga dari semua harta di dunia ini, Irene. Aku benar-benar beruntung memilikimu sebagai sahabat. Dan aku juga akan selalu ada untukmu, sebagai temanmu, sebagai saudaramu. Selalu.\"", 30);
    delayPrint(L"Irene: \"Saya tahu, Tuan Muda. Dan kepercayaan itu adalah segalanya bagi saya. Kita akan saling menjaga, bukan?\"", 30);
    delayPrint(L"Weiss: \"Tentu saja, Irene. Kita akan saling menjaga.\"", 30);
    delayPrint(L"Ada ikrar tak terucap yang lebih kuat dari sumpah manapun dalam tatapan kalian, sebuah janji kesetiaan dan dukungan timbal balik yang melampaui kata-kata. Kamu merasa aman, diterima, dan memiliki sekutu sejati, sebuah perasaan yang langka dan sangat berharga bagimu.", 30);

    printLine();
    waitForEnter();
}

void sceneIreneLevel10() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Irene - Maid ✦ Level 10 ✦ Taman Belakang Mansion ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Irene: (Menghampirimu dengan ekspresi yang sangat khidmat dan sedikit gugup, membawa sebuah kotak kayu kecil yang diukir dengan motif bunga lili yang sangat halus) \"Tuan Muda Weiss, bolehkah saya meminta sedikit waktu Anda? Ada sesuatu yang sangat istimewa yang ingin saya sampaikan dan berikan kepada Anda hari ini. Ini adalah... ungkapan terima kasih saya yang terdalam atas semua yang telah Anda lakukan, atas persahabatan kita yang luar biasa.\"", 30);
    delayPrint(L"Weiss: \"Tentu saja, Irene. Seluruh waktuku untukmu. Ada apa? kamu terlihat sangat... khidmat dan sedikit berbeda hari ini. Apakah semuanya baik-baik saja?\"", 30);
    delayPrint(L"Irene: (Mengambil napas dalam-dalam) \"Semuanya lebih dari baik, Tuan Muda. Dengan tangan yang sedikit gemetar karena haru namun penuh keyakinan, dia membuka kotak itu perlahan, memperlihatkan sebuah jam saku perak antik dengan ukiran inisial 'WVA' yang sangat halus dan elegan di penutupnya. Rantainya terbuat dari perak murni yang berkilau lembut.\"", 30);
    delayPrint(L"Irene: \"Ini... ini adalah jam saku peninggalan kakek buyut saya, Tuan Muda. Beliau adalah seorang cendekiawan dan penasihat raja yang sangat dihormati pada masanya. Beliau sangat menjunjung tinggi integritas, kebijaksanaan, dan keberanian untuk melakukan hal yang benar, bahkan ketika itu sulit.\"", 30);
    delayPrint(L"Irene: \"Sebelum beliau wafat, beliau berpesan kepada keluarga kami agar jam ini dijaga baik-baik dan suatu hari nanti diwariskan kepada seseorang di luar garis keturunan kami, seseorang yang benar-benar mencerminkan nilai-nilai luhur yang beliau anut. Seseorang yang memiliki potensi untuk membawa perubahan besar yang positif bagi banyak orang. Selama ini, jam ini menjadi pusaka keluarga kami, menunggu orang yang tepat itu.\"", 30);
    delayPrint(L"Irene: \"Dan setelah mengenal Anda, Tuan Muda Weiss, setelah melihat transformasi luar biasa dalam diri Anda, setelah merasakan kebaikan hati dan kebijaksanaan Anda yang tulus... saya dan keluarga saya berdiskusi, dan kami semua setuju. Orang itu... adalah Anda.\"", 30);
    delayPrint(L"Weiss: (Terpana, tak bisa berkata-kata, menerima kotak berisi jam saku itu dengan kedua tangan gemetar. Beratnya terasa lebih dari sekadar logam mulia) \"Irene... aku... aku tidak tahu harus berkata apa. Ini... ini adalah sebuah kehormatan yang tak terhingga. Sebuah warisan yang begitu berharga... Aku merasa... aku belum pantas menerimanya.\"", 30);
    delayPrint(L"Irene: (Menggeleng lembut, matanya berkaca-kaca namun senyumnya penuh keyakinan) \"Anda lebih dari pantas, Tuan Muda. Anda telah menunjukkan semua kualitas yang kakek buyut saya kagumi dan hargai. Anggaplah ini sebagai simbol bahwa waktu selalu berharga, dan setiap detik adalah kesempatan untuk terus tumbuh, belajar, dan menjadi lebih baik, seperti yang telah Anda buktikan kepada kami semua tanpa henti.\"", 30);
    delayPrint(L"Irene: \"Lebih dari itu, Tuan Muda, ini adalah janji kesetiaan abadi dari saya dan keluarga saya. Selama jarum jam ini masih berdetak, selama itu pula dukungan, doa, dan persahabatan kami akan selalu menyertai Anda, dalam suka maupun duka, dalam setiap keputusan dan langkah yang Anda ambil. Anda tidak akan pernah berjalan sendirian.\"", 30);
    delayPrint(L"Weiss: (Menggenggam jam saku itu erat, suaranya serak karena emosi yang meluap) \"Irene... hadiah ini, dan kepercayaan yang kamu dan keluargamu berikan padaku... adalah kehormatan terbesar dalam hidupku. Aku bersumpah akan menjaganya seperti aku menjaga nyawaku sendiri, dan seperti aku menjaga persahabatan kita yang tak ternilai harganya. kamu bukan hanya pelayan, bukan hanya teman. kamu adalah saudari, bagian dari jiwaku, bagian dari keluargaku sekarang.\"", 30);
    delayPrint(L"Irene: (Meneteskan air mata bahagia yang tak terbendung, namun senyumnya begitu tulus dan cerah) \"Bagi saya pun begitu, Tuan Muda. Anda adalah kakak, pelindung, dan sahabat terbaik yang pernah saya miliki. Dan saya akan selalu bangga menjadi bagian dari perjalanan hidup Anda, menjadi saksi dari semua hal hebat yang akan Anda capai.\"", 30);
    delayPrint(L"Weiss: \"Terima kasih, Irene. Terima kasih untuk segalanya. Kita akan melalui apapun yang datang di depan, bersama-sama. Selalu.\"", 30);
    delayPrint(L"Irene: \"Selalu, Tuan Muda Weiss. Selalu.\"", 30);
    delayPrint(L"Di bawah langit taman yang menjadi saksi bisu perjalanan persahabatan mereka, sebuah ikatan yang tak terukur nilainya, lebih berharga dari semua harta dunia, telah terjalin abadi. Jam saku itu bukan sekadar penunjuk waktu, melainkan simbol harapan, perubahan, kesetiaan, dan cinta persaudaraan yang akan selalu mereka kenang dan pegang teguh.", 30);

    waitForEnter(L" Kamu telah membentuk ikatan terkuat...... Tekan Enter untuk melihat detailnya");

    if (!socialLinks["Irene"].completed) { 
        applySocialLinkBonus("Irene"); 
        socialLinks["Irene"].completed = true; 
    }    

    printLine();
    waitForEnter();
}

void sceneEllaLevel1() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 1 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Masuk ke Cross Guild yang ramai dengan lalu-lalang petualang) \"Permisi, apakah Anda Nona Ella, pemilik Cross Guild ini?\"", 30);
    delayPrint(L"Ella: (Mengalihkan pandangan dari setumpuk perkamen di mejanya, menatap Weiss dengan tatapan menilai) \"Benar. Saya Ella. Ada urusan apa Tuan Muda dari keluarga Astra datang ke tempat seperti ini? Jarang sekali bangsawan mampir.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya ingin melihat langsung bagaimana sebuah guild petualang beroperasi. Keluarga Astra memiliki kepentingan dalam stabilitas kota, dan guild Anda memainkan peran penting dalam hal itu, bukan?\"", 30);
    delayPrint(L"Ella: \"Peran penting, ya? Kami hanya menyediakan platform bagi mereka yang mencari pekerjaan dan mereka yang membutuhkan jasa. Simbiosis mutualisme, Tuan Muda. Apakah Anda mencari quest tertentu? Atau sekadar... observasi?\"", 30);
    delayPrint(L"Weiss: \"Untuk saat ini, lebih ke observasi. Saya ingin memahami dinamika dan jenis-jenis permintaan yang biasa masuk. Mungkin ada cara keluarga kami bisa berkontribusi lebih efektif.\"", 30);
    delayPrint(L"Ella: (Mengangkat sebelah alisnya, sedikit skeptis namun tetap profesional) \"Kontribusi dari keluarga Astra selalu diterima, selama itu menguntungkan kedua belah pihak. Silakan melihat-lihat. Papan quest ada di sebelah sana. Jangan membuat keributan, anak-anak buah saya terkadang sedikit... bersemangat.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti. Terima kasih atas waktu Anda, Nona Ella. Saya akan berusaha tidak mengganggu.\"", 30);
    delayPrint(L"Ella: \"Hm. Jika ada pertanyaan spesifik, tanyakan saja pada Griz, wakil saya. Dia lebih punya banyak waktu luang.\" (Kembali fokus pada perkamennya)", 30);
    delayPrint(L"Weiss: \"Baik. Terima kasih atas informasinya.\"", 30);
    delayPrint(L"Ella: \"Sama-sama, Tuan Muda.\"", 30);
    delayPrint(L"Kesan pertama, Ella adalah wanita yang tegas, praktis, dan tidak suka basa-basi. Kamu merasa ini akan menjadi hubungan yang menarik untuk dijalin.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel2() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 2 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Nona Ella, saya kembali. Saya sudah melihat-lihat papan quest. Cukup beragam ya, mulai dari pengawalan pedagang hingga perburuan monster.\"", 30);
    delayPrint(L"Ella: (Mendongak dari catatannya, sedikit kurang terkejut melihatmu kali ini) \"Tuan Muda Astra. Selamat datang kembali. Ya, kebutuhan kota ini memang beragam. Apa ada yang menarik perhatian Anda secara khusus?\"", 30);
    delayPrint(L"Weiss: \"Saya perhatikan ada beberapa permintaan investigasi kasus pencurian kecil di distrik pengrajin. Apakah kasus seperti itu sering terjadi dan ditangani oleh guild? Bukankah itu tugas penjaga kota?\"", 30);
    delayPrint(L"Ella: \"Penjaga kota punya prioritas mereka sendiri, Tuan Muda. Terkadang sumber daya mereka terbatas. Untuk kasus-kasus yang dianggap 'kecil', warga lebih suka menyewa petualang dari guild. Lebih cepat, dan terkadang lebih... efektif dalam menemukan barang yang hilang, jika Anda mengerti maksud saya.\"", 30);
    delayPrint(L"Weiss: \"Saya mulai mengerti. Jadi guild Anda mengisi celah yang tidak terjangkamu oleh aparat resmi. Apakah ada kesulitan dalam menangani jenis quest seperti itu? Mungkin terkait bukti atau yurisdiksi?\"", 30);
    delayPrint(L"Ella: \"Selalu ada tantangan. Kami punya aturan main sendiri di sini. Selama tidak melanggar hukum besar kerajaan dan semua pihak sepakat, kami jalan terus. Petualang kami juga punya kode etik... setidaknya sebagian besar dari mereka.\", (tersenyum miring)", 30);
    delayPrint(L"Weiss: \"Sebuah sistem yang menarik, meskipun mungkin sedikit... abu-abu. Apakah Anda sendiri yang menyeleksi quest yang masuk atau ada tim khusus?\"", 30);
    delayPrint(L"Ella: \"Untuk quest dengan risiko tinggi atau bayaran besar, saya akan meninjaunya langsung. Sisanya, Griz dan beberapa staf senior yang menangani. Kami harus memastikan quest itu layak dan tidak membahayakan reputasi guild secara keseluruhan.\"", 30);
    delayPrint(L"Weiss: \"Manajemen risiko yang cermat. Saya menghargai keterbukaan Anda dalam menjelaskan, Nona Ella.\"", 30);
    delayPrint(L"Ella: \"Anggap saja ini bagian dari transparansi, Tuan Muda. Semakin Anda mengerti cara kerja kami, semakin baik potensi 'kontribusi' yang Anda sebutkan tempo hari, bukan?\"", 30);
    delayPrint(L"Weiss: \"Anda benar. Saya akan terus belajar. Terima kasih.\"", 30);
    delayPrint(L"Ella hanya mengangguk singkat, tapi kamu merasa ada sedikit rasa hormat yang mulai tumbuh di matanya terhadap keseriusanmu.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel3() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 3 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Suasana guild hari ini tampak lebih ramai dari biasanya, Nona Ella. Apakah ada event khusus atau permintaan besar yang masuk?\"", 30);
    delayPrint(L"Ella: (Menyesap cangkir tehnya, memandang ke arah kerumunan petualang) \"Tidak ada event khusus, Tuan Muda. Hanya saja, musim berburu monster di Hutan Merah baru saja dibuka kembali setelah badai minggu lalu. Banyak yang antusias mencari peruntungan.\"", 30);
    delayPrint(L"Weiss: \"Ah, Hutan Merah. Saya dengar medannya cukup berbahaya. Apakah guild sering menerima permintaan terkait area tersebut?\"", 30);
    delayPrint(L"Ella: \"Sangat sering. Mulai dari mengumpulkan bahan langka, menyelamatkan petualang yang tersesat, hingga mengendalikan populasi monster tertentu yang mulai meresahkan desa-desa di perbatasan hutan. Itu salah satu sumber pendapatan utama guild, sekaligus yang paling berisiko.\"", 30);
    delayPrint(L"Weiss: \"Pasti tidak mudah mengelola begitu banyak petualang dengan berbagai tingkat keahlian dan temperamen. Bagaimana Anda memastikan semuanya berjalan sesuai aturan dan tidak ada konflik internal yang besar?\"", 30);
    delayPrint(L"Ella: (Tersenyum tipis, ada kilat geli di matanya) \"Aturan dibuat untuk dilanggar, Tuan Muda, terutama oleh para petualang. Tapi ya, kami punya sistem peringkat, kontrak yang jelas, dan... beberapa 'penegak disiplin' tidak resmi yang memastikan semua orang tahu batasnya. Konflik kecil itu biasa, seperti bumbu dalam masakan. Selama tidak meledakkan seluruh dapur, saya biarkan saja.\"", 30);
    delayPrint(L"Weiss: \"Sebuah pendekatan yang sangat pragmatis. Apakah Anda tidak pernah merasa lelah dengan semua drama dan potensi masalah ini setiap hari?\"", 30);
    delayPrint(L"Ella: \"Lelah itu pasti, Tuan Muda. Tapi ada kepuasan tersendiri saat melihat sebuah quest berhasil diselesaikan, atau saat petualang muda yang dulu ceroboh kini tumbuh jadi veteran yang dihormati. Guild ini lebih dari sekadar bisnis bagi saya. Ini... semacam keluarga besar yang kacau balau.\"", 30);
    delayPrint(L"Weiss: \"Saya bisa melihat dedikasi Anda, Nona Ella. Dan saya mulai mengerti mengapa guild ini begitu dihormati di Arcadia.\"", 30);
    delayPrint(L"Ella: \"Hormat itu harus diperoleh, Tuan Muda, bukan diberikan. Sama seperti reputasi Anda sendiri yang sedang Anda bangun kembali, bukan?\", (Menatap Weiss dengan tajam namun tidak permusuhan)", 30);
    delayPrint(L"Weiss: (Sedikit terkejut dengan observasinya yang menusuk, namun mengangguk) \"Anda benar, Nona Ella. Saya sedang berusaha.\"", 30);
    delayPrint(L"Ella: \"Teruslah berusaha. Kota ini membutuhkan lebih banyak orang seperti Anda yang mau turun tangan, bukan hanya duduk di menara gading.\"", 30);
    delayPrint(L"Kamu merasa ada sedikit pengakuan dalam kata-katanya. Dia mulai melihatmu lebih dari sekadar nama besar keluarga Astra.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel4() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 4 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Saat Weiss sedang berbicara dengan Ella di konternya, tiba-tiba terdengar keributan dari area papan quest. Dua petualang tampak berdebat sengit.", 30);
    delayPrint(L"Petualang A: \"Quest ini jelas milik timku! Kami yang melihatnya pertama!\"", 30);
    delayPrint(L"Petualang B: \"Melihat bukan berarti mengambil, Bodoh! Timku yang sudah mendaftarkannya pada Griz!\"", 30);
    delayPrint(L"Ella: (Menghela napas panjang, memijat pelipisnya) \"Setiap hari selalu ada saja. Sepertinya ini akan jadi pagi yang panjang.\"", 30);
    delayPrint(L"Weiss: \"Apakah ini sering terjadi, Nona Ella? Perebutan quest seperti ini?\"", 30);
    delayPrint(L"Ella: \"Lebih sering dari yang Anda bayangkan, Tuan Muda. Terutama untuk quest dengan imbalan besar atau item langka. Terkadang mereka seperti anak-anak yang berebut mainan baru.\"", 30);
    delayPrint(L"Ella kemudian bangkit dan berjalan menuju keributan itu dengan langkah tenang namun berwibawa. \"Ada masalah apa di sini? Jangan membuat keributan di guild-ku pagi-pagi begini.\", (nadanya dingin dan tegas)", 30);
    delayPrint(L"Kedua petualang itu langsung terdiam, tampak sedikit gentar. Setelah mendengar penjelasan singkat, Ella mengambil keputusan dengan cepat.", 30);
    delayPrint(L"Ella: \"Quest ini akan diberikan kepada tim yang pertama kali mendaftarkannya secara resmi. Itu aturannya. Tim lain, cari quest lain atau tunggu giliran. Tidak ada diskusi lagi.\"", 30);
    delayPrint(L"Para petualang itu menggerutu, tapi akhirnya membubarkan diri. Ella kembali ke konter.", 30);
    delayPrint(L"Weiss: \"Penyelesaian yang cepat dan tegas. Saya terkesan.\"", 30);
    delayPrint(L"Ella: \"Ketegasan itu perlu, Tuan Muda. Jika tidak, tempat ini akan jadi pasar malam. Tapi terkadang, saya berharap mereka bisa sedikit lebih dewasa. Anda sendiri, apakah di dunia bangsawan juga sering ada 'perebutan quest' semacam ini, mungkin dalam bentuk yang berbeda?\"", 30);
    delayPrint(L"Weiss: (Tersenyum tipis) \"Oh, tentu saja, Nona Ella. Perebutan pengaruh, harta, dan kehormatan. Hanya saja, medannya berbeda dan senjatanya terkadang lebih... halus namun mematikan.\"", 30);
    delayPrint(L"Ella: (Tertawa kecil, tawa yang mengejutkanmu karena terdengar cukup tulus) \"Saya bisa membayangkannya. Setidaknya di sini, jika ada masalah, kami bisa menyelesaikannya dengan adu jotos di arena belakang. Lebih sederhana.\"", 30);
    delayPrint(L"Weiss: \"Setiap dunia punya caranya sendiri, sepertinya. Tapi saya setuju, kesederhanaan terkadang lebih baik.\"", 30);
    delayPrint(L"Kamu merasa ada sedikit keakraban yang terjalin setelah insiden kecil itu. Humor sarkastis Ella ternyata cukup menarik.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel5() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 5 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Nona Ella, saya perhatikan banyak petualang yang mengeluhkan tentang kurangnya informasi detail pada beberapa quest pengintaian. Mereka sering membuang waktu karena target atau lokasi yang kurang jelas.\"", 30);
    delayPrint(L"Ella: (Mengangkat sebelah alis) \"Oh ya? Keluhan itu belum sampai ke telinga saya secara langsung. Tapi saya tidak heran. Klien terkadang pelit informasi atau memang tidak tahu detailnya. Apa Anda punya usulan, Tuan Muda Astra yang penuh perhatian?\", (nadanya sedikit menyindir, tapi ada rasa ingin tahu)", 30);
    delayPrint(L"Weiss: \"Saya hanya berpikir, mungkin Guild bisa membuat semacam formulir standar yang lebih detail untuk klien saat mengajukan quest investigasi. Pertanyaan spesifik tentang ciri-ciri target, waktu terakhir terlihat, area yang dicurigai. Mungkin juga ada insentif kecil bagi klien yang memberikan informasi paling akurat?\"", 30);
    delayPrint(L"Ella: (Tertegun sejenak, memandang Weiss dengan tatapan baru) \"Formulir standar... Insentif untuk informasi akurat... Itu... sebenarnya bukan ide yang buruk, Tuan Muda. Sangat tidak buruk. Bisa mengurangi risiko kegagalan quest dan perselisihan.\"", 30);
    delayPrint(L"Weiss: \"Hanya sebuah pemikiran. Anda yang lebih memahami seluk-beluk operasional guild ini. Mungkin bisa disesuaikan.\"", 30);
    delayPrint(L"Ella: \"Saya akan memikirkannya. Serius. Mungkin saya akan meminta Griz untuk merancang draf formulirnya. Terima kasih atas masukannya, Tuan Muda. Saya tidak menyangka seorang bangsawan punya perhatian sampai ke detail operasional seperti ini.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya ingin melihat semua pihak mendapatkan hasil yang optimal, Nona Ella. Efisiensi itu baik untuk semua, bukan? Termasuk reputasi Guild.\"", 30);
    delayPrint(L"Ella: \"Anda benar. Reputasi adalah aset terbesar kami. Baiklah, Tuan Muda, sebagai ucapan terima kasih atas ide brilian Anda, bagaimana kalau secangkir kopi terbaik dari kedai seberang? Saya yang traktir.\"", 30);
    delayPrint(L"Weiss: (Sedikit terkejut dengan tawaran itu) \"Sebuah kehormatan, Nona Ella. Saya terima dengan senang hati.\"", 30);
    delayPrint(L"Ella: \"Bagus. Jarang-jarang saya menemukan seseorang yang bisa memberikan masukan berguna selain keluhan. Anda mulai membuat saya terkesan, Tuan Muda.\"", 30);
    delayPrint(L"Kamu merasa ada perubahan signifikan dalam cara Ella memandangmu. Bukan lagi sekadar bangsawan yang penasaran, tapi seseorang yang punya ide dan bisa diajak berpikir.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel6() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 6 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Suatu sore, Weiss menemukan Ella sedang memandangi sebuah peta tua wilayah sekitar Arcadia yang terpajang di dinding kantornya, ekspresinya tampak serius.", 30);
    delayPrint(L"Weiss: \"Peta yang menarik, Nona Ella. Sepertinya jauh lebih detail daripada peta resmi yang dikeluarkan balai kota. Apakah ini peta khusus milik guild?\"", 30);
    delayPrint(L"Ella: (Menoleh, senyum tipis tersungging) \"Ah, Tuan Muda. Ya, ini peta hasil kompilasi laporan dari para petualang kami selama bertahun-tahun. Lebih banyak menandai jalur tikus, sarang monster, dan reruntuhan tersembunyi daripada jalan utama.\"", 30);
    delayPrint(L"Weiss: \"Pasti sangat berharga. Saya lihat Anda menandai area di sekitar Pegunungan Naga Merah. Apakah ada sesuatu yang terjadi di sana?\"", 30);
    delayPrint(L"Ella: \"Selalu ada sesuatu yang terjadi di Pegunungan Naga Merah, Tuan Muda.\" (Menghela napas) \"Beberapa tahun lalu, ada wabah aneh yang menyerang hewan ternak di desa-desa kaki gunung. Banyak yang mengira itu kutukan. Kami mengirim tim terbaik kami untuk menyelidikinya.\"", 30);
    delayPrint(L"Ella: \"Ternyata itu disebabkan oleh tanaman beracun langka yang tumbuh subur setelah musim hujan ekstrem, mencemari sumber air. Para petualang kami, setelah melalui banyak rintangan dan kehilangan beberapa rekan, berhasil menemukan sumbernya dan cara menetralisirnya. Itu salah satu quest tersulit sekaligus paling memuaskan yang pernah ditangani guild ini.\"", 30);
    delayPrint(L"Weiss: \"Sebuah kisah kepahlawanan yang luar biasa. Para petualang itu pasti sangat berani dan berdedikasi. Apakah guild memberikan penghargaan khusus untuk mereka?\"", 30);
    delayPrint(L"Ella: \"Imbalan materi sudah pasti. Tapi yang lebih penting, nama mereka terukir di Aula Kehormatan Guild. Dan yang terpenting, mereka menyelamatkan banyak nyawa. Itulah esensi sejati dari Cross Guild ini, Tuan Muda. Bukan hanya uang atau ketenaran, tapi membantu mereka yang membutuhkan, menjaga keseimbangan.\"", 30);
    delayPrint(L"Weiss: \"Saya semakin memahami dalamnya dedikasi Anda pada guild ini dan orang-orangnya, Nona Ella. Ini lebih dari sekadar pekerjaan bagi Anda.\"", 30);
    delayPrint(L"Ella: \"Guild ini adalah hidup saya, Tuan Muda. Sejak saya mengambil alih dari ayah saya. Ada banyak suka dan duka, tapi saya tidak akan menukarnya dengan apapun. Nah, cukup dengan cerita lama. Apa ada yang bisa saya bantu hari ini?\"", 30);
    delayPrint(L"Weiss: \"Tidak ada, Nona Ella. Saya hanya senang mendengar cerita Anda. Itu memberi saya banyak inspirasi.\"", 30);
    delayPrint(L"Ella: \"Kapan saja, Tuan Muda. Pintu kantor saya selalu terbuka jika Anda ingin mendengar dongeng sebelum tidur dari seorang Guild Master tua.\" (Mengedipkan sebelah mata)", 30);
    delayPrint(L"Kamu tertawa. Sisi humoris dan hangat Ella semakin terlihat, di balik fasadnya yang tegas.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel7() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 7 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Nona Ella, saya butuh pendapat Anda mengenai suatu masalah. Ini sedikit di luar urusan guild, tapi saya merasa insting dan pengalaman Anda di kota ini bisa memberikan pencerahan.\"", 30);
    delayPrint(L"Ella: (Meletakkan penanya, menatap Weiss dengan penuh perhatian) \"Oh? Tumben sekali Anda meminta pendapat saya, Tuan Muda. Biasanya Anda yang memberi masukan. Ada apa? Silakan ceritakan.\"", 30);
    delayPrint(L"Weiss: \"Saya mendengar desas-desus tentang adanya kelompok penyelundup yang mulai aktif di area dermaga. Mereka katanya mendatangkan barang-barang terlarang. Pihak penjaga kota sepertinya belum berhasil melacak mereka. Saya khawatir ini bisa berdampak buruk pada keamanan Arcadia.\"", 30);
    delayPrint(L"Ella: (Mengangguk pelan, ekspresinya serius) \"Penyelundupan di dermaga, ya? Bukan hal baru, tapi jika skalanya besar, itu memang mengkhawatirkan. Jaringan informasi saya juga menangkap beberapa sinyal aneh dari sana. Apa yang ingin Anda ketahui dari saya?\"", 30);
    delayPrint(L"Weiss: \"Menurut Anda, siapa kira-kira pemain besar di balik ini? Dan bagaimana cara terbaik untuk mendapatkan informasi lebih lanjut tanpa menimbulkan kecurigaan besar? Saya tidak ingin gegabah dan membuat situasi semakin rumit.\"", 30);
    delayPrint(L"Ella: (Berpikir sejenak, jemarinya mengetuk-ngetuk meja) \"Pemain besar di dermaga biasanya ada beberapa faksi lama. Tapi jika ini barang terlarang skala besar, mungkin ada pemain baru yang lebih licin. Untuk informasi, Anda bisa mencoba mendekati beberapa informan lepas yang sering mangkal di kedai 'Saucy Siren'. Tapi hati-hati, Tuan Muda, mereka seperti belut, licin dan hanya setia pada koin emas.\"", 30);
    delayPrint(L"Ella: \"Pastikan Anda tidak pergi sendirian dan membawa 'sesuatu' untuk melancarkan pembicaraan. Dan jangan pernah menyebut nama saya atau guild. Kami berusaha menjaga netralitas dalam hal seperti ini, kecuali jika sudah sangat mengancam stabilitas umum.\"", 30);
    delayPrint(L"Weiss: \"Informasi yang sangat berharga, Nona Ella. 'Saucy Siren', ya? Saya akan mengingatnya. Dan tentu saja, saya akan sangat berhati-hati. Apakah ada hal lain yang perlu saya waspadai?\"", 30);
    delayPrint(L"Ella: \"Selalu waspada pada bayangan Anda sendiri, Tuan Muda. Dermaga itu tempat yang keras. Dan jika Anda memang serius ingin memberantas ini, pastikan Anda punya rencana cadangan. Penyelundup kelas kakap tidak akan segan-segan menyingkirkan pengganggu.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti. Terima kasih banyak atas nasihat dan peringatan Anda, Nona Ella. Ini sangat membantu saya menyusun langkah selanjutnya.\"", 30);
    delayPrint(L"Ella: \"Gunakan informasi itu dengan bijak, Tuan Muda. Dan jika situasinya memburuk dan Anda butuh bantuan 'non-resmi', Anda tahu di mana mencari saya. Tapi ingat, ada harga untuk segalanya.\", (tersenyum penuh arti)", 30);
    delayPrint(L"Weiss: \"Akan saya ingat itu. Terima kasih.\"", 30);
    delayPrint(L"Kamu merasa Ella mulai mempercayaimu dengan informasi yang lebih sensitif. Dia melihatmu sebagai seseorang yang bisa bertindak, bukan hanya berbicara.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel8() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 8 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Ella: \"Tuan Muda Astra, ada waktu sebentar? Saya baru saja menyelesaikan laporan keuangan bulanan guild, dan nama Anda beberapa kali muncul sebagai donatur untuk misi-misi kemanusiaan kecil yang kami tangani. Saya tidak menyangka.\"", 30);
    delayPrint(L"Weiss: \"Oh, itu... hanya sumbangan kecil, Nona Ella. Saya merasa terpanggil untuk membantu jika ada kesempatan. Terutama untuk misi yang berkaitan dengan panti asuhan atau bantuan bencana alam di desa terpencil.\"", 30);
    delayPrint(L"Ella: (Menatap Weiss dengan ekspresi yang sulit diartikan, campuran antara terkejut dan... hormat?) \"Sumbangan kecil katamu? Jumlah itu cukup untuk memberi makan seluruh panti asuhan selama sebulan. Anda tahu, Tuan Muda, saya sudah berurusan dengan banyak bangsawan selama bertahun-tahun. Sebagian besar dari mereka hanya peduli pada reputasi dan keuntungan pribadi.\"", 30);
    delayPrint(L"Ella: \"Tapi Anda... Anda berbeda. Anda datang ke sini, mencoba memahami kami, memberikan masukan, bahkan diam-diam berdonasi tanpa mencari publisitas. Anda bukan tipikal bangsawan manja yang saya bayangkan saat pertama kali Anda masuk ke guild ini.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya berusaha menjadi orang yang berguna, Nona Ella. Harta dan status tidak akan berarti jika tidak bisa membawa kebaikan bagi orang lain. Saya belajar itu dengan cara yang... cukup keras.\"", 30);
    delayPrint(L"Ella: \"Apapun pelajaran itu, sepertinya itu pelajaran yang sangat berharga. Kota ini, bahkan guild ini, beruntung memiliki seseorang seperti Anda yang mulai peduli. Dulu, saya pikir keluarga Astra hanya akan menambah beban birokrasi.\"", 30);
    delayPrint(L"Weiss: \"Saya harap saya bisa terus membuktikan bahwa saya berbeda dari stereotip itu. Dan saya juga berterima kasih pada Anda, Nona Ella. Anda telah banyak mengajari saya tentang sisi lain kota ini, tentang realitas yang tidak pernah saya lihat dari balik tembok mansion.\"", 30);
    delayPrint(L"Ella: \"Anggap saja ini pertukaran yang adil, Tuan Muda. Anda memberi kami perspektif baru, kami memberi Anda sedikit pelajaran tentang kerasnya dunia.\" (tersenyum tipis) \"Tapi serius, tindakan Anda itu... mengesankan. Jangan berhenti melakukannya.\"", 30);
    delayPrint(L"Weiss: \"Saya tidak akan berhenti, Nona Ella. Selama saya mampu.\"", 30);
    delayPrint(L"Ella: \"Bagus. Karena dunia ini butuh lebih banyak orang seperti itu. Sekarang, bagaimana kalau kita membahas proposal Anda tentang patroli keamanan gabungan di distrik pasar? Saya punya beberapa ide tambahan.\"", 30);
    delayPrint(L"Weiss: \"Dengan senang hati, Nona Ella.\"", 30);
    delayPrint(L"Kamu merasa telah mendapatkan rasa hormat yang tulus dari Ella. Dia tidak lagi melihatmu hanya sebagai 'Tuan Muda Astra', tapi sebagai Weiss, seseorang yang punya prinsip dan tindakan nyata.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel9() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 9 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Menemukan Ella sedang menatap keluar jendela kantornya, memandang hiruk pikuk kota di bawah dengan ekspresi termenung) \"Pemandangan yang cukup menarik dari sini, Nona Ella. Seluruh aktivitas kota terlihat seperti miniatur.\"", 30);
    delayPrint(L"Ella: (Menoleh, senyum lelah namun tulus terukir) \"Tuan Muda Weiss. Ya, dari sini saya bisa melihat denyut nadi Arcadia. Setiap hari, ada harapan baru, ada kekecewaan, ada perjuangan. Kota ini tidak pernah tidur.\"", 30);
    delayPrint(L"Weiss: \"Dan guild Anda adalah salah satu jantungnya, memastikan denyut itu tetap stabil. Akhir-akhir ini, saya mendengar beberapa keluhan dari para pedagang kecil tentang adanya pungutan liar oleh preman-preman di pasar malam. Ini meresahkan mereka.\"", 30);
    delayPrint(L"Ella: (Menghela napas, rahangnya sedikit mengeras) \"Saya juga sudah mendengar desas-desus itu. Kelompok tikus-tikus got yang mencoba mengambil keuntungan dari yang lemah. Ini bukan yang pertama kali, dan mungkin bukan yang terakhir. Hal seperti ini mencoreng nama baik kota dan merugikan banyak orang.\"", 30);
    delayPrint(L"Weiss: \"Saya setuju. Saya sedang mempertimbangkan untuk meminta penjaga kota meningkatkan patroli, tapi saya khawatir itu tidak akan cukup efektif untuk menangkap biang keladinya. Apakah guild punya cara untuk membantu mengatasi ini, mungkin secara tidak langsung?\"", 30);
    delayPrint(L"Ella: \"Kami memang bukan aparat penegak hukum resmi, Tuan Muda. Tapi kami punya 'telinga' dan 'mata' di banyak tempat. Jika Anda serius ingin membereskan ini, mungkin kita bisa 'mendorong' beberapa informasi ke arah yang benar, atau memberikan 'dukungan tak terduga' kepada pihak yang berwenang.\"", 30);
    delayPrint(L"Ella: \"Saya juga punya kepentingan pribadi dalam hal ini. Banyak anggota guild saya yang keluarganya bergantung pada kelancaran pasar malam. Saya tidak akan tinggal diam jika ada yang mencoba mengganggu periuk nasi mereka. Kita berada di pihak yang sama dalam masalah ini, Tuan Muda.\"", 30);
    delayPrint(L"Weiss: \"Saya senang mendengarnya, Nona Ella. Mengetahui kita punya tujuan yang sama membuat saya lebih optimis. Bagaimana kalau kita diskusikan strategi yang mungkin? Saya punya beberapa ide awal.\"", 30);
    delayPrint(L"Ella: \"Silakan. Saya siap mendengarkan. Dua kepala lebih baik dari satu, terutama jika salah satunya adalah kepala bangsawan yang cerdas dan satunya lagi adalah kepala guild yang... yah, cukup berpengalaman dengan tikus got.\" (tersenyum miring)", 30);
    delayPrint(L"Weiss: (Tersenyum membalas) \"Kombinasi yang menarik, saya rasa. Mari kita mulai.\"", 30);
    delayPrint(L"Ella: \"Dengan senang hati. Mari kita buat para pedagang itu bisa tidur nyenyak lagi.\"", 30);
    delayPrint(L"Kamu merasakan adanya semangat kemitraan yang kuat antara dirimu dan Ella. Kalian berdua memiliki kepedulian yang sama terhadap kesejahteraan kota, meskipun dengan cara pendekatan yang mungkin berbeda. Ini adalah awal dari sebuah aliansi yang berharga.", 30);

    printLine();
    waitForEnter();
}

void sceneEllaLevel10() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Ella - Guild Master ✦ Level 10 ✦ Cross Guild, Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Ella: \"Tuan Muda Weiss, silakan masuk ke ruangan pribadi saya. Ada sesuatu yang ingin saya diskusikan dan tunjukkan kepada Anda, sesuatu yang hanya diketahui oleh segelintir orang.\", (nadanya serius namun ada nada bangga)", 30);
    delayPrint(L"Weiss: (Mengikuti Ella ke sebuah ruangan yang lebih kecil dan lebih privat di belakang kantor utamanya, dindingnya dipenuhi rak buku dan beberapa artefak menarik) \"Ruangan yang nyaman, Nona Ella. Apa gerangan yang begitu rahasia?\"", 30);
    delayPrint(L"Ella: (Berdiri di depan sebuah lemari kayu ek yang besar dan terkunci) \"Selama ini, Anda telah menunjukkan integritas, kecerdasan, dan kepedulian yang tulus terhadap kota ini dan orang-orangnya, termasuk para petualang di guild saya. Anda telah membuktikan diri sebagai sekutu yang bisa diandalkan, jauh melebihi ekspektasi awal saya terhadap seorang bangsawan Astra.\"", 30);
    delayPrint(L"Ella membuka lemari itu, memperlihatkan sebuah piagam kuno berbingkai perak dan sebuah lencana berbentuk perisai dengan simbol singa dan pedang bersilang.", 30);
    delayPrint(L"Ella: \"Ini adalah Piagam Pendirian Asli Cross Guild, yang ditandatangani oleh para pendiri pertama, termasuk kakek buyut saya. Dan ini... adalah Lencana Kehormatan Guild Tertinggi, 'Aegis Arcadia'. Lencana ini hanya diberikan kepada individu di luar guild yang telah memberikan kontribusi luar biasa bagi keamanan dan kesejahteraan kota, serta menunjukkan dukungan tak tergoyahkan kepada prinsip-prinsip Cross Guild.\"", 30);
    delayPrint(L"Ella: \"Sejak guild ini berdiri, baru ada tiga orang yang menerimanya. Dan hari ini, Tuan Muda Weiss von Astra, saya, sebagai Guild Master Cross Guild saat ini, dengan bangga dan penuh keyakinan, menganugerahkan Lencana Kehormatan ini kepada Anda.\"", 30);
    delayPrint(L"Weiss: (Benar-benar terkejut dan terharu, menatap lencana itu dengan tak percaya) \"Nona Ella... saya... saya tidak tahu harus berkata apa. Ini... ini adalah sebuah kehormatan yang tak terbayangkan. Saya merasa... belum cukup pantas menerimanya.\"", 30);
    delayPrint(L"Ella: (Tersenyum tulus, senyum yang jarang sekali ia perlihatkan) \"Anda lebih dari pantas, Weiss. Jangan merendah. Lencana ini bukan hanya pengakuan atas apa yang telah Anda lakukan, tapi juga simbol kepercayaan penuh saya dan guild ini kepada Anda. Dengan lencana ini, Anda akan selalu memiliki akses khusus ke sumber daya guild, informasi prioritas, dan yang terpenting, dukungan penuh dari kami dalam setiap upaya Anda untuk kebaikan Arcadia.\"", 30);
    delayPrint(L"Ella: \"Saya mendirikan guild ini, melanjutkan warisan ayah saya, bukan hanya untuk bisnis, Weiss. Tapi karena saya percaya bahwa setiap orang, tidak peduli latar belakangnya, berhak mendapatkan kesempatan dan perlindungan. Dan saya melihat semangat yang sama dalam diri Anda. Kita mungkin berasal dari dunia yang berbeda, tapi tujuan kita selaras.\"", 30);
    delayPrint(L"Weiss: (Menerima lencana itu dengan tangan gemetar, rasa haru dan tanggung jawab memenuhi hatinya) \"Ella... terima kasih. Terima kasih atas kepercayaan ini. Saya bersumpah akan menjaga kehormatan lencana ini dan akan selalu menjadi mitra setia Cross Guild dan kota Arcadia. Anda telah memberi saya lebih dari sekadar lencana, Anda memberi saya keluarga baru dan tujuan yang lebih besar.\"", 30);
    delayPrint(L"Ella: \"Anggap saja kita adalah dua sisi dari koin yang sama, Weiss. Bangsawan yang peduli dan Guild Master yang pragmatis. Kombinasi yang cukup ampuh, bukan?\" (Mengulurkan tangannya)", 30);
    delayPrint(L"Weiss: (Menjabat tangan Ella dengan erat) \"Sangat ampuh, Ella. Sangat ampuh. Mari kita jaga kota ini bersama-sama.\"", 30);
    delayPrint(L"Ella: \"Dengan senang hati, partner.\" (Mengedipkan sebelah mata)", 30);
    delayPrint(L"Di ruangan pribadi itu, sebuah aliansi yang kuat dan tulus telah termeterai. Bukan lagi antara Tuan Muda Astra dan Guild Master, tapi antara Weiss dan Ella, dua individu yang berbagi visi dan siap berjuang bersama untuk masa depan Arcadia yang lebih baik.", 30);

    waitForEnter(L" Kamu telah membentuk ikatan terkuat...... Tekan Enter untuk melihat detailnya");

    if (!socialLinks["Ella"].completed) { 
        applySocialLinkBonus("Ella"); 
        socialLinks["Ella"].completed = true; 
    }

    printLine();
    waitForEnter();
}


void sceneCharlotteLevel1() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 1 ✦ Depan Balai Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Baru saja keluar dari pertemuan di Balai Kota, dihampiri oleh seorang wanita muda yang energik dengan buku catatan dan pena di tangan)", 30);
    delayPrint(L"Charlotte: \"Permisi, Tuan Muda Weiss von Astra, bukan? Saya Charlotte, dari Harian Arcadia Chronicle. Bolehkah saya meminta waktu Anda sebentar untuk beberapa pertanyaan?\"", 30);
    delayPrint(L"Weiss: \"Charlotte dari Arcadia Chronicle? Tentu. Ada apa yang bisa saya bantu, Nona Charlotte?\"", 30);
    delayPrint(L"Charlotte: \"Kami mendengar Anda akhir-akhir ini cukup aktif terlibat dalam beberapa inisiatif kota. Apa yang mendorong seorang bangsawan muda seperti Anda untuk turun langsung ke masyarakat? Apakah ini terkait dengan posisi keluarga Astra?\"", 30);
    delayPrint(L"Weiss: \"Saya percaya bahwa setiap warga, termasuk bangsawan, memiliki tanggung jawab untuk berkontribusi pada kemajuan kotanya. Ini bukan hanya tentang nama keluarga, tapi tentang keinginan tulus untuk melihat Arcadia menjadi tempat yang lebih baik.\"", 30);
    delayPrint(L"Charlotte: (Mencatat dengan cepat) \"Keinginan tulus, ya? Menarik. Apa ada program spesifik yang sedang Anda fokuskan saat ini, Tuan Muda? Mungkin terkait perbaikan fasilitas umum atau dukungan untuk pengrajin lokal yang sempat Anda kunjungi?\"", 30);
    delayPrint(L"Weiss: \"Beberapa hal sedang dalam tahap diskusi dan perencanaan. Saya lebih suka berbicara tentang hasil nyata daripada janji-janji. Tapi, ya, dukungan untuk ekonomi lokal adalah salah satu perhatian saya.\"", 30);
    delayPrint(L"Charlotte: \"Saya mengerti. Pendekatan yang hati-hati. Terima kasih atas waktu Anda, Tuan Muda. Mungkin saya akan menghubungi Anda lagi jika ada perkembangan menarik terkait inisiatif Anda.\"", 30);
    delayPrint(L"Weiss: \"Silakan, Nona Charlotte. Semoga hari Anda lancar.\"", 30);
    delayPrint(L"Charlotte: \"Anda juga, Tuan Muda.\" (Ia tersenyum sekilas, lalu bergegas pergi, mungkin mengejar berita lain di sekitar Balai Kota).", 30);
    delayPrint(L"Kamu merasakan tatapan matanya yang tajam dan analitis. Charlotte tampak seperti wartawan yang gigih dan tidak mudah percaya pada kata-kata manis.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel2() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 2 ✦ Lobi Balai Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Sedang menunggu giliran untuk bertemu salah satu anggota dewan, melihat Charlotte sedang berbicara dengan seorang staf administrasi di meja resepsionis Balai Kota) \"Nona Charlotte? Bertemu lagi kita.\"", 30);
    delayPrint(L"Charlotte: (Menoleh, sedikit terkejut) \"Oh, Tuan Muda Astra. Selamat siang. Sepertinya Balai Kota ini jadi tempat pertemuan kita yang baru ya?\" (Tersenyum tipis) \"Anda sendiri, ada urusan penting dengan dewan?\"", 30);
    delayPrint(L"Weiss: \"Hanya beberapa diskusi rutin terkait program pengembangan kota. Anda sendiri, sepertinya sedang mengejar berita lagi? Apakah ada perkembangan dari insiden di dermaga yang Anda sebutkan tempo hari?\"", 30);
    delayPrint(L"Charlotte: \"Tepat sekali, Tuan Muda. Saya sedang mencoba mendapatkan akses ke beberapa laporan publik terkait keamanan dermaga dari staf di sini. Guild Master Ella sangat rapat menutup mulutnya, jadi saya coba jalur resmi. Sayangnya, birokrasi di sini terkadang lebih alot dari daging panggang gosong.\"", 30);
    delayPrint(L"Weiss: \"Saya bisa membayangkan. Kesabaran ekstra memang dibutuhkan di sini. Apakah Anda punya metode khusus untuk mendapatkan informasi yang akurat di tengah semua formalitas ini?\"", 30);
    delayPrint(L"Charlotte: \"Kegigihan, Tuan Muda. Dan kemampuan membangun jaringan. Bahkan staf administrasi tingkat rendah pun terkadang punya informasi berharga jika didekati dengan cara yang tepat. Selain itu, insting seorang jurnalis tidak boleh diremehkan. Terkadang, apa yang mereka coba sembunyikan justru menjadi petunjuk terbesar.\"", 30);
    delayPrint(L"Weiss: \"Sebuah keahlian yang mengesankan dan butuh dedikasi. Saya jadi bertanya-tanya, apa yang membuat Anda memilih profesi yang penuh tantangan dan terkadang membuat frustrasi ini, Nona Charlotte? Pasti ada dorongan yang kuat.\"", 30);
    delayPrint(L"Charlotte: (Menatap sekeliling lobi Balai Kota yang sibuk sejenak) \"Saya percaya pada kekuatan informasi, Tuan Muda. Pada hak publik untuk tahu apa yang sebenarnya terjadi di kota mereka. Dan... mungkin ada sedikit jiwa idealis dalam diri saya yang tidak suka melihat ketidakadilan atau kebenaran ditutup-tutupi hanya karena kepentingan segelintir orang.\"", 30);
    delayPrint(L"Weiss: \"Sebuah motivasi yang sangat mulia. Saya menghargainya. Semoga Anda berhasil mendapatkan laporan yang Anda butuhkan hari ini.\"", 30);
    delayPrint(L"Charlotte: \"Terima kasih, Tuan Muda. Kegigihan biasanya membuahkan hasil. Oh, sepertinya giliran Anda sudah dipanggil. Sampai jumpa lagi.\"", 30);
    delayPrint(L"Weiss: \"Sampai jumpa, Nona Charlotte.\"", 30);
    delayPrint(L"Dia kembali fokus pada usahanya, buku catatannya siap di tangan. Kamu mulai melihat sisi lain dari Charlotte, di balik profesionalismenya ada idealisme yang kuat dan semangat yang tak mudah padam.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel3() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 3 ✦ Ruang Tunggu Kantor Urusan Perizinan, Balai Kota ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Melihat Charlotte sedang duduk dengan ekspresi sedikit kesal di ruang tunggu, tampaknya menunggu sesuatu) \"Nona Charlotte, sepertinya Anda sedang kurang beruntung hari ini? Antrean panjang atau birokrasi yang berbelit?\"", 30);
    delayPrint(L"Charlotte: (Menoleh, sedikit terkejut lalu menghela napas) \"Tuan Muda Astra. Kombinasi keduanya, sepertinya. Saya sedang mencoba mendapatkan izin liputan untuk acara peletakan batu pertama pasar baru, tapi formulirnya entah di mana dan petugasnya sedang istirahat makan siang yang 'diperpanjang'. Sementara itu, saya mendengar keluhan dari beberapa pedagang yang izin usahanya dipersulit tanpa alasan jelas.\"", 30);
    delayPrint(L"Weiss: \"Itu berita yang kurang menyenangkan. Saya juga mendengar beberapa keluhan serupa dari penyewa properti keluarga Astra di distrik pasar lama. Apakah Anda sudah mendapatkan petunjuk mengapa izin mereka dipersulit?\"", 30);
    delayPrint(L"Charlotte: \"Masih simpang siur, Tuan Muda. Ada yang bilang karena 'peraturan baru' yang tidak jelas, ada yang curiga ini ada hubungannya dengan rencana relokasi paksa. Saya sedang mencoba mengumpulkan kesaksian. Ini bukan sekadar masalah izin, tapi menyangkut hajat hidup banyak orang kecil.\"", 30);
    delayPrint(L"Weiss: \"Hmm, jika ini menyangkut nasib para pedagang kecil, ini juga menjadi perhatian saya. Begini, Nona Charlotte, saya kebetulan beberapa hari lalu tidak sengaja mendengar percakapan antara dua staf Balai Kota di koridor. Mereka menyebut-nyebut tentang 'kontribusi khusus' untuk memperlancar izin di area pasar. Mungkin tidak ada hubungannya, tapi siapa tahu bisa jadi petunjuk awal untuk Anda?\"", 30);
    delayPrint(L"Charlotte: (Mengangkat sebelah alisnya, matanya menatap Weiss dengan tajam) \"'Kontribusi khusus'? Itu istilah yang sangat... diplomatis untuk pungli, Tuan Muda. Di koridor mana Anda mendengarnya? Dan siapa staf yang terlibat, jika Anda sempat melihatnya?\"", 30);
    delayPrint(L"Weiss: \"Saya tidak begitu jelas siapa, hanya siluet dari kejauhan. Tapi itu di dekat sayap barat, dekat kantor perencanaan tata kota. Saya hanya menyampaikan apa yang saya dengar, semoga bisa berguna.\"", 30);
    delayPrint(L"Charlotte: (Setelah terdiam sejenak, senyum tipis namun penuh arti muncul di bibirnya) \"Anda... benar-benar berbeda dari yang saya bayangkan, Tuan Muda Astra. Seorang bangsawan yang mau berbagi 'gosip koridor'? Terima kasih atas informasinya. Ini bisa jadi benang merah yang saya cari. Saya akan mencoba menyelidikinya dengan hati-hati.\"", 30);
    delayPrint(L"Weiss: \"Saya percaya pada transparansi, Nona Charlotte. Dan saya yakin Harian Arcadia Chronicle bisa membawa masalah ini ke perhatian publik yang lebih luas. Jika ada perkembangan, atau jika Anda butuh 'saksi' yang kebetulan mendengar sesuatu, Anda tahu di mana mencari saya.\"", 30);
    delayPrint(L"Charlotte: \"Akan saya ingat itu, Tuan Muda. Anda mungkin akan terkejut betapa seringnya saya akan 'mengingat' tawaran itu.\" (Mengedipkan mata sekilas sebelum kembali memasang wajah serius menunggu petugas).", 30);
    delayPrint(L"Weiss: \"Saya menantikannya, Nona Charlotte. Semoga urusan izin Anda segera beres.\"", 30);
    delayPrint(L"Charlotte: \"Harapan yang sama untuk Anda, Tuan Muda.\"", 30);
    delayPrint(L"Sepertinya tindakanmu memberikan 'tip' kecil ini mulai membangun jembatan kepercayaan antara dirimu dan wartawan yang gigih ini. Dia mulai melihatmu sebagai potensi sumber, bukan hanya subjek berita.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel4() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 4 ✦ Ruang Pers Balai Kota Arcadia (Kosong) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Selesai rapat dan berjalan melewati Ruang Pers Balai Kota yang biasanya ramai, namun kini kosong kecuali satu sosok, Charlotte, yang sedang membentur-benturkan kepalanya pelan ke meja dengan frustrasi, dikelilingi kertas-kertas.)", 30);
    delayPrint(L"Weiss: \"Nona Charlotte? Apakah Anda baik-baik saja? Meja itu sepertinya tidak bersalah.\"", 30);
    delayPrint(L"Charlotte: (Mendongak kaget, wajahnya kusut dan ada lingkaran hitam di bawah matanya) \"Tuan Muda Astra! Maaf, saya tidak menyadari ada orang. Saya hanya... sedang mencapai batas kesabaran saya dengan artikel ini. Rasanya semua jalan buntu!\"", 30);
    delayPrint(L"Weiss: \"Artikel tentang 'kontribusi khusus' yang kita bicarakan tempo hari? Apakah ada masalah dengan penyelidikan Anda?\"", 30);
    delayPrint(L"Charlotte: \"Masalah besar! Saya berhasil menemukan beberapa korban yang mau bicara, tapi secara anonim. Saya juga melacak aliran dana ke salah satu pejabat rendahan di kantor perencanaan. Tapi atasannya... dia seperti belut! Selalu berhasil berkelit dan punya alibi kuat. Dan sekarang, sumber internal saya tiba-tiba bungkam, sepertinya dia ketakutan.\"", 30);
    delayPrint(L"Weiss: \"Saya bisa membayangkan betapa membuat frustrasinya. Birokrasi dan orang-orang yang saling melindungi memang tembok yang sulit ditembus. Apakah tidak ada celah sama sekali?\"", 30);
    delayPrint(L"Charlotte: (Menghela napas panjang) \"Saya sudah mencoba semua sudut, Tuan Muda. Rasanya seperti melawan naga berkepala tujuh sendirian dengan tusuk gigi. Tapi jika saya menyerah sekarang, mereka akan menang. Para pedagang kecil itu akan terus diperas. Saya tidak bisa membiarkannya.\"", 30);
    delayPrint(L"Weiss: \"Semangat Anda itu yang luar biasa, Nona Charlotte. Jangan biarkan frustrasi memadamkannya. Mungkin... Anda butuh perspektif baru? Atau mungkin ada detail kecil yang terlewat? Terkadang saat kita terlalu fokus, kita justru melewatkan hal yang jelas.\"", 30);
    delayPrint(L"Charlotte: \"Perspektif baru?\" (Menatap Weiss dengan penuh pertimbangan) \"Anda benar. Saya mungkin terlalu terpaku pada satu alur. Tuan Muda, Anda punya akses ke lingkaran sosial yang berbeda dari saya. Pernahkah Anda mendengar desas-desus atau keluhan tentang pejabat tertentu di kantor perencanaan itu dari kolega bangsawan Anda? Sesuatu yang mungkin tampak tidak relevan tapi bisa jadi petunjuk?\"", 30);
    delayPrint(L"Weiss: \"Saya akan coba mengingat-ingat dan bertanya secara tidak langsung kepada beberapa kontak saya. Tidak janji, tapi akan saya usahakan. Sementara itu, jangan terlalu memaksakan diri. Istirahatlah sejenak, mungkin ide baru akan muncul.\"", 30);
    delayPrint(L"Charlotte: (Senyum lelah namun penuh rasa terima kasih muncul di wajahnya) \"Terima kasih, Tuan Muda. Atas perhatian dan tawaran bantuannya. Anda benar-benar... berbeda. Mungkin secangkir teh panas dan tidur sebentar bisa membantu. Besok saya akan coba lagi dengan semangat baru.\"", 30);
    delayPrint(L"Weiss: \"Itu rencana yang bagus. Jika ada yang bisa saya bantu lebih lanjut, Anda tahu di mana mencari saya. Jangan menyerah, Charlotte.\"", 30);
    delayPrint(L"Charlotte: \"Tidak akan, Tuan Muda. Terima kasih.\" (Dia mulai merapikan kertas-kertasnya dengan energi baru).", 30);
    delayPrint(L"Kamu melihat semangat juang yang tak kenal lelah dalam diri Charlotte. Dia mungkin terlihat sinis di permukaan, tapi hatinya ada di tempat yang benar, dan dia mulai melihatmu sebagai seseorang yang bisa diajak bicara, bahkan mungkin dipercaya.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel5() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 5 ✦ Arsip Balai Kota Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Sedang meneliti beberapa dokumen lama keluarga Astra di ruang arsip Balai Kota, menemukan Charlotte juga di sana, terbenam di antara tumpukan gulungan peta dan buku besar berdebu).", 30);
    delayPrint(L"Weiss: \"Nona Charlotte, sepertinya kita punya tujuan yang sama hari ini: menggali masa lalu. Sedang mencari harta karun terpendam di antara dokumen-dokumen ini?\"", 30);
    delayPrint(L"Charlotte: (Mendongak, wajahnya sedikit berdebu tapi matanya berbinar) \"Tuan Muda Astra! Bisa dibilang begitu. Saya sedang mencoba melacak sejarah kepemilikan beberapa properti di distrik pasar yang terkait dengan kasus pungli itu. Saya curiga ada pola pengambilalihan lahan secara tidak wajar sejak beberapa dekade lalu.\"", 30);
    delayPrint(L"Weiss: \"Penyelidikan yang sangat mendalam. Apakah Anda menemukan sesuatu yang signifikan? Saya sendiri juga sedang menelusuri beberapa transaksi properti keluarga saya dari era yang sama, mencari anomali.\"", 30);
    delayPrint(L"Charlotte: \"Saya menemukan beberapa transaksi jual beli paksa dengan harga sangat rendah yang melibatkan perusahaan bernama 'Arcadia Land Development', yang ternyata adalah perusahaan cangkang milik beberapa pejabat kota saat itu. Sangat mencurigakan. Bagaimana dengan Anda, Tuan Muda?\"", 30);
    delayPrint(L"Weiss: \"Saya menemukan beberapa catatan harian kakek saya yang menyebutkan 'tekanan halus' dari beberapa 'rekan berpengaruh' untuk menjual beberapa properti komersial di area tersebut dengan harga di bawah pasar. Beliau menolaknya, tapi sepertinya tidak semua orang seberuntung itu. Mungkin kita bisa mencocokkan temuan kita?\"", 30);
    delayPrint(L"Charlotte: (Matanya membelalak) \"Catatan harian kakek Anda? Itu bisa jadi bukti yang sangat kuat, Tuan Muda! Jika Anda bersedia membagikannya, tentu saja dengan kerahasiaan penuh, saya bisa mencocokkannya dengan daftar transaksi yang saya temukan. Ini bisa jadi 'bom' untuk artikel saya!\"", 30);
    delayPrint(L"Weiss: \"Saya tidak keberatan membagikan bagian yang relevan, Charlotte. Tujuan kita sama, bukan? Mengungkap kebenaran dan membawa keadilan. Sebagai gantinya, mungkin Anda bisa memberitahu saya jika nama 'Arcadia Land Development' itu muncul lagi dalam penyelidikan Anda yang lain?\"", 30);
    delayPrint(L"Charlotte: (Mengangguk cepat) \"Tentu saja! Ini pertukaran informasi yang sangat adil! Saya akan siapkan salinan temuan saya untuk Anda. Ini... ini adalah kemajuan besar! Terima kasih, Tuan Muda. Anda benar-benar sekutu yang tak ternilai.\"", 30);
    delayPrint(L"Weiss: \"Kita adalah tim dalam hal ini, Charlotte. Mari kita lihat kemana petunjuk ini membawa kita. Kapan Anda ada waktu untuk membahas ini lebih detail?\"", 30);
    delayPrint(L"Charlotte: \"Bagaimana kalau besok pagi, sebelum Balai Kota terlalu ramai? Kita bisa bertemu di taman belakang Balai Kota, lebih privat. Saya akan bawa semua yang saya punya.\"", 30);
    delayPrint(L"Weiss: \"Sepakat. Sampai besok, Charlotte. Dan hati-hati dengan debu arsip ini.\" (Tersenyum)", 30);
    delayPrint(L"Charlotte: \"Anda juga, Tuan Muda. Semoga kita menemukan 'emas' di antara tumpukan kertas tua ini.\"", 30);
    delayPrint(L"Hubungan kalian mulai bergeser menjadi kemitraan investigatif yang didasari rasa saling percaya dan tujuan bersama. Masing-masing membawa aset unik ke meja perundingan.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel6() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 6 ✦ Taman Belakang Balai Kota (Sore Hari) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Menunggu Charlotte di taman belakang Balai Kota yang sepi. Charlotte datang dengan langkah cepat, membawa tas penuh dokumen).", 30);
    delayPrint(L"Charlotte: \"Maaf membuat Anda menunggu, Weiss.\" (Dia mulai memanggilmu Weiss secara informal saat tidak ada orang lain) \"Saya terjebak wawancara dadakan dengan salah satu anggota dewan yang tiba-tiba ingin 'klarifikasi' soal artikel saya minggu lalu.\"", 30);
    delayPrint(L"Weiss: \"Tidak masalah, Charlotte. Saya mengerti kesibukan Anda. Apakah ada tekanan lebih lanjut setelah artikel tentang 'Arcadia Land Development' mulai beredar samar-samar?\"", 30);
    delayPrint(L"Charlotte: \"Ada beberapa 'peringatan halus' dari pihak-pihak yang tidak ingin namanya disebut. Tapi itu sudah biasa. Yang lebih penting, berkat catatan harian kakek Anda dan data transaksi yang kita gabungkan, saya hampir menyelesaikan draf artikel yang jauh lebih kuat. Ini bisa mengungkap jaringan korupsi lahan yang sudah berlangsung puluhan tahun!\"", 30);
    delayPrint(L"Weiss: \"Luar biasa! Tapi apakah kita sudah punya cukup bukti untuk menghadapi serangan balik mereka? Orang-orang ini pasti punya banyak cara untuk membela diri atau bahkan menyerang balik kredibilitas Anda.\"", 30);
    delayPrint(L"Charlotte: \"Itulah kekhawatiran saya. Saya punya banyak bukti tidak langsung dan beberapa kesaksian kunci, tapi mereka bisa saja menyangkal atau memutarbalikkan fakta. Idealnya, kita butuh pengakuan dari seseorang di dalam lingkaran mereka, atau bukti transaksi keuangan yang tak terbantahkan.\"", 30);
    delayPrint(L"Weiss: \"Pengakuan internal itu sulit. Tapi bagaimana dengan transaksi keuangan? Saya punya beberapa kontak di sektor perbankan yang mungkin bisa membantu melacak aliran dana mencurigakan jika kita punya nama perusahaan atau individu target yang lebih spesifik. Tentu saja, ini harus dilakukan dengan sangat rahasia.\"", 30);
    delayPrint(L"Charlotte: (Matanya berbinar) \"Anda serius, Weiss? Itu... itu bisa menjadi terobosan besar! Saya punya beberapa nama direksi 'Arcadia Land Development' dan perusahaan afiliasinya yang aliran dananya sangat janggal. Jika kita bisa membuktikan uang hasil penjualan paksa lahan itu mengalir ke kantong pribadi mereka... permainan selesai.\"", 30);
    delayPrint(L"Weiss: \"Berikan saya nama-namanya. Saya akan coba jalur saya. Tapi ini akan butuh waktu dan sangat berisiko. Anda juga harus sangat berhati-hati. Jangan mengambil langkah gegabah sebelum kita punya semua amunisi.\"", 30);
    delayPrint(L"Charlotte: \"Saya mengerti. Saya akan fokus menyusun narasi dan mengumpulkan kesaksian pendukung selagi Anda bekerja dari sisi itu. Kita seperti dua detektif yang bekerja dalam kasus besar, ya?\" (Tersenyum, ada semangat petualangan di matanya)", 30);
    delayPrint(L"Weiss: \"Anggap saja begitu. Dan semoga 'penjahatnya' segera tertangkap. Jaga diri Anda baik-baik, Charlotte. Kabari saya jika ada perkembangan atau jika Anda butuh bantuan.\"", 30);
    delayPrint(L"Charlotte: \"Pasti, Weiss. Anda juga. Terima kasih sudah mau sejauh ini. Saya tidak tahu apa jadinya tanpa bantuan Anda.\"", 30);
    delayPrint(L"Weiss: \"Kita lakukan ini bersama. Demi Arcadia.\"", 30);
    delayPrint(L"Kalian berdua kini terlibat lebih dalam dalam sebuah investigasi yang berisiko. Rasa saling percaya dan ketergantungan satu sama lain semakin menguat. Ini bukan lagi hanya tentang berita, tapi tentang keadilan.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel7() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 7 ✦ Ruang Rapat Kecil Tak Terpakai, Balai Kota ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Charlotte: (Mengajak Weiss bertemu di sebuah ruang rapat kecil yang jarang digunakan di Balai Kota, suasananya tegang) \"Weiss, terima kasih sudah datang secepat ini. Saya punya kabar... baik dan buruk.\"", 30);
    delayPrint(L"Weiss: \"Ada apa, Charlotte? kamu terlihat sangat cemas. Apakah ada masalah dengan penyelidikan kita?\"", 30);
    delayPrint(L"Charlotte: \"Kabar baiknya, salah satu kontak perbankan Anda berhasil! Dia menemukan bukti transfer dana dalam jumlah besar dari rekening 'Arcadia Land Development' ke rekening pribadi di luar negeri milik salah satu pejabat tinggi kota yang namanya sering kita diskusikan! Ini 'senjata berasap' yang kita butuhkan!\"", 30);
    delayPrint(L"Weiss: \"Itu luar biasa, Charlotte! Ini bisa menjatuhkan mereka semua! Lalu... apa kabar buruknya?\"", 30);
    delayPrint(L"Charlotte: (Menghela napas berat) \"Kabar buruknya... sepertinya mereka tahu kita sudah terlalu dekat. Sumber saya yang memberikan data awal tentang 'Arcadia Land Development' tiba-tiba menghilang. Rumahnya kosong, dan tidak ada yang tahu dia ke mana. Saya khawatir mereka sudah mencapainya.\"", 30);
    delayPrint(L"Weiss: \"Ini gawat. Keselamatan sumber adalah prioritas. Apakah Anda sudah mencoba menghubunginya melalui jalur lain?\"", 30);
    delayPrint(L"Charlotte: \"Sudah, tapi tidak ada jawaban. Dan pagi ini, saya menerima 'kunjungan' dari dua orang berbadan tegap yang 'menyarankan' saya untuk berhenti mengorek-ngorek urusan tertentu jika tidak ingin 'celaka'. Ancaman yang cukup jelas.\"", 30);
    delayPrint(L"Weiss: (Rahangnya mengeras) \"Mereka sudah mulai bermain kotor. Ini tidak bisa dibiarkan. Charlotte, keselamatanmu juga terancam. Mungkin sudah saatnya kita menyerahkan semua bukti ini ke Tuan Albright, ketua komite investigasi yang kita percayai? Dengan bukti transfer ini, dia tidak bisa lagi mengabaikannya.\"", 30);
    delayPrint(L"Charlotte: \"Saya setuju. Tapi kita harus melakukannya dengan sangat hati-hati. Kita tidak tahu siapa lagi yang terlibat di dalam Balai Kota. Bagaimana jika Tuan Albright juga ditekan atau bahkan... bagian dari mereka?\"", 30);
    delayPrint(L"Weiss: \"Itu risiko yang harus kita ambil, tapi kita bisa meminimalisirnya. Saya akan meminta pertemuan pribadi dengannya di tempat netral, mungkin di kediaman saya. Saya akan membawa beberapa pengawal terpercaya. Anda bisa ikut jika merasa aman, atau serahkan buktinya pada saya. Yang penting, bukti ini sampai ke tangannya tanpa bisa dicegat.\"", 30);
    delayPrint(L"Charlotte: \"Tidak, Weiss. Saya akan ikut. Saya yang memulai ini, saya harus melihatnya sampai akhir. Kita akan hadapi ini bersama. Saya sudah menyiapkan salinan digital semua bukti, terenkripsi. Kita akan berikan itu padanya. Kapan Anda bisa mengatur pertemuan?\"", 30);
    delayPrint(L"Weiss: \"Secepatnya. Mungkin besok pagi. Saya akan menghubunginya sekarang juga. Charlotte... tetaplah waspada. Jangan sendirian malam ini. Jika perlu, menginaplah di salah satu properti keluarga Astra yang aman.\"", 30);
    delayPrint(L"Charlotte: (Menatap Weiss dengan campuran rasa takut dan terima kasih) \"Terima kasih atas perhatianmu, Weiss. Saya akan baik-baik saja. Saya lebih khawatir tentang Anda. Anda yang akan berhadapan langsung dengan Albright.\"", 30);
    delayPrint(L"Weiss: \"Kita berdua sama-sama dalam bahaya. Tapi bersama, kita lebih kuat. Percayalah.\"", 30);
    delayPrint(L"Situasi semakin genting dan berbahaya. Namun, di tengah ancaman, ikatan kalian sebagai rekan seperjuangan semakin erat, ditempa oleh tujuan bersama untuk mengungkap kebenaran.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel8() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 8 ✦ Kantor Sementara Weiss di Balai Kota ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Beberapa hari setelah pertemuan dengan Tuan Albright, Weiss menggunakan pengaruhnya untuk mendapatkan ruang kerja sementara di Balai Kota untuk memantau perkembangan kasus. Charlotte datang mengunjunginya.", 30);
    delayPrint(L"Charlotte: \"Ruangan yang cukup strategis, Weiss. Dekat dengan pusat informasi dan jauh dari telinga-telinga yang tidak diinginkan.\" (Melirik ke luar jendela yang menghadap taman Balai Kota)", 30);
    delayPrint(L"Weiss: \"Sengaja kupilih. Bagaimana perkembangan dari sisi Anda? Apakah ada tekanan lebih lanjut setelah kita menyerahkan bukti kepada Tuan Albright?\"", 30);
    delayPrint(L"Charlotte: \"Tekanan itu selalu ada, seperti udara yang kita hirup di kota ini.\" (Tersenyum masam) \"Tapi sepertinya Tuan Albright benar-benar bergerak. Saya dengar beberapa aset 'Golden Serpent' mulai dibekukan, dan beberapa pejabat yang namanya ada di daftar kita dipanggil untuk 'wawancara mendalam'. Artikel lanjutan saya yang lebih berani juga mendapat respons besar dari publik. Banyak yang mulai menuntut transparansi.\"", 30);
    delayPrint(L"Weiss: \"Itu kabar yang sangat baik. Artinya kita berada di jalur yang benar. Tapi kita belum menang. Mereka pasti tidak akan menyerah begitu saja. Apakah sumber Anda yang hilang sudah ada kabar?\"", 30);
    delayPrint(L"Charlotte: (Ekspresinya berubah sedih) \"Belum, Weiss. Saya sudah mencoba semua cara. Saya khawatir yang terburuk sudah terjadi padanya. Ini... ini adalah pengingat betapa berbahayanya pekerjaan yang kita lakukan. Terkadang saya bertanya-tanya, apakah semua ini sepadan dengan risikonya?\"", 30);
    delayPrint(L"Weiss: (Meletakkan tangannya di bahu Charlotte dengan lembut) \"Saya mengerti perasaanmu, Charlotte. Kehilangan sumber, apalagi karena dia mencoba membantu kita, adalah pukulan berat. Tapi perjuangannya tidak akan sia-sia jika kita berhasil mengungkap kebenaran ini sampai tuntas. Keadilan untuknya, dan untuk semua korban mereka, itu yang harus jadi tujuan kita.\"", 30);
    delayPrint(L"Charlotte: (Menghela napas, lalu menatap Weiss dengan tekad baru) \"Anda benar. Kita tidak boleh membiarkan pengorbanannya sia-sia. Kita harus lebih pintar dan lebih kuat dari mereka. Ngomong-ngomong, Weiss, saya ingin mengatakan sesuatu yang mungkin terdengar aneh.\"", 30);
    delayPrint(L"Weiss: \"Apa itu?\"", 30);
    delayPrint(L"Charlotte: \"Selama ini, saya selalu memandang bangsawan sebagai kelompok elite yang terpisah dari kenyataan, yang hanya peduli pada kekuasaan dan harta. Tapi Anda... Anda telah mengubah pandangan saya sepenuhnya. Anda rela mempertaruhkan nama baik keluarga, bahkan keselamatan Anda sendiri, demi sesuatu yang Anda yakini benar, demi orang-orang yang bahkan tidak Anda kenal secara pribadi. Itu... itu adalah sesuatu yang sangat langka dan berharga.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya melakukan apa yang seharusnya dilakukan, Charlotte. Mungkin saya memang berasal dari dunia yang berbeda, tapi hati nurani kita berbicara bahasa yang sama, bukan? Dan Anda, dengan keberanian dan kegigihan Anda, telah mengajari saya banyak hal tentang arti perjuangan yang sesungguhnya.\"", 30);
    delayPrint(L"Charlotte: (Tersenyum tulus) \"Kita saling belajar, sepertinya. Dan itu membuat tim kita semakin kuat. Terima kasih, Weiss. Karena telah menjadi lebih dari sekadar 'Tuan Muda Astra' bagi saya.\"", 30);
    delayPrint(L"Weiss: \"Dan terima kasih telah menjadi lebih dari sekadar 'wartawan pencari berita', Charlotte. kamu adalah sahabat.\"", 30);
    delayPrint(L"Di tengah ketegangan penyelidikan, sebuah pengakuan tulus mempererat hubungan kalian. Kalian bukan lagi sekadar mitra, tapi dua sahabat yang saling menguatkan dalam menghadapi badai.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel9() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 9 ✦ Diskusi di Balai Kota & Transisi ke Gudang ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss dan Charlotte bertemu di ruang kerja sementara Weiss di Balai Kota, wajah mereka tegang namun penuh antisipasi.", 30);
    delayPrint(L"Charlotte: \"Informasi dari kontak perbankanmu sangat akurat, Weiss! Saya berhasil melacak bahwa akan ada serah terima 'pembayaran terakhir' untuk membungkam saksi kunci di gudang tua dermaga malam ini. Ini kesempatan kita untuk menangkap basah mereka dengan bukti yang tak terbantahkan!\"", 30);
    delayPrint(L"Weiss: \"Gudang yang sama dengan yang pernah kuberitahukan padamu dulu? Mereka benar-benar ceroboh atau terlalu percaya diri. Ini kesempatan emas, tapi juga sangat berbahaya. Kita tidak tahu berapa banyak orang yang akan ada di sana.\"", 30);
    delayPrint(L"Charlotte: \"Saya tahu risikonya. Tapi jika kita berhasil mendapatkan rekaman transaksi itu, ditambah dengan semua bukti yang sudah kita kumpulkan, Tuan Albright tidak akan bisa lagi menunda penangkapan besar-besaran. Ini bisa jadi akhir dari jaringan 'Golden Serpent'. Apakah Anda siap untuk ini, Weiss?\"", 30);
    delayPrint(L"Weiss: \"Aku siap jika kamu siap, Charlotte. Tapi kita harus punya rencana yang matang. Aku akan membawa beberapa orang kepercayaanku untuk berjaga di sekitar area, tapi kita tidak boleh melibatkan mereka secara langsung kecuali darurat. Fokus kita adalah mendapatkan bukti tanpa memicu konfrontasi besar.\"", 30);
    delayPrint(L"Charlotte: \"Saya setuju. Saya sudah menyiapkan kamera tersembunyi dan perekam suara. Tugas saya adalah dokumentasi. Tugas Anda... memastikan kita bisa keluar dari sana dengan selamat jika keadaan memburuk. Bisakah saya mempercayakan itu padamu?\"", 30);
    delayPrint(L"Weiss: (Menggenggam tangan Charlotte dengan mantap) \"kamu bisa mempercayakan nyawamu padaku, Charlotte. Kita akan melalui ini bersama. Setelah semua ini selesai, kita akan merayakannya dengan berita utama terbesar yang pernah ada di Arcadia Chronicle.\"", 30);
    delayPrint(L"Charlotte: (Tersenyum, ada keyakinan di matanya) \"Saya menantikannya. Mari kita persiapkan semuanya. Malam ini, kita akan menulis sejarah.\"", 30);
    delayPrint(L"--- TRANSISI KE MALAM HARI DI GUDANG DERMAGA ---", 50);
    delayPrint(L"Weiss dan Charlotte bersembunyi dalam kegelapan, mengamati aktivitas mencurigakan di gudang tua. Mereka berhasil mendapatkan informasi bahwa akan ada transaksi besar malam ini.", 30);
    delayPrint(L"Charlotte: (Berbisik, sambil mengarahkan kamera kecilnya) \"Itu dia target kita. Pria berjas abu-abu yang baru datang dengan koper itu... dia adalah tangan kanan dari salah satu direktur 'Golden Serpent'. Dan orang-orang yang menyambutnya... mereka adalah anggota geng penyelundup yang terkenal sadis.\"", 30);
    delayPrint(L"Weiss: (Mengamati dengan seksama) \"Transaksi serah terima barang bukti, sepertinya. Koper itu kemungkinan berisi uang suap atau dokumen penting. Kita harus mendapatkan bukti visual yang jelas tanpa ketahuan. Apakah kamera Anda bisa menangkap gambar dalam kondisi minim cahaya seperti ini?\"", 30);
    delayPrint(L"Charlotte: \"Ini kamera khusus untuk investigasi malam hari, Weiss. Kualitasnya cukup baik. Tapi kita harus sangat berhati-hati. Satu suara saja bisa membuat mereka waspada. Apakah Anda yakin dengan rencana 'pengalihan perhatian' jika situasinya memburuk?\"", 30);
    delayPrint(L"Weiss: \"Saya sudah menyiapkan semuanya. Beberapa anak buah setia keluarga Astra ada di sekitar area ini, siap membuat keributan kecil di ujung jalan jika saya memberi sinyal. Itu akan memberi kita waktu untuk melarikan diri jika diperlukan. Fokus Anda adalah mendapatkan gambarnya, Charlotte.\"", 30);
    delayPrint(L"Charlotte: \"Saya mengerti. Jantung saya berdebar kencang sekali. Rasanya seperti di tengah-tengah cerita detektif yang saya tulis.\" (Tersenyum tegang)", 30);
    delayPrint(L"Weiss: \"Anggap saja begitu. Tapi ini nyata, dan risikonya juga nyata. Tetap fokus. Saya akan mengawasi punggung Anda.\"", 30);
    delayPrint(L"Saat transaksi mulai terjadi, Charlotte dengan cekatan mengambil beberapa foto dan rekaman video singkat. Tiba-tiba, salah satu penjaga tampak curiga dan mulai berjalan ke arah persembunyian mereka.", 30);
    delayPrint(L"Weiss: (Berbisik cepat) \"Kita ketahuan! Sinyal sekarang! Charlotte, lari ke arah selatan, temui orangku di sana! Aku akan menahan mereka sebentar!\"", 30);
    delayPrint(L"Charlotte: \"Weiss, tidak! Ini terlalu berbahaya untukmu! Kita pergi bersama!\"", 30);
    delayPrint(L"Weiss: \"Tidak ada waktu untuk berdebat! Bukti ini lebih penting! Pergi! Aku akan menyusul!\" Tanpa menunggu jawaban, Weiss keluar dari persembunyian, membuat suara untuk menarik perhatian para penjaga.", 30);
    delayPrint(L"Charlotte, meskipun ragu, akhirnya berlari sesuai instruksi Weiss, membawa bukti yang sangat berharga. Kamu berhasil mengulur waktu cukup lama hingga Charlotte aman, sebelum akhirnya kamu sendiri berhasil meloloskan diri dengan sedikit susah payah.", 30);
    delayPrint(L"--- KEMBALI KE BALAI KOTA (KANTOR WEISS, DINI HARI) ---", 50);
    delayPrint(L"Charlotte: (Masuk dengan napas terengah, langsung memeluk Weiss dengan erat, suaranya bergetar) \"Weiss! Syukurlah kamu baik-baik saja! Aku sangat khawatir! Jangan pernah melakukan hal senekat itu lagi! Itu tadi... itu tadi gila!\"", 30);
    delayPrint(L"Weiss: (Membalas pelukannya, berusaha menenangkan) \"Aku baik-baik saja, Charlotte. Hanya sedikit lecet. Yang penting, apakah kamu berhasil mendapatkan buktinya? Apakah semuanya aman?\"", 30);
    delayPrint(L"Charlotte: (Mengangguk, air mata haru dan lega mengalir) \"Ya. Semuanya terekam jelas. Ini... ini akan menjatuhkan mereka semua. Ini adalah akhir dari 'Golden Serpent'. Berkat keberanianmu, Weiss. Berkat pengorbananmu.\"", 30);
    delayPrint(L"Weiss: \"Keberanian kita berdua, Charlotte. Kita adalah tim. Dan kita berhasil. Sekarang, serahkan ini pada Tuan Albright. Biarkan hukum yang bekerja.\"", 30);
    delayPrint(L"Charlotte: \"Pagi ini juga. Dan setelah itu... mungkin kita benar-benar bisa merayakannya. Dengan tidur, mungkin?\"", 30);
    delayPrint(L"Weiss: (Tertawa lelah) \"Tidur terdengar seperti hadiah terbaik saat ini.\"", 30);
    delayPrint(L"Malam itu, di tengah bahaya, ikatan kalian sebagai rekan seperjuangan menjadi tak terpatahkan. Kalian telah mempertaruhkan nyawa bersama demi kebenaran, dan berhasil.", 30);

    printLine();
    waitForEnter();
}

void sceneCharlotteLevel10() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Charlotte - Wartawan ✦ Level 10 ✦ Depan Balai Kota Arcadia (Setelah Konferensi Pers) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Beberapa minggu setelah penyerahan bukti, Tuan Albright mengadakan konferensi pers besar di Balai Kota, mengumumkan penangkapan para petinggi 'Golden Serpent Trading' dan beberapa pejabat kota yang terlibat korupsi. Harian Arcadia Chronicle menjadi media utama yang meliputnya dengan detail.", 30);
    delayPrint(L"Weiss: (Menemui Charlotte yang baru saja selesai diwawancarai oleh beberapa wartawan junior) \"Liputan yang luar biasa, Charlotte. Anda menjadi bintang hari ini. Seluruh kota membicarakan keberanian Arcadia Chronicle.\"", 30);
    delayPrint(L"Charlotte: (Tersenyum lebar, wajahnya berseri meskipun masih ada sisa kelelahan) \"Weiss! Ini semua tidak akan terjadi tanpamu! Kita berhasil! Keadilan akhirnya ditegakkan! Rasanya... luar biasa! Seperti mimpi yang jadi kenyataan!\"", 30);
    delayPrint(L"Weiss: \"Ini adalah buah dari kerja keras dan kegigihanmu selama bertahun-tahun, Charlotte. Saya hanya beruntung bisa menjadi bagian kecil dari perjuanganmu di saat yang tepat. Ayahmu pasti sangat bangga melihatmu hari ini.\"", 30);
    delayPrint(L"Charlotte: (Matanya berkaca-kaca, menatap ke arah langit) \"Saya harap begitu, Weiss. Saya harap begitu. Beliau selalu mengajarkan saya untuk tidak pernah takut pada kebenaran, seberapapun sulitnya. Dan Anda... Anda mengingatkan saya pada semangat beliau itu.\"", 30);
    delayPrint(L"Charlotte: \"kamu tahu, Weiss, awalnya saya mendekati Anda karena menganggap Anda 'berita'. Seorang bangsawan muda yang mencoba mengubah citra. Tapi seiring waktu, saya melihat lebih dari itu. Saya melihat ketulusan, keberanian, dan keinginan untuk melakukan hal yang benar, bahkan ketika itu berisiko. Anda telah mengembalikan kepercayaan saya bahwa masih ada orang-orang baik dan berprinsip di dunia ini, bahkan di kalangan elite sekalipun.\"", 30);
    delayPrint(L"Weiss: \"Dan Anda, Charlotte, telah menunjukkan pada saya kekuatan sesungguhnya dari sebuah pena dan integritas jurnalistik. Anda adalah suara bagi mereka yang tak bersuara, dan penjaga kebenaran di kota ini. Saya sangat menghormati Anda.\"", 30);
    delayPrint(L"Charlotte: \"Sebagai tanda terima kasih dan persahabatan abadi kita, saya ingin memberimu ini.\" (Dia menyerahkan sebuah pena perak yang sangat elegan dengan ukiran inisial 'C & W' dan simbol gulungan perkamen serta timbangan keadilan) \"Ini adalah 'Pena Saksi Kebenaran'. Dibuat khusus. Semoga ini selalu mengingatkanmu bahwa kata-kata punya kekuatan untuk mengubah dunia, dan bahwa kebenaran, meskipun terkadang pahit, akan selalu menemukan jalannya.\"", 30);
    delayPrint(L"Weiss: (Menerima pena itu dengan haru dan rasa hormat) \"Charlotte... ini... ini adalah hadiah yang sangat indah dan penuh makna. Saya akan menyimpannya dan menggunakannya selalu. Ini akan menjadi pengingat abadi akan perjuangan kita bersama, dan persahabatan kita yang tak ternilai.\"", 30);
    delayPrint(L"Charlotte: \"Tepat sekali. Dan ketahuilah, Weiss, 'Arcadia Chronicle' dan saya pribadi akan selalu menjadi sekutumu dalam memperjuangkan transparansi, kebenaran, dan keadilan di kota ini. Kapanpun Anda butuh sesuatu untuk 'disuarakan', atau membutuhkan informasi yang 'sulit didapat' untuk tujuan yang baik, pintu saya selalu terbuka. Kita adalah partner, bukan?\"", 30);
    delayPrint(L"Weiss: \"Sebuah kehormatan yang tak ternilai, Charlotte. Dan Anda juga akan selalu mendapatkan dukunganku, baik sebagai Weiss von Astra maupun sebagai teman. Kita akan terus memastikan Arcadia menjadi tempat yang lebih baik, satu berita dan satu tindakan pada satu waktu. Bagaimana kalau kita mulai dengan mengungkap mengapa harga roti di pasar utara tiba-tiba naik?\" (Mengedipkan mata)", 30);
    delayPrint(L"Charlotte: (Tertawa lepas, semangatnya kembali menyala) \"Anda benar-benar tidak bisa diam ya, Weiss? Baiklah, partner! Itu akan jadi investigasi kita selanjutnya! Tapi setelah kita merayakan kemenangan besar ini dengan makan siang terenak di Arcadia. Saya yang traktir! Anda pantas mendapatkannya!\"", 30);
    delayPrint(L"Weiss: (Tersenyum lebar) \"Saya tidak akan menolak tawaran itu, Charlotte! Ayo!\"", 30);
    delayPrint(L"Di tengah keriuhan kota yang merayakan terungkapnya skandal besar, Weiss dan Charlotte berjalan berdampingan, bukan lagi hanya sebagai bangsawan dan wartawan, tapi sebagai dua sahabat, dua sekutu, yang telah membuktikan bahwa bersama, mereka bisa membawa perubahan. Pena dan pengaruh, ketika digabungkan dengan niat baik, memang bisa menjadi kekuatan yang luar biasa.", 30);

    waitForEnter(L" Kamu telah membentuk ikatan terkuat...... Tekan Enter untuk melihat detailnya");

    if (!socialLinks["Charlotte"].completed) { 
        applySocialLinkBonus("Charlotte"); 
        socialLinks["Charlotte"].completed = true; 
    }    

    printLine();
    waitForEnter();
}


void sceneMarsLevel1() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 1 ✦ Pos Hutan Merah ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Menghampiri Pos Hutan yang sederhana namun kokoh, seorang pria bertubuh tegap dengan seragam penjaga hutan sedang mengasah kapaknya). \"Permisi, apakah Anda Penjaga Mars? Saya Weiss von Astra.\"", 30);
    delayPrint(L"Mars: (Menghentikan pekerjaannya, menatap Weiss dengan tatapan tajam dan menilai dari atas ke bawah) \"Benar. Saya Mars. Ada keperluan apa Tuan Muda von Astra datang ke pos jaga di pinggir hutan belantara ini? Ini bukan tempat biasa untuk bangsawan berjalan-jalan.\"", 30);
    delayPrint(L"Weiss: \"Saya memiliki ketertarikan pada Hutan Merah, Penjaga Mars. Keluarga Astra juga memiliki beberapa kepentingan terkait sumber daya dan keamanan di sekitar area ini. Saya ingin memahami lebih baik kondisi hutan dan tantangan yang Anda hadapi.\"", 30);
    delayPrint(L"Mars: \"Ketertarikan, ya? Hutan ini bukan taman bermain, Tuan Muda. Isinya penuh bahaya, mulai dari binatang buas hingga medan yang sulit. Tugas kami di sini adalah memastikan batas hutan aman dan melaporkan aktivitas mencurigakan. Itu saja.\"", 30);
    delayPrint(L"Weiss: \"Saya tidak meremehkan bahayanya, Penjaga. Justru karena itu saya ingin belajar dari ahlinya. Apakah ada laporan khusus atau area tertentu yang perlu perhatian lebih saat ini?\"", 30);
    delayPrint(L"Mars: (Menyipitkan matanya sedikit) \"Hutan selalu punya rahasianya sendiri, Tuan Muda. Laporan rutin saya serahkan ke Balai Kota. Jika Anda benar-benar tertarik, Anda bisa membacanya di sana. Untuk saat ini, area sekitar Sungai Merah arusnya sedang deras pasca hujan, beberapa jalur setapak mungkin terputus.\"", 30);
    delayPrint(L"Weiss: \"Informasi yang berguna. Terima kasih. Saya tidak akan mengganggu pekerjaan Anda lebih lama. Mungkin lain kali saya bisa bertanya lebih banyak tentang flora dan fauna unik di hutan ini?\"", 30);
    delayPrint(L"Mars: \"Jika saya sedang tidak sibuk patroli, silakan saja. Tapi ingat, hutan menuntut rasa hormat. Jangan masuk terlalu dalam sendirian jika tidak punya pengalaman.\"", 30);
    delayPrint(L"Weiss: \"Akan saya ingat nasihat Anda, Penjaga Mars. Sampai jumpa.\"", 30);
    delayPrint(L"Mars: \"Hati-hati di jalan, Tuan Muda.\", (Kembali melanjutkan mengasah kapaknya).", 30);
    delayPrint(L"Mars tampak seperti pria yang tidak banyak bicara dan sangat mengutamakan tugasnya. Mendapatkan kepercayaannya sepertinya akan membutuhkan lebih dari sekadar kata-kata.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel2() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 2 ✦ Pos Hutan Merah ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Kembali ke Pos Hutan, Mars sedang memeriksa peta wilayah yang terpasang di dinding) \"Penjaga Mars, selamat siang. Apakah ini waktu yang kurang tepat?\"", 30);
    delayPrint(L"Mars: (Menoleh, ekspresinya masih datar namun sedikit kurang kaku dari pertemuan pertama) \"Tuan Muda Astra. Tidak masalah. Saya hanya sedang meninjau rute patroli untuk minggu ini. Ada yang bisa saya bantu?\"", 30);
    delayPrint(L"Weiss: \"Saya hanya ingin menindaklanjuti pembicaraan kita tempo hari. Saya sudah membaca beberapa laporan Anda di Balai Kota. Tampaknya aktivitas perburuan liar masih menjadi masalah utama di sektor utara?\"", 30);
    delayPrint(L"Mars: \"Selalu menjadi masalah, Tuan Muda. Para pemburu itu licin seperti belut dan mengenal hutan lebih baik dari kebanyakan penjaga baru. Kami sudah meningkatkan patroli, tapi Hutan Merah ini luas. Menangkap mereka bukan perkara mudah.\"", 30);
    delayPrint(L"Weiss: \"Saya bisa membayangkan frustrasinya. Apakah ada jenis hewan tertentu yang menjadi target utama mereka? Atau mereka mengambil apa saja yang berharga?\"", 30);
    delayPrint(L"Mars: \"Biasanya Rusa Ekor Perak untuk tanduk dan dagingnya, atau Beruang Cakar Besi untuk empedu dan cakarnya yang konon punya khasiat obat. Praktik yang merusak ekosistem. Kami berusaha keras melindunginya.\"", 30);
    delayPrint(L"Weiss: \"Dedikasi Anda dan tim penjaga lainnya patut diacungi jempol. Apakah ada dukungan atau peralatan tambahan yang menurut Anda bisa membantu efektivitas patroli? Mungkin keluarga saya bisa membantu mengusulkannya ke dewan kota.\"", 30);
    delayPrint(L"Mars: (Menatap Weiss sejenak, menilai) \"Peralatan komunikasi yang lebih baik antar pos jaga dan mungkin beberapa perangkap non-mematikan untuk menangkap pemburu tanpa konfrontasi besar akan sangat membantu. Tapi usulan seperti itu biasanya butuh waktu lama untuk disetujui birokrasi.\"", 30);
    delayPrint(L"Weiss: \"Saya akan coba bicarakan ini dengan beberapa kontak saya. Tidak ada salahnya mencoba mempercepat prosesnya. Keamanan hutan ini penting bagi kita semua.\"", 30);
    delayPrint(L"Mars: \"Saya hargai niat baik Anda, Tuan Muda. Setiap bantuan, sekecil apapun, akan berarti. Tapi jangan terlalu berharap banyak pada politisi di kota.\"", 30);
    delayPrint(L"Weiss: \"Saya akan tetap berusaha. Terima kasih atas informasinya, Penjaga Mars. Saya belajar banyak hari ini.\"", 30);
    delayPrint(L"Mars: \"Hutan adalah guru terbaik, Tuan Muda. Selama Anda mau mendengarkan bisikannya.\"", 30);
    delayPrint(L"Meskipun masih menjaga jarak profesional, kamu merasa Mars mulai sedikit melunak dan menghargai ketertarikanmu yang tulus.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel3() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 3 ✦ Pos Hutan Merah ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Menemukan Mars sedang membersihkan jejak lumpur dari sepatunya di depan pos) \"Baru kembali dari patroli, Penjaga Mars? Medannya pasti berat setelah hujan semalam.\"", 30);
    delayPrint(L"Mars: (Mengangguk) \"Tuan Muda Astra. Benar. Beberapa jalur tergenang, dan tanah jadi sangat licin. Tapi tidak ada laporan insiden berarti, syukurlah. Hanya menemukan beberapa jejak babi hutan yang tidak biasa besarnya di dekat Air Terjun Kembar.\"", 30);
    delayPrint(L"Weiss: \"Babi hutan sebesar apa? Apakah itu normal untuk area tersebut? Saya pernah dengar cerita tentang 'Raja Babi Hutan' dari para penebang kayu.\"", 30);
    delayPrint(L"Mars: (Sedikit tersenyum, senyum yang langka) \"Cerita penebang kayu memang sering dilebih-lebihkan, Tuan Muda. Tapi jejak ini memang lebih besar dari rata-rata. Mungkin hanya individu alfa yang sedang mencari teritori baru. Hutan ini selalu punya kejutan.\"", 30);
    delayPrint(L"Weiss: \"Kejutan yang terkadang bisa berbahaya, saya bayangkan. Selain binatang buas, apa lagi yang biasanya menjadi tantangan sehari-hari bagi penjaga hutan seperti Anda?\"", 30);
    delayPrint(L"Mars: \"Cuaca yang tidak menentu, Tuan Muda. Terkadang badai datang tiba-tiba. Lalu ada juga pencari jamur atau herbal yang tersesat karena nekat masuk terlalu dalam tanpa pemandu. Menemukan mereka bisa memakan waktu berhari-hari.\"", 30);
    delayPrint(L"Weiss: \"Pekerjaan yang benar-benar menuntut kesigapan dan pengetahuan medan yang luar biasa. Apakah Anda pernah tersesat di hutan ini selama bertugas?\"", 30);
    delayPrint(L"Mars: (Terkekeh pelan) \"Sekali atau dua kali saat masih muda dan terlalu percaya diri, Tuan Muda. Tapi hutan selalu mengajarkan kerendahan hati. Sekarang, saya lebih percaya pada peta, kompas, dan tanda-tanda alam. Dan insting, tentu saja.\"", 30);
    delayPrint(L"Weiss: \"Insting yang terasah oleh pengalaman bertahun-tahun, saya yakin. Saya jadi semakin menghargai peran Anda dalam menjaga keseimbangan Hutan Merah ini.\"", 30);
    delayPrint(L"Mars: \"Hutan ini adalah rumah saya, Tuan Muda. Menjaganya adalah panggilan jiwa. Apakah Anda punya rencana untuk menjelajahi bagian hutan yang lebih aman hari ini? Ada jalur edukasi di dekat sini yang baru kami buka.\"", 30);
    delayPrint(L"Weiss: \"Oh, benarkah? Itu ide yang bagus. Mungkin saya akan mencobanya. Terima kasih atas sarannya, Penjaga Mars.\"", 30);
    delayPrint(L"Mars: \"Sama-sama. Bawa air yang cukup dan perhatikan tanda jalur.\"", 30);
    delayPrint(L"Kamu merasa percakapan kalian semakin santai. Mars mulai berbagi lebih banyak cerita dan pengalamannya, menunjukkan sisi manusianya di balik seragam penjaga yang tegas.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel4() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 4 ✦ Pos Hutan Merah ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: \"Penjaga Mars, saya membawa beberapa buah apel dari kebun mansion. Sebagai ucapan terima kasih atas semua informasi yang telah Anda berikan. Semoga Anda menyukainya.\"", 30);
    delayPrint(L"Mars: (Menerima keranjang kecil itu dengan sedikit canggung namun menghargai) \"Tidak perlu repot-repot, Tuan Muda Astra. Tapi... terima kasih. Ini sangat baik dari Anda. Apel segar selalu jadi kemewahan di sini.\"", 30);
    delayPrint(L"Weiss: \"Sama-sama. Ngomong-ngomong, saya baru saja kembali dari jalur edukasi yang Anda sarankan. Sangat menarik. Saya melihat beberapa tanaman obat yang belum pernah saya lihat sebelumnya. Misalnya, yang daunnya berbentuk hati dengan bintik ungu itu, apa namanya dan apa khasiatnya?\"", 30);
    delayPrint(L"Mars: (Mengambil sebatang ranting dari meja, mulai menggambar bentuk daun di tanah) \"Ah, Anda pasti maksud Daun Jantung Ungu. Penduduk desa menyebutnya begitu. Getahnya bisa untuk mengobati luka bakar ringan atau gigitan serangga. Tapi harus diolah dengan benar, jika tidak malah bisa menyebabkan iritasi.\"", 30);
    delayPrint(L"Weiss: \"Pengetahuan yang sangat berguna. Apakah semua penjaga hutan diwajibkan mempelajari tentang tanaman obat seperti ini? Atau ini keahlian khusus Anda?\"", 30);
    delayPrint(L"Mars: \"Dasar-dasarnya kami pelajari, Tuan Muda. Untuk pertolongan pertama di hutan. Tapi pengetahuan mendalam biasanya diwariskan turun-temurun atau dipelajari dari para tabib desa. Saya sendiri belajar banyak dari kakek saya, beliau juga penjaga hutan.\"", 30);
    delayPrint(L"Weiss: \"Jadi ini semacam tradisi keluarga? Itu sangat mengagumkan. Apakah ada tanaman lain di Hutan Merah yang punya legenda atau mitos menarik di baliknya?\"", 30);
    delayPrint(L"Mars: (Berpikir sejenak, matanya menerawang) \"Ada cerita tentang Bunga Bulan Perak, Tuan Muda. Konon hanya mekar di malam bulan purnama tertentu di tempat yang sangat tersembunyi. Cahayanya bisa menyembuhkan segala penyakit, tapi dijaga oleh roh hutan. Tentu saja, itu hanya legenda.\"", 30);
    delayPrint(L"Weiss: \"Legenda yang sangat puitis. Meskipun hanya cerita, itu menambah pesona hutan ini. Terima kasih sudah berbagi, Penjaga Mars. Saya selalu belajar hal baru setiap kali berbicara dengan Anda.\"", 30);
    delayPrint(L"Mars: \"Hutan ini penuh dengan pengetahuan bagi mereka yang mau mencari, Tuan Muda. Saya senang Anda punya ketertarikan yang tulus. Sekarang, jika Anda tidak keberatan, saya harus bersiap untuk patroli senja.\"", 30);
    delayPrint(L"Weiss: \"Tentu. Jangan biarkan saya menahan Anda. Hati-hati di jalan.\"", 30);
    delayPrint(L"Mars: \"Selalu, Tuan Muda. Dan terima kasih sekali lagi untuk apelnya.\"", 30);
    delayPrint(L"Mars tampak lebih ramah dan terbuka. Dia mulai menghargai ketulusanmu dan kesediaanmu untuk belajar tentang dunianya, dunia hutan yang liar namun penuh kearifan.", 30);

    printLine();
    waitForEnter();;
}

void sceneMarsLevel5() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 5 ✦ Pos Hutan Merah ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Suatu hari, Weiss datang ke Pos Hutan dan menemukan Mars sedang memperbaiki pagar kayu yang rusak akibat diseruduk binatang.", 30);
    delayPrint(L"Weiss: \"Pekerjaan yang berat, Penjaga Mars. Perlu bantuan? Saya mungkin tidak seahli Anda, tapi setidaknya saya bisa memegangi kayunya.\"", 30);
    delayPrint(L"Mars: (Menoleh, sedikit terkejut dengan tawaran itu, lalu menyeka keringat di dahinya) \"Tuan Muda Astra. Tidak kusangka seorang bangsawan mau mengotori tangannya. Tapi tawaran Anda saya hargai. Sebenarnya, tambahan sepasang tangan akan sangat membantu.\"", 30);
    delayPrint(L"Weiss pun ikut membantu, memegangi tiang kayu sementara Mars memalunya. Pekerjaan itu cukup berat dan memakan waktu.", 30);
    delayPrint(L"Mars: \"Anda... cukup kuat juga, Tuan Muda. Tidak seperti bangsawan lain yang pernah saya temui, yang biasanya hanya memberi perintah dari jauh.\", (Sambil mengambil napas)", 30);
    delayPrint(L"Weiss: \"Saya percaya setiap pekerjaan punya nilainya sendiri, Penjaga. Dan saya tidak keberatan bekerja keras jika itu untuk tujuan yang baik. Lagipula, pagar ini penting untuk keamanan pos, bukan?\"", 30);
    delayPrint(L"Mars: \"Sangat penting. Terutama untuk menghalau hewan liar yang lebih kecil atau pencuri kayu skala kecil. Anda benar-benar berbeda dari Tuan Muda Astra yang dulu sering saya dengar ceritanya dari para pedagang. Mereka bilang Anda angkuh dan tidak peduli.\"", 30);
    delayPrint(L"Weiss: (Sedikit tersenyum getir) \"Orang bisa berubah, Penjaga Mars. Saya harap perubahan saya ke arah yang lebih baik. Apa yang Anda dengar tentang saya dulu, apakah sangat buruk?\"", 30);
    delayPrint(L"Mars: \"Cukup buruk hingga membuat saya waspada saat Anda pertama kali datang ke sini. Tapi tindakan Anda berbicara lebih keras daripada rumor. Anda menunjukkan ketertarikan tulus pada hutan, menghargai pekerjaan kami, bahkan mau membantu seperti ini. Itu... mengesankan.\"", 30);
    delayPrint(L"Setelah pagar selesai diperbaiki, Mars menawarkan Weiss segelas air dari tempayan tanah liat.", 30);
    delayPrint(L"Mars: \"Ini, Tuan Muda. Anda pasti haus. Air dari mata air hutan, sangat segar.\" (Menyodorkan gelas kayu).", 30);
    delayPrint(L"Weiss: (Menerima dan meminumnya) \"Terima kasih, Penjaga Mars. Ini benar-benar menyegarkan. Dan terima kasih atas kejujuran Anda. Saya menghargainya.\"", 30);
    delayPrint(L"Mars: \"Sama-sama, Tuan Muda. Saya juga menghargai bantuan Anda hari ini. Jarang sekali saya punya 'asisten' sekaliber Anda.\" (Ada sedikit nada bercanda dalam suaranya).", 30);
    delayPrint(L"Weiss: \"Kapan saja jika Anda butuh bantuan lagi, selama saya ada waktu. Anggap saja ini bagian dari kontribusi saya untuk Hutan Merah.\"", 30);
    delayPrint(L"Mars: \"Akan saya ingat itu. Sekarang, sebaiknya Anda membersihkan diri. Saya tidak mau Nyonya Astra mengira saya membuat putranya jadi kuli bangunan.\" (Tersenyum tipis).", 30);
    delayPrint(L"Kamu merasa ada dinding formalitas yang runtuh hari ini. Mars mulai melihatmu sebagai individu, bukan hanya sebagai gelar bangsawannya.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel6() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 6 ✦ Pos Hutan Merah (Malam, Hujan Deras) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss terjebak hujan deras saat sedang dalam perjalanan kembali dari desa dekat hutan dan memutuskan berteduh di Pos Hutan. Mars menyambutnya dengan secangkir teh herbal hangat.", 30);
    delayPrint(L"Weiss: \"Terima kasih sudah mengizinkan saya berteduh, Penjaga Mars. Dan untuk tehnya. Saya tidak menyangka hujannya akan sebesar ini.\"", 30);
    delayPrint(L"Mars: \"Tidak masalah, Tuan Muda Astra. Hujan di Hutan Merah memang seringkali tak terduga. Duduklah dekat perapian, hangatkan diri Anda. Berbahaya melanjutkan perjalanan dalam cuaca seperti ini.\"", 30);
    delayPrint(L"Suara hujan deras dan gemuruh petir sesekali terdengar di luar. Mereka duduk dalam keheningan yang nyaman sejenak.", 30);
    delayPrint(L"Mars: (Menatap ke luar jendela yang basah) \"Hujan seperti ini selalu membuat saya khawatir, Tuan Muda. Khawatir akan longsor di lereng utara, atau banjir bandang di Sungai Merah yang bisa merendam desa-desa di hilir.\"", 30);
    delayPrint(L"Weiss: \"Apakah sering terjadi bencana alam seperti itu di sini? Saya jarang mendengar beritanya sampai ke kota.\"", 30);
    delayPrint(L"Mars: \"Cukup sering, terutama di musim penghujan. Skalanya mungkin tidak selalu besar hingga jadi berita kota, tapi dampaknya sangat terasa bagi penduduk desa sekitar hutan. Tahun lalu, jembatan utama ke Desa Pinus hanyut terbawa banjir. Butuh waktu berminggu-minggu untuk membangun jembatan darurat.\"", 30);
    delayPrint(L"Weiss: \"Itu pasti sangat menyulitkan mereka. Apakah ada sistem peringatan dini atau upaya mitigasi bencana yang dilakukan?\"", 30);
    delayPrint(L"Mars: \"Kami para penjaga hutan selalu berusaha memantau ketinggian air sungai dan kondisi lereng, lalu memberi peringatan ke kepala desa. Tapi sumber daya kami terbatas. Kami butuh lebih banyak pos pantau dan peralatan yang lebih baik. Proposal sudah sering diajukan ke Balai Kota, tapi responsnya lambat.\"", 30);
    delayPrint(L"Weiss: (Mengangguk prihatin) \"Ini masalah serius, Mars.\" (Weiss mulai memanggilnya Mars secara lebih akrab) \"Mungkin saya bisa membantu mendorong proposal itu. Dengan data yang akurat tentang dampak dan kebutuhan mendesak, saya bisa berbicara dengan beberapa anggota dewan yang berpengaruh. Keselamatan warga adalah prioritas utama.\"", 30);
    delayPrint(L"Mars: (Menatap Weiss dengan sorot mata yang menunjukkan harapan baru) \"Anda... Anda bersedia melakukan itu, Tuan Muda? Itu akan sangat berarti bagi kami semua di sini. Selama ini, suara kami dari pinggir hutan seringkali tidak terdengar sampai ke pusat kekuasaan.\"", 30);
    delayPrint(L"Weiss: \"Anggap saja ini tanggung jawab kita bersama, Mars. Hutan dan orang-orang di sekitarnya adalah bagian dari wilayah yang harus kita jaga. Berikan saya semua data yang Anda miliki. Saya akan mempelajarinya dan menyusun argumen yang kuat.\"", 30);
    delayPrint(L"Mars: \"Akan saya siapkan semuanya besok pagi, Tuan Muda. Terima kasih. Terima kasih yang sebesar-besarnya. Anda telah memberikan kami harapan baru.\"", 30);
    delayPrint(L"Weiss: \"Kita berjuang bersama untuk ini, Mars.\"", 30);
    delayPrint(L"Di tengah badai di luar, sebuah percakapan penting telah terjadi. Kamu dan Mars kini berbagi kepedulian yang sama terhadap nasib hutan dan penduduknya, membangun fondasi untuk kerjasama yang lebih erat.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel7() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 7 ✦ Pos Hutan Merah ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Beberapa minggu setelah Weiss membantu mendorong proposal ke dewan kota, Mars menyambutnya dengan antusias di Pos Hutan.", 30);
    delayPrint(L"Mars: \"Tuan Muda Weiss! Kabar baik! Proposal kita untuk pos pantau tambahan dan peralatan mitigasi bencana disetujui oleh dewan kota! Bahkan mereka menambahkan anggaran untuk pelatihan penjaga hutan dalam penanganan darurat! Ini semua berkat bantuan Anda!\"", 30);
    delayPrint(L"Weiss: (Tersenyum lega) \"Syukurlah, Mars! Saya senang usaha kita membuahkan hasil. Ini bukan hanya bantuan saya, tapi juga kegigihan Anda dalam menyediakan data dan argumen yang kuat. Kita tim yang baik, bukan?\"", 30);
    delayPrint(L"Mars: \"Lebih dari baik, Tuan Muda! Anda telah melakukan apa yang tidak bisa kami lakukan selama bertahun-tahun. Para kepala desa mengirimkan salam hormat dan terima kasih mereka untuk Anda. Mereka bilang, akhirnya ada bangsawan yang benar-benar peduli pada nasib mereka.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya menjalankan kewajiban saya. Tapi, Mars, dengan adanya persetujuan ini, tantangan selanjutnya adalah implementasi. Apakah Anda sudah punya rencana bagaimana pos pantau itu akan dibangun dan siapa yang akan mengelolanya?\"", 30);
    delayPrint(L"Mars: \"Kami sudah melakukan survei lokasi potensial, Tuan Muda. Ada beberapa titik strategis di sepanjang Sungai Merah dan lereng utara. Untuk pengelolaan, kami akan membentuk tim patroli khusus yang sudah dilatih. Tapi, kami mungkin butuh sedikit bantuan logistik untuk pengangkutan material ke area yang sulit dijangkamu.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti. Bagaimana jika keluarga Astra membantu menyediakan beberapa gerobak tambahan dan tenaga angkut dari pekerja perkebunan kami yang sedang tidak terlalu sibuk? Itu bisa mempercepat prosesnya. Anggap saja ini kelanjutan dari dukungan kami.\"", 30);
    delayPrint(L"Mars: (Tertegun sejenak, lalu tersenyum lebar) \"Tuan Muda... Anda benar-benar tidak ada habisnya memberi kejutan baik. Tawaran itu akan sangat, sangat membantu kami. Dengan begitu, pos pantau bisa beroperasi lebih cepat sebelum musim hujan berikutnya mencapai puncaknya.\"", 30);
    delayPrint(L"Weiss: \"Itulah tujuannya. Segera koordinasikan dengan kepala pekerja perkebunan saya. Saya akan memberinya instruksi. Selain itu, apakah ada hal lain yang bisa saya bantu untuk memastikan program ini berjalan lancar?\"", 30);
    delayPrint(L"Mars: \"Untuk saat ini, itu sudah lebih dari cukup, Tuan Muda. Anda telah memberikan kami alat dan harapan. Sisanya, serahkan pada kami para penjaga hutan. Kami akan memastikan setiap koin dari anggaran itu digunakan dengan benar dan setiap pos pantau berfungsi maksimal.\"", 30);
    delayPrint(L"Weiss: \"Saya percaya penuh pada Anda dan tim Anda, Mars. Kabari saya jika ada perkembangan atau kendala. Kita akan terus mengawal ini bersama.\"", 30);
    delayPrint(L"Mars: \"Siap, Tuan Muda! Sekali lagi, atas nama seluruh penjaga Hutan Merah dan masyarakat sekitar, terima kasih. Anda adalah sahabat sejati hutan ini.\"", 30);
    delayPrint(L"Weiss: \"Dan Anda adalah penjaga setianya, Mars. Sebuah kehormatan bisa bekerja sama dengan Anda.\"", 30);
    delayPrint(L"Rasa hormat dan kemitraan antara kalian semakin dalam. Bukan lagi sekadar Tuan Muda dan Penjaga Hutan, tapi dua individu yang bekerja bahu-membahu demi kebaikan bersama.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel8() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 8 ✦ Pos Hutan Merah (Api Unggun Malam Hari) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss mengunjungi Mars di malam hari. Mereka duduk di dekat api unggun kecil di depan pos, menikmati keheningan hutan malam yang hanya dipecah oleh suara jangkrik dan gemerisik daun.", 30);
    delayPrint(L"Weiss: \"Malam yang tenang, Mars. Berbeda sekali dengan kebisingan kota. Terkadang aku iri dengan kedamaian yang kamu miliki di sini.\"", 30);
    delayPrint(L"Mars: (Tersenyum tipis sambil menatap api) \"Hutan memang punya caranya sendiri untuk menenangkan jiwa, Tuan Muda. Tapi kedamaian ini juga harus dijaga. Setiap malam, selalu ada kewaspadaan. Kita tidak pernah tahu apa yang bersembunyi di balik bayang-bayang.\"", 30);
    delayPrint(L"Weiss: \"kamu sudah berapa lama menjadi penjaga hutan, Mars? Sepertinya kamu sudah sangat menyatu dengan tempat ini.\"", 30);
    delayPrint(L"Mars: \"Hampir dua puluh tahun, Tuan Muda. Sejak saya masih sangat muda, mengikuti jejak ayah dan kakek saya. Hutan ini sudah seperti darah daging bagi saya. Saya mengenal setiap pohon, setiap suara binatang, setiap perubahan angin.\"", 30);
    delayPrint(L"Mars: \"Saya ingat dulu, saat pertama kali patroli sendirian, saya tersesat selama dua hari. Hanya berbekal pisau dan sedikit pengetahuan bertahan hidup. Saat itu saya benar-benar takut. Tapi hutan justru mengajari saya banyak hal. Tentang kerendahan hati, tentang pentingnya mengamati, dan tentang bagaimana cara 'mendengarkan' alam.\"", 30);
    delayPrint(L"Weiss: \"Pengalaman yang pasti sangat membentuk dirimu. Apakah ada momen paling berkesan atau paling berbahaya yang pernah kamu alami selama bertugas?\"", 30);
    delayPrint(L"Mars: (Terpekur sejenak, matanya menatap jauh ke dalam api) \"Ada satu malam, bertahun-tahun lalu. Saya berhadapan langsung dengan seekor Beruang Cakar Besi raksasa yang sedang mengamuk karena anaknya terperangkap jerat pemburu. Ukurannya luar biasa besar, dan matanya merah menyala penuh amarah.\"", 30);
    delayPrint(L"Mars: \"Saya pikir itu akan jadi malam terakhir saya. Tapi entah bagaimana, saya berhasil tetap tenang, tidak menunjukkan rasa takut. Saya berbicara padanya dengan suara pelan, mencoba meyakinkannya bahwa saya tidak bermaksud jahat. Perlahan, saya berhasil membebaskan anaknya. Dan beruang itu... dia hanya menatap saya sejenak, lalu pergi menghilang ke dalam hutan bersama anaknya tanpa menyakiti saya sedikit pun.\"", 30);
    delayPrint(L"Weiss: (Mendengarkan dengan napas tertahan) \"Luar biasa... Itu... itu seperti cerita dari legenda. kamu benar-benar pemberani, Mars.\"", 30);
    delayPrint(L"Mars: \"Bukan keberanian, Tuan Muda. Mungkin lebih ke... pemahaman. Saya percaya bahwa setiap makhluk di hutan ini punya jiwa dan alasan untuk bertindak. Jika kita menghormati mereka, mereka juga akan menghormati kita. Hutan ini punya hukumnya sendiri, hukum keseimbangan alam. Tugas kita adalah menjaganya, bukan merusaknya.\"", 30);
    delayPrint(L"Weiss: \"Sebuah filosofi yang sangat mendalam. Saya semakin mengerti mengapa kamu begitu berdedikasi pada tempat ini. Hutan Merah beruntung memiliki penjaga sepertimu.\"", 30);
    delayPrint(L"Mars: \"Dan saya beruntung memiliki teman seperti Anda, Tuan Muda, yang mau mendengarkan cerita seorang penjaga hutan tua dan memahami pentingnya menjaga warisan ini.\" (Menatap Weiss dengan tulus)", 30);
    delayPrint(L"Weiss: \"Kehormatan ada di pihak saya, Mars.\"", 30);
    delayPrint(L"Di bawah langit malam berbintang, diiringi suara alam, kamu merasa sebuah ikatan persahabatan yang kuat dan tulus telah terjalin dengan Mars. Sebuah persahabatan yang didasari rasa hormat dan pemahaman yang mendalam.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel9() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 9 ✦ Pos Hutan Merah & Area Hutan Sekitar ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Mars: (Dengan wajah cemas) \"Tuan Muda Weiss, ada masalah. Salah satu tim patroli belum kembali dari sektor barat laut. Mereka seharusnya sudah melapor dua jam yang lalu. Komunikasi radio juga tidak berhasil.\"", 30);
    delayPrint(L"Weiss: \"Sektor barat laut? Bukankah itu area yang medannya cukup sulit dan berkabut tebal akhir-akhir ini? Apa perkiraan terakhir posisi mereka?\"", 30);
    delayPrint(L"Mars: \"Benar. Mereka sedang menyelidiki laporan tentang adanya aktivitas penebangan liar di sana. Posisi terakhir mereka sekitar tiga kilometer dari Pos Jaga Lembah Serigala. Saya khawatir terjadi sesuatu. Saya akan memimpin tim pencari sekarang juga.\"", 30);
    delayPrint(L"Weiss: \"Saya ikut dengan Anda, Mars. Saya mungkin tidak sehebat Anda dalam melacak jejak, tapi saya bisa membantu membawa peralatan tambahan atau memberikan pertolongan pertama jika diperlukan. Anggap saya sebagai anggota tim Anda hari ini.\"", 30);
    delayPrint(L"Mars: (Menatap Weiss dengan sedikit ragu, lalu mengangguk mantap) \"Baiklah, Tuan Muda. Keberanian Anda selalu mengejutkan saya. Tapi ingat, ikuti instruksi saya dengan saksama. Hutan tidak memberi ampun pada kecerobohan. Bawa perlengkapan hujan dan penerangan tambahan.\"", 30);
    delayPrint(L"Mereka berdua, bersama beberapa penjaga lain, segera berangkat menembus hutan yang mulai diselimuti kabut senja.", 30);
    delayPrint(L"Setelah beberapa jam pencarian yang menegangkan, mengikuti jejak samar dan sesekali memanggil, mereka akhirnya menemukan tim patroli yang hilang. Salah satu dari mereka kakinya terkilir dan radio mereka rusak terkena air.", 30);
    delayPrint(L"Weiss dengan sigap membantu memberikan pertolongan pertama pada penjaga yang terluka, menggunakan pengetahuan medis dasar yang pernah ia pelajari.", 30);
    delayPrint(L"Mars: (Setelah memastikan semua anak buahnya aman dan mulai mengatur perjalanan kembali) \"Kerja bagus, Tuan Muda. Kehadiran dan bantuan Anda sangat berarti hari ini. Anda tetap tenang di bawah tekanan dan tindakan Anda cepat. Anda punya bakat alami seorang pemimpin.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya melakukan apa yang bisa saya lakukan, Mars. Yang penting semua orang selamat. Ini adalah pengingat betapa berbahayanya pekerjaan Anda setiap hari.\"", 30);
    delayPrint(L"Penjaga yang Terluka: \"Terima kasih banyak, Tuan Muda Astra, Penjaga Mars. Kami sempat putus asa tadi.\"", 30);
    delayPrint(L"Mars: \"Istirahatlah. Kita akan segera kembali ke pos. Dan Tuan Muda... terima kasih. Anda telah membuktikan diri bukan hanya sebagai teman hutan, tapi juga sebagai rekan yang bisa diandalkan dalam situasi sulit.\"", 30);
    delayPrint(L"Weiss: \"Kapan saja, Mars. Kapan saja. Kita adalah tim.\"", 30);
    delayPrint(L"Malam itu, saat kembali ke pos dengan selamat, kamu merasakan kelelahan namun juga kepuasan. Pengalaman menghadapi kesulitan bersama telah menempa ikatanmu dengan Mars menjadi semakin kuat, sebuah persaudaraan yang lahir dari hutan.", 30);

    printLine();
    waitForEnter();
}

void sceneMarsLevel10() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Mars - Penjaga Pos Hutan ✦ Level 10 ✦ Puncak Bukit Pengamatan, Hutan Merah ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Mars mengajak Weiss ke sebuah bukit pengamatan yang jarang diketahui orang, yang menyuguhkan pemandangan Hutan Merah yang luar biasa luas dan indah saat matahari terbit.", 30);
    delayPrint(L"Mars: \"Bagaimana menurut Anda pemandangan dari sini, Tuan Muda Weiss? Ini adalah tempat favorit saya di seluruh Hutan Merah. Dari sini, saya bisa melihat hampir seluruh wilayah jelajah saya.\"", 30);
    delayPrint(L"Weiss: (Terpesona oleh keindahan di hadapannya) \"Luar biasa, Mars... Sungguh menakjubkan. Saya tidak pernah membayangkan Hutan Merah bisa seindah dan semegah ini. Rasanya seperti melihat jantung dunia berdetak.\"", 30);
    delayPrint(L"Mars: \"Inilah yang saya jaga setiap hari, Tuan Muda. Inilah warisan yang ingin saya tinggalkan untuk generasi mendatang. Sebuah hutan yang sehat, lestari, dan penuh kehidupan.\"", 30);
    delayPrint(L"Mars: \"Selama ini, Anda telah menunjukkan kepedulian yang tulus, keberanian yang nyata, dan dukungan yang tak ternilai bagi Hutan Merah dan kami para penjaganya. Anda bukan lagi sekadar Tuan Muda von Astra bagi saya. Anda adalah Weiss, sahabat hutan, pelindung alam, dan rekan seperjuangan saya.\"", 30);
    delayPrint(L"Mars kemudian mengeluarkan sebuah kalung sederhana dengan liontin kayu berbentuk ukiran serigala yang sangat detail dan artistik.", 30);
    delayPrint(L"Mars: \"Ini adalah 'Taring Serigala Penjaga'. Serigala adalah simbol penjaga yang setia, cerdas, dan bekerja dalam tim di hutan ini. Saya mengukirnya sendiri dari kayu Jati Merah keramat. Saya ingin memberikannya kepada Anda sebagai tanda persahabatan abadi kita, dan sebagai pengakuan bahwa Anda adalah salah satu dari kami, seorang Penjaga Hutan dalam hati.\"", 30);
    delayPrint(L"Weiss: (Menerima kalung itu dengan penuh rasa haru dan hormat) \"Mars... ini... ini adalah kehormatan terbesar yang pernah saya terima. Ukiran ini sangat indah dan penuh makna. Saya akan memakainya selalu sebagai pengingat akan persahabatan kita dan tanggung jawab kita bersama terhadap hutan ini.\"", 30);
    delayPrint(L"Mars: \"Saya tahu Anda akan menjaganya dengan baik. Ingatlah selalu, Weiss, bahwa hutan ini akan selalu menyambut Anda sebagai bagian darinya. Dan saya, Mars, akan selalu menjadi saudara Anda, siap bertarung di sisi Anda kapan pun dibutuhkan, baik untuk melindungi hutan ini maupun untuk hal lain yang Anda anggap benar.\"", 30);
    delayPrint(L"Weiss: \"Dan Anda juga akan selalu menjadi saudara bagi saya, Mars. Seorang mentor, sahabat, dan penjaga sejati. Mari kita terus jaga Hutan Merah ini bersama-sama, demi masa depan Arcadia dan generasi yang akan datang. Apakah ada proyek konservasi baru yang bisa kita mulai?\"", 30);
    delayPrint(L"Mars: (Tertawa senang, matanya berbinar menatap matahari terbit) \"Anda benar-benar tidak bisa diam ya, Weiss? Selalu ada ide baru! Tentu saja ada! Saya punya rencana untuk program reboisasi di area bekas kebakaran. Dan saya tahu persis siapa yang akan jadi mitra terbaik saya dalam proyek itu!\"", 30);
    delayPrint(L"Weiss: (Tersenyum lebar) \"Saya siap, Komandan Mars! Mari kita mulai!\"", 30);
    delayPrint(L"Mars: \"Ayo! Tapi setelah kita menikmati secangkir kopi panas dan sarapan sederhana di pos. Perut juga butuh dijaga, bukan?\"", 30);
    delayPrint(L"Di puncak bukit itu, dengan Hutan Merah terbentang di bawah mereka sebagai saksi, sebuah persahabatan yang kokoh dan penuh makna telah mencapai puncaknya. Weiss dan Mars, dua jiwa dari dunia yang berbeda, kini bersatu dalam semangat dan dedikasi untuk menjaga alam dan memperjuangkan kebaikan.", 30);

    waitForEnter(L" Kamu telah membentuk ikatan terkuat...... Tekan Enter untuk melihat detailnya");

    if (!socialLinks["Mars"].completed) { 
        applySocialLinkBonus("Mars"); 
        socialLinks["Mars"].completed = true; 
    }

    printLine();
    waitForEnter();
}

void sceneKinichLevel1() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 1 ✦ Camp Avernix, Goa Avernix ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Menghampiri area Camp Avernix yang berdebu, seorang pria berperawakan keras dengan wajah lelah dan waspada sedang memeriksa peralatan tambang). \"Permisi, apakah Anda Penjaga Kinich yang bertanggung jawab atas keamanan area tambang ini? Saya Weiss von Astra.\"", 30);
    delayPrint(L"Kinich: (Meletakkan beliungnya, menatap Weiss dengan tatapan menyelidik, tidak ramah namun juga tidak langsung bermusuhan) \"Benar. Saya Kinich. Ada urusan apa seorang von Astra sampai ke tempat terpencil dan berbahaya seperti Goa Avernix ini? Kami jarang menerima kunjungan dari kamum Anda.\"", 30);
    delayPrint(L"Weiss: \"Keluarga Astra memiliki sebagian saham dalam operasi penambangan di sini, Penjaga Kinich. Saya datang untuk melihat langsung kondisi lapangan, memahami tantangan operasional, dan memastikan semuanya berjalan sesuai standar keamanan yang ditetapkan.\"", 30);
    delayPrint(L"Kinich: (Mengangguk pelan, ekspresinya masih skeptis) \"Standar keamanan, ya? Di atas kertas mungkin terlihat bagus, Tuan Muda. Tapi kenyataan di dalam perut bumi ini berbeda. Setiap hari adalah pertaruhan nyawa. Apa yang ingin Anda lihat secara spesifik?\"", 30);
    delayPrint(L"Weiss: \"Untuk hari ini, saya hanya ingin mendapatkan gambaran umum tentang aktivitas di camp dan area pintu masuk tambang. Mungkin Anda bisa menjelaskan secara singkat tentang jenis mineral utama yang ditambang dan potensi bahaya yang paling sering dihadapi para penambang?\"", 30);
    delayPrint(L"Kinich: \"Mineral utama di sini adalah Bijih Besi Merah dan Kristal Kegelapan. Bahaya utama? Longsoran batu, gas beracun di lorong-lorong dalam, dan tentu saja... makhluk-makhluk yang menghuni kegelapan abadi di bawah sana. Bukan tempat untuk mereka yang bernyali kecil.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti. Kedengarannya memang bukan pekerjaan yang mudah. Terima kasih atas penjelasan awalnya, Penjaga Kinich. Saya akan mengamati dari area yang aman untuk saat ini.\"", 30);
    delayPrint(L"Kinich: \"Itu keputusan yang bijak, Tuan Muda. Pastikan Anda tidak melewati batas aman tanpa pengawalan. Saya punya banyak pekerjaan yang harus diurus.\" (Kembali memeriksa peralatannya).", 30);
    delayPrint(L"Weiss: \"Saya akan berhati-hati. Mungkin lain kali saya bisa bertanya lebih banyak tentang sistem peringatan dini atau prosedur evakuasi di sini?\"", 30);
    delayPrint(L"Kinich: \"Jika Anda memang serius ingin tahu dan tidak hanya sekadar 'tur wisata', saya akan luangkan waktu. Tapi jangan berharap saya akan memanjakan Anda.\"", 30);
    delayPrint(L"Weiss: \"Saya tidak mengharapkannya, Penjaga. Terima kasih.\"", 30);
    delayPrint(L"Kinich hanya menggeram pelan sebagai jawaban. Jelas bahwa mendapatkan rasa hormat dari pria keras seperti dia akan menjadi sebuah tantangan tersendiri.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel2() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 2 ✦ Area Logistik Camp Avernix ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Menemukan Kinich sedang mengawasi pembongkaran pasokan baru untuk para penambang – makanan, air, dan beberapa peralatan) \"Penjaga Kinich, selamat siang. Sepertinya pasokan baru sudah tiba?\"", 30);
    delayPrint(L"Kinich: (Menoleh, wajahnya masih berdebu seperti biasa) \"Tuan Muda Astra. Ya, datang lebih lambat dari jadwal seharusnya. Jalan menuju kemari dari kota semakin rusak parah. Apakah Anda datang untuk 'inspeksi' logistik juga sekarang?\"", 30);
    delayPrint(L"Weiss: \"Tidak secara spesifik. Saya hanya ingin tahu, bagaimana kondisi para penambang di sini? Apakah persediaan makanan dan air selalu mencukupi? Dan bagaimana dengan upah serta jaminan kesehatan mereka?\"", 30);
    delayPrint(L"Kinich: (Menatap Weiss dengan sedikit terkejut, tidak menyangka pertanyaan seperti itu) \"Pertanyaan yang tidak biasa dari seorang bangsawan. Untuk makanan dan air, kami berusaha keras memenuhinya, Tuan Muda, meskipun terkadang terlambat seperti ini. Upah... cukuplah untuk menghidupi keluarga di desa, meski tidak sebanding dengan risikonya. Jaminan kesehatan? Jika mereka terluka parah di dalam, kami bawa ke tabib terdekat di desa kaki gunung. Itu saja.\"", 30);
    delayPrint(L"Weiss: \"Kedengarannya masih banyak yang perlu diperbaiki dalam hal kesejahteraan mereka. Apakah pernah ada upaya dari pihak perusahaan atau keluarga Astra untuk meningkatkan fasilitas atau jaminan bagi para penambang?\"", 30);
    delayPrint(L"Kinich: (Tersenyum sinis) \"Upaya di atas kertas mungkin ada, Tuan Muda. Proposal dan janji-janji manis. Tapi implementasinya seringkali terhambat birokrasi atau 'pemotongan anggaran'. Bagi mereka yang duduk nyaman di kota, kami di sini mungkin hanya angka statistik.\"", 30);
    delayPrint(L"Weiss: \"Itu pandangan yang menyedihkan, tapi mungkin ada benarnya. Saya akan coba mempelajari lebih lanjut tentang kontrak kerja dan proposal kesejahteraan yang pernah diajukan. Mungkin ada sesuatu yang bisa saya dorong dari atas.\"", 30);
    delayPrint(L"Kinich: (Mengangkat sebelah alisnya) \"Anda serius? Seorang von Astra mau repot-repot mengurusi nasib penambang rendahan seperti kami? Jangan membuat saya tertawa, Tuan Muda.\"", 30);
    delayPrint(L"Weiss: \"Saya serius, Kinich.\" (Memanggilnya dengan nama untuk pertama kali) \"Setiap nyawa berharga. Dan setiap pekerja berhak mendapatkan perlakuan yang layak, terutama mereka yang mempertaruhkan nyawanya setiap hari seperti di sini. Saya akan lihat apa yang bisa saya lakukan.\"", 30);
    delayPrint(L"Kinich: (Tertegun sejenak menatap kesungguhan di mata Weiss, lalu mengalihkan pandangannya) \"Hmph. Saya sudah terlalu sering mendengar janji. Saya akan percaya jika sudah ada bukti nyata. Sekarang, jika Anda permisi, saya harus memastikan karung-karung gandum ini tidak basah.\"", 30);
    delayPrint(L"Weiss: \"Tentu. Terima kasih atas waktunya, Kinich.\"", 30);
    delayPrint(L"Kinich: \"Ya.\"", 30);
    delayPrint(L"Meskipun sikapnya masih kasar, kamu merasa ada sedikit celah di dinding pertahanannya. Pertanyaanmu tentang kesejahteraan penambang sepertinya menyentuh sesuatu dalam dirinya.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel3() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 3 ✦ Pintu Masuk Goa Avernix ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Berdiri di dekat pintu masuk goa yang gelap dan berangin, Kinich baru saja keluar bersama beberapa penambang yang wajahnya pucat). \"Ada masalah di dalam, Kinich? Kalian terlihat... terguncang.\"", 30);
    delayPrint(L"Kinich: (Mengusap wajahnya yang penuh keringat dingin) \"Tuan Muda Astra. Getaran kecil tadi, Anda merasakannya? Di Lorong Tujuh terjadi sedikit longsoran. Tidak ada korban jiwa, syukurlah. Tapi beberapa peralatan tertimbun dan jalan terblokir sementara.\"", 30);
    delayPrint(L"Weiss: \"Getaran? Saya tidak merasakannya di camp. Apakah longsoran seperti ini sering terjadi? Ini pasti sangat menakutkan bagi para penambang.\"", 30);
    delayPrint(L"Kinich: \"Perut bumi ini hidup, Tuan Muda. Dia bergerak dan bernapas sesuka hatinya. Longsoran kecil atau sedang itu sudah jadi 'sarapan' kami. Yang kami takutkan adalah 'Guncangan Besar' yang konon bisa meruntuhkan seluruh lorong utama. Para penambang tua punya banyak cerita tentang itu.\"", 30);
    delayPrint(L"Weiss: \"'Guncangan Besar'? Apakah itu mitos atau pernah benar-benar terjadi? Dan apakah ada cara untuk memprediksinya?\"", 30);
    delayPrint(L"Kinich: (Menatap ke dalam kegelapan goa dengan pandangan jauh) \"Beberapa generasi lalu, katanya pernah terjadi. Menelan ratusan nyawa. Tidak ada yang tahu pasti. Untuk memprediksinya? Kami hanya bisa berdoa dan memperhatikan tanda-tanda kecil. Misalnya, jika tikus-tikus tambang berlarian keluar goa secara massal, atau jika air di sumur bawah tanah tiba-tiba surut drastis. Itu pertanda buruk.\"", 30);
    delayPrint(L"Weiss: \"Superstisi atau kearifan lokal yang teruji waktu, ya? Hidup di sini benar-benar seperti berjudi dengan alam setiap hari. Saya jadi semakin menghargai keberanian para penambang.\"", 30);
    delayPrint(L"Kinich: \"Mereka bukan hanya berani, Tuan Muda. Mereka putus asa. Banyak dari mereka tidak punya pilihan lain untuk menghidupi keluarga. Goa ini memberi kami kehidupan, sekaligus mengancamnya. Ironis, bukan?\"", 30);
    delayPrint(L"Weiss: \"Sangat ironis. Apakah ada ritual atau tradisi tertentu yang biasa dilakukan para penambang sebelum masuk ke dalam untuk memohon keselamatan?\"", 30);
    delayPrint(L"Kinich: \"Setiap pagi, kami menaburkan sedikit garam di mulut goa, sebagai persembahan untuk 'Roh Penunggu Goa'. Dan kami tidak pernah bersiul di dalam lorong, katanya itu bisa membangunkan 'mereka' yang tidur di kedalaman. Mungkin terdengar konyol bagi orang kota seperti Anda, tapi bagi kami, itu adalah cara untuk menghormati tempat ini.\"", 30);
    delayPrint(L"Weiss: \"Saya tidak menganggapnya konyol, Kinich. Setiap budaya punya caranya sendiri untuk berdamai dengan alam dan ketidakpastian. Terima kasih sudah berbagi cerita ini. Ini memberi saya pemahaman yang lebih dalam.\"", 30);
    delayPrint(L"Kinich: \"Hmph. Setidaknya Anda mau mendengarkan. Kebanyakan bangsawan hanya peduli berapa banyak bijih yang bisa kami angkut keluar.\" (Meludah ke tanah). \"Sekarang saya harus mengatur tim untuk membersihkan Lorong Tujuh.\"", 30);
    delayPrint(L"Weiss: \"Hati-hati, Kinich. Dan sampaikan salam saya untuk para penambang. Semoga mereka semua aman.\"", 30);
    delayPrint(L"Kinich hanya mengangguk singkat sebelum berbalik dan memberi perintah kepada anak buahnya. Kamu mulai melihat sisi lain dari Kinich, seorang pria yang dibentuk oleh kerasnya alam dan kepercayaan mistis tambang.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel4() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 4 ✦ Camp Avernix (Dekat Peta Tambang) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Melihat Kinich sedang mempelajari peta lorong-lorong tambang yang besar dan rumit di dinding kantornya yang sederhana) \"Peta yang sangat detail, Kinich. Pasti butuh waktu lama untuk membuatnya seakurat ini.\"", 30);
    delayPrint(L"Kinich: (Tanpa menoleh) \"Setiap jengkalnya digambar dengan darah dan keringat, Tuan Muda. Peta ini adalah nyawa kami di bawah sana. Salah belok sedikit bisa berarti terjebak atau bertemu sesuatu yang tidak ingin ditemui. Ada perlu apa?\"", 30);
    delayPrint(L"Weiss: \"Saya sedang mencoba memahami lebih baik tentang struktur Goa Avernix. Saya dengar ada beberapa jenis kristal selain Kristal Kegelapan yang bisa ditemukan di sini, meskipun mungkin tidak bernilai komersial tinggi. Apakah Anda tahu di mana area yang potensial untuk menemukannya? Ini murni untuk riset pribadi.\"", 30);
    delayPrint(L"Kinich: (Akhirnya menoleh, menatap Weiss dengan curiga) \"Riset pribadi? Bangsawan biasanya tidak tertarik pada 'batu berkilau' yang tidak bisa dijual mahal. Kristal apa yang Anda cari? Kristal Lumina yang katanya bisa bersinar sendiri, atau Geode Guntur yang berderak saat disentuh?\"", 30);
    delayPrint(L"Weiss: \"Keduanya terdengar menarik. Terutama Kristal Lumina. Apakah benar ada? Dan di mana kira-kira bisa ditemukan? Saya tidak berniat masuk terlalu dalam, hanya area yang relatif aman.\"", 30);
    delayPrint(L"Kinich: (Menunjuk satu titik di peta di sektor barat yang tidak terlalu jauh dari pintu masuk) \"Ada satu lorong buntu di sekitar sini, 'Gua Kunang-Kunang' kami menyebutnya. Dindingnya sering memancarkan cahaya redup kehijauan karena ada endapan mineral fosfor alami. Beberapa penambang pernah menemukan pecahan kecil Kristal Lumina di sana, tapi sangat jarang dan biasanya tertanam jauh di dalam batu.\"", 30);
    delayPrint(L"Kinich: \"Tapi saya peringatkan, Tuan Muda. Meskipun relatif dekat, area itu jarang dilewati dan pencahayaannya minim. Pastikan Anda membawa penerangan yang cukup dan jangan pergi sendirian. Dan jangan pernah menyentuh lumut bercahaya aneh yang tumbuh di sana, bisa membuat kulit gatal selama berhari-hari.\"", 30);
    delayPrint(L"Weiss: \"'Gua Kunang-Kunang'. Informasi yang sangat berharga. Dan terima kasih atas peringatannya, akan saya ingat baik-baik. Apakah ada tanda khusus untuk mencapai lorong itu? Peta ini terlihat sangat rumit bagi saya.\"", 30);
    delayPrint(L"Kinich: (Mengambil sepotong arang dan membuat beberapa tanda tambahan di salinan peta kecil di mejanya) \"Ikuti jalur utama sampai persimpangan ketiga, lalu ambil belokan kiri yang menurun. Setelah melewati jembatan kayu rapuh, cari celah sempit di dinding kanan yang ditandai dengan ukiran tiga bulan sabit. Itu pintu masuknya. Tapi sekali lagi, hati-hati.\"", 30);
    delayPrint(L"Weiss: \"Saya akan sangat berhati-hati. Terima kasih banyak atas bantuan dan petunjuknya, Kinich. Ini lebih dari yang saya harapkan.\"", 30);
    delayPrint(L"Kinich: \"Hmph. Anggap saja ini balas budi karena Anda mau mendengarkan keluh kesah penambang tua seperti saya. Tapi jika Anda menemukan bongkahan Kristal Lumina sebesar kepala, jangan lupa bagi hasilnya ya?\" (Ada sedikit nada bercanda, yang sangat langka darinya).", 30);
    delayPrint(L"Weiss: (Tersenyum) \"Akan saya pertimbangkan, Kinich. Akan saya pertimbangkan. Terima kasih lagi.\"", 30);
    delayPrint(L"Kinich hanya mengangguk dan kembali mempelajari petanya. Kamu merasa ada sedikit kehangatan dalam sikapnya hari ini, seolah dia mulai menikmati berbagi pengetahuannya tentang goa yang misterius ini.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel5() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 5 ✦ Camp Avernix (Saat Istirahat Makan Siang Penambang) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss datang ke Camp Avernix membawa beberapa kotak berisi roti isi daging dan buah-buahan segar dari mansion, membagikannya kepada para penambang yang sedang beristirahat. Kinich mengamati dari kejauhan dengan ekspresi yang sulit ditebak.", 30);
    delayPrint(L"Penambang 1: \"Wah, Tuan Muda Astra baik sekali! Roti ini enak sekali!\"", 30);
    delayPrint(L"Penambang 2: \"Terima kasih banyak, Tuan Muda! Buah segar seperti ini jarang kami nikmati di sini!\"", 30);
    delayPrint(L"Weiss: \"Sama-sama. Anggap saja ini sedikit perhatian dari keluarga Astra. Kalian semua sudah bekerja keras. Jaga kesehatan kalian.\"", 30);
    delayPrint(L"Setelah selesai membagikan, Weiss menghampiri Kinich yang duduk sendirian, hanya minum air.", 30);
    delayPrint(L"Weiss: \"Kinich, saya sisihkan satu kotak untuk Anda. Anda juga sudah bekerja keras mengawasi mereka.\"", 30);
    delayPrint(L"Kinich: (Menerima kotak itu tanpa banyak bicara, tapi matanya menatap Weiss dengan lebih lembut) \"Tidak perlu repot-repot, Tuan Muda. Tapi... terima kasih.\"", 30);
    delayPrint(L"Weiss: \"Saya dengar dari salah satu mandor, ada masalah dengan pasokan lampu karbit baru-baru ini? Beberapa penambang mengeluh pencahayaan di lorong semakin redup dan berbahaya.\"", 30);
    delayPrint(L"Kinich: (Menghela napas berat) \"Benar. Kiriman terakhir kualitasnya buruk, cepat habis dan cahayanya tidak terang. Sudah saya laporkan ke manajemen di kota, tapi responsnya seperti biasa, 'sedang diproses'. Sementara itu, anak buah saya yang menanggung risikonya di bawah sana.\"", 30);
    delayPrint(L"Weiss: \"Ini tidak bisa dibiarkan. Keselamatan mereka harus jadi prioritas. Saya akan menghubungi langsung pemasok peralatan tambang yang biasa bekerja sama dengan keluarga Astra. Saya akan pastikan kiriman lampu karbit berkualitas tinggi segera datang ke sini dalam beberapa hari. Saya yang akan menanggung biayanya jika perlu.\"", 30);
    delayPrint(L"Kinich: (Menatap Weiss dengan campuran tak percaya dan... haru?) \"Anda... Anda serius mau melakukan itu, Tuan Muda? Hanya demi beberapa lampu untuk kami? Itu... itu di luar dugaan saya.\"", 30);
    delayPrint(L"Weiss: \"Setiap detail kecil yang menyangkut keselamatan pekerja itu penting, Kinich. Saya tidak mau mendengar ada kecelakaan hanya karena masalah penerangan yang sebenarnya bisa diatasi. Anggap saja ini bagian dari tanggung jawab saya sebagai salah satu pemilik saham.\"", 30);
    delayPrint(L"Kinich: (Tertegun sejenak, lalu ada senyum tulus yang langka terukir di wajahnya yang keras) \"Tuan Muda Weiss... Anda benar-benar... berbeda. Saya tidak tahu harus berkata apa. Atas nama semua penambang di sini, terima kasih. Terima kasih yang sebesar-besarnya. Anda telah menunjukkan kepedulian yang nyata.\"", 30);
    delayPrint(L"Weiss: \"Sama-sama, Kinich. Saya hanya melakukan apa yang benar. Tolong awasi terus kondisi di bawah. Jika ada kebutuhan mendesak lainnya, jangan ragu beritahu saya.\"", 30);
    delayPrint(L"Kinich: \"Akan saya lakukan, Tuan Muda. Dan... ini.\" (Menyodorkan sepotong kecil kristal berwarna biru redup dari sakunya) \"Ini Kristal Biru Penenang. Tidak terlalu berharga, tapi penambang percaya ini bisa membawa ketenangan di tengah kegelapan goa. Anggap saja ini tanda terima kasih kecil dari saya.\"", 30);
    delayPrint(L"Weiss: (Menerima kristal itu) \"Indah sekali, Kinich. Terima kasih. Akan saya simpan baik-baik.\"", 30);
    delayPrint(L"Kinich: \"Jaga diri Anda, Tuan Muda. Dan... hati-hati dengan orang-orang di kota. Tidak semua orang punya niat sebaik Anda.\"", 30);
    delayPrint(L"Sikap Kinich hari ini benar-benar berbeda. Sepertinya tindakan nyata Weiss telah berhasil meluluhkan hatinya yang keras dan membangun jembatan kepercayaan yang kuat.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel6() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 6 ✦ Camp Avernix (Malam di sekitar Api Unggun) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss duduk bersama Kinich dan beberapa penambang senior di sekitar api unggun, berbagi cerita setelah seharian bekerja. Suasana lebih santai dari biasanya.", 30);
    delayPrint(L"Penambang Senior 1: \"...Jadi, Tuan Muda, begitulah ceritanya kami hampir terjebak longsoran di Lorong Sembilan belas tahun lalu. Untung ada Kinich yang memimpin jalan keluar melalui celah sempit yang bahkan tikus pun ragu melewatinya!\", (Tertawa terbahak-bahak).", 30);
    delayPrint(L"Kinich: (Menggerutu pelan) \"kamu melebih-lebihkan, Borin. Celah itu cukup untuk kita semua. Hanya saja kamu terlalu banyak makan roti saat itu.\"", 30);
    delayPrint(L"Weiss: (Tersenyum) \"Kalian semua punya banyak cerita keberanian dan ketahanan yang luar biasa. Saya jadi bertanya-tanya, Kinich, apa yang membuat Anda tetap bertahan dalam pekerjaan berbahaya ini selama bertahun-tahun? Pasti ada banyak godaan untuk mencari pekerjaan yang lebih aman di kota.\"", 30);
    delayPrint(L"Kinich: (Menatap api unggun, pandangannya menerawang) \"Kota... bukan tempat untuk saya, Tuan Muda. Terlalu banyak basa-basi, terlalu banyak kepalsuan. Di sini, di Goa Avernix ini, semuanya nyata. Bahayanya nyata, tapi persaudaraan kami juga nyata. Kami saling menjaga punggung satu sama lain karena nyawa kami bergantung pada itu.\"", 30);
    delayPrint(L"Kinich: \"Selain itu... ada sesuatu tentang goa ini. Sesuatu yang memanggil. Mungkin karena ayah dan kakek saya juga penambang di sini. Rasanya seperti ada ikatan tak kasat mata. Dan terus terang, Tuan Muda, saya khawatir jika bukan orang seperti saya yang menjaga tempat ini, siapa lagi? Banyak orang hanya melihat goa ini sebagai lubang penghasil uang, tanpa peduli pada 'Roh Goa' atau keseimbangan di dalamnya.\"", 30);
    delayPrint(L"Weiss: \"'Roh Goa'? Anda benar-benar mempercayainya? Saya kira itu hanya takhayul untuk menakut-nakuti penambang baru.\"", 30);
    delayPrint(L"Kinich: \"Anda boleh percaya atau tidak, Tuan Muda. Tapi saya sudah melihat terlalu banyak hal aneh di bawah sana yang tidak bisa dijelaskan dengan akal sehat. Suara-suara tanpa wujud, cahaya yang bergerak sendiri, lorong yang tiba-tiba berubah arah... Goa ini punya kehidupannya sendiri. Dan jika kita tidak menghormatinya, dia akan menelan kita bulat-bulat.\"", 30);
    delayPrint(L"Weiss: \"Sebuah perspektif yang menarik, meskipun sedikit... menyeramkan. Apakah Anda pernah merasa benar-benar dalam bahaya besar karena hal-hal 'tak kasat mata' itu?\"", 30);
    delayPrint(L"Kinich: (Menghela napas dalam) \"Pernah sekali. Saya dan tim saya terjebak di lorong yang belum terpetakan. Tiba-tiba semua lampu kami padam serentak, dan kami mendengar suara seperti... bisikan marah dari semua arah. Kami semua berdoa menurut kepercayaan kami masing-masing. Entah bagaimana, setelah beberapa saat yang terasa seperti selamanya, satu lampu menyala kembali, cukup untuk menunjukkan jalan keluar yang sangat sempit yang sebelumnya tidak kami lihat. Sejak saat itu, saya tidak pernah meremehkan kekuatan goa ini.\"", 30);
    delayPrint(L"Weiss: \"Cerita yang membuat bulu kuduk berdiri. Terima kasih sudah mau berbagi pengalaman pribadi seperti ini, Kinich. Ini membuat saya semakin menghargai pekerjaan Anda dan misteri yang menyelimuti Goa Avernix.\"", 30);
    delayPrint(L"Kinich: \"Tidak masalah, Tuan Muda. Anggap saja ini dongeng sebelum tidur versi penambang. Yang penting, Anda sekarang tahu bahwa di balik setiap bongkahan bijih yang Anda lihat, ada cerita dan risiko yang kami hadapi.\"", 30);
    delayPrint(L"Weiss: \"Saya akan selalu mengingatnya. Dan saya akan berusaha memastikan risiko itu bisa diminimalisir sebisa mungkin.\"", 30);
    delayPrint(L"Kinich: (Mengangguk, ada sedikit senyum di wajahnya yang terpapar cahaya api unggun) \"Saya percaya Anda akan melakukannya, Tuan Muda. Saya percaya.\"", 30);
    delayPrint(L"Di bawah langit malam yang dingin, dihangatkan oleh api unggun dan cerita-cerita tambang, kamu merasa semakin dekat dengan Kinich dan para penambang. Ada rasa persaudaraan yang unik di tempat keras ini.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel7() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 7 ✦ Camp Avernix (Kedatangan Peralatan Baru) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Beberapa gerobak besar tiba di Camp Avernix, membawa peralatan keamanan baru: helm yang lebih kuat, lampu karbit berkualitas tinggi, tabung oksigen darurat, dan beberapa alat pendeteksi gas model terbaru. Ini adalah hasil dari lobi Weiss kepada dewan kota dan sebagian menggunakan dana pribadi keluarga Astra.", 30);
    delayPrint(L"Kinich: (Menginspeksi peralatan baru itu dengan mata berbinar, sesuatu yang sangat jarang terlihat) \"Tuan Muda Weiss... Ini... ini semua... saya tidak tahu harus berkata apa. Ini seperti mimpi bagi kami para penambang.\"", 30);
    delayPrint(L"Weiss: \"Ini adalah apa yang seharusnya kalian dapatkan sejak lama, Kinich. Peralatan yang layak untuk pekerjaan seberbahaya ini. Anggap saja ini realisasi dari proposal yang pernah kita diskusikan dan sedikit tambahan dari saya pribadi.\"", 30);
    delayPrint(L"Penambang lain yang berkumpul tampak takjub dan penuh rasa terima kasih.", 30);
    delayPrint(L"Penambang 1: \"Helm ini jauh lebih kuat dari yang lama! Dan lampunya terang sekali!\"", 30);
    delayPrint(L"Penambang 2: \"Dengan alat deteksi gas ini, kita bisa lebih tenang bekerja di lorong dalam! Terima kasih, Tuan Muda!\"", 30);
    delayPrint(L"Kinich: \"Tuan Muda, ini... ini lebih dari yang pernah kami bayangkan. Selama bertahun-tahun kami mengajukan permintaan, tapi selalu hanya janji kosong atau barang bekas berkualitas rendah. Anda... Anda benar-benar menepati janji Anda.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya melakukan apa yang benar, Kinich. Keselamatan kalian adalah yang utama. Sekarang, yang penting adalah memastikan semua penambang mendapatkan pelatihan yang tepat untuk menggunakan peralatan baru ini secara efektif. Apakah Anda sudah punya rencana untuk itu?\"", 30);
    delayPrint(L"Kinich: \"Tentu saja, Tuan Muda. Saya akan segera mengatur jadwal pelatihan per kelompok. Kami akan pastikan semua orang paham cara kerjanya. Ini akan sangat mengurangi angka kecelakaan, saya yakin itu. Anda telah memberikan kami lebih dari sekadar alat, Anda memberi kami rasa aman.\"", 30);
    delayPrint(L"Weiss: \"Itulah tujuan saya. Apakah ada kendala dalam distribusi atau penyimpanan peralatan ini? Saya ingin memastikan semuanya berjalan lancar.\"", 30);
    delayPrint(L"Kinich: \"Tidak ada masalah sama sekali, Tuan Muda. Gudang logistik kami sudah siap. Dan semangat para penambang langsung naik drastis melihat semua ini. Mereka bilang, akhirnya ada 'orang atas' yang benar-benar peduli pada nasib mereka di bawah tanah.\"", 30);
    delayPrint(L"Weiss: \"Saya senang mendengarnya. Tolong sampaikan pada mereka untuk terus bekerja dengan hati-hati dan saling menjaga. Peralatan hanyalah alat, kewaspadaan tetap nomor satu.\"", 30);
    delayPrint(L"Kinich: (Menepuk bahu Weiss dengan rasa hormat yang tulus – sebuah gestur yang tak pernah ia lakukan pada bangsawan lain) \"Akan saya sampaikan, Weiss.\" (Memanggilnya dengan nama tanpa gelar untuk pertama kalinya di depan umum) \"Anda telah mendapatkan rasa hormat kami semua. Bukan karena gelar Anda, tapi karena tindakan Anda. Terima kasih.\"", 30);
    delayPrint(L"Weiss: (Tersenyum) \"Sama-sama, Kinich. Jaga mereka baik-baik.\"", 30);
    delayPrint(L"Melihat wajah para penambang yang penuh harapan dan rasa terima kasih, serta pengakuan tulus dari Kinich, kamu merasa semua usahamu tidak sia-sia. Ini adalah langkah nyata menuju perubahan yang lebih baik.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel8() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 8 ✦ Camp Avernix (Sore Hari, Setelah Insiden Kecil) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Baru saja terjadi insiden kecil di salah satu lorong dangkal – beberapa penambang muda terjebak karena salah menginterpretasikan peta dan mengambil jalan buntu yang rapuh. Kinich dan Weiss (yang kebetulan sedang berkunjung) turut membantu proses evakuasi yang berjalan lancar tanpa korban.", 30);
    delayPrint(L"Kinich: (Menghela napas lega sambil membersihkan debu dari pakaiannya) \"Syukurlah semua anak itu selamat. Mereka masih hijau, terlalu bersemangat dan kurang hati-hati. Ini pelajaran berharga bagi mereka. Dan terima kasih atas bantuan Anda tadi, Weiss. Kehadiran Anda menenangkan mereka.\"", 30);
    delayPrint(L"Weiss: \"Tidak masalah, Kinich. Saya senang bisa membantu. Pengalaman seperti ini memang bisa jadi guru terbaik, meskipun terkadang menakutkan. Apakah sering terjadi penambang baru tersesat atau salah jalur?\"", 30);
    delayPrint(L"Kinich: \"Cukup sering. Goa ini seperti labirin hidup. Peta memang membantu, tapi insting dan pengalaman di lapangan itu yang utama. Saya sendiri pernah mengalami yang lebih buruk saat masih seumuran mereka.\"", 30);
    delayPrint(L"Weiss: \"Oh ya? Cerita seperti apa? Jika Anda tidak keberatan berbagi, tentu saja.\"", 30);
    delayPrint(L"Kinich: (Duduk di atas sebuah peti kayu, menatap ke arah pintu masuk goa yang menganga) \"Dulu sekali, saat saya baru beberapa tahun bekerja, ada seorang teman akrab saya, namanya Kael. Kami seperti saudara. Suatu hari, kami ditugaskan menjelajahi lorong baru yang katanya punya kandungan kristal berkualitas tinggi.\"", 30);
    delayPrint(L"Kinich: \"Kami terlalu bernafsu, masuk terlalu dalam tanpa memperhatikan tanda-tanda alam. Tiba-tiba terjadi gempa susulan, dan lorong di belakang kami runtuh total. Kami terjebak dalam kegelapan total, hanya dengan satu lampu karbit yang hampir habis dan sedikit air.\"", 30);
    delayPrint(L"Weiss: (Mendengarkan dengan saksama, bisa merasakan ketegangan dalam cerita Kinich) \"Itu pasti situasi yang mengerikan. Bagaimana kalian bisa keluar?\"", 30);
    delayPrint(L"Kinich: \"Kami mencoba mencari jalan lain selama berjam-jam, tapi sia-sia. Kael mulai putus asa. Tapi saya teringat ajaran kakek saya, 'Jika tersesat di goa, ikuti aliran udara sekecil apapun'. Dengan sisa tenaga, kami meraba-raba dinding, mencari celah. Akhirnya, setelah hampir seharian, kami merasakan sedikit hembusan angin. Kami mengikutinya, merangkak melalui lorong sempit yang penuh batu tajam, hingga akhirnya kami melihat secercah cahaya dari kejauhan.\"", 30);
    delayPrint(L"Kinich: \"Sayangnya... Kael tidak seberuntung saya. Dia terlalu lemah karena dehidrasi dan luka-lukanya. Dia meninggal dalam pelukan saya beberapa saat sebelum tim penyelamat menemukan kami.\" (Suara Kinich bergetar, matanya menerawang penuh kesedihan).", 30);
    delayPrint(L"Weiss: (Terdiam, merasakan duka yang mendalam dari cerita Kinich) \"Kinich... saya... saya turut berduka cita atas kehilanganmu. Itu pasti pengalaman yang sangat traumatis. Saya tidak bisa membayangkan betapa beratnya itu bagimu.\"", 30);
    delayPrint(L"Kinich: (Menghela napas panjang, berusaha menguasai emosinya) \"Sudah lama sekali, Weiss. Tapi kenangan itu tidak pernah benar-benar hilang. Sejak saat itu, saya bersumpah pada diri sendiri untuk selalu memprioritaskan keselamatan anak buah saya di atas segalanya. Saya tidak ingin ada orang lain yang mengalami apa yang Kael alami, atau apa yang saya rasakan saat itu.\"", 30);
    delayPrint(L"Weiss: \"Dedikasimu pada keselamatan mereka... sekarang saya mengerti dari mana datangnya itu. kamu bukan hanya penjaga, Kinich. kamu adalah pelindung mereka, dengan cara yang sangat personal. Dan Kael... dia pasti bangga melihatmu sekarang.\"", 30);
    delayPrint(L"Kinich: (Menatap Weiss, ada sedikit air mata di sudut matanya yang langsung ia seka dengan kasar) \"Terima kasih, Weiss. Tidak banyak orang yang mau mendengarkan cerita lama seorang penambang. Anda... Anda teman yang baik.\"", 30);
    delayPrint(L"Weiss: \"Kapan saja, Kinich. Kapan saja.\"", 30);
    delayPrint(L"Membagikan cerita yang begitu personal dan menyakitkan adalah tanda kepercayaan yang luar biasa dari Kinich. Kamu merasa hubungan kalian telah mencapai level yang sangat dalam, sebuah persahabatan yang ditempa oleh saling pengertian dan rasa hormat.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel9() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 9 ✦ Camp Avernix & Pintu Masuk Goa (Situasi Krisis) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Sirene darurat tiba-tiba meraung di Camp Avernix. Para penambang berlarian panik. Kinich menghampiri Weiss yang sedang meninjau laporan produksi dengan wajah tegang.", 30);
    delayPrint(L"Kinich: \"Weiss! Ada masalah besar! Terjadi kebocoran gas beracun di Sektor Lima! Beberapa penambang masih terjebak di dalam! Kita harus segera bertindak!\"", 30);
    delayPrint(L"Weiss: \"Gas beracun? Sektor Lima itu cukup dalam, bukan? Berapa banyak orang yang terjebak? Dan apakah kita punya cukup peralatan pelindung?\"", 30);
    delayPrint(L"Kinich: \"Sekitar tujuh atau delapan orang, termasuk mandor senior. Peralatan pelindung kita terbatas, terutama tabung oksigen cadangan setelah pengiriman terakhir belum juga datang dari kota karena masalah administrasi sialan itu! Kita butuh bantuan secepatnya!\"", 30);
    delayPrint(L"Weiss: \"Tenang, Kinich. Panik tidak akan membantu. Segera kumpulkan semua tim penyelamat yang ada dan peralatan pelindung yang tersedia. Saya akan segera menghubungi Balai Kota dan markas keluarga Astra di Arcadia untuk mengirimkan bantuan medis darurat dan pasokan tabung oksigen tambahan menggunakan jalur komunikasi prioritas. Ini akan lebih cepat daripada menunggu prosedur normal.\"", 30);
    delayPrint(L"Kinich: \"Anda bisa melakukan itu? Jalur prioritas? Itu akan sangat membantu! Sementara menunggu, tim saya akan mencoba masuk melalui jalur ventilasi alternatif untuk mencapai mereka dan memberikan tabung oksigen yang kita punya. Tapi itu sangat berisiko.\"", 30);
    delayPrint(L"Weiss: \"Lakukan apa yang harus kamulakukan untuk mencapai mereka dengan aman, Kinich. Aku percaya pada keahlianmu. Aku akan urus birokrasi di kota. Berapa lama perkiraan timmu bisa mencapai mereka melalui jalur ventilasi?\"", 30);
    delayPrint(L"Kinich: \"Mungkin satu atau dua jam jika tidak ada halangan. Jalurnya sempit dan belum sepenuhnya stabil. Saya akan memimpin tim itu sendiri. Anda fokus pada bantuan dari kota.\"", 30);
    delayPrint(L"Weiss: \"Baik. Segera berangkat. Aku akan terus berkoordinasi denganmu melalui radio ini.\" (Menyerahkan radio komunikasi khusus). \"Gunakan frekuensi darurat keluarga Astra. Itu akan menembus gangguan sinyal di bawah sana. Jaga dirimu dan timmu, Kinich. Nyawa mereka ada di tanganmu.\"", 30);
    delayPrint(L"Kinich: (Menggenggam radio itu erat, menatap Weiss dengan campuran tekad dan rasa terima kasih) \"Saya mengerti, Weiss. Saya tidak akan mengecewakanmu, atau anak buah saya. Terima kasih... atas segalanya. Anda benar-benar berbeda dari yang pernah saya bayangkan.\"", 30);
    delayPrint(L"Weiss: \"Tidak ada waktu untuk itu sekarang. Selamatkan mereka, Kinich. Itu yang terpenting. Aku akan pastikan bantuan datang secepat kilat.\"", 30);
    delayPrint(L"Kinich: \"Siap!\" (Berlari memimpin timnya menuju pintu masuk goa).", 30);
    delayPrint(L"Weiss segera menggunakan otoritasnya untuk menghubungi pihak-pihak terkait di Arcadia, memotong jalur birokrasi dan memastikan bantuan darurat segera dikirim. Beberapa jam kemudian, berkat koordinasi yang baik antara tim Kinich di dalam goa dan bantuan yang cepat datang dari kota, semua penambang yang terjebak berhasil dievakuasi dengan selamat, meskipun beberapa mengalami keracunan ringan.", 30);
    delayPrint(L"Kinich: (Menghampiri Weiss yang menunggu dengan cemas di Camp Avernix, wajahnya kotor dan lelah tapi ada kelegaan besar) \"Semua... semua selamat, Weiss. Berkat kamu... berkat tindakan cepatmu. Bantuan dari kota datang tepat pada waktunya. Tabung oksigen tambahan itu menyelamatkan banyak nyawa.\"", 30);
    delayPrint(L"Weiss: (Menghela napas lega) \"Syukurlah, Kinich. Ini kerja tim. kamu dan anak buahmu yang mempertaruhkan nyawa di bawah sana. Aku hanya membantu dari sini. Bagaimana kondisi mereka sekarang?\"", 30);
    delayPrint(L"Kinich: \"Beberapa masih dirawat tim medis, tapi dokter bilang mereka akan pulih. Hari ini... hari ini kita berhasil menghindari tragedi besar. Dan itu semua karena ada seseorang di 'atas' yang akhirnya benar-benar peduli pada kami di 'bawah' sini.\"", 30);
    delayPrint(L"Weiss: \"Kita semua adalah bagian dari komunitas yang sama, Kinich. Keselamatan setiap individu itu penting. Istirahatlah. kamu pantas mendapatkannya.\"", 30);
    delayPrint(L"Kinich: (Menepuk bahu Weiss dengan erat) \"kamu juga, Weiss. kamu juga. kamu telah membuktikan dirimu lebih dari sekadar bangsawan. kamu adalah pemimpin sejati.\"", 30);
    delayPrint(L"Dalam situasi krisis, kalian berdua telah menunjukkan kemampuan untuk bekerja sama secara efektif, saling mempercayai, dan mengambil keputusan sulit. Ikatan kalian kini bukan hanya persahabatan, tapi juga kemitraan yang teruji dalam menghadapi bahaya.", 30);

    printLine();
    waitForEnter();
}

void sceneKinichLevel10() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Kinich - Penjaga Tambang ✦ Level 10 ✦ 'Jantung Goa' Avernix (Area Kristal Tersembunyi) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Beberapa waktu setelah insiden kebocoran gas, Kinich mengajak Weiss ke sebuah bagian goa yang sangat dalam dan jarang dijamah, yang hanya diketahui oleh para penjaga tambang paling senior.", 30);
    delayPrint(L"Kinich: \"Hati-hati melangkah, Weiss. Jalur ini tidak ada di peta resmi. Hanya sedikit dari kami yang tahu tempat ini. Saya ingin menunjukkan sesuatu padamu sebagai rasa terima kasih atas semua yang telah kamu lakukan untuk kami.\"", 30);
    delayPrint(L"Weiss: (Mengikuti Kinich dengan hati-hati, hanya diterangi oleh lampu karbit mereka) \"Ke mana kamu akan membawaku, Kinich? Ini terasa seperti petualangan sungguhan. Apakah ini aman?\"", 30);
    delayPrint(L"Kinich: \"Relatif aman jika kamu tahu jalannya. Dan ya, ini adalah petualangan.\" (Tersenyum tipis). Setelah melewati lorong sempit dan turunan yang curam, mereka tiba di sebuah gua besar yang dindingnya dipenuhi kristal-kristal berwarna-warni yang berpendar dengan cahaya redup, menciptakan pemandangan yang luar biasa indah dan magis.", 30);
    delayPrint(L"Weiss: (Ternganga takjub) \"Demi para Dewa... Kinich... tempat apa ini? Ini... ini seperti surga tersembunyi di perut bumi! Belum pernah aku melihat kristal seindah dan sebanyak ini!\"", 30);
    delayPrint(L"Kinich: (Menatap sekeliling dengan bangga) \"Kami menyebutnya 'Jantung Goa', Weiss. Tempat ini adalah sumber kehidupan dan energi Goa Avernix, menurut kepercayaan para tetua kami. Kristal-kristal ini bukan untuk ditambang. Mereka adalah penjaga keseimbangan goa ini. Hanya sedikit orang yang pernah melihatnya secara langsung.\"", 30);
    delayPrint(L"Weiss: \"Mengapa... mengapa kamu menunjukkannya padaku, Kinich? Ini pasti rahasia besar bagi kalian.\"", 30);
    delayPrint(L"Kinich: \"Karena kamu telah membuktikan dirimu sebagai sahabat sejati para penambang dan pelindung Goa Avernix, Weiss. kamu telah menunjukkan kepedulian yang melampaui keuntungan materi. kamu telah mempertaruhkan dirimu demi kami. Bagi kami, itu menjadikanmu bagian dari 'keluarga' goa ini.\"", 30);
    delayPrint(L"Kinich kemudian mengambil sebuah kristal sebesar genggaman tangan yang memancarkan cahaya biru paling terang dari sebuah ceruk.", 30);
    delayPrint(L"Kinich: \"Ini adalah 'Air Mata Avernix'. Legenda mengatakan kristal ini terbentuk dari air mata Roh Penunggu Goa yang berduka atas keserakahan manusia. Tapi bagi kami, ini adalah simbol harapan dan perlindungan. Saya ingin kamu memilikinya, Weiss. Sebagai tanda persahabatan abadi kita, dan sebagai pengingat bahwa bahkan di tempat tergelap sekalipun, selalu ada cahaya keindahan dan harapan.\"", 30);
    delayPrint(L"Weiss: (Menerima kristal itu dengan tangan gemetar, merasakan energi hangat yang mengalir darinya) \"Kinich... aku... aku benar-benar tidak bisa berkata-kata. Ini adalah hadiah paling luar biasa dan paling berarti yang pernah kuterima. Aku bersumpah akan menjaganya dengan segenap jiwaku, seperti aku menjaga kepercayaan yang telah kamu berikan padaku.\"", 30);
    delayPrint(L"Kinich: (Menepuk bahu Weiss dengan erat) \"Aku tahu kamu akan melakukannya, saudaraku. Ingatlah, Weiss, Goa Avernix ini mungkin keras dan berbahaya, tapi dia juga murah hati kepada mereka yang menghormatinya. Dan kami, para penambang dan penjaga, akan selalu menjadi sekutumu, di dalam maupun di luar goa ini. kamu telah mendapatkan kesetiaan kami yang tak tergoyahkan.\"", 30);
    delayPrint(L"Weiss: \"Dan kalian juga telah mendapatkan kesetiaan dan dukunganku selamanya, Kinich. Kita akan terus memastikan bahwa goa ini memberikan kehidupan, bukan mengambilnya. Mungkin kita bisa memulai program eksplorasi yang lebih aman dan bertanggung jawab, dengan memprioritaskan kesejahteraan penambang dan kelestarian goa?\"", 30);
    delayPrint(L"Kinich: (Tertawa terbahak-bahak, suara tawanya menggema di gua kristal itu) \"kamu benar-benar tidak pernah kehabisan ide untuk bekerja ya, Weiss! Tapi aku suka semangatmu itu! Tentu saja! Dengan kamu di sisi kami, aku yakin masa depan Goa Avernix akan jauh lebih cerah! Tapi untuk sekarang... mari kita nikmati keindahan 'Jantung Goa' ini sejenak. Ini adalah momen langka.\"", 30);
    delayPrint(L"Weiss: (Tersenyum, memandang sekeliling dengan takjub) \"kamu benar, Kinich. Sangat benar.\"", 30);
    delayPrint(L"Di tengah keindahan magis 'Jantung Goa', sebuah ikatan persaudaraan yang ditempa oleh bahaya, kepercayaan, dan rasa hormat timbal balik telah mencapai puncaknya. Weiss dan Kinich, dua pria dari dunia yang sangat berbeda, kini bersatu sebagai penjaga dan sahabat Goa Avernix, siap menghadapi masa depan bersama.", 30);

    waitForEnter(L" Kamu telah membentuk ikatan terkuat...... Tekan Enter untuk melihat detailnya");

    if (!socialLinks["Kinich"].completed) { 
        applySocialLinkBonus("Kinich"); 
        socialLinks["Kinich"].completed = true; 
    }

    printLine();
    waitForEnter();
}

void sceneMashaLevel1() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 1 ✦ Taman Norelia, Puncak Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss: (Melihat seorang wanita muda bangsawan dengan pakaian elegan sedang menatap pemandangan kota dari Puncak Arcadia dengan ekspresi dingin dan angkuh. Weiss mendekat dengan sopan) \"Permisi, pemandangan dari sini sungguh menakjubkan, bukan? Saya Weiss von Astra.\"", 30);
    delayPrint(L"Masha: (Menoleh sekilas ke arah Weiss, tatapannya dingin dan menilai, lalu kembali memandang ke kejauhan) \"Pemandangan hanyalah pemandangan, Tuan von Astra. Biasa saja. Apakah ada keperluan mendesak yang membuat Anda merasa perlu mengganggu ketenangan saya?\"", 30);
    delayPrint(L"Weiss: \"Tidak ada yang mendesak, Nona... maaf, saya belum tahu nama Anda. Saya hanya berpikir untuk memulai percakapan ringan. Jarang bertemu sesama bangsawan di tempat setenang ini.\"", 30);
    delayPrint(L"Masha: \"Masha. Masha von Aurora. Dan saya lebih suka menikmati ketenangan ini sendirian, jika Anda tidak keberatan. Saya datang ke sini untuk menjernihkan pikiran, bukan untuk basa-basi.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti, Nona von Aurora. Maafkan kelancangan saya. Saya tidak akan mengganggu lebih lama. Semoga Anda menemukan kejernihan yang Anda cari.\"", 30);
    delayPrint(L"Masha: (Hanya memberikan anggukan singkat tanpa menoleh, seolah Weiss sudah tidak ada lagi di sana).", 30);
    delayPrint(L"Weiss: (Dalam hati) \"Putri Es dari keluarga Aurora rupanya. Sesuai dengan reputasinya. Ini akan jadi interaksi yang... menarik.\"", 30);
    delayPrint(L"Masha: \"Apakah ada hal lain, Tuan von Astra? Atau Anda hanya suka berdiri mematung di dekat orang asing?\", (Nadanya setajam es).", 30);
    delayPrint(L"Weiss: \"Tidak ada, Nona von Aurora. Sekali lagi, permisi.\" (Weiss memutuskan untuk tidak memaksakan diri lebih jauh).", 30);
    delayPrint(L"Masha: \"Hmph.\"", 30);
    delayPrint(L"Pertemuan pertama yang sangat dingin. Masha jelas bukan tipe orang yang mudah didekati. Mendapatkan perhatiannya saja sudah merupakan sebuah pencapaian.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel2() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 2 ✦ Taman Norelia, Puncak Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss kembali ke Taman Norelia beberapa hari kemudian, dan lagi-lagi menemukan Masha di tempat yang sama, sedang membaca sebuah buku bersampul kulit tebal dengan ekspresi serius.", 30);
    delayPrint(L"Weiss: (Berusaha menjaga jarak aman, hanya mengangguk sopan) \"Selamat siang, Nona von Aurora. Semoga hari Anda menyenangkan.\"", 30);
    delayPrint(L"Masha: (Melirik sekilas dari balik bukunya, ekspresinya tidak berubah) \"Siang. Saya harap Anda tidak berencana untuk 'memulai percakapan ringan' lagi hari ini, Tuan von Astra. Saya sedang sibuk.\"", 30);
    delayPrint(L"Weiss: \"Saya tidak akan mengganggu kegiatan membaca Anda, Nona. Saya hanya ingin menikmati udara segar. Kebetulan bunga Azalea di sudut sana sedang mekar dengan indah. Apakah Anda sempat memperhatikannya?\"", 30);
    delayPrint(L"Masha: \"Bunga hanyalah bunga, Tuan von Astra. Keindahannya fana dan tidak banyak berguna. Berbeda dengan pengetahuan dalam buku ini, yang abadi dan mencerahkan.\" (Kembali fokus pada bukunya).", 30);
    delayPrint(L"Weiss: \"Setiap hal punya keindahannya masing-masing, saya rasa. Bahkan yang fana sekalipun bisa memberi inspirasi. Buku apa yang sedang Anda baca, jika saya boleh tahu? Sepertinya sangat menarik perhatian Anda.\"", 30);
    delayPrint(L"Masha: (Menutup bukunya dengan jari sebagai pembatas, menatap Weiss dengan sedikit kesal) \"Apakah rasa ingin tahu Anda tidak ada batasnya, Tuan von Astra? Ini adalah risalah filosofi tentang 'Keseimbangan Kekuasaan dan Moralitas Pemerintahan'. Saya ragu topik seperti ini akan menarik bagi Anda.\"", 30);
    delayPrint(L"Weiss: \"Justru sebaliknya, Nona. Topik itu sangat relevan dengan posisi saya. Mungkin suatu saat kita bisa berdiskusi tentang pandangan filsuf Xantus mengenai hal itu? Saya menemukan beberapa argumennya cukup... problematis.\"", 30);
    delayPrint(L"Masha: (Alisnya sedikit terangkat, ada sebersit keterkejutan yang cepat ia sembunyikan) \"Anda... membaca Xantus? Saya tidak menyangka. Kebanyakan bangsawan seusia Anda lebih tertarik pada pesta dan perburuan.\"", 30);
    delayPrint(L"Weiss: \"Saya mencoba memperluas wawasan saya, Nona. Pesta dan perburuan memang menyenangkan, tapi tidak memberikan jawaban atas pertanyaan-pertanyaan penting dalam hidup.\"", 30);
    delayPrint(L"Masha: \"Hmph. Mungkin Anda tidak sepenuhnya... dangkal seperti yang saya kira. Tapi tetap saja, saya lebih suka membaca dalam ketenangan.\" (Kembali membuka bukunya, namun kali ini ada sedikit keraguan dalam gerakannya).", 30);
    delayPrint(L"Weiss: \"Saya mengerti. Selamat melanjutkan, Nona von Aurora.\"", 30);
    delayPrint(L"Meskipun masih sangat dingin, setidaknya dia tidak langsung mengusirmu. Menyebut Xantus sepertinya sedikit menarik perhatiannya, walau hanya sesaat.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel3() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 3 ✦ Taman Norelia, Puncak Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Saat Weiss sedang menikmati pemandangan, Masha mendekat dengan langkah anggun namun tetap menjaga jarak.", 30);
    delayPrint(L"Masha: \"Tuan von Astra. Mengenai Xantus yang Anda sebutkan tempo hari. Argumen mana yang Anda anggap problematis? Apakah tentang konsepnya mengenai 'Keadilan Ilahiah' yang melegitimasi kekuasaan absolut?\"", 30);
    delayPrint(L"Weiss: (Sedikit terkejut Masha yang memulai percakapan) \"Nona von Aurora. Ya, tepat sekali. Saya merasa konsep itu terlalu menyederhanakan kompleksitas keadilan dan mudah disalahgunakan untuk menindas. Bagaimana menurut Anda?\"", 30);
    delayPrint(L"Masha: \"Xantus menulis dalam konteks zamannya, Tuan von Astra. Di mana stabilitas adalah segalanya. Namun, saya setuju bahwa interpretasi literal atas karyanya bisa berbahaya. Ada filsuf lain, Lady Seraphina, yang menawarkan kritik menarik terhadap Xantus. Pernahkah Anda membacanya?\"", 30);
    delayPrint(L"Weiss: \"Lady Seraphina dari Valoria? 'Dialektika Kepatuhan dan Kebebasan'? Ya, saya sudah membacanya. Argumennya tentang hak individu memang lebih sesuai dengan perkembangan zaman. Tapi bukankah dia juga terlalu idealis dalam beberapa aspek?\"", 30);
    delayPrint(L"Masha: (Untuk pertama kalinya, Weiss melihat secercah senyum tipis di bibir Masha, meskipun cepat menghilang) \"Idealisme adalah kemewahan bagi mereka yang tidak memegang kekuasaan riil, Tuan von Astra. Tapi pemikirannya memberikan alternatif yang menyegarkan. Saya terkejut Anda memiliki pemahaman sejauh ini tentang topik yang... cukup kering bagi kebanyakan orang.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya berusaha memahami dunia di sekitar saya, Nona. Dan terkadang, diskusi dengan orang yang punya perspektif berbeda bisa sangat mencerahkan. Apakah Anda sering membaca risalah filosofi di waktu luang Anda?\"", 30);
    delayPrint(L"Masha: \"Saya menemukan bahwa memahami pemikiran para filsuf besar membantu saya menavigasi... kerumitan interaksi sosial dan politik di kalangan bangsawan. Lebih berguna daripada mendengarkan gosip di pesta dansa.\"", 30);
    delayPrint(L"Weiss: \"Saya setuju sepenuhnya. Gosip memang melelahkan. Mungkin lain kali kita bisa membahas lebih lanjut tentang pandangan Lady Seraphina mengenai etika kepemimpinan? Ada beberapa poinnya yang masih saya pertanyakan.\"", 30);
    delayPrint(L"Masha: (Setelah jeda singkat) \"...Mungkin. Jika saya sedang tidak ada urusan yang lebih mendesak. Jangan salah paham, Tuan von Astra, ini murni diskusi akademis.\" (Nadanya kembali sedikit dingin, seolah menyadari dirinya terlalu 'terbuka').", 30);
    delayPrint(L"Weiss: \"Tentu saja, Nona von Aurora. Murni akademis. Saya menantikannya.\"", 30);
    delayPrint(L"Masha: \"Hmph.\" (Dia berbalik dan kembali ke tempat duduknya yang biasa, membuka bukunya).", 30);
    delayPrint(L"Sebuah kemajuan besar! Masha tidak hanya memulai percakapan, tapi juga terlibat dalam diskusi intelektual. Dinding esnya mungkin mulai retak, meskipun sangat perlahan.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel4() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 4 ✦ Taman Norelia, Puncak Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss melihat Masha sedang berdiri di dekat hamparan bunga Edelweiss langka yang tumbuh di salah satu sudut tersembunyi Taman Norelia. Dia tampak sedang mengamati bunga itu dengan intensitas yang tidak biasa.", 30);
    delayPrint(L"Weiss: (Menghampiri dengan hati-hati) \"Bunga yang indah, bukan, Nona von Aurora? Saya dengar Edelweiss ini hanya tumbuh di tempat-tempat tinggi dan sulit dijangkamu. Keberadaannya di sini cukup istimewa.\"", 30);
    delayPrint(L"Masha: (Menoleh, sedikit terkejut karena tidak menyadari kehadiran Weiss) \"Tuan von Astra. Anda lagi. Ya, Edelweiss memang bunga yang unik. Simbol ketahanan dan kemurnian. Tidak banyak yang menghargai keberadaannya yang sederhana namun kuat.\"", 30);
    delayPrint(L"Weiss: \"Anda tampak sangat memahaminya. Apakah Anda punya pengetahuan khusus tentang botani? Saya perhatikan cara Anda mengamati bunga ini berbeda dari sekadar menikmati keindahannya.\"", 30);
    delayPrint(L"Masha: (Ada sedikit keraguan di matanya sebelum menjawab) \"Saya... memiliki sedikit ketertarikan pada herbologi dan khasiat tanaman. Edelweiss, misalnya, selain keindahannya, ekstraknya dipercaya memiliki sifat anti-penuaan dan melindungi dari radikal bebas. Pengetahuan yang cukup berguna, bukan?\"", 30);
    delayPrint(L"Weiss: \"Sangat berguna dan sangat menarik! Saya tidak tahu Edelweiss punya khasiat seperti itu. Apakah keluarga Aurora memiliki tradisi dalam mempelajari herbologi? Atau ini murni minat pribadi Anda?\"", 30);
    delayPrint(L"Masha: (Mengalihkan pandangannya kembali ke bunga) \"Ini hanya hobi pribadi, Tuan von Astra. Sesuatu untuk mengisi waktu luang selain membaca buku-buku berat. Tidak semua hal harus selalu terkait dengan tradisi keluarga atau politik, bukan?\"", 30);
    delayPrint(L"Weiss: \"Anda benar sekali. Terkadang hobi pribadi adalah tempat kita menemukan diri kita yang sesungguhnya. Jika Anda tidak keberatan, mungkin suatu saat Anda bisa berbagi lebih banyak tentang tanaman menarik lainnya di taman ini? Saya yakin banyak yang punya cerita atau khasiat tersembunyi.\"", 30);
    delayPrint(L"Masha: \"Saya tidak melihat alasan mengapa saya harus melakukannya.\" (Nadanya kembali dingin, namun ada sedikit nada defensif yang tidak biasa). \"Pengetahuan adalah kekuatan, Tuan von Astra. Tidak untuk dibagikan sembarangan.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti maksud Anda, Nona. Tapi terkadang, berbagi pengetahuan justru bisa memperkaya, bukan mengurangi. Namun, saya hormati keputusan Anda.\" (Memberikan senyum tipis).", 30);
    delayPrint(L"Masha: (Tertegun sejenak oleh respons Weiss yang tidak memaksa, lalu membuang muka) \"Saya harus pergi. Ada urusan lain.\" (Berlalu dengan cepat).", 30);
    delayPrint(L"Weiss: \"Hati-hati di jalan, Nona von Aurora.\"", 30);
    delayPrint(L"Meskipun dia kembali menarik diri, kamu berhasil melihat sekilas minat tersembunyinya. Ada lebih banyak hal dalam diri Putri Es ini daripada yang terlihat di permukaan.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel5() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 5 ✦ Taman Norelia, Puncak Arcadia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Masha sedang duduk di bangku taman, membaca surat bersampul lambang keluarga Aurora dengan ekspresi yang lebih tegang dari biasanya. Weiss yang kebetulan lewat, ragu sejenak sebelum memutuskan untuk menyapa.", 30);
    delayPrint(L"Weiss: \"Nona von Aurora, selamat sore. Maaf jika mengganggu, tapi Anda terlihat... sedikit kurang baik hari ini. Apakah ada masalah?\"", 30);
    delayPrint(L"Masha: (Mendongak kaget, buru-buru melipat surat itu dan memasukkannya ke dalam tasnya. Ekspresi dinginnya kembali terpasang, meski ada sedikit jejak keresahan di matanya) \"Tuan von Astra. Urusan saya bukan urusan Anda. Seperti biasa, Anda terlalu ingin tahu.\"", 30);
    delayPrint(L"Weiss: \"Saya tidak bermaksud ikut campur, Nona. Hanya saja, sebagai sesama... yah, bangsawan, saya tahu terkadang kita menerima surat yang isinya kurang menyenangkan atau membawa beban tanggung jawab yang berat. Jika Anda butuh seseorang untuk sekadar mengalihkan pikiran, saya ada di sini.\"", 30);
    delayPrint(L"Masha: (Menatap Weiss lama, menilai ketulusan dalam kata-katanya) \"Beban tanggung jawab, katamu? Apa yang seorang von Astra yang terkenal 'malas' dan 'tidak peduli' tahu tentang beban tanggung jawab?\" (Nadanya sinis, tapi ada sedikit nada ingin menguji).", 30);
    delayPrint(L"Weiss: (Menghela napas, memutuskan untuk sedikit lebih terbuka) \"Reputasi saya memang mendahului saya, Nona. Dan saya akui, sebagian besar benar adanya... dulu. Tapi orang bisa berubah. Dan saya sedang berusaha memikul tanggung jawab yang selama ini saya abaikan. Percayalah, tekanan dari keluarga dan ekspektasi publik itu... nyata, tidak peduli seberapa tebal tembok mansion kita.\"", 30);
    delayPrint(L"Masha: (Tertegun mendengar kejujuran Weiss. Ada sesuatu dalam nada suaranya yang membuatnya terdiam sejenak) \"...Setidaknya Anda mengakuinya. Kebanyakan bangsawan terlalu angkuh untuk mengakui kelemahan atau kesalahan masa lalu mereka. Surat ini... ya, ini berkaitan dengan perjodohan yang diatur keluarga. Sesuatu yang sangat... kuno dan menyebalkan.\", (Dia mengucapkan kalimat terakhir dengan nada rendah, hampir seperti bergumam pada diri sendiri).", 30);
    delayPrint(L"Weiss: \"Perjodohan. Saya turut... bersimpati. Itu memang salah satu 'kemewahan' yang seringkali tidak kita miliki sebagai bangsawan, kebebasan untuk memilih pasangan hidup. Apakah... apakah calonnya seseorang yang tidak Anda sukai?\"", 30);
    delayPrint(L"Masha: (Mendengus pelan) \"Saya bahkan belum pernah bertemu dengannya. Ini murni aliansi politik antara keluarga Aurora dan keluarga Ruberius dari Utara. Mereka hanya melihat saya sebagai aset, bukan sebagai individu. Sangat... menghinakan.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti perasaan itu. Perasaan menjadi bidak catur dalam permainan orang lain. Saya tidak bisa menawarkan solusi, Nona. Tapi saya bisa menawarkan telinga untuk mendengar, jika Anda merasa perlu meluapkan kekesalan Anda pada sistem yang terkadang tidak adil ini.\"", 30);
    delayPrint(L"Masha: (Menatap Weiss lagi, kali ini dengan ekspresi yang lebih lembut, meskipun masih dijaga) \"...Terima kasih, Tuan von Astra. Mungkin... mungkin lain kali. Untuk saat ini, saya hanya ingin sendirian. Tapi... tawaran Anda... saya hargai.\"", 30);
    delayPrint(L"Weiss: \"Kapan saja, Nona von Aurora. Saya harap Anda bisa menemukan sedikit ketenangan di taman ini.\"", 30);
    delayPrint(L"Masha: \"Saya juga berharap begitu.\"", 30);
    delayPrint(L"Ini adalah pertama kalinya Masha menunjukkan sedikit sisi rentannya padamu. Meskipun singkat dan dia langsung menarik diri, kamu merasa ada kemajuan besar. Beban menjadi bangsawan ternyata adalah sesuatu yang bisa kalian 'bagikan', meski hanya dalam diam.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel6() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 6 ✦ Taman Norelia (Dekat Air Mancur Tersembunyi) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss berjalan menuju bagian taman yang lebih jarang dikunjungi, dekat sebuah air mancur kecil yang tersembunyi di balik rimbunnya pepohonan. Samar-samar ia mendengar suara Masha, bukan nada dingin yang biasa, tapi nada yang lebih... bersemangat, berbicara dengan seorang pelayan wanitanya.", 30);
    delayPrint(L"Masha: (Tidak menyadari kehadiran Weiss) \"...dan bayangkan, Livia! Jika kita bisa mengembangbiakkan jenis Anggrek Bulan Salju itu di iklim Arcadia, nilainya akan sangat tinggi! Aku sudah membaca semua jurnal penelitiannya, teknik penyerbukannya memang rumit, tapi bukan tidak mungkin! Ini bisa jadi proyek botani yang revolusioner!\"", 30);
    delayPrint(L"Pelayan Livia: \"Anda memang selalu punya ide-ide cemerlang, Nona Masha. Tapi apakah Tuan Besar von Aurora akan menyetujui proyek yang 'tidak biasa' ini?\"", 30);
    delayPrint(L"Masha: \"Ayah... yah, dia mungkin akan menganggapnya buang-buang waktu. Dia lebih suka aku fokus pada pelajaran etiket dan mempersiapkan diri untuk... ah, sudahlah. Tapi aku yakin, jika aku bisa membuktikan nilai komersial dan ilmiahnya...\"", 30);
    delayPrint(L"Weiss: (Sengaja membuat sedikit suara agar kehadirannya diketahui) \"Permisi, Nona von Aurora. Maaf tidak sengaja mendengar. Proyek Anggrek Bulan Salju? Kedengarannya sangat ambisius dan menarik.\"", 30);
    delayPrint(L"Masha: (Terlonjak kaget, wajahnya langsung kembali dingin dan waspada. Pelayannya segera menunduk hormat) \"Tuan von Astra! Apa yang Anda lakukan di sini? Menguping pembicaraan pribadi orang lain? Sungguh tidak sopan!\"", 30);
    delayPrint(L"Weiss: \"Saya sungguh tidak bermaksud menguping, Nona. Saya hanya sedang berjalan-jalan dan tidak sengaja mendengar antusiasme Anda. Saya minta maaf jika membuat Anda tidak nyaman. Tapi, jika boleh jujur, saya terkesan dengan semangat Anda terhadap proyek botani itu.\"", 30);
    delayPrint(L"Masha: (Pipinya sedikit merona, entah karena marah atau malu) \"Itu... itu hanya selingan. Bukan sesuatu yang serius. Lupakan saja apa yang Anda dengar. Pelayan saya pasti salah bicara.\" (Melirik tajam ke arah Livia).", 30);
    delayPrint(L"Livia: \"M-maafkan saya, Nona Masha, Tuan Muda.\"", 30);
    delayPrint(L"Weiss: \"Saya rasa tidak ada yang salah, Nona. Memiliki gairah terhadap sesuatu, apapun itu, adalah hal yang baik. Saya sendiri sedang mencoba menemukan hal yang benar-benar bisa membuat saya bersemangat. Mungkin Anggrek Bulan Salju itu bisa jadi salah satunya jika Anda bersedia berbagi sedikit tentangnya?\"", 30);
    delayPrint(L"Masha: (Menatap Weiss dengan curiga, mencoba membaca niatnya) \"Saya tidak punya waktu untuk menjelaskan hal-hal sepele kepada Anda, Tuan von Astra. Saya punya banyak urusan yang lebih penting. Permisi.\" (Bergegas pergi, diikuti pelayannya).", 30);
    delayPrint(L"Weiss: (Menghela napas sambil tersenyum tipis) \"Yah, setidaknya aku melihat sisi lainnya hari ini, walau hanya sekilas.\"", 30);
    delayPrint(L"Meskipun dia kembali memasang dinding esnya, kamu tahu sekarang bahwa di balik sikap dingin itu ada gairah dan kecerdasan yang terpendam. Dia bukan hanya sekadar 'Putri Es'.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel7() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 7 ✦ Gazebo Taman Norelia ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Weiss sedang membaca di gazebo ketika Masha datang dan duduk di bangku seberang, juga dengan sebuah buku. Suasana hening sejenak.", 30);
    delayPrint(L"Masha: \"Tuan von Astra. Saya sudah memikirkan diskusi kita tentang Xantus dan Seraphina. Saya menemukan beberapa inkonsistensi dalam argumen Seraphina mengenai 'otonomi absolut individu' jika diterapkan dalam struktur masyarakat yang kompleks. Bagaimana menurut Anda?\"", 30);
    delayPrint(L"Weiss: (Menutup bukunya, senang karena Masha yang memulai) \"Sebuah pengamatan yang menarik, Nona von Aurora. Saya setuju bahwa otonomi absolut bisa berbenturan dengan kebutuhan akan keteraturan sosial. Tapi bukankah keteraturan yang terlalu kaku juga bisa mematikan inovasi dan kebebasan berpikir, seperti yang dikritik Seraphina terhadap sistem yang diidealkan Xantus?\"", 30);
    delayPrint(L"Masha: \"Inovasi tanpa arah bisa berbahaya, Tuan von Astra. Kebebasan berpikir tanpa tanggung jawab bisa melahirkan anarki. Harus ada keseimbangan. Pertanyaannya, siapa yang berhak menentukan titik keseimbangan itu? Apakah negara, seperti kata Xantus, atau individu melalui kontrak sosial, seperti yang diusulkan Seraphina?\"", 30);
    delayPrint(L"Weiss: \"Itulah dilema utamanya. Saya pribadi lebih condong pada kontrak sosial yang dinamis, yang bisa ditinjau ulang seiring perkembangan masyarakat. Kekuasaan negara yang absolut, bahkan jika didasari 'Keadilan Ilahiah', terlalu rentan terhadap penyalahgunaan oleh individu yang memegang kekuasaan tersebut.\"", 30);
    delayPrint(L"Masha: \"Tapi kontrak sosial juga bisa dimanipulasi oleh kelompok mayoritas yang menindas minoritas, atau oleh demagog yang pandai memainkan emosi massa. Setidaknya, konsep 'Keadilan Ilahiah' Xantus, meskipun problematis, mencoba memberikan landasan moral transenden yang tidak bergantung pada opini publik yang mudah berubah.\"", 30);
    delayPrint(L"Weiss: \"Anda ada benarnya. Tidak ada sistem yang sempurna. Mungkin solusinya terletak pada kombinasi keduanya? Sebuah negara yang kuat namun dibatasi oleh hukum yang menjamin hak-hak dasar individu, dan partisipasi publik yang cerdas dalam mengawasi jalannya pemerintahan?\"", 30);
    delayPrint(L"Masha: (Tertegun sejenak, lalu mengangguk pelan) \"Sebuah... sintesis yang menarik, Tuan von Astra. Memadukan stabilitas Xantus dengan dinamisme Seraphina. Saya belum pernah memikirkannya dari sudut pandang itu. Anda... ternyata punya pemikiran yang cukup mendalam, di luar dugaan saya.\"", 30);
    delayPrint(L"Weiss: \"Saya hanya berusaha mencari jawaban, sama seperti Anda, Nona. Dan diskusi seperti ini sangat membantu. Apakah Anda punya rekomendasi buku lain yang membahas topik serupa dari perspektif yang berbeda?\"", 30);
    delayPrint(L"Masha: \"Ada beberapa. 'Republik Utopia' karya Magister Lucian, atau 'Risalah tentang Tirani Kebaikan' oleh Historian Amara. Keduanya menawarkan pandangan yang cukup... provokatif. Mungkin Anda akan tertarik.\"", 30);
    delayPrint(L"Weiss: \"Akan saya cari buku-buku itu. Terima kasih atas rekomendasinya, Nona von Aurora. Dan terima kasih untuk diskusinya. Ini sangat mencerahkan.\"", 30);
    delayPrint(L"Masha: \"Diskusi ini... cukup bisa ditoleransi, Tuan von Astra.\" (Ada sedikit senyum yang sangat tipis, yang langsung ia sembunyikan dengan kembali membuka bukunya).", 30);
    delayPrint(L"Weiss: \"Saya anggap itu pujian tertinggi dari Anda.\" (Tersenyum dalam hati).", 30);
    delayPrint(L"Perdebatan intelektual ini, meskipun masih ada nada formal, menunjukkan adanya rasa hormat timbal balik terhadap kecerdasan masing-masing. Dinding es Masha benar-benar mulai mencair.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel8() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 8 ✦ Taman Norelia (Cuaca Mendung) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Cuaca hari itu mendung, mencerminkan suasana hati Masha yang tampak lebih suram dari biasanya. Dia berdiri sendirian di tepi tebing, memandang ke arah kota yang diselimuti awan kelabu.", 30);
    delayPrint(L"Weiss: (Menghampirinya dengan hati-hati) \"Nona von Aurora? Langit hari ini tampak ikut berduka. Apakah ada sesuatu yang membebani pikiran Anda? Anda terlihat... lebih pendiam dari biasanya.\"", 30);
    delayPrint(L"Masha: (Menoleh, matanya tampak lelah. Dia tidak langsung memasang sikap dinginnya yang biasa) \"Tuan von Astra. Hanya... hari yang melelahkan. Terlalu banyak tuntutan, terlalu banyak ekspektasi yang tidak masuk akal dari keluarga. Terkadang saya merasa seperti boneka pajangan yang hanya boleh tersenyum dan mengangguk.\"", 30);
    delayPrint(L"Weiss: \"Saya mengerti perasaan itu lebih dari yang Anda bayangkan, Masha.\" (Menggunakan namanya tanpa gelar secara refleks, lalu sedikit ragu) \"Maaf... Nona von Aurora. Maksud saya, tekanan menjadi pewaris bangsawan memang terkadang menyesakkan.\"", 30);
    delayPrint(L"Masha: (Tidak mengoreksi panggilan Weiss, hanya menghela napas panjang) \"Ayah saya... beliau baru saja memberitahu bahwa rencana perjodohan saya dengan Pangeran dari Utara itu akan dipercepat. Mereka bahkan tidak bertanya apakah saya setuju atau tidak. Seolah pendapat saya tidak penting sama sekali. Yang mereka pedulikan hanya aliansi dan perluasan pengaruh.\"", 30);
    delayPrint(L"Weiss: \"Itu... sangat tidak adil. Anda berhak menentukan jalan hidup Anda sendiri, termasuk dengan siapa Anda akan menghabiskan sisa hidup Anda. Apakah tidak ada cara untuk menolak atau setidaknya menundanya?\"", 30);
    delayPrint(L"Masha: \"Melawan keinginan Kepala Keluarga Aurora? Itu sama saja dengan bunuh diri sosial, Weiss.\" (Dia juga memanggil nama Weiss tanpa gelar, suaranya terdengar pahit) \"Saya dididik untuk patuh, untuk menjadi 'putri yang baik', untuk mengorbankan kebahagiaan pribadi demi 'kebaikan keluarga'. Sangat munafik, bukan?\"", 30);
    delayPrint(L"Weiss: \"Sangat munafik. Dan sangat menyedihkan. Tapi, Masha, Anda adalah wanita yang cerdas dan kuat. Saya sudah melihatnya. Pasti ada sesuatu yang bisa Anda lakukan. Mungkin... mencari sekutu di dalam keluarga Anda? Atau menunjukkan bahwa Anda punya nilai lebih dari sekadar 'alat' perjodohan? Proyek Anggrek Bulan Salju Anda, misalnya?\"", 30);
    delayPrint(L"Masha: (Menatap Weiss, ada secercah harapan di matanya yang redup) \"Proyek anggrek itu... Ayah menganggapnya mainan anak kecil. Tapi... Anda benar. Mungkin jika saya bisa membuktikan bahwa saya bisa mandiri secara finansial atau membawa kehormatan bagi keluarga melalui jalur lain... mungkin mereka akan sedikit melunak.\"", 30);
    delayPrint(L"Weiss: \"Itu patut dicoba. Dan jika Anda butuh dukungan, baik itu koneksi, sumber daya, atau sekadar teman untuk berdiskusi strategi, saya siap membantu. Anda tidak sendirian dalam hal ini, Masha.\"", 30);
    delayPrint(L"Masha: (Untuk pertama kalinya, dia menatap Weiss dengan tatapan yang benar-benar terbuka, tanpa dinding es. Ada kerapuhan, tapi juga secercah tekad) \"...Kenapa Anda mau membantu saya, Weiss? Apa untungnya bagi Anda?\"", 30);
    delayPrint(L"Weiss: \"Karena saya tahu bagaimana rasanya terkurung dalam sangkar emas, Masha. Dan karena saya percaya setiap orang berhak memperjuangkan kebahagiaannya. Anggap saja... saya ingin melihat 'Putri Es' ini akhirnya bisa tersenyum tulus karena pilihannya sendiri.\"", 30);
    delayPrint(L"Masha: (Tertegun, lalu sebuah senyum yang sangat tipis namun tulus terukir di bibirnya) \"...Terima kasih, Weiss. Kata-kata Anda... sangat berarti. Saya... saya akan memikirkannya. Terima kasih sudah mau mendengarkan.\"", 30);
    delayPrint(L"Weiss: \"Kapan saja, Masha. Kapan saja.\"", 30);
    delayPrint(L"Momen kerentanan ini, di mana Masha membagikan beban hatinya dan Weiss menawarkan dukungan tulus, menjadi titik balik penting dalam hubungan kalian. Dinding es itu benar-benar mulai runtuh.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel9() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 9 ✦ Taman Norelia (Setelah Badai Kecil) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Badai semalam telah merusak sebagian kecil Taman Norelia. Beberapa pot bunga pecah dan ranting pohon berserakan. Weiss melihat Masha sedang sendirian, dengan hati-hati mencoba menegakkan kembali sebatang tanaman mawar langka yang batangnya patah.", 30);
    delayPrint(L"Weiss: (Menghampirinya) \"Masha, hati-hati. Batang itu terlihat rapuh. Perlu bantuan? Saya membawa beberapa tali dan penyangga dari pos jaga taman.\"", 30);
    delayPrint(L"Masha: (Menoleh, wajahnya sedikit kotor terkena tanah, tapi ekspresinya penuh tekad) \"Weiss. Terima kasih. Saya tidak tahu harus mulai dari mana. Mawar ini... ini adalah varietas 'Aurora Dawn', sangat langka dan berharga bagi saya. Saya khawatir dia tidak akan selamat.\"", 30);
    delayPrint(L"Weiss: \"Kita akan coba selamatkan bersama. Saya pernah membaca beberapa teknik grafting dan perbanyakan tanaman. Mungkin kita bisa menyambungnya, atau setidaknya mengambil stek untuk ditanam kembali jika bagian utamanya tidak bisa diselamatkan.\"", 30);
    delayPrint(L"Mereka berdua bekerja bersama dalam diam namun penuh konsentrasi, membersihkan area sekitar mawar, memasang penyangga, dan dengan hati-hati mencoba menyatukan kembali batang yang patah dengan balutan kain dan tali.", 30);
    delayPrint(L"Masha: \"Anda... tahu banyak tentang tanaman juga rupanya, Weiss. Saya kira minat Anda hanya pada buku-buku filosofi berat.\", (Ada nada menggoda yang tidak biasa dalam suaranya).", 30);
    delayPrint(L"Weiss: (Tersenyum) \"Saya punya banyak minat tersembunyi, Masha. Sama seperti Anda dengan herbologi dan Anggrek Bulan Salju itu. Bagaimana kabar proyek itu, ngomong-ngomong? Apakah ada kemajuan?\"", 30);
    delayPrint(L"Masha: \"Berkat beberapa jurnal penelitian yang Anda bantu carikan dari perpustakaan keluarga Astra, saya menemukan metode baru untuk aklimatisasi bibitnya. Sudah ada beberapa yang mulai menunjukkan tanda-tanda pertumbuhan positif. Saya... saya sangat berterima kasih atas bantuan Anda itu, Weiss. Itu sangat berarti.\"", 30);
    delayPrint(L"Weiss: \"Saya senang bisa membantu. Melihat semangat Anda saat membahasnya membuat saya ikut termotivasi. Nah, sepertinya mawar ini sudah cukup stabil untuk sementara. Kita tinggal berharap yang terbaik.\"", 30);
    delayPrint(L"Masha: (Menatap mawar yang sudah ditopang itu, lalu menatap Weiss. Ada kelembutan yang tulus di matanya) \"Terima kasih, Weiss. Bukan hanya untuk mawar ini. Tapi... untuk segalanya. Untuk mau mendengarkan, untuk menawarkan bantuan tanpa pamrih, untuk... melihat saya lebih dari sekadar 'Putri Es'.\"", 30);
    delayPrint(L"Weiss: \"Setiap orang punya sisi hangatnya masing-masing, Masha. Terkadang hanya butuh orang yang tepat untuk melihatnya. Dan saya... saya senang bisa melihat sisi hangat Anda.\" (Memberikan senyum tulus).", 30);
    delayPrint(L"Masha: (Untuk pertama kalinya, dia tidak membuang muka atau menyembunyikan senyumnya. Sebuah senyum yang manis dan tulus, yang membuat wajahnya tampak begitu berbeda dan mempesona) \"Mungkin... mungkin Anda benar, Weiss. Mungkin memang begitu.\"", 30);
    delayPrint(L"Weiss: \"Lain kali, jika ada badai lagi, jangan sungkan meminta bantuan, ya? Dua pasang tangan selalu lebih baik dari satu, terutama untuk menyelamatkan mawar langka.\"", 30);
    delayPrint(L"Masha: (Tertawa kecil, suara tawa yang merdu) \"Akan saya ingat itu. Dan mungkin... setelah ini kita bisa minum teh hangat? Saya yang buatkan. Saya punya campuran herbal spesial yang bisa meredakan lelah.\"", 30);
    delayPrint(L"Weiss: \"Sebuah tawaran yang tidak mungkin saya tolak, Masha.\"", 30);
    delayPrint(L"Di tengah taman yang sedikit porak-poranda, sebuah hubungan yang tadinya dingin kini mekar menjadi sesuatu yang hangat dan tulus. Kalian berdua telah menemukan kenyamanan dan dukungan satu sama lain.", 30);

    printLine();
    waitForEnter();
}

void sceneMashaLevel10() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ Masha - Putri Bangsawan Aurora ✦ Level 10 ✦ Taman Norelia (Festival Bunga Tahunan) ✦✦✦");
    printLine();
    wcout << endl;

    delayPrint(L"Taman Norelia hari itu sangat ramai. Festival Bunga Tahunan sedang berlangsung, dan Masha, secara mengejutkan, menjadi salah satu panitia utama yang mengurus paviliun tanaman langka dan eksotis, termasuk beberapa Anggrek Bulan Salju hasil percobaannya yang mulai mekar.", 30);
    delayPrint(L"Weiss: (Menghampiri Masha yang sedang sibuk memberikan penjelasan kepada beberapa pengunjung bangsawan) \"Paviliun Anda luar biasa, Masha! Anggrek Bulan Salju itu... benar-benar memukamu! Anda berhasil!\"", 30);
    delayPrint(L"Masha: (Menoleh, senyum bangga dan bahagia terpancar di wajahnya. Dia tidak lagi terlihat dingin, melainkan penuh percaya diri dan antusiasme) \"Weiss! Terima kasih! Ini semua juga berkat dukungan dan masukan dari Anda! Lihat, mereka mekar dengan sempurna! Ayah saya bahkan datang tadi dan... beliau terlihat cukup terkesan!\"", 30);
    delayPrint(L"Weiss: \"Saya tidak ragu beliau akan terkesan. Anda telah membuktikan kemampuan dan dedikasi Anda. Bagaimana dengan... perjodohan itu? Apakah ada kabar baik?\"", 30);
    delayPrint(L"Masha: (Senyumnya sedikit meredup, tapi tetap ada ketegasan di sana) \"Setelah melihat kesuksesan paviliun ini dan beberapa proposal bisnis yang saya ajukan terkait budidaya tanaman langka, Ayah setuju untuk... menunda perjodohan itu tanpa batas waktu. Beliau bilang, mungkin saya memang punya 'nilai' lain bagi keluarga Aurora selain menjadi istri Pangeran Utara.\" (Mengedipkan mata).", 30);
    delayPrint(L"Weiss: \"Itu berita terbaik yang saya dengar hari ini, Masha! Saya ikut bahagia untuk Anda! Anda berhak mendapatkan kebebasan untuk memilih jalan hidup Anda sendiri!\"", 30);
    delayPrint(L"Masha: \"Dan kebebasan itu sebagian besar karena Anda, Weiss. Anda yang memberi saya keberanian untuk melawan, untuk menunjukkan siapa diri saya sebenarnya. Anda yang percaya pada saya ketika tidak ada orang lain yang melakukannya, bahkan diri saya sendiri pun ragu.\"", 30);
    delayPrint(L"Masha: \"Sebagai tanda terima kasih saya yang tak terhingga, dan sebagai simbol persahabatan kita yang telah tumbuh dari taman ini, saya ingin memberikan ini untuk Anda.\" (Dia mengambil sebuah kotak beludru kecil dari balik meja).", 30);
    delayPrint(L"Di dalamnya, ada sebuah bros perak berbentuk bunga Edelweiss yang dikerjakan dengan sangat halus, dengan sebutir safir kecil di tengahnya yang berkilau seperti mata Masha.", 30);
    delayPrint(L"Masha: \"Edelweiss, simbol ketahanan dan kemurnian. Dan safir, melambangkan kebijaksanaan dan ketulusan. Semoga ini selalu mengingatkan Anda pada Puncak Arcadia, pada Taman Norelia, dan pada... sahabat Anda di sini.\"", 30);
    delayPrint(L"Weiss: (Menerima bros itu dengan penuh haru) \"Masha... ini... ini sangat indah. Lebih dari indah. Ini adalah simbol dari perjalanan luar biasa yang telah kita lalui bersama. Dari Putri Es yang angkuh hingga menjadi wanita kuat dan inspiratif yang berdiri di hadapan saya sekarang. Saya akan memakai ini dengan bangga.\"", 30);
    delayPrint(L"Masha: (Pipinya merona, namun tatapannya mantap dan hangat) \"Dunia bangsawan mungkin penuh dengan kepalsuan dan intrik, Weiss. Tapi persahabatan kita adalah salah satu hal paling nyata dan berharga dalam hidup saya. Ketahuilah, keluarga Aurora, atau setidaknya saya pribadi, akan selalu menjadi sekutu Anda. Apapun yang terjadi.\"", 30);
    delayPrint(L"Weiss: \"Dan keluarga Astra, atau setidaknya saya, juga akan selalu menjadi sekutu dan sahabat Anda, Masha. Mari kita hadapi dunia ini bersama, dengan keberanian dan ketulusan, seperti Edelweiss yang tumbuh di puncak tertinggi.\"", 30);
    delayPrint(L"Masha: (Mengulurkan tangannya) \"Bersama, Weiss. Bersama.\"", 30);
    delayPrint(L"Weiss: (Menjabat tangan Masha dengan erat) \"Bersama.\"", 30);
    delayPrint(L"Di tengah kemeriahan festival, di antara keindahan bunga-bunga yang mekar, sebuah persahabatan yang unik dan kuat telah mencapai puncaknya. Weiss dan Masha, dua jiwa bangsawan yang menemukan koneksi tak terduga, kini siap melangkah maju, saling mendukung, dan mungkin, bersama-sama membawa perubahan positif bagi dunia mereka.", 30);

    waitForEnter(L" Kamu telah membentuk ikatan terkuat...... Tekan Enter untuk melihat detailnya");

    if (!socialLinks["Masha"].completed) { 
        applySocialLinkBonus("Masha"); 
        socialLinks["Masha"].completed = true; 
    }    

    printLine();
    waitForEnter();
}

void showGenericCompanionDialogue(const string& npcName) {
    system("cls");
    printLine();
    centerText(L" berbincang santai dengan " + utf8_to_wstring(npcName) + L" ");
    printLine();
    wcout << endl;

    vector<wstring> dialogues;

    if (npcName == "Ruigerd") {
        dialogues = {
            L"Ruigerd: \"Ah, Tuan Muda Weiss. Ada yang bisa saya bantu di dapur hari ini? Atau hanya ingin secangkir teh hangat?\"",
            L"Ruigerd: \"Pastikan Anda makan dengan cukup, Tuan Muda. Pertarungan ke depan pasti akan berat.\"",
            L"Ruigerd: \"Melihat perkembangan Anda mengingatkan saya pada semangat Tuan Besar Alaric dulu.\"",
            L"Ruigerd: \"Bagaimana kabarmu hari ini, Weiss? Semua baik-baik saja di mansion?\"",
            L"Ruigerd: \"Jangan sungkan meminta apapun jika kamu butuh sesuatu dari dapur, Tuan Muda.\""
        };
    } else if (npcName == "Irene") {
        dialogues = {
            L"Irene: \"Tuan Muda Weiss! Senang melihat Anda lagi. Taman hari ini sangat indah, bukan?\"",
            L"Irene: \"Apakah ada buku baru yang menarik yang sedang Anda baca, Tuan Muda?\"",
            L"Irene: \"Semoga hari Anda menyenangkan, Tuan Muda. Jika butuh sesuatu, jangan ragu panggil saya.\"",
            L"Irene: \"Bunga-bunga mawar ini mengingatkanku padamu, selalu berusaha mekar walau ada duri.\"",
            L"Irene: \"Aku baru saja merapikan beberapa koleksi herbal Nyonya. Aroma mereka menenangkan.\""
        };
    } else if (npcName == "Ella") {
        dialogues = {
            L"Ella: \"Weiss. Ada angin apa kamu mampir? Ada masalah yang butuh 'diselesaikan' atau hanya ingin berbagi cerita?\"",
            L"Ella: \"Guild berjalan seperti biasa. Beberapa petualang baru membuat ulah, tapi tidak ada yang tidak bisa kutangani.\"",
            L"Ella: \"Jangan lupakan kesepakatan kita, partner. Kota ini butuh kita berdua.\"",
            L"Ella: \"Kadang aku berpikir, menjadi bangsawan sepertimu mungkin lebih mudah. Tapi kurasa sama saja rumitnya.\"",
            L"Ella: \"Ada gosip baru dari dunia bawah? Atau kamu hanya ingin kopi pahit kesukaanku?\""
        };
    } else if (npcName == "Charlotte") {
        dialogues = {
            L"Charlotte: \"Weiss! Kebetulan sekali! Aku baru saja dapat gosip panas dari Balai Kota. Mau dengar?\"",
            L"Charlotte: \"Bagaimana investigasimu tentang harga roti di pasar utara? Arcadia Chronicle siap mengangkatnya!\"",
            L"Charlotte: \"Jaga dirimu baik-baik, Weiss. Orang-orang yang kita lawan tidak akan tinggal diam.\"",
            L"Charlotte: \"Kadang aku lelah menjadi wartawan, tapi melihat perubahan positif di kota ini memberiku semangat lagi.\"",
            L"Charlotte: \"Ada berita menarik yang kamu dengar? Atau hanya ingin bertukar pikiran soal artikel berikutnya?\""
        };
    } else if (npcName == "Mars") {
        dialogues = {
            L"Mars: \"Weiss, kawan. Bagaimana kabarmu? Hutan hari ini tenang, pertanda baik.\"",
            L"Mars: \"Jangan lupa untuk sesekali kembali ke hutan, udaranya baik untuk menjernihkan pikiran.\"",
            L"Mars: \"Para penjaga hutan mengirim salam untukmu. Mereka sangat menghargaimu.\"",
            L"Mars: \"Aku melihat jejak Lynx Emas tadi pagi. Pertanda langka.\"",
            L"Mars: \"Ingatlah untuk selalu menghormati alam, maka alam akan menghormatimu kembali.\""
        };
    } else if (npcName == "Kinich") {
        dialogues = {
            L"Kinich: \"Weiss. Ada perlu? Atau hanya ingin memastikan para penambang ini tidak bermalas-malasan?\"",
            L"Kinich: \"Goa Avernix masih menyimpan banyak rahasia. Mungkin suatu saat kita bisa menjelajahinya lagi bersama.\"",
            L"Kinich: \"Ingat pesanku, hati-hati dengan orang licik di kota. Di sini setidaknya bahayanya terlihat jelas.\"",
            L"Kinich: \"Debu tambang hari ini tidak terlalu parah. Mungkin 'Roh Goa' sedang berbaik hati.\"",
            L"Kinich: \"Jangan lupakan dari mana kamu berasal, tapi jangan biarkan itu membatasimu, Weiss.\""
        };
    } else if (npcName == "Masha") {
        dialogues = {
            L"Masha: (Sedikit tersenyum saat melihatmu) \"Weiss. Pemandangan hari ini cukup... menenangkan. Tidak seperti biasanya.\"",
            L"Masha: \"Bagaimana kabar proyek Anggrek Bulan Salju-mu? Milikku menunjukkan perkembangan bagus berkat jurnal darimu.\"",
            L"Masha: \"Jangan terlalu memaksakan diri dengan semua urusan itu. Terkadang, menikmati ketenangan seperti ini juga penting.\"",
            L"Masha: \"Aku sedang membaca risalah filosofi baru. Mungkin kamu tertarik untuk berdiskusi nanti?\"",
            L"Masha: \"Edelweiss di paviliun itu mekar dengan indah hari ini. Mengingatkanku pada sesuatu.\""
        };
    } else {
        dialogues = {
            utf8_to_wstring(npcName) + L": \"Senang bertemu denganmu lagi, Weiss.\"",
            utf8_to_wstring(npcName) + L": \"Bagaimana kabarmu hari ini?\"",
            utf8_to_wstring(npcName) + L": \"Selalu ada hal menarik yang terjadi di Arcadia, bukan?\""
        };
    }

    if (!dialogues.empty()) {
        int randomIndex = rand() % dialogues.size();
        delayPrint(dialogues[randomIndex], 30);
    } else {
        delayPrint(utf8_to_wstring(npcName) + L" tersenyum ramah padamu.", 30);
    }
    wcout << endl;
    waitForEnter();
}


void interactWithNPC(const string& npcName) {
    Companion* pCompanion = nullptr;
    for(auto& comp : companions){
        if(comp.name == npcName){
            pCompanion = &comp;
            break;
        }
    }

    if(!pCompanion || !pCompanion->met){
        delayPrint(L"kamu belum mengenal " + utf8_to_wstring(npcName) + L" dengan baik atau mereka tidak ada di sini.", 20);
        waitForEnter();
        return;
    }

    SocialLink& link = socialLinks[npcName]; 
    int currentSocialLevel = link.currentLevel;

    if (link.completed && currentSocialLevel >= 10) { 
        showGenericCompanionDialogue(npcName); 
        
        return; 
    } else {
        if (talkedToday[npcName]) {
            wcout << L"Kamu sudah berbicara dengan " << utf8_to_wstring(npcName) << L" hari ini untuk meningkatkan hubungan." << endl;
            waitForEnter();
            return;
        }

        wcout << L"Apakah kamu yakin ingin menghabiskan waktu dengan " << utf8_to_wstring(npcName) << L" untuk meningkatkan hubungan? (y/n): ";
        char choice_confirm; 
        cin >> choice_confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (choice_confirm != 'y' && choice_confirm != 'Y') {
            delayPrint(L"Kamu memutuskan untuk tidak berbicara saat ini.", 20);
            waitForEnter();
            return;
        }

        if (currentActionsRemaining <= 0) {
            wcout << L"Kamu tidak punya cukup poin aksi untuk menghabiskan waktu." << endl;
            waitForEnter();
            return;
        }

        consumeAction();
        talkedToday[npcName] = true;
        
        const auto& lockedLevels = socialLinkStories[npcName].lockedLevels;
        if (lockedLevels.count(currentSocialLevel) > 0) {
            wcout << L"Level hubungan dengan " << utf8_to_wstring(npcName) << L" ini terkunci. Selesaikan event cerita tertentu untuk membukanya." << endl;
            waitForEnter();
            return;
        }
        
        if (npcName == "Ruigerd") {
            if (currentSocialLevel == 1) sceneRuigerdLevel1(); else if (currentSocialLevel == 2) sceneRuigerdLevel2(); else if (currentSocialLevel == 3) sceneRuigerdLevel3(); else if (currentSocialLevel == 4) sceneRuigerdLevel4(); else if (currentSocialLevel == 5) sceneRuigerdLevel5(); else if (currentSocialLevel == 6) sceneRuigerdLevel6(); else if (currentSocialLevel == 7) sceneRuigerdLevel7(); else if (currentSocialLevel == 8) sceneRuigerdLevel8(); else if (currentSocialLevel == 9) sceneRuigerdLevel9(); else if (currentSocialLevel == 10) sceneRuigerdLevel10();
        } else if (npcName == "Irene") {
            if (currentSocialLevel == 1) sceneIreneLevel1(); else if (currentSocialLevel == 2) sceneIreneLevel2(); else if (currentSocialLevel == 3) sceneIreneLevel3(); else if (currentSocialLevel == 4) sceneIreneLevel4(); else if (currentSocialLevel == 5) sceneIreneLevel5(); else if (currentSocialLevel == 6) sceneIreneLevel6(); else if (currentSocialLevel == 7) sceneIreneLevel7(); else if (currentSocialLevel == 8) sceneIreneLevel8(); else if (currentSocialLevel == 9) sceneIreneLevel9(); else if (currentSocialLevel == 10) sceneIreneLevel10();
        } else if (npcName == "Ella") {
            if (currentSocialLevel == 1) sceneEllaLevel1(); else if (currentSocialLevel == 2) sceneEllaLevel2(); else if (currentSocialLevel == 3) sceneEllaLevel3(); else if (currentSocialLevel == 4) sceneEllaLevel4(); else if (currentSocialLevel == 5) sceneEllaLevel5(); else if (currentSocialLevel == 6) sceneEllaLevel6(); else if (currentSocialLevel == 7) sceneEllaLevel7(); else if (currentSocialLevel == 8) sceneEllaLevel8(); else if (currentSocialLevel == 9) sceneEllaLevel9(); else if (currentSocialLevel == 10) sceneEllaLevel10();
        } else if (npcName == "Charlotte") {
            if (currentSocialLevel == 1) sceneCharlotteLevel1(); else if (currentSocialLevel == 2) sceneCharlotteLevel2(); else if (currentSocialLevel == 3) sceneCharlotteLevel3(); else if (currentSocialLevel == 4) sceneCharlotteLevel4(); else if (currentSocialLevel == 5) sceneCharlotteLevel5(); else if (currentSocialLevel == 6) sceneCharlotteLevel6(); else if (currentSocialLevel == 7) sceneCharlotteLevel7(); else if (currentSocialLevel == 8) sceneCharlotteLevel8(); else if (currentSocialLevel == 9) sceneCharlotteLevel9(); else if (currentSocialLevel == 10) sceneCharlotteLevel10();
        } else if (npcName == "Mars") {
            if (currentSocialLevel == 1) sceneMarsLevel1(); else if (currentSocialLevel == 2) sceneMarsLevel2(); else if (currentSocialLevel == 3) sceneMarsLevel3(); else if (currentSocialLevel == 4) sceneMarsLevel4(); else if (currentSocialLevel == 5) sceneMarsLevel5(); else if (currentSocialLevel == 6) sceneMarsLevel6(); else if (currentSocialLevel == 7) sceneMarsLevel7(); else if (currentSocialLevel == 8) sceneMarsLevel8(); else if (currentSocialLevel == 9) sceneMarsLevel9(); else if (currentSocialLevel == 10) sceneMarsLevel10();
        } else if (npcName == "Kinich") {
            if (currentSocialLevel == 1) sceneKinichLevel1(); else if (currentSocialLevel == 2) sceneKinichLevel2(); else if (currentSocialLevel == 3) sceneKinichLevel3(); else if (currentSocialLevel == 4) sceneKinichLevel4(); else if (currentSocialLevel == 5) sceneKinichLevel5(); else if (currentSocialLevel == 6) sceneKinichLevel6(); else if (currentSocialLevel == 7) sceneKinichLevel7(); else if (currentSocialLevel == 8) sceneKinichLevel8(); else if (currentSocialLevel == 9) sceneKinichLevel9(); else if (currentSocialLevel == 10) sceneKinichLevel10();
        } else if (npcName == "Masha") {
            if (currentSocialLevel == 1) sceneMashaLevel1(); else if (currentSocialLevel == 2) sceneMashaLevel2(); else if (currentSocialLevel == 3) sceneMashaLevel3(); else if (currentSocialLevel == 4) sceneMashaLevel4(); else if (currentSocialLevel == 5) sceneMashaLevel5(); else if (currentSocialLevel == 6) sceneMashaLevel6(); else if (currentSocialLevel == 7) sceneMashaLevel7(); else if (currentSocialLevel == 8) sceneMashaLevel8(); else if (currentSocialLevel == 9) sceneMashaLevel9(); else if (currentSocialLevel == 10) sceneMashaLevel10();
        } else {
            wcout << L"Data scene untuk " << utf8_to_wstring(npcName) << L" tidak ditemukan.\n";
            waitForEnter();
            return;
        }

        if (link.currentLevel < 10 && !link.completed) { 
            link.currentLevel++;
        }
    }
}

void temporarilyGrantAllMagicToPlayer(Character& playerChar, bool grant) {
    static vector<string> originalKnownSpells_backup; // Ganti nama variabel agar tidak konflik
    static vector<string> originalUnlockedElements_backup;
    static int originalIntBuff_backup = 0; 
    static int originalMagicAttackBuff_backup = 0;
    static int originalMaxMana_backup = 0;
    static int originalMaxHp_backup = 0;


    if (grant) {
        originalKnownSpells_backup = playerChar.knownSpells;
        originalUnlockedElements_backup = playerChar.unlockedMagicElements;
        originalIntBuff_backup = 25; 
        originalMagicAttackBuff_backup = 30;
        originalMaxMana_backup = playerChar.maxMana; // Simpan maxMana asli
        originalMaxHp_backup = playerChar.maxHp;   // Simpan maxHp asli


        playerChar.knownSpells.clear();
        playerChar.unlockedMagicElements.clear();
        
        delayPrint(L"kamu merasakan gelombang energi sihir liar dan tak terbatas melonjak dalam dirimu!", 30);
        delayPrint(L"Semua pengetahuan sihir dari setiap elemen kini terbuka paksa untukmu!", 40);

        for (const auto& pair : allMagicElements) {
            playerChar.unlockedMagicElements.push_back(pair.first);
            for (const auto& spellPair : pair.second.spells) {
                if (spellPair.second.tier <= 2) { 
                    bool alreadyHas = false;
                    for(const string& id : playerChar.knownSpells) if(id == spellPair.first) alreadyHas = true;
                    if(!alreadyHas) playerChar.knownSpells.push_back(spellPair.first);
                }
            }
        }
        playerChar.intelligence += originalIntBuff_backup; 
        playerChar.magicAttack += originalMagicAttackBuff_backup;
        playerChar.maxMana = static_cast<int>(originalMaxMana_backup * 1.8); // Buff Max Mana lebih besar
         if(playerChar.maxMana < 300) playerChar.maxMana = 300; // Minimal Max Mana saat buff
        playerChar.mana = playerChar.maxMana; 
        playerChar.maxHp = static_cast<int>(originalMaxHp_backup * 1.5); // Buff Max HP juga
        playerChar.hp = playerChar.maxHp;

        wcout << L"Kekuatanmu meluap! (Semua Elemen Terbuka, Statistik Ditingkatkan Sementara!)" << endl;

    } else { 
        playerChar.knownSpells = originalKnownSpells_backup;
        playerChar.unlockedMagicElements = originalUnlockedElements_backup;
        playerChar.intelligence -= originalIntBuff_backup; 
        playerChar.magicAttack -= originalMagicAttackBuff_backup;
        playerChar.maxMana = originalMaxMana_backup; // Kembalikan Max Mana
        if(playerChar.mana > playerChar.maxMana) playerChar.mana = playerChar.maxMana;
        playerChar.maxHp = originalMaxHp_backup; // Kembalikan Max HP
        if(playerChar.hp > playerChar.maxHp) playerChar.hp = playerChar.maxHp;
    }
}

void setupBuffedAllainForDuel(Enemy& allainDuelTarget) {
    allainDuelTarget.name = "Allain Ragna, Sang Pahlawan Bersinar";
    allainDuelTarget.level = player.level + 12; 
    allainDuelTarget.maxHp = static_cast<int>(player.maxHp * 3.0 + 700); 
    if (allainDuelTarget.maxHp < 2000) allainDuelTarget.maxHp = 2000;
    allainDuelTarget.hp = allainDuelTarget.maxHp;
    allainDuelTarget.attack = player.strength + 40; 
    allainDuelTarget.defense = player.defense + 25;  
    allainDuelTarget.magicDefense = player.intelligence + 15; 
    allainDuelTarget.isBoss = true;
    allainDuelTarget.enemyType = "Heroic Embodiment"; 

    delayPrint(L"Allain Ragna memegang erat Lumanaire MoonSword. Pedang suci itu bersinar membutakan, memberinya kekuatan fisik yang tak terbayangkan!", 30);
    delayPrint(L"Aura emas murni menyelimutinya. Dia siap menghadapi ancaman terbesar sekalipun!", 40);
}

void triggerDuelAllainRagna() {
    if (storyFlags["duel_persahabatan"] == 0) {
        system("cls");
        printLine();
        centerText(L"⚔ SEBUAH UNDANGAN KE ARENA ⚔");
        printLine();
        wcout << endl;

        delayPrint(L"Suatu pagi yang cerah di Mansion Astra, beberapa hari setelah penjelajahanmu yang semakin intensif,", 30);
        delayPrint(L"seorang pelayan berliveri dari keluarga kerajaan datang membawakan sebuah gulungan perkamen tebal,", 30);
        delayPrint(L"tersegel dengan lambang singa emas kebanggaan Kerajaan Arcadia.", 30);
        wcout << endl;

        delayPrint(L"Dengan sedikit rasa ingin tahu bercampur waspada, kamu membuka segel itu. Isinya adalah sebuah undangan resmi:", 30);
        printLine(70, L'-');
        centerText(L"📜 UNDANGAN KEHORMATAN 📜", 70);
        delayPrint(L"   Kepada Yang Terhormat,", 20);
        delayPrint(L"   Tuan Muda Weiss von Astra,", 20);
        delayPrint(L"   Dengan ini kami mengundang Anda untuk berpartisipasi dalam", 20);
        delayPrint(L"   \"Turnamen Persahabatan Bangsawan Agung Arcadia\"", 20);
        delayPrint(L"   yang akan diselenggarakan di Colosseum Imperial MALAM INI.", 20);
        delayPrint(L"   Kehadiran dan partisipasi Anda akan menjadi kehormatan besar.", 20);
        delayPrint(L"   Salah satu peserta kehormatan yang telah mengkonfirmasi kehadirannya", 20);
        delayPrint(L"   adalah Tuan Muda Allain von Ragna, pahlawan muda kebanggaan kita.", 20);
        delayPrint(L"   Tertanda,", 20);
        delayPrint(L"   Panitia Kerajaan Turnamen Arcadia.", 20);
        printLine(70, L'-');
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk merenungkan undangan ini...");

        system("cls");
        printLine();
        centerText(L"⚡️  PERGOLAKAN BATIN SANG ANTAGONIS ⚡️");
        printLine();
        wcout << endl;

        delayPrint(L"\"Allain von Ragna...\" Nama itu bergema dalam benakmu. Sang protagonis dari novel yang menjebakmu dalam takdir ini.", 30);
        delayPrint(L"Dalam alur cerita asli, Weiss yang sombong dan gegabah menerima undangan serupa, hanya untuk dipermalukan habis-habisan oleh Allain di hadapan para bangsawan.", 30);
        delayPrint(L"Kekalahan itu menjadi salah satu paku pertama di peti mati reputasi dan nasib buruknya.", 30);
        wcout << endl;

        delayPrint(L"Tapi kamu bukan lagi Weiss yang itu. kamu telah berlatih, mempelajari sihir, dan memperkuat dirimu.", 30);
        delayPrint(L"Ini... ini adalah kesempatan emas. Panggung pertama untuk merobek halaman takdir yang telah dituliskan untukmu.", 30);
        delayPrint(L"Mengalahkan Allain Ragna di sini, di duel persahabatan ini, akan menjadi pernyataan kuat.", 30);
        delayPrint(L"Sebuah pernyataan bahwa kamu tidak akan tunduk pada alur cerita sialan itu.", 30);
        wcout << endl;

        delayPrint(L"Jantungmu berdegup sedikit lebih kencang. Secercah kegugupan bercampur dengan api tekad yang membara.", 30);
        delayPrint(L"\"Ini dia...\" bisikmu dalam hati. \"Saatnya mengubah segalanya.\"", 30);
        waitForEnter(L"Tekan Enter untuk mempersiapkan diri menuju Colosseum malam ini...");

        system("cls");
        printLine();
        centerText(L"🏛️  COLOSSEUM IMPERIAL ARCADIA - MALAM HARI 🏛️");
        printLine();
        wcout << endl;

        delayPrint(L"Malam harinya, kamu tiba di Colosseum Imperial Arcadia yang bermandikan cahaya obor.", 30);
        delayPrint(L"Bangunan megah itu menjulang tinggi, saksi bisu berbagai pertarungan legendaris dan perayaan akbar.", 30);
        delayPrint(L"Sorak-sorai penonton sudah terdengar riuh dari dalam, bercampur dengan dentingan musik penyemangat.", 30);
        delayPrint(L"Para bangsawan dari berbagai keluarga terkemuka telah mengambil tempat duduk mereka di tribun kehormatan,", 30);
        delayPrint(L"berpakaian mewah dan berbisik penuh antisipasi di bawah temaram lampu.", 30);
        wcout << endl;

        delayPrint(L"Seorang herald mengumumkan namamu dengan suara lantang:", 30);
        centerText(L"📢 \"Memasuki arena... Tuan Muda WEISS VON ASTRA!!!\" 📢", 70);
        wcout << endl;

        delayPrint(L"kamu melangkah ke tengah arena yang berpasir putih, diterangi oleh puluhan obor yang menyala terang.", 30);
        delayPrint(L"Pandangan mata para penonton tertuju padamu, beberapa penasaran, beberapa meremehkan, mengingat reputasi lamamu.", 30);
        delayPrint(L"kamu mengabaikan mereka. Fokusmu hanya satu.", 30);
        wcout << endl;

        delayPrint(L"Kemudian, sang herald kembali berseru dengan nada yang lebih bersemangat:", 30);
        centerText(L"🌟 \"Dan lawannya... Pahlawan muda kebanggaan Arcadia... ALLAIN VON RAGNA!!!\" 🌟", 70);
        wcout << endl;

        delayPrint(L"Allain Ragna melangkah masuk dengan percaya diri. Rambut pirang keemasannya berkilau memantulkan cahaya obor,", 30);
        delayPrint(L"senyum ramah namun penuh keyakinan terpasang di wajahnya yang tampan.", 30);
        delayPrint(L"Dia adalah perwujudan sempurna sang pahlawan novel. Aura kebaikan dan kekuatan memancar darinya.", 30);
        delayPrint(L"Sorak-sorai penonton semakin membahana menyambut kedatangannya.", 30);
        wcout << endl;
        
        delayPrint(L"kamu merasakan aura yang berbeda dari Allain. Berbeda dari penyihir atau ksatria biasa.", 30);
        delayPrint(L"Rumor mengatakan dia terlahir dengan 'Fisik Surgawi', memberkahinya dengan kekuatan, kecepatan, dan ketahanan fisik yang jauh melampaui manusia normal.", 30);
        delayPrint(L"Karena anugerah ini, dia tidak memiliki bakat dalam sihir ataupun cadangan mana sedikitpun. Seluruh potensinya tercurah pada kesempurnaan ragawi.", 30);
        delayPrint(L"Dia adalah perwujudan puncak dari kekuatan fisik murni.", 30);
        wcout << endl;

        delayPrint(L"Allain menghampirimu, mengulurkan tangan. \"Weiss. Sebuah kehormatan bisa berduel denganmu malam ini. Semoga ini menjadi pertarungan yang adil dan menghibur.\"", 30);
        delayPrint(L"kamu menjabat tangannya. \"Kehormatan ada di pihakku, Allain. Mari kita berikan yang terbaik.\"", 30);
        wcout << endl;

        system("cls");
        printLine();
        centerText(L"⚔ DUEL PERSAHABATAN: WEISS vs ALLAIN RAGNA ⚔");
        printLine();
        delayPrint(L"kamu menatap Allain Ragna, sang pahlawan utama dalam kisah asli, kini berdiri di hadapanmu sebagai lawan.", 30);
        delayPrint(L"Aura percaya dirinya begitu kuat, namun kamu tidak gentar.", 30);
        delayPrint(L"Inilah panggungmu. Inilah waktunya membuktikan bahwa kamu bisa mengalahkan takdirmu.", 30);
        delayPrint(L"Seluruh mata di Colosseum tertuju pada kalian berdua. Pertarungan akan segera dimulai.", 30);
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk memulai duel...");

        Enemy allain;
        if (enemyDatabase.count("Allain Ragna")) { 
            allain = enemyDatabase["Allain Ragna"];
        } else {
            allain.name = "Allain Ragna"; 
        }
        
        allain.level = player.level; 
        allain.maxHp = player.maxHp + 50; 
        allain.hp = allain.maxHp;
        allain.attack = player.strength + 8;   
        allain.defense = player.defense + 5; 
        allain.magicDefense = player.intelligence / 2; 
        allain.expReward = 300; 
        allain.goldDrop = 600;
        allain.isBoss = true;
  
        BattleResult result = startBattle(allain, ""); 

        if (result == ENEMY_DEAD) {
            system("cls");
            printLine();
            centerText(L"🏆 KEMENANGAN BERSEJARAH! 🏆");
            printLine();
            delayPrint(L"Dengan serangan terakhir yang telak, Allain Ragna, sang pemilik Fisik Surgawi, tersungkur!", 50);
            delayPrint(L"Penonton terdiam sesaat, tak percaya, lalu gemuruh sorak-sorai membahana untukmu!", 50);
            delayPrint(L"kamu berhasil! kamu mengalahkan sang protagonis asli dengan kekuatan fisik murninya!", 50);
            delayPrint(L"Sebuah langkah besar telah kamu ambil untuk mengubah alur takdirmu!", 50);
            storyFlags["duel_persahabatan"] = 1; 
            player.exp += 150; 
            player.gold += 300; 
            wcout << endl;
            delayPrint(L"Hadiah Kemenangan: +150 EXP, +300 Gold!", 30);
            delayPrint(L"Reputasimu di kalangan bangsawan mulai berubah...", 30);

        } else if (result == PLAYER_DEAD) { 
            system("cls");
            printLine();
            centerText(L"💔 KEKALAHAN YANG PAHIT 💔");
            printLine();
            delayPrint(L"Meskipun kamu telah berjuang keras, kekuatan 'Fisik Surgawi' Allain Ragna masih terlalu dahsyat.", 50);
            delayPrint(L"kamu terjatuh, dikalahkan di hadapan seluruh bangsawan Arcadia.", 50);
            delayPrint(L"Bisik-bisik cemoohan dan tatapan kasihan terasa menusuk.", 50);
            delayPrint(L"Sepertinya... takdir lamamu masih berusaha mencengkerammu dengan erat.", 50);
            storyFlags["duel_persahabatan"] = 0; 
        }
        waitForEnter(L"Tekan Enter setelah pertarungan usai...");
        
        currentActionsRemaining = 0; 
        advanceToNextDay(); 
    }
}


void triggerInvasiMansion() {
    if (storyFlags["invasi_mansion"] == 0) {
        system("cls");
        printLine();
        centerText(L"💀 INVASI MENGEJUTKAN DI MANSION ASTRA 💀");
        printLine();
        wcout << endl;

        delayPrint(L"Keheningan dini hari di Mansion Astra terkoyak dengan brutal...", 40);
        delayPrint(L"BLAARRR!!! Suara ledakan kaca yang memekakkan telinga, diikuti gemuruh benda jatuh, menggema dari lobi utama!", 50);
        delayPrint(L"kamu tersentak dari lelapmu, naluri waspadamu menjerit. Tanpa ragu, kamu melesat menuju sumber suara.", 40);
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk memeriksa kekacauan...");

        system("cls");
        printLine();
        centerText(L"LOBI MANSION - KEHANCURAN DI BAWAH REMBULAN");
        printLine();
        wcout << endl;

        delayPrint(L"Pemandangan di lobi utama adalah mimpi buruk yang menjadi nyata.", 40);
        delayPrint(L"Atap kaca patri yang megah telah runtuh, serpihannya menghujani lantai marmer yang dulu tak bernoda.", 40);
        delayPrint(L"Debu dan kegelapan menari di bawah sinar bulan yang kini menerobos bebas.", 40);
        delayPrint(L"Dan di episentrum kehancuran itu, berdiri sesosok entitas dari neraka terdalam.", 40);
        wcout << endl;

        delayPrint(L"Sayap kulit raksasa, sehitam jelaga dosa, mengepak perlahan, menebarkan aura dingin yang menusuk tulang.", 30);
        delayPrint(L"Sosoknya jangkung dan ramping, terbalut armor obsidian yang meredam cahaya. Wajahnya bengis, dengan sepasang mata yang menyala merah membara, memancarkan kecerdasan licik dan kekejaman purba.", 30);
        // displayEnemyASCII("AzazelFallenWing"); 

        wcout << endl;

        wstring demonName = L"Azazel, Sang Sayap Jatuh";
        delayPrint(L"Makhluk itu menolehkan kepalanya perlahan ke arahmu, senyum tipis namun penuh arogansi terukir di bibirnya.", 40);
        delayPrint(L"\"Hmm, jadi inikah Weiss von Astra yang berhasil menarik perhatian Tuanku? Penampilanmu tidak terlalu mengesankan, fana.\"", 40);
        delayPrint(L"Suaranya elegan namun menusuk, bagai beludru yang menyembunyikan bilah es.", 30);
        delayPrint(L"\"Aku adalah " + demonName + L", Utusan Khusus dari Sang Penguasa Kegelapan, Raja Iblis yang Agung!\"", 50);
        wcout << endl;

        delayPrint(L"Azazel melangkah anggun di antara puing-puing, \"Pertunjukan kecilmu di Colosseum itu, melawan 'pahlawan' mereka... cukup menggelitik.\"", 40);
        delayPrint(L"\"kamu memiliki... percikan. Sebuah potensi yang menarik, jika saja tidak tersia-siakan di dunia yang fana dan penuh kepalsuan ini.\"", 40);
        delayPrint(L"\"Tuanku, Raja Iblis, melihat benih itu dalam dirimu. Beliau berkenan memberimu kehormatan yang tak terhingga: sebuah tempat di antara para Elitnya.\"", 40);
        delayPrint(L"\"Bayangkan, Weiss von Astra! Kekuatan sejati, keabadian, kesempatan untuk membentuk ulang dunia ini sesuai kehendak yang lebih agung! Tinggalkan cangkang moralitasmu yang rapuh!\"", 50);
        delayPrint(L"\"Bergabunglah dengan kami! Bersujudlah pada Kegelapan, dan kamu akan terlahir kembali!\"", 40);
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk menanggapi tawarannya...");

        system("cls");
        printLine();
        centerText(L"PENOLAKAN YANG BERANI");
        printLine();
        wcout << endl;
        delayPrint(L"kamu menatap Azazel dengan tatapan dingin dan tak gentar. Mansionmu telah dinodai, dan kini jiwamu ditawar.", 40);
        delayPrint(L"Weiss: \"Sujud pada kegelapan? Menjadi pion Raja Iblis? Itu bukan kehormatan, itu adalah perbudakan!\"", 50);
        delayPrint(L"Weiss: \"Tawaranmu menjijikkan. Pergilah dari rumahku, Azazel, sebelum aku yang mengusirmu dengan cara yang lebih menyakitkan!\"", 40);
        wcout << endl;

        delayPrint(L"Ekspresi Azazel mengeras, senyumnya lenyap digantikan tatapan dingin mematikan.", 40);
        delayPrint(L"\"Sungguh pilihan yang... mengecewakan. Namun bisa ditebak dari makhluk serendah dirimu.\"", 50);
        delayPrint(L"\"Jika kebijaksanaan tidak mampu menuntunmu, maka mungkin rasa sakit akan menjadi guru yang lebih baik!\"", 40);
        delayPrint(L"\"Karena kamu telah menolak kemurahan hati Tuanku, maka jiwamu akan menjadi persembahan!\"", 50);
        delayPrint(L"Azazel merentangkan sayapnya sepenuhnya, aura kegelapan meledak darinya, memenuhi lobi dengan tekanan yang menyesakkan. Pertarungan untuk nyawamu dan mansionmu dimulai!", 40);
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk menghadapi Utusan Raja Iblis!");

        Enemy azazel;
        azazel.name = "Azazel the Fallen Wing";
        azazel.level = player.level + 8; 
        azazel.maxHp = static_cast<int>(player.maxHp * 2.8 + 250); 
        if (azazel.maxHp < 600) azazel.maxHp = 600; 
        azazel.hp = azazel.maxHp;
        azazel.attack = player.strength + 25; 
        azazel.defense = player.defense + 15;
        azazel.magicDefense = player.intelligence + 10; 
        azazel.expReward = 800;  
        azazel.goldDrop = 2000; 
        azazel.isBoss = true;
        azazel.enemyType = "Demon";


        BattleResult result = startBattle(azazel, "");

        if (result == ENEMY_DEAD) { 
            system("cls");
            printLine();
            centerText(L"✨ KEMENANGAN ATAS UTUSAN KEGELAPAN ✨");
            printLine();
            delayPrint(L"Dengan perjuangan yang luar biasa dan mengerahkan seluruh kemampuanmu, kamu berhasil mengalahkan " + demonName + L"!", 50);
            delayPrint(L"Tubuh iblis itu menjerit kesakitan sebelum akhirnya hancur menjadi kepulan asap hitam dan menghilang, meninggalkan aroma belerang yang tajam.", 40);
            delayPrint(L"Lobi mansionmu porak-poranda, namun kamu berhasil memukul mundur tangan kiri Raja Iblis.", 40);
            delayPrint(L"Ini adalah kemenangan besar, namun juga peringatan akan ancaman yang jauh lebih mengerikan.", 40);
            storyFlags["invasi_mansion"] = 1; 
            
            int bonusExp = azazel.expReward;
            int bonusGold = azazel.goldDrop;

            player.exp += bonusExp; 
            player.gold += bonusGold; 
            wcout << endl;
            delayPrint(L"Hadiah Kemenangan: +" + to_wstring(bonusExp) + L" EXP, +" + to_wstring(bonusGold) + L" Gold!", 30);
            delayPrint(L"Reputasimu sebagai pelindung Mansion Astra mulai tersebar. Namun, kamu tahu ini baru permulaan...", 30);

        } else if (result == PLAYER_DEAD) { 
            system("cls");
            printLine();
            centerText(L"⚔️ DI AMBANG KEKALAHAN... NAMUN HARAPAN MUNCUL! ⚔️");
            printLine();
            delayPrint(L"Kekuatan " + demonName + L" terlalu dahsyat. Pandanganmu mulai kabur, tubuhmu terasa remuk...", 50);
            delayPrint(L"Azazel mendekat, siap memberikan serangan terakhir. \"Kasihan sekali, manusia kecil. Inilah akhir dari perlawananmu yang sia-sia!\"", 40);
            wcout << endl;
            delayPrint(L"Namun, tepat ketika harapan tampak sirna...", 40);
            delayPrint(L"BRAKK! Pintu utama mansion didobrak!", 30);
            delayPrint(L"Serangkaian teriakan perang dan denting senjata terdengar dari berbagai arah!", 40);
            delayPrint(L"\"UNTUK RAJA DAN ARCADIA! SERANG IBLIS ITU!\"", 30);
            wcout << endl;
            delayPrint(L"Sekelompok Ksatria Kerajaan Elit, bersama beberapa Penyihir Perang bersenjatakan tongkat bercahaya, menyerbu lobi!", 50);
            delayPrint(L"Azazel terkejut. \"Apa-apaan ini?! Beraninya kalian mengganggu perburuanku!\"", 40);
            delayPrint(L"Pertarungan sengit pun terjadi. Para Ksatria mengepung Azazel, sementara para Penyihir melancarkan rentetan sihir pelindung dan serangan cahaya.", 50);
            delayPrint(L"Azazel, meskipun kuat, tampak kewalahan menghadapi serangan terkoordinasi dari segala arah.", 40);
            delayPrint(L"Dengan sebuah jeritan panjang yang membelah udara, tubuh " + demonName + L" akhirnya tertembus oleh tombak cahaya suci, lalu meledak menjadi debu kegelapan.", 60);
            wcout << endl;
            delayPrint(L"Salah satu Ksatria menghampirimu yang terkapar. \"Tuan Muda von Astra! Anda selamat! Kami datang secepat mungkin setelah laporan adanya aktivitas iblis di area ini.\"", 40);
            delayPrint(L"kamu berhasil diselamatkan, namun mansionmu rusak parah, dan kemenangan ini bukan milikmu seorang.", 50);
            delayPrint(L"Ancaman telah diatasi untuk sementara, tetapi kegagalanmu mengalahkan Azazel sendiri meninggalkan rasa pahit.", 40);
            
            storyFlags["invasi_mansion"] = 0; 
            player.hp = 1; 
        }
        waitForEnter();
    }
}

void triggerInvasiArcadia() {
    if (storyFlags["invasi_arcadia"] == 0) {
        system("cls");
        printLine();
        centerText(L"🔥 KOTA ARCADIA DALAM API! 🔥");
        printLine();
        wcout << endl;

        delayPrint(L"Hari itu berjalan seperti biasa, hingga pekikan panik dan suara genderang perang mulai terdengar dari arah Ibukota Arcadia.", 40);
        delayPrint(L"Asap hitam tebal membumbung ke langit, membawa aroma kematian dan kehancuran.", 50);
        delayPrint(L"Seorang pengungsi yang berlari terhuyung-huyung berteriak, \"Iblis! Iblis menyerang Arcadia! Balai Kota... Balai Kota dikepung!\"", 40);
        delayPrint(L"Tidak ada waktu untuk ragu. Sebagai seorang bangsawan dan petarung, kamu tahu tanggung jawabmu.", 30);
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk bergegas ke Balai Kota Arcadia...");

        system("cls");
        printLine();
        centerText(L"BALAI KOTA ARCADIA - MEDAN PEMBANTAIAN");
        printLine();
        wcout << endl;

        delayPrint(L"Apa yang kamu saksikan di depan Balai Kota Arcadia adalah pemandangan neraka di bumi.", 40);
        delayPrint(L"Bangunan-bangunan di sekitar terbakar hebat, memuntahkan api dan asap yang menyesakkan.", 40);
        delayPrint(L"Mayat para ksatria penjaga kota dan warga sipil yang malang bergelimpangan di mana-mana, bersimbah darah.", 40);
        delayPrint(L"Teriakan kesakitan, raungan iblis, dan dentang senjata yang beradu menciptakan simfoni kematian yang mengerikan.", 30);
        delayPrint(L"Di tengah alun-alun depan Balai Kota yang kini menjadi medan pembantaian, berdiri sesosok raksasa mengerikan.", 50);
        wcout << endl;

        delayPrint(L"Dia adalah perwujudan kekuatan brutal. Tubuhnya besar dan berotot kekar, terbungkus armor hitam pekat yang dihiasi paku-paku tajam.", 30);
        delayPrint(L"Sebuah helm bertanduk menutupi sebagian wajahnya, namun sepasang mata merah menyala penuh amarah dan kehausan akan darah terlihat jelas.", 30);
        delayPrint(L"Di tangannya tergenggam sebuah gada raksasa yang berlumuran darah segar. Setiap ayunannya tampak mampu meremukkan batu.", 30);
        // displayEnemyASCII("BaelTheIronFist"); 

        wcout << endl;
        wstring demonCommanderName = L"Bael, Sang Tinju Besi";
        delayPrint(L"Dia baru saja menghantam seorang kapten ksatria hingga terlempar jauh. Dia lalu menginjak panji Arcadia yang tergeletak di tanah dengan penuh penghinaan.", 40);
        delayPrint(L"\"Manusia lemah! Perlawanan kalian sia-sia!\" Suaranya menggelegar, berat dan serak bagai longsoran batu.", 50);
        delayPrint(L"\"Aku, " + demonCommanderName + L", Tangan Kanan dari Raja Iblis Agung, telah datang untuk mengklaim kota ini atas nama Tuanku!\"", 40);
        delayPrint(L"\"Hari ini, Arcadia akan bertekuk lutut!\"", 30);
        wcout << endl;

        delayPrint(L"Bael melihatmu mendekat, tatapannya yang membara tertuju padamu. \"Oh? Ada lagi serangga kecil yang berani merayap ke hadapanku?\"", 40);
        delayPrint(L"\"kamu punya nyali, aku akui. Tapi nyali saja tidak akan menyelamatkanmu dari kemurkaanku!\"", 30);
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk menantang Bael...");

        system("cls");
        printLine();
        centerText(L"MELAWAN SANG TINJU BESI");
        printLine();
        wcout << endl;
        delayPrint(L"kamu menghunus senjatamu, amarah dan tekad membara di dadamu. kamu tidak akan membiarkan kota ini jatuh tanpa perlawanan!", 40);
        delayPrint(L"Weiss: \"" + demonCommanderName + L"! Selama aku masih berdiri, Arcadia tidak akan pernah menjadi milikmu atau rajamu!\"", 50);
        delayPrint(L"Weiss: \"Bersiaplah menghadapi keadilan, Iblis!\"", 30);
        wcout << endl;

        delayPrint(L"Bael tertawa mengejek. \"Keadilan? Kata-kata kosong dari makhluk fana yang sekarat!\"", 40);
        delayPrint(L"\"Akan kuhancurkan kamu dan harapan kecilmu itu! Mari kita lihat seberapa kuat 'keadilanmu' bisa bertahan dari tinjuku!\"", 50);
        delayPrint(L"Dia mengangkat gadanya, siap untuk menghancurkanmu. Pertarungan untuk nasib Arcadia dimulai!", 40);
        wcout << endl;
        waitForEnter(L"Tekan Enter untuk memulai pertempuran sengit!");

        Enemy bael;
        bael.name = "Bael the Iron Fist";
        bael.level = player.level + 10; 
        bael.maxHp = static_cast<int>(player.maxHp * 3.5 + 400);
        if (bael.maxHp < 800) bael.maxHp = 800;
        bael.hp = bael.maxHp;
        bael.attack = player.strength + 35; 
        bael.defense = player.defense + 20; 
        bael.magicDefense = player.intelligence + 5; 
        bael.expReward = 1200;
        bael.goldDrop = 3000;
        bael.isBoss = true;
        bael.enemyType = "Demon";


        BattleResult result = startBattle(bael, "");

        if (result == ENEMY_DEAD) { 
            system("cls");
            printLine();
            centerText(L"🛡️ ARCADIA BERTAHAN! 🛡️");
            printLine();
            delayPrint(L"Dengan pertarungan yang paling sengit dalam hidupmu, kamu berhasil mengalahkan " + demonCommanderName + L"!", 50);
            delayPrint(L"Tubuh raksasa iblis itu ambruk ke tanah dengan suara berdebam, armornya retak dan hancur.", 40);
            wcout << endl;
            delayPrint(L"Bael terbatuk, darah hitam mengalir dari bibirnya. Dia menatapmu dengan sisa-sisa kebencian.", 30);
            delayPrint(L"Bael: \"Ka-kamu... manusia sialan... mengira ini sudah berakhir?\" (tertawa serak)", 40);
            delayPrint(L"Bael: \"Ini... baru permulaan! Tuanku... Raja Iblis... akan segera bangkit sepenuhnya!\"", 50);
            delayPrint(L"Bael: \"Saat Dia tiba... seluruh negeri ini... Arcadia... akan menjadi lautan api dan keputusasaan! Kalian semua... akan binasa! Hahaha... ha...\"", 40);
            delayPrint(L"Dengan kata-kata terakhir itu, cahaya di mata Bael meredup, dan tubuhnya hancur menjadi debu kegelapan.", 50);
            wcout << endl;
            delayPrint(L"Meskipun Balai Kota hancur lebur dan banyak korban berjatuhan, jatuhnya sang komandan iblis memberikan secercah harapan.", 40);
            delayPrint(L"Para ksatria yang tersisa dan warga yang berani mulai bersorak. kamu telah memukul mundur invasi besar!", 50);
            storyFlags["invasi_arcadia"] = 1; 
            
            int bonusExp = bael.expReward;
            int bonusGold = bael.goldDrop;

            player.exp += bonusExp;
            player.gold += bonusGold;
            wcout << endl;
            delayPrint(L"Hadiah Kemenangan Epik: +" + to_wstring(bonusExp) + L" EXP, +" + to_wstring(bonusGold) + L" Gold!", 30);
            delayPrint(L"Namamu kini dielu-elukan sebagai Pahlawan Arcadia! Namun, peringatan Bael tentang Raja Iblis terus terngiang...", 30);

        } else if (result == PLAYER_DEAD) { 
            system("cls");
            printLine();
            centerText(L"⚔️ DI AMBANG KEHANCURAN... SECERCAH CAHAYA DATANG TERLAMBAT! ⚔️");
            printLine();
            delayPrint(L"Kekuatan " + demonCommanderName + L" terlalu luar biasa. Setiap pukulannya terasa meremukkan tulang.", 50);
            delayPrint(L"kamu terlempar dan jatuh dengan keras, pandanganmu kabur. Bael tertawa menggelegar, \"Sudah kubilang, perlawananmu sia-sia!\"", 40);
            delayPrint(L"Dia mengangkat gadanya untuk serangan penghabisan...", 40);
            wcout << endl;
            delayPrint(L"Tiba-tiba, sebuah kilatan perak melesat dari kejauhan!", 50);
            delayPrint(L"\"CUKUP SUDAH KEKACAUAN INI, BAEL!\" Suara Allain Ragna menggema, penuh amarah suci.", 40);
            delayPrint(L"Allain, dengan Lumanaire MoonSword bersinar terang, tiba di medan pertempuran yang telah porak-poranda.", 50);
            delayPrint(L"Bael: \"Pahlawan Kecil lainnya! kamu terlambat! Kota ini sudah jadi milikku!\"", 30);
            delayPrint(L"Allain: \"Belum selama aku masih di sini!\"", 40);
            wcout << endl;
            delayPrint(L"Pertarungan sengit dan cepat terjadi antara Allain dan Bael. Lumanaire MoonSword menari di tangan Allain, membelah serangan brutal Bael.", 50);
            delayPrint(L"Meskipun Bael sangat kuat, energi suci dari pedang legendaris itu terbukti menjadi tandingannya.", 40);
            delayPrint(L"Dengan sebuah serangan akhir yang memancarkan cahaya membutakan, Allain berhasil mengalahkan Bael.", 60);
            delayPrint(L"Sang Tinju Besi Raja Iblis akhirnya tumbang, namun Balai Kota Arcadia telah jatuh dan banyak nyawa melayang.", 50);
            wcout << endl;
            delayPrint(L"Allain menghampirimu yang terkapar. \"Weiss! Bertahanlah! Maaf aku terlambat...\"", 40);
            delayPrint(L"kamu diselamatkan, namun kota ini telah terluka parah. Kemenangan ini sepenuhnya milik Allain.", 50);
            
            storyFlags["invasi_arcadia"] = 0; 
            player.hp = max(1, player.maxHp / 10); 
            wcout << endl;
            delayPrint(L"kamu terpaksa mundur dan memulihkan diri, sementara Allain memimpin sisa pasukan untuk mengamankan kota...", 30);
        }
        waitForEnter();
    }
}

void triggerPedangPahlawan() {
    if (storyFlags["pedang_pahlawan"] == 0) { 
        system("cls");
        printLine();
        centerText(L"🌟 CAHAYA HARAPAN DI TENGAH KOTA 🌟");
        printLine();
        wcout << endl;

        delayPrint(L"Sebuah fenomena tak terduga mengguncang seluruh Arcadia.", 40);
        delayPrint(L"Tepat di tengah Alun-Alun Utama, tempat Patung Pahlawan berdiri, sebuah cahaya menyilaukan memancar dari tanah.", 50);
        delayPrint(L"Ketika cahaya mereda, tertancaplah di sana sebilah pedang indah yang belum pernah dilihat siapa pun.", 40);
        delayPrint(L"Bilahnya berkilauan dengan cahaya rembulan meskipun hari masih siang, gagangnya dihiasi permata safir yang memancarkan aura suci dan kuat.", 30);
        delayPrint(L"Pedang itu seolah bernyanyi, melodi harapan yang samar namun nyata.", 40);
        wcout << endl;

        delayPrint(L"Kabar menyebar secepat kilat. Para tetua dan cendekiawan teringat akan sebuah ramalan kuno:", 40);
        centerText(L"📜 \"Kala bayangan tergelap mulai menelan negeri, Sang Rembulan akan menurunkan bilahnya ke bumi.", 70);
        centerText(L"   Hanya tangan sang pahlawan sejati, yang hatinya murni dan tekadnya membaja,", 70);
        centerText(L"   yang sanggup mengangkatnya, membawa sinar harapan untuk mengusir kegelapan abadi.\" 📜", 70);
        wcout << endl;
        waitForEnter(L"Tekan Enter saat para bangsawan dipanggil...");

        system("cls");
        printLine();
        centerText(L"🏛️ PERKUMPULAN PARA BANGSAWAN DI ALUN-ALUN 🏛️");
        printLine();
        wcout << endl;

        delayPrint(L"Seluruh bangsawan penting dari Arcadia dan wilayah sekitarnya, termasuk dirimu, Weiss von Astra, dipanggil ke Alun-Alun Utama.", 40);
        delayPrint(L"Raja, para penasihat, kesatria kehormatan, dan kepala keluarga bangsawan berkumpul dengan wajah tegang dan penuh harap.", 40);
        delayPrint(L"Di tengah mereka, Lumanaire MoonSword berdiri megah, memancarkan cahaya lembut yang seolah menilai setiap jiwa yang hadir.", 50);
        wcout << endl;

        delayPrint(L"Seorang Penasihat Raja yang dituakan membuka suara,", 30);
        delayPrint(L"Penasihat: \"Yang Mulia Raja, Tuan dan Nyonya Bangsawan sekalian. Kita semua telah menyaksikan keajaiban ini.\"", 40);
        delayPrint(L"Penasihat: \"Ramalan telah tergenapi. Pedang Sang Rembulan telah turun. Kini, pertanyaannya adalah, siapa di antara kita yang ditakdirkan menjadi pahlawan?\"", 40);
        wcout << endl;

        delayPrint(L"Suasana menjadi riuh. Beberapa bangsawan muda yang ambisius mulai saling pandang, ada yang dengan percaya diri menunjuk dirinya sendiri.", 30);
        delayPrint(L"Bangsawan Muda 1: \"Jelas ini adalah pertanda! Keluarga kami telah mengabdi pada kerajaan selama berabad-abad! Saya siap!\"", 30);
        delayPrint(L"Bangsawan Tua Bijak: \"Ini bukan tentang garis keturunan semata, anak muda. Ramalan menyebut 'hati yang murni dan tekad membaja'.\"", 40);
        wcout << endl;

        delayPrint(L"Nama Allain Ragna pun disebut-sebut. Kemenangannya di Colosseum (jika dia menang melawan Weiss) dan reputasinya sebagai pahlawan muda membuatnya menjadi kandidat kuat di mata banyak orang.", 40);
        if (storyFlags["duel_persahabatan"] == 0) { 
            delayPrint(L"Seorang Jenderal: \"Tuan Muda Allain von Ragna! Dia telah menunjukkan keberanian dan keterampilannya! Dia pantas mencoba!\"", 30);
        }
        wcout << endl;

        delayPrint(L"Di tengah perdebatan itu, kamu, Weiss von Astra, juga menjadi subjek pembicaraan.", 30);
        bool weissLayak = false;
        if (storyFlags["duel_persahabatan"] == 1) {
            delayPrint(L"Seorang Bangsawan Wanita: \"Jangan lupakan Tuan Muda Weiss von Astra! Kemenangannya di Colosseum menunjukkan perubahan besar dalam dirinya!\"", 40);
            if (storyFlags["invasi_mansion"] == 1) {
                delayPrint(L"Kepala Pengawal Mansion Astra: \"Dan dia seorang diri berhasil memukul mundur utusan Raja Iblis yang menyerang kediamannya! Itu keberanian luar biasa!\"", 40);
                if (storyFlags["invasi_arcadia"] == 1) {
                    delayPrint(L"Seorang Kapten Ksatria: \"Benar! Tuan Muda Weiss juga yang memimpin perlawanan dan mengalahkan Komandan Iblis Bael saat Arcadia diserang! Dia adalah pahlawan kota kami!\"", 40);
                    weissLayak = true; 
                } else {
                    delayPrint(L"Namun, jatuhnya Balai Kota Arcadia meski Tuan Muda Weiss berjuang, masih menjadi bayang-bayang...", 30);
                }
            } else {
                delayPrint(L"Namun, insiden penyerangan di Mansion Astra yang berhasil diatasi oleh pihak lain menjadi catatan...", 30);
            }
        } else {
             delayPrint(L"Beberapa mengingat reputasi lamamu, namun ada juga yang mengakui usahamu yang baru-baru ini untuk berubah...", 30);
        }
        wcout << endl;
        waitForEnter(L"Tekan Enter saat keputusan akan diambil...");

        system("cls");
        printLine();
        centerText(L"⚔️ PEDANG MEMILIH TUANNYA ⚔️");
        printLine();
        wcout << endl;

        delayPrint(L"Setelah perdebatan panjang, Raja akhirnya angkat bicara dengan suara berwibawa,", 40);
        delayPrint(L"Raja: \"Kita tidak bisa memutuskan takdir hanya dengan perdebatan. Biarkan Lumanaire MoonSword sendiri yang memilih!\"", 50);
        delayPrint(L"Raja: \"Siapapun yang didekati atau diakui oleh pedang ini, dialah yang akan memimpin kita melawan Raja Iblis!\"", 40);
        wcout << endl;

        bool weissChosen = false;
        bool allainChosen = false;

        if (weissLayak) {
            delayPrint(L"Semua mata tertuju padamu, Weiss von Astra. Dengan langkah mantap, kamu mendekati pedang suci itu.", 40);
            delayPrint(L"Saat kamu semakin dekat, Lumanaire MoonSword bergetar hebat. Cahayanya semakin menyilaukan, seolah menyambut kedatanganmu.", 50);
            delayPrint(L"Sebuah pancaran energi lembut namun kuat mengalir dari pedang ke arahmu, menyelimutimu dalam kehangatan.", 40);
            delayPrint(L"kamu mengulurkan tanganmu... dan gagang pedang itu seolah pas dengan genggamanmu. Cahaya pedang memuncak, menerangi seluruh alun-alun!", 50);
            wcout << endl;
            centerText(L"✨ WEISS VON ASTRA TELAH DIPILIH OLEH LUMANAIRE MOONSWORD! ✨", 70);
            wcout << endl;
            delayPrint(L"Sorak-sorai membahana. Keraguan sirna, digantikan oleh decak kagum dan harapan baru.", 40);
            delayPrint(L"Raja: \"Takdir telah berbicara! Weiss von Astra adalah Pahlawan yang diramalkan! Dia yang akan memimpin kita!\"", 50);
            
            storyFlags["pedang_pahlawan_weiss_chosen"] = 1;
            storyFlags["pedang_pahlawan_allain_chosen"] = 0; // Pastikan hanya satu yang terpilih
            weissChosen = true;

            if (weaponDatabase.count("Lumanaire MoonSword")) {
                Weapon* lumanaire = weaponDatabase["Lumanaire MoonSword"];
                bool alreadyOwned = false;
                for (const auto* pWeapon : player.weapons) {
                    if (pWeapon && pWeapon->name == lumanaire->name) {
                        alreadyOwned = true;
                        break;
                    }
                }
                if (!alreadyOwned) {
                    player.weapons.push_back(lumanaire);
                    delayPrint(L"kamu merasakan kekuatan dahsyat mengalir dari Lumanaire MoonSword. Pedang ini kini milikmu!", 30);
                }
            } else {
                delayPrint(L"[ERROR DATA] Lumanaire MoonSword tidak ditemukan di database senjata.", 30);
            }

        } else {
            delayPrint(L"Meskipun ada yang menyebut namamu, perhatian utama tertuju pada Allain Ragna, sang pahlawan muda.", 40);
            delayPrint(L"Allain melangkah maju dengan rendah hati namun penuh keyakinan.", 30);
            delayPrint(L"Saat Allain mendekat, Lumanaire MoonSword juga bergetar dan memancarkan cahaya yang lebih terang, mengarah padanya.", 50);
            delayPrint(L"Allain menyentuh gagang pedang itu, dan cahaya keemasan menyelimutinya. Pedang itu telah memilihnya.", 40);
            wcout << endl;
            centerText(L"🌟 ALLAIN RAGNA TELAH DIPILIH OLEH LUMANAIRE MOONSWORD! 🌟", 70);
            wcout << endl;
            delayPrint(L"Sebagian besar bangsawan mengangguk setuju. Inilah yang mereka harapkan. Sang pahlawan telah mendapatkan senjatanya.", 40);
            delayPrint(L"Raja: \"Ramalan terbukti! Allain Ragna adalah Pahlawan yang akan menyelamatkan negeri ini!\"", 50);
            storyFlags["pedang_pahlawan_allain_chosen"] = 1;
            storyFlags["pedang_pahlawan_weiss_chosen"] = 0; 
            allainChosen = true;
            wcout << endl;
            delayPrint(L"kamu merasakan sedikit kekecewaan, namun juga kelegaan bahwa setidaknya harapan kini ada pada seseorang.", 30);
            delayPrint(L"Mungkin peranmu dalam perang melawan Raja Iblis akan berbeda, namun kamu tetap akan berjuang.", 40);
        }

        storyFlags["pedang_pahlawan"] = 1; 

        wcout << endl;
        if (weissChosen) {
            delayPrint(L"Dengan Lumanaire MoonSword di tanganmu, tatapan seluruh negeri kini tertuju padamu. Beban sebagai pahlawan terasa nyata.", 50);
        } else if (allainChosen) {
            delayPrint(L"Allain Ragna kini memegang pedang takdir. Perhatian kini tertuju padanya, dan kamu merenungkan peran apa yang akan kamu mainkan.", 50);
        }
        delayPrint(L"Persiapan untuk perang melawan Raja Iblis akan segera dimulai...", 40);
        waitForEnter();
    }
}

void triggerFinalBossRajaIblis() {
    if (storyFlags["raja_iblis_final"] == 0) {
        system("cls");
        printLine();
        centerText(L"🌍 AKHIR DUNIA TELAH TIBA? 🌍");
        printLine();
        wcout << endl;

        delayPrint(L"Getaran dahsyat mengguncang seluruh penjuru negeri, seolah bumi sendiri menjerit ketakutan.", 40);
        delayPrint(L"Langit yang tadinya biru kini tertutup awan hitam pekat dan berputar-putar, memuntahkan petir berwarna darah.", 50);
        delayPrint(L"Di Ibukota Arcadia, sirene meraung tanpa henti. Warga sipil telah dievakuasi ke tempat-tempat perlindungan bawah tanah.", 40);
        delayPrint(L"Semua ksatria, penyihir, petualang, dan siapapun yang bisa mengangkat senjata, kini berkumpul di benteng terakhir kota, termasuk Allain Ragna yang berdiri di barisan depan para pahlawan, bersiap menghadapi yang tak terhindarkan.", 30);
        delayPrint(L"Udara terasa berat, dipenuhi dengan keputusasaan dan secercah keberanian terakhir.", 40);
        wcout << endl;
        waitForEnter(L"Tekan Enter saat gerbang kota tak mampu lagi bertahan...");

        system("cls");
        printLine();
        centerText(L"GERBANG ARCADIA RUNTUH - SANG RAJA IBLIS TIBA!");
        printLine();
        wcout << endl;

        delayPrint(L"Dengan suara ledakan yang membelah langit, Gerbang Utama Arcadia yang perkasa hancur berkeping-keping!", 50);
        delayPrint(L"Gelombang energi gelap menyapu ke dalam kota, meruntuhkan bangunan dan menebarkan teror.", 40);
        delayPrint(L"Dari balik debu dan kehancuran, sesosok makhluk melangkah masuk. Auranya begitu menindas hingga membuat lutut para prajurit gemetar.", 50);
        delayPrint(L"Sosoknya raksasa, menjulang tinggi dengan armor kuno yang tampak menyerap cahaya. Ini adalah Vorlag dalam wujud awalnya yang mengintimidasi.", 30);
        // displayEnemyASCII("VorlagGiantForm_P1"); 

        wcout << endl;
        wstring demonKingName = L"Vorlag, Sang Penguasa Bencana";
        delayPrint(L"Dia mengangkat kepalanya, memandang rendah para pembela kota yang tersisa.", 40);
        delayPrint(L"\"Manusia... Makhluk fana yang congkak.\" Suaranya bukan teriakan, melainkan gemuruh dalam yang meresonansi dengan kekuatan kosmik, tenang namun penuh dengan finalitas.", 50);
        delayPrint(L"\"Perlawanan kalian adalah hiburan sesaat sebelum tirai kegelapan menutupi dunia kalian selamanya.\"", 40);
        delayPrint(L"\"Aku adalah " + demonKingName + L". Aku adalah akhir dari segalanya! Dan kalian... hanyalah debu di bawah kakiku.\"", 50);
        wcout << endl;

        bool playerIsTheHero = (storyFlags["pedang_pahlawan_weiss_chosen"] == 1);
        bool allainIsTheHero = (storyFlags["pedang_pahlawan_allain_chosen"] == 1);

        if (playerIsTheHero) {
            delayPrint(L"kamu, Weiss von Astra, pemegang Lumanaire MoonSword, melangkah maju dengan pedang terhunus, auranya bersinar menantang kegelapan.", 40);
            delayPrint(L"Weiss: \"Vorlag! Selama masih ada kehidupan yang berharga di negeri ini, kami tidak akan pernah menyerah padamu! Cahaya akan selalu menemukan cara untuk mengusir kegelapan!\"", 50);
        } else if (allainIsTheHero && player.hp > 0) { 
            delayPrint(L"Allain Ragna, dengan Lumanaire MoonSword di tangannya, maju dengan tatapan membara, siap melindungi yang tersisa.", 40);
            delayPrint(L"Allain: \"Raja Iblis Vorlag! Kezalimanmu akan berakhir hari ini! Atas nama seluruh kehidupan, aku akan menghentikanmu!\"", 50);
            delayPrint(L"kamu berdiri di sisinya, siap membantu sang pahlawan terpilih.", 30);
        } else { 
            delayPrint(L"Meskipun tanpa pedang ramalan, kamu dan para pejuang lainnya bersiap untuk pertempuran terakhir yang menentukan.", 40);
            delayPrint(L"Weiss: \"Kami mungkin tidak punya senjata legendaris, tapi kami punya keberanian! Kami akan bertarung sampai titik darah penghabisan!\"", 50);
        }
        wcout << endl;

        delayPrint(L"Vorlag tersenyum meremehkan. \"Keberanian? Itu hanya ilusi sebelum kematian. Mari kita mulai tarian kehancuran ini!\"", 50);
        waitForEnter(L"Tekan Enter untuk memulai pertempuran terakhir melawan Raja Iblis!");

        Enemy vorlag_p1;
        vorlag_p1.name = "Vorlag, Wujud Awal Bencana";
        vorlag_p1.level = player.level + 5; 
        vorlag_p1.maxHp = static_cast<int>(player.maxHp * 2.0 + 300); 
        if (vorlag_p1.maxHp < 1200) vorlag_p1.maxHp = 1200;
        vorlag_p1.hp = vorlag_p1.maxHp;
        vorlag_p1.attack = player.strength + 15; 
        vorlag_p1.defense = player.defense + 10; 
        vorlag_p1.magicDefense = player.intelligence + 5;
        vorlag_p1.expReward = 1000; 
        vorlag_p1.goldDrop = 2000; 
        vorlag_p1.isBoss = true;
        vorlag_p1.enemyType = "Demon Lord (Form 1)";
        
        BattleResult result_p1 = startBattle(vorlag_p1, "");

        if (result_p1 == PLAYER_DEAD) { 
            system("cls");
            printLine();
            centerText(L"☠️ KEHANCURAN TOTAL - HARAPAN PADAM ☠️");
            printLine();
            delayPrint(L"Bahkan wujud awal Vorlag terlalu perkasa untukmu. Perlawananmu hancur seketika.", 50);
            delayPrint(L"Raja Iblis tertawa saat duniamu menjadi gelap. Arcadia jatuh, dan tidak ada yang bisa menghentikannya.", 60);
            delayPrint(L"Takdirmu sebagai pecundang... akhirnya tergenapi.", 50);
            storyFlags["raja_iblis_final"] = 3; 
            gameRunning = false;

        } else if (result_p1 == ENEMY_DEAD) { 
            player.exp += vorlag_p1.expReward; 
            player.gold += vorlag_p1.goldDrop;
            delayPrint(L"kamu mendapatkan " + to_wstring(vorlag_p1.expReward) + L" EXP dan " + to_wstring(vorlag_p1.goldDrop) + L" Gold dari mengalahkan wujud awalnya!", 30);
            waitForEnter();

            system("cls");
            printLine();
            centerText(L"🌑 KEHENINGAN YANG MENGERIKAN... KEKUATAN SEJATI BANGKIT! 🌑");
            printLine();
            wcout << endl;
            delayPrint(L"Tubuh raksasa Vorlag yang perkasa tersungkur, pedang besarnya menghantam tanah dengan dentuman keras.", 40);
            delayPrint(L"Untuk sesaat, keheningan mencekam. kamu mencoba mengatur napas, mengira kemenangan sudah di tangan...", 40);
            delayPrint(L"Namun, dari jasad Vorlag, aura kegelapan yang jauh lebih pekat dan dingin mulai memancar, menyerap semua cahaya di sekitarnya.", 50);
            delayPrint(L"Asap hitam yang tadi menyelimutinya kini menyusut dengan cepat, memadat, membentuk sosok baru yang lebih ramping, lebih kecil, namun setiap garisnya memancarkan kekuatan murni yang absolut.", 50);
            wcout << endl;
            delayPrint(L"Vorlag kini berdiri dalam wujudnya yang sejati, 'perfect form'. Matanya terbuka, kini menjadi dua titik merah membara dalam kegelapan, tanpa emosi, hanya kehampaan dan kekuatan penghancur.", 40);
            // displayEnemyASCII("VorlagPerfectForm_P2"); 
            delayPrint(L"Vorlag: (Suaranya kini lebih dalam, tenang, namun sarat dengan ancaman absolut) \"Wujudku yang sesungguhnya... akhirnya terbebas.\"", 60);
            delayPrint(L"Vorlag: \"Sekarang... saksikanlah keputusasaan yang sebenarnya.\"", 50);
            wcout << endl;
            
            delayPrint(L"Sebelum kamu sempat menarik napas, Vorlag menghilang dari pandanganmu!", 30);
            delayPrint(L"Detik berikutnya, dia muncul TEPAT DI DEPANMU! Sebuah pukulan dahsyat menghantam dadamu dengan kekuatan tak terbendung!", 60);
            delayPrint(L"BRAAAKKK!!! Tubuhmu terpental jauh ke belakang laksana meteor, menabrak sisa-sisa bangunan hingga hancur berkeping-keping!", 50);
            delayPrint(L"Rasa sakit luar biasa merobek kesadaranmu, pandanganmu menggelap...", 40);
            player.hp = max(1, player.hp / 10); 
            wcout << endl;
            waitForEnter(L"Tekan Enter saat kamu hampir kehilangan kesadaran...");

            delayPrint(L"\"WEISS!/BERTAHANLAH!\" Sebuah suara familiar berteriak.", 30);
            delayPrint(L"Dalam sekejap, Allain Ragna melesat secepat kilat, menangkap tubuhmu tepat sebelum kamu menghantam reruntuhan tajam lebih jauh!", 50);
            delayPrint(L"Allain: \"Sialan! Kekuatan macam apa ini?!\" Dia dengan cepat mengeluarkan sebuah botol dari kantungnya.", 40);
            delayPrint(L"Allain: \"Minumlah ini, Weiss! Cepat! Ini Potion Penyembuh terbaik yang kumiliki!\"", 30); 
            
            player.hp = player.maxHp; 
            delayPrint(L"Cairan penyembuh itu seketika memulihkan seluruh lukamu dan mengisi kembali tenagamu! HP-mu penuh kembali!", 30);
            delayPrint(L"HP-mu kini: " + to_wstring(player.hp) + L"/" + to_wstring(player.maxHp), 30);
            wcout << endl;

            delayPrint(L"Raungan iblis-iblis yang lebih kecil terdengar dari segala arah, mereka mulai mengerumuni reruntuhan tempat kalian berada!", 40);
            delayPrint(L"Allain berdiri siaga di depanmu, pedangnya menebas beberapa iblis yang mendekat.", 40);
            delayPrint(L"Allain: \"Weiss! Serahkan saja gerombolan iblis ini padaku! kamu harus pusatkan seluruh energimu untuk Vorlag!\"", 50); 
            delayPrint(L"Allain: \"Jika kamu Pahlawan terpilih, hanya kamu yang bisa mengimbangi wujud sempurnanya itu! Jika tidak, kita akan menghadapinya bersama setelah aku menahan mereka!\"", 50);
            delayPrint(L"Allain: \"Jangan sia-siakan pengorbanan para ksatria! Kalahkan dia! Aku percaya padamu!\"", 30);
            wcout << endl;
            waitForEnter(L"Tekan Enter untuk menghadapi Wujud Sempurna Vorlag!");

            Enemy vorlag_p2;
            vorlag_p2.name = "Vorlag, Wujud Sempurna Bencana";
            vorlag_p2.level = vorlag_p1.level + 7; 
            vorlag_p2.maxHp = static_cast<int>(vorlag_p1.maxHp * 1.2); 
            if (vorlag_p2.maxHp < 2500) vorlag_p2.maxHp = 2500;
            vorlag_p2.hp = vorlag_p2.maxHp;
            vorlag_p2.attack = vorlag_p1.attack + 30; 
            vorlag_p2.defense = vorlag_p1.defense + 5; 
            vorlag_p2.magicDefense = vorlag_p1.magicDefense + 20; 
            vorlag_p2.expReward = 50000; 
            vorlag_p2.goldDrop = 100000;
            vorlag_p2.isBoss = true;
            vorlag_p2.enemyType = "True Demon Sovereign";

            BattleResult result_p2 = startBattle(vorlag_p2, "");

            if (result_p2 == ENEMY_DEAD) { 
                system("cls");
                printLine();
                centerText(L"🌟 KEMENANGAN MUTLAK! DUNIA TELAH SELAMAT! 🌟");
                printLine();
                delayPrint(L"Setelah pertarungan yang melampaui batas kemampuan, Wujud Sempurna Vorlag akhirnya takluk di hadapan kekuatanmu!", 50);
                delayPrint(L"Tubuhnya yang kini lebih kecil namun padat energi itu bergetar hebat. \"Tidak mungkin... oleh... manusia...?\"", 40);
                delayPrint(L"Vorlag: \"Kalian... akan membayar ini... Tuanku yang Agung... akan... bang...kit...\"", 50); 
                delayPrint(L"Dengan erangan terakhir, tubuh Vorlag hancur menjadi debu hitam yang tertiup angin, lenyap tanpa sisa.", 60);
                delayPrint(L"Awan hitam pekat di langit perlahan tersibak, memperlihatkan fajar pertama dari era baru yang damai.", 50);
                delayPrint(L"Perang telah usai. Kegelapan tertinggi telah dikalahkan. Dunia diselamatkan oleh keberanian dan kekuatanmu!", 40);
                storyFlags["raja_iblis_final"] = 1; 
                player.exp += vorlag_p2.expReward;
                player.gold += vorlag_p2.goldDrop;
                wcout << endl;
                delayPrint(L"kamu berdiri di tengah medan pertempuran yang kini sunyi, lelah namun dipenuhi kelegaan dan kemenangan.", 30);
                delayPrint(L"Sorak-sorai para pejuang yang selamat dan warga yang mulai keluar dari persembunyian terdengar, mengelu-elukan namamu.", 40);
                delayPrint(L"WEISS VON ASTRA, YANG PERNAH DIKENAL SEBAGAI ANTAGONIS, KINI DIABADIKAN SEBAGAI PAHLAWAN TERBESAR, SANG PENYELAMAT DUNIA!", 60);
                wcout << endl;
                centerText(L"🎉 SELAMAT! ANDA TELAH MENAMATKAN GAME! 🎉", 70);
                gameRunning = false; 

            } else if (result_p2 == PLAYER_DEAD) { 
                system("cls");
                printLine();

                if (playerIsTheHero) { 
                    centerText(L"💔 PENGORBANAN SANG PAHLAWAN... HARAPAN DITERUSKAN 💔");
                    printLine();
                    delayPrint(L"Wujud Sempurna Vorlag terbukti terlalu kuat, bahkan untukmu yang memegang Lumanaire MoonSword.", 50);
                    delayPrint(L"kamu bertarung hingga titik darah penghabisan, namun akhirnya tubuhmu tak sanggup lagi menahan serangan brutal Raja Iblis.", 60);
                    delayPrint(L"Saat pandanganmu memudar, kamu melihat Allain Ragna masih berjuang mati-matian melawan gerombolan iblis yang tak ada habisnya.", 40);
                    delayPrint(L"Dengan sisa kekuatanmu, kamu melemparkan Lumanaire MoonSword ke arah Allain, menancap di tanah di dekat kakinya.", 50);
                    delayPrint(L"Weiss: \"Allain... pedang ini... kini milikmu... Selesaikan... apa yang kumulai! Lindungi... dunia ini!\"", 70);
                    delayPrint(L"Allain menangkap pedang sucimu. Matanya berkilat dengan kesedihan mendalam dan tekad baru yang membara.", 40);
                    delayPrint(L"Allain: \"WEISS! Tidak! Aku... aku akan memenuhi janjimu! Aku akan menggunakan kekuatan ini untuk mengakhiri semuanya!\"", 50);
                    wcout << endl;
                    delayPrint(L"Dengan Lumanaire MoonSword kini di tangannya, Allain Ragna menghadapi Vorlag. Pertarungan mereka mengguncang langit dan bumi.", 60);
                    delayPrint(L"Akhirnya, setelah pertempuran yang menghancurkan sisa-sisa kota, Allain berhasil mengalahkan Vorlag.", 50);
                    delayPrint(L"Dunia selamat, namun atas pengorbananmu. Allain akan melanjutkan warisanmu sebagai pahlawan sejati, selalu mengingat sahabat yang telah memberinya jalan.", 60);
                    storyFlags["raja_iblis_final"] = 2; 
                    gameRunning = false;

                } else if (allainIsTheHero) { 
                    centerText(L"🖤 JIWA TERENGGUT, PERTARUNGAN ANTAR TAKDIR 🖤");
                    printLine();
                    delayPrint(L"kamu telah berjuang sekuat tenaga melawan Wujud Sempurna Vorlag, namun akhirnya kegelapan mulai merayapimu...", 50);
                    delayPrint(L"Tubuhmu ambruk, energi kehidupanmu terkuras habis. Vorlag mendekat, bukan untuk menghancurkan, tapi dengan tatapan penuh perhitungan licik.", 40);
                    delayPrint(L"Vorlag: \"Menarik... Jiwa yang memiliki potensi seperti ini, namun bukan Pahlawan Terpilih... kamu mampu menahan sebagian kekuatanku dan berinteraksi dengan artefak suci. kamu akan menjadi wadah yang jauh lebih menarik dan mudah dikendalikan!\"", 60);
                    delayPrint(L"Vorlag: \"Tubuhmu, jiwamu, potensimu... SEMUANYA AKAN MENJADI MILIKKU, WEISS VON ASTRA! KITA AKAN MENJADI SATU!\"", 50);
                    wcout << endl;
                    delayPrint(L"Aura hitam pekat keluar dari Vorlag dan dengan paksa menyelimuti dan merasuki tubuhmu yang tak berdaya!", 60);
                    delayPrint(L"kamu merasakan kesadaranmu terkoyak, digantikan oleh kehendak dingin dan kejam Raja Iblis. Matamu terbuka, kini menyala dengan cahaya merah jahat dan aura dari semua elemen sihir.", 50);
                    
                    centerText(L"ANDA KINI ADALAH WEISS-VORLAG!", 70);
                    wcout << endl;

                    temporarilyGrantAllMagicToPlayer(player, true); 
                    // HP dan Mana sudah di-set full di dalam temporarilyGrantAllMagicToPlayer

                    delayPrint(L"\"Kekuatan ini... HAHAHA! Luar biasa! Dunia akan menjadi milikku!\" suara gabungan Weiss dan Vorlag menggema.", 40);
                    delayPrint(L"Allain Ragna, yang baru saja menghalau serbuan iblis terakhir, melihatmu bangkit dengan aura yang mengerikan, berbeda dari sebelumnya.", 30);
                    delayPrint(L"Allain: \"Weiss?! Apa yang terjadi padamu?! Energi ini... ini bukan dirimu! Vorlag! Keluar dari tubuhnya!\"", 40);
                    
                    delayPrint(L"Weiss-Vorlag: \"Weiss yang lemah sudah lenyap, Pahlawan Kecil! Sekarang hanya ada kami!\"", 50);
                    delayPrint(L"Weiss-Vorlag melesat ke arah Allain, tangannya yang diliputi energi gelap mencoba merebut Lumanaire MoonSword!", 50);
                    delayPrint(L"Namun, pedang suci itu sendiri seolah menolak, memancarkan gelombang energi perak yang membuat tangan Weiss-Vorlag sedikit terbakar dan mundur!", 60);
                    delayPrint(L"Allain: (Menggenggam Lumanaire lebih erat) \"kamu tidak akan pernah bisa menyentuh kekuatan suci ini dengan jiwa iblismu, Vorlag! Aku akan membebaskan Weiss!\"", 50);
                    delayPrint(L"Weiss-Vorlag: (Mendesis) \"Pedang itu akan menjadi milikku setelah aku menghancurkanmu, Pahlawan kecil! Dan jiwa Weiss akan selamanya menjadi bagian dariku!\"", 40);
                    wcout << endl;
                    waitForEnter(L"Tekan Enter untuk memulai duel terakhir: WEISS-VORLAG vs ALLAIN RAGNA!");

                    Enemy buffedAllain;
                    setupBuffedAllainForDuel(buffedAllain); 

                    BattleResult weissVorlagVsAllainResult = startBattle(buffedAllain, "");
                    
                    temporarilyGrantAllMagicToPlayer(player, false); 


                    if (weissVorlagVsAllainResult == ENEMY_DEAD) { 
                        system("cls");
                        printLine();
                        centerText(L"💥 KEHANCURAN BERSAMA - TAKDIR TRAGIS PARA PAHLAWAN 💥");
                        printLine();
                        delayPrint(L"Dengan kekuatan iblis yang menguasaimu sepenuhnya, kamu berhasil mengalahkan Allain Ragna, sang Pahlawan Terpilih Arcadia.", 50);
                        delayPrint(L"Allain tergeletak tak berdaya, Lumanaire MoonSword meredup di sisinya, namun masih memancarkan secercah cahaya suci.", 40);
                        delayPrint(L"Allain: (Dengan napas terakhir, menatapmu dengan pandangan sedih namun penuh tekad) \"Weiss... kuharap... suatu saat... kamu menemukan... kedamaian... Aku... tidak akan membiarkan Vorlag... menang...\"", 60);
                        delayPrint(L"Melihat Pahlawan terakhir gugur, Allain memutuskan tindakan pamungkas.", 40);
                        delayPrint(L"Dia menyalurkan seluruh sisa esensi kehidupannya dan kekuatan sucinya yang terakhir ke dalam Lumanaire MoonSword yang tergeletak.", 50);
                        delayPrint(L"\"CAHAYA ABADI... LENYAPKAN KEGELAPAN INI SELAMANYA!\" teriak Allain.", 40);
                        delayPrint(L"Pedang itu meledak dalam pancaran cahaya suci yang maha dahsyat, menyelimuti seluruh medan pertempuran, menelanmu (Weiss-Vorlag) dan jasad Allain.", 70);
                        delayPrint(L"Ketika cahaya mereda, tidak ada yang tersisa selain kehancuran total dan keheningan. Raja Iblis Vorlag, bersama wadahnya, dan sang Pahlawan Allain Ragna, keduanya telah musnah.", 60);
                        delayPrint(L"Dunia mungkin selamat dari ancaman langsung Vorlag, tapi dengan harga yang tak terbayangkan: kehilangan kedua sosok yang bisa menjadi pahlawannya.", 50);
                        storyFlags["raja_iblis_final"] = 4; 
                        gameRunning = false;

                    } else if (weissVorlagVsAllainResult == PLAYER_DEAD) { 
                        system("cls");
                        printLine();
                        centerText(L"✨ PENYELAMATAN TERAKHIR - JIWA YANG DIBEBASKAN ✨");
                        printLine();
                        delayPrint(L"Meskipun dirasuki kekuatan Vorlag dan menguasai semua elemen, Allain Ragna, dengan Lumanaire MoonSword dan tekad Pahlawan Terpilih, bertarung dengan gigih.", 50);
                        delayPrint(L"Setelah pertempuran yang mengerikan, Allain berhasil menemukan celah dalam pertahananmu.", 40);
                        delayPrint(L"Dengan serangan terakhir yang dipenuhi cahaya suci dari Lumanaire, dia berhasil menghancurkan entitas Vorlag yang bersemayam dalam dirimu.", 50);
                        delayPrint(L"Tubuh Weiss tergeletak. Energi gelap Vorlag menjerit dan lenyap. Untuk sesaat, matamu kembali menjadi dirimu sendiri.", 60);
                        delayPrint(L"Weiss: (Berbisik lemah pada Allain) \"Allain... kamu berhasil... Terima kasih... telah membebaskanku...\"", 70);
                        delayPrint(L"Dengan senyum tipis, jiwamu akhirnya menemukan kedamaian sejati.", 40);
                        delayPrint(L"Allain Ragna berdiri sebagai pahlawan tunggal, telah menyelamatkan dunia dari Raja Iblis dan membebaskan jiwa sahabatnya dari takdir yang mengerikan.", 60);
                        storyFlags["raja_iblis_final"] = 5; 
                        gameRunning = false;
                    }
                } else { 
                     system("cls"); printLine();
                     centerText(L"☠️ KEGELAPAN ABADI TELAH MENYELIMUTI DUNIA ☠️");
                     printLine();
                    delayPrint(L"Tanpa Pahlawan Terpilih yang memegang senjata suci, bahkan Wujud Sempurna Vorlag tak terhentikan.", 50);
                    delayPrint(L"Kekalahanmu adalah kekalahan dunia.", 60);
                    storyFlags["raja_iblis_final"] = 3; 
                    gameRunning = false; 
                }
            }
        }
        waitForEnter(L"Tekan Enter untuk melanjutkan...");
    }
}


void checkStoryTriggers() {
            if (currentDay == 15 && storyFlags["duel_persahabatan"] == 0) {
                triggerDuelAllainRagna();
            }
            if (currentDay == 25 && storyFlags["invasi_mansion"] == 0) {
                triggerInvasiMansion();
            }
            if (currentDay == 35 && storyFlags["invasi_arcadia"] == 0) {
                triggerInvasiArcadia();
            }
            if (currentDay == 50 && storyFlags["pedang_pahlawan"] == 0) {
                triggerPedangPahlawan();
            }
            if (currentDay == 60 && storyFlags["raja_iblis_final"] == 0) {
                triggerFinalBossRajaIblis();
            }
        }



void showGameMenu() {
    int choice;
    do {
        system("cls");
        printLine();
        centerText(L"✦✦✦ " + wstring(currentSubArea.begin(), currentSubArea.end()) + L" - " + wstring(currentWorld.begin(), currentWorld.end()) + L" ✦✦✦");
        printLine();
        wcout << L"Lokasi: " << currentSubArea.c_str() << L" di " << currentWorld.c_str() << endl;
        wcout << L"Hari: " << currentDay << endl;
        wcout << L"Aksi tersisa hari ini: " << currentActionsRemaining << L"/" << maxActionsPerDay << endl;
        printLine();    
        const auto& actions = allWorlds[currentWorld].subAreas[currentSubArea].actions;
        for (int i = 0; i < actions.size(); ++i) {
            wcout << L"❖ " << i + 1 << L". " << actions[i].c_str() << endl;
        }
        printLine(50, L'─');
        wcout << L"Pilih aksi ✦: ";
        
        choice = getValidatedChoice(1, 6); 
        if (choice > 0 && choice <= actions.size()) {
            string action = actions[choice - 1];

            if (action == "Cek Sekitar") {
                exploreArea();
            } else if (action == "Membuka Diary" || action == "Buka Diary") {
                showDiaryMenu();
            } else if (action == "Istirahat") {
                int pilihanIstirahat;
                system("cls");
                printLine();
                centerText(L"✦✦✦ ISTIRAHAT ✦✦✦");
                printLine();
                delayPrint(L"Tempat tidur tampak nyaman. Apakah kamu ingin beristirahat dan mengakhiri hari ini?", 20);
                wcout << L"\n❖ 1. Ya, beristirahat\n❖ 2. Tidak, kembali ke aktivitas\n";
                printLine();
                wcout << L"Pilih opsi ✦: ";
                
                wstring istirahatInputRaw;

                if (wcin.rdbuf()->in_avail() > 0 && wcin.peek() == L'\n') { 
                    wcin.ignore();
                }
                getline(wcin, istirahatInputRaw);
                try {
                    if (!istirahatInputRaw.empty()) {
                        pilihanIstirahat = stoi(istirahatInputRaw);
                    } else {
                        pilihanIstirahat = 0; 
                    }
                } catch (const exception& e) {
                    pilihanIstirahat = 0; 
                }

                if (pilihanIstirahat == 1) {
                    currentActionsRemaining = 0;    
                    delayPrint(L"Kamu merebahkan diri di atas tempat tidur, membiarkan kelelahan hari ini larut dalam kehangatan selimut...", 30);
                    delayPrint(L"Zzz...", 40);
                    advanceToNextDay();
                    void checkStoryTriggers();


                ActiveDailyQuestNode* current = activeDailyQuestsHead;
                while (current != nullptr) {
                    ActiveDailyQuestNode* next = current->next;
                    delete current;
                    current = next;
                }
                activeDailyQuestsHead = nullptr;
                generateDailyQuests();
            } else {
                delayPrint(L"Kamu memutuskan untuk tetap terjaga dan melanjutkan aktivitas hari ini.", 20);
                waitForEnter();
            }
            }  else if (action == "Pilih Lokasi") {
                showLocationMenu();
            } else if (action == "Bicara dengan Ruigerd") {
                interactWithNPC("Ruigerd");
            } else if (action == "Bicara dengan Irene") {
                interactWithNPC("Irene");
            } else if (action == "Bicara dengan Ella") {
                interactWithNPC("Ella");
            } else if (action == "Bicara dengan Charlotte") {
                interactWithNPC("Charlotte");
            } else if (action == "Bicara dengan Mars") {
                interactWithNPC("Mars");
            } else if (action == "Bicara dengan Kinich") {
                interactWithNPC("Kinich");
            } else if (action == "Bicara dengan Masha") {
                interactWithNPC("Masha");            
            } else if (action == "Quest Board") {
                showQuestBoard();
            } else if (action == "Item Shop") {
                showItemShop();
            } else if (action == "Penempa Besi") {
                showBlacksmith();
            } else if (action == "Cek Berita Kota") {
                system("cls");
                printLine();
                centerText(L"✦✦✦ KABAR DARI ARCADIA CHRONICLE ✦✦✦");
                printLine();
                delayPrint(L"kamu mengambil edisi terbaru Harian Arcadia Chronicle yang terpajang...", 20);
                wcout << endl;

                bool beritaUtamaTampil = false;
                if (storyFlags.count("raja_iblis_final") && storyFlags.at("raja_iblis_final") == 1) {
                    delayPrint(L"HEADLINE UTAMA: DUNIA SELAMAT! RAJA IBLIS VORLAG DITAKLUKKAN OLEH PAHLAWAN WEISS VON ASTRA!", 30);
                    delayPrint(L"  Isi Berita: Seluruh negeri bersukacita atas kemenangan gemilang melawan Penguasa Bencana. Era baru perdamaian dan pembangunan kembali telah dimulai berkat kepahlawanan Tuan Muda Weiss.", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("raja_iblis_final") && storyFlags.at("raja_iblis_final") == 2) {
                    delayPrint(L"HEADLINE UTAMA: RAJA IBLIS MUSNAH! ALLAIN RAGNA MENYELAMATKAN DUNIA DI SAAT-SAAT AKHIR!", 30);
                    delayPrint(L"  Isi Berita: Dalam pertempuran terakhir yang menentukan, Allain Ragna, dengan warisan Pedang Pahlawan, berhasil mengalahkan Vorlag. Weiss von Astra dikenang sebagai martir yang membuka jalan.", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("raja_iblis_final") && storyFlags.at("raja_iblis_final") == 4) {
                    delayPrint(L"HEADLINE UTAMA: TRAGEDI DAN KEMENANGAN! KEDUA PENANTANG RAJA IBLIS GUGUR DALAM KEHANCURAN BERSAMA!", 30);
                    delayPrint(L"  Isi Berita: Dunia selamat dari Vorlag, namun harus kehilangan Weiss von Astra dan Allain Ragna dalam ledakan kekuatan terakhir yang menghancurkan kedua belah pihak. Sebuah kemenangan yang dibayar mahal.", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("raja_iblis_final") && storyFlags.at("raja_iblis_final") == 5) {
                    delayPrint(L"HEADLINE UTAMA: ALLAIN RAGNA HENTIKAN ANCAMAN GANDA! JIWA WEISS DIBEBASKAN, RAJA IBLIS MUSNAH!", 30);
                    delayPrint(L"  Isi Berita: Setelah Weiss von Astra dirasuki Vorlag, Allain Ragna berhasil mengalahkan keduanya. Dunia kini aman...", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("raja_iblis_final") && storyFlags.at("raja_iblis_final") == 3) {
                    delayPrint(L"HEADLINE UTAMA: KEGELAPAN MENANG! ARCADIA JATUH DI BAWAH KEKUASAAN RAJA IBLIS VORLAG!", 30);
                    delayPrint(L"  Isi Berita: Perlawanan terakhir telah dipatahkan. Tidak ada lagi harapan. Vorlag kini berkuasa mutlak atas negeri ini...", 20);
                    beritaUtamaTampil = true;
                }
  
                else if (storyFlags.count("pedang_pahlawan_weiss_chosen") && storyFlags.at("pedang_pahlawan_weiss_chosen") == 1 && storyFlags.count("raja_iblis_final") == 0) {
                    delayPrint(L"HEADLINE: LUMANAIRE MOONSWORD TELAH MEMILIH TUANNYA! WEISS VON ASTRA SANG PAHLAWAN TERPILIH!", 30);
                    delayPrint(L"  Isi Berita: Seluruh bangsawan menjadi saksi saat pedang legendaris mengakui Weiss von Astra. Harapan kini ada padanya untuk menghadapi ancaman Raja Iblis yang semakin nyata!", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("pedang_pahlawan_allain_chosen") && storyFlags.at("pedang_pahlawan_allain_chosen") == 1 && storyFlags.count("raja_iblis_final") == 0) {
                    delayPrint(L"HEADLINE: ALLAIN RAGNA, SANG CAHAYA HARAPAN! DIPILIH OLEH PEDANG LEGENDARIS LUMANAIRE!", 30);
                    delayPrint(L"  Isi Berita: Ramalan tergenapi! Allain Ragna diakui oleh Lumanaire MoonSword sebagai pahlawan yang akan memimpin perlawanan melawan kegelapan. Seluruh negeri menaruh harapan padanya.", 20);
                    beritaUtamaTampil = true;
                }

                else if (storyFlags.count("invasi_arcadia") && storyFlags.at("invasi_arcadia") == 1 && storyFlags.count("pedang_pahlawan") == 0) {
                    delayPrint(L"HEADLINE: HEROISME DI BALAI KOTA! WEISS VON ASTRA PATAHKAN SERBUAN IBLIS BAEL!", 30);
                    delayPrint(L"  Isi Berita: Ibukota Arcadia berhasil mempertahankan diri dari serangan Komandan Iblis Bael berkat keberanian Tuan Muda Weiss yang mengalahkan langsung Tangan Kanan Raja Iblis. Warga merayakan, namun kewaspadaan meningkat.", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("invasi_arcadia") == 0 && currentDay > 35 && storyFlags.count("pedang_pahlawan") == 0) {
                    delayPrint(L"HEADLINE: TRAGEDI DI BALAI KOTA! KOMANDAN IBLIS BAEL REBUT PUSAT PEMERINTAHAN!", 30);
                    delayPrint(L"  Isi Berita: Meskipun ada perlawanan, Balai Kota Arcadia jatuh ke tangan iblis. Allain Ragna terlihat memimpin sisa pasukan untuk mengamankan warga dan mundur. Kerusakan parah tak terhindarkan.", 20);
                    beritaUtamaTampil = true;
                }

                else if (storyFlags.count("invasi_mansion") && storyFlags.at("invasi_mansion") == 1 && storyFlags.count("invasi_arcadia") == 0) {
                    delayPrint(L"HEADLINE: PENYERANGAN MENGERIKAN DI KEDIAMAN ASTRA! WEISS VON ASTRA BERHASIL MENGUSIR UTUSAN IBLIS!", 30);
                    delayPrint(L"  Isi Berita: Rumor yang beredar santer tentang serangan iblis tingkat tinggi di Mansion Astra akhirnya terkonfirmasi. Tuan Muda Weiss dikabarkan berhasil mengatasi ancaman tersebut seorang diri. Para bangsawan mulai membicarakan keberaniannya.", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("invasi_mansion") == 0 && currentDay > 25 && storyFlags.count("invasi_arcadia") == 0) {
                    delayPrint(L"HEADLINE: INSIDEN DI MANSION ASTRA! KEDIAMAN BANGSAWAN DISERANG, BANTUAN DATANG TEPAT WAKTU!", 30);
                    delayPrint(L"  Isi Berita: Dilaporkan terjadi serangan misterius di Mansion Astra. Meskipun Tuan Muda Weiss terluka, pasukan kerajaan berhasil mengatasi penyerang. Keamanan di sekitar kediaman bangsawan ditingkatkan.", 20);
                    beritaUtamaTampil = true;
                }
          
                else if (storyFlags.count("duel_persahabatan") && storyFlags.at("duel_persahabatan") == 1 && storyFlags.count("invasi_mansion") == 0) {
                    delayPrint(L"HEADLINE: KEJUTAN DI TURNAMEN BANGSAWAN! WEISS VON ASTRA TAMPIL MEMUkamu, KALAHKAN ALLAIN RAGNA!", 30);
                    delayPrint(L"  Isi Berita: Turnamen persahabatan bangsawan di Colosseum Imperial berakhir dengan kemenangan tak terduga Tuan Muda Weiss atas favorit juara, Allain Ragna. Perubahan besar terlihat pada Tuan Muda Astra, banyak yang mulai memperhitungkannya.", 20);
                    beritaUtamaTampil = true;
                } else if (storyFlags.count("duel_persahabatan") == 0 && currentDay > 15 && storyFlags.count("invasi_mansion") == 0) {
                     delayPrint(L"HEADLINE: ALLAIN RAGNA KEMBALI BERSINAR DI COLOSSEUM!", 30);
                     delayPrint(L"  Isi Berita: Pahlawan muda Allain Ragna sekali lagi menunjukkan kebolehannya dalam turnamen persahabatan bangsawan, mengukuhkan reputasinya sebagai pendekar pedang terbaik di generasinya.", 20);
                     beritaUtamaTampil = true;
                }
                
                if (!beritaUtamaTampil) {
                    int randomBerita = rand() % 4;
                    if (randomBerita == 0) {
                        delayPrint(L"BERITA LOKAL: Perbaikan jalan di distrik perdagangan akan dimulai minggu depan. Beberapa penutupan jalan mungkin terjadi.", 20);
                    } else if (randomBerita == 1) {
                        delayPrint(L"GOSIP BANGSAWAN: Putri Masha von Aurora terlihat semakin sering mengunjungi Taman Norelia untuk proyek botani rahasianya. Ada apa gerangan?", 20);
                    } else if (randomBerita == 2) {
                        delayPrint(L"INFO GUILD: Cross Guild melaporkan peningkatan aktivitas monster minor di sekitar Hutan Merah. Para petualang baru dihimbau berhati-hati.", 20);
                    } else {
                        delayPrint(L"Tidak ada berita yang terlalu menonjol hari ini. Kota Arcadia tampak relatif tenang, meskipun ketegangan perang masih terasa.", 20);
                    }
                }
                wcout << endl;
                waitForEnter();
            } else if (action == "Masuk ke Ancient Temple (Dungeon)") {
                enterDungeon("Ancient Temple");
            } else if (action == "Masuk ke Goa Avernix (Dungeon)") {
                enterDungeon("Goa Avernix");
            } else {
                wcout << L"Aksi belum dikenali!" << endl;
                waitForEnter();
            }
        } else {
            wcout << L"Pilihan tidak valid!" << endl;
            waitForEnter();
        }

            } while(gameRunning && choice != 0);
        }


void exploreArea() {
    string uniqueSubAreaKey = currentWorld + "_" + currentSubArea;

    if (subAreasExploredOnceGlobal.count(uniqueSubAreaKey)) {
        system("cls");
        printLine();
        centerText(L"✦✦✦ CEK SEKITAR ✦✦✦");
        printLine();
        delayPrint(L"kamu sudah memeriksa area " + utf8_to_wstring(currentSubArea) + L" ini dengan saksama sebelumnya.", 20);
        delayPrint(L"Sepertinya tidak ada hal baru yang bisa ditemukan di sini untuk saat ini.", 20);
        printLine();
        waitForEnter();
        return;
    }

    system("cls");
    printLine();
    centerText(L"✦✦✦ CEK SEKITAR ✦✦✦");
    printLine();
    
    delayPrint(L"kamu mengedarkan pandangan, memperhatikan detail di " + utf8_to_wstring(currentSubArea) + L", " + utf8_to_wstring(currentWorld) + L"...", 20);

    int outcomeRoll = rand() % 100;
    bool eventKhususTerjadi = false;

    if (currentWorld == "Mansion Astra") {
        if (currentSubArea == "Kamar Weiss") {
            if (outcomeRoll < 20) {
                delayPrint(L"kamu menemukan beberapa koin emas yang sepertinya terjatuh di bawah ranjang.", 20);
                int foundGold = 5 + rand() % 11; 
                player.gold += foundGold;
                delayPrint(L"💰 Gold +" + to_wstring(foundGold) + L"!", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 40) {
                delayPrint(L"Di antara tumpukan buku di mejamu, ada satu yang belum pernah kamu baca. Isinya tentang etiket bangsawan kuno.", 20);
                player.exp += 5;
                delayPrint(L"📚 EXP +" + to_wstring(5) + L" dari bacaan ringan!", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 70) {
                delayPrint(L"Jendelamu sedikit terbuka, angin sepoi-sepoi masuk membawa aroma taman.", 20);
                delayPrint(L"Tidak ada yang terlalu istimewa, hanya kamarmu yang tenang.", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"kamu merapikan sedikit barang-barangmu. Kamar ini butuh sedikit sentuhan sihir pembersih, mungkin?", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Dapur Mansion") {
            if (outcomeRoll < 25 && sudahBertemuCompanion("Ruigerd")) {
                delayPrint(L"Dari kejauhan, kamu melihat Kepala Koki Ruigerd sedang dengan serius mengawasi para juru masak muda.", 20);
                delayPrint(L"Aroma masakan yang lezat tercium samar-samar.", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 50) {
                delayPrint(L"kamu menemukan beberapa bumbu dapur berkualitas yang sepertinya tidak terpakai.", 20);
                int value = 3 + rand() % 8;
                player.gold += value; 
                delayPrint(L"💰 (Senilai " + to_wstring(value) + L" Gold dari bumbu)!", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Suara dentingan panci dan wajan terdengar dari dalam. Dapur tampak sibuk seperti biasa.", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Taman Floresia") {
            if (outcomeRoll < 25 && sudahBertemuCompanion("Irene")) {
                delayPrint(L"Irene terlihat sedang merawat hamparan bunga mawar dengan sangat telaten di ujung taman.", 20);
                delayPrint(L"Dia tampak sangat damai di antara bunga-bunga itu.", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 50) {
                delayPrint(L"Seekor kupu-kupu berwarna cerah hinggap di jemarimu sejenak sebelum terbang menjauh.", 20);
                delayPrint(L"Momen kecil yang menyenangkan.", 20);
                player.exp += 3;
                delayPrint(L"📚 EXP +" + to_wstring(3) + L"!", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Aroma bunga mawar dan melati memenuhi udara. Taman ini benar-benar terawat dengan baik.", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Lorong Panjang") {
            if (outcomeRoll < 30) {
                delayPrint(L"kamu melihat sebuah lukisan potret leluhur keluarga Astra yang tampak mengawasimu.", 20);
                delayPrint(L"Ada aura kuno dan sedikit misterius darinya.", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Lorong ini panjang dan sedikit temaram. Langkah kakimu menggema pelan di lantai marmer.", 20);
                eventKhususTerjadi = true;
            }
        }
    } else if (currentWorld == "Kota Arcadia") {
        if (currentSubArea == "Balai Kota") {
            if (outcomeRoll < 25 && sudahBertemuCompanion("Charlotte")) {
                delayPrint(L"kamu melihat Charlotte sedang berdebat sengit dengan salah satu staf administrasi, buku catatannya siap di tangan.", 20);
                delayPrint(L"Sepertinya dia sedang mengejar berita penting lagi.", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 50) {
                delayPrint(L"Beberapa bangsawan terlihat keluar dari ruang rapat dengan wajah serius.", 20);
                delayPrint(L"Sepertinya ada pembahasan penting yang baru saja selesai.", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Suasana Balai Kota hari ini cukup sibuk dengan lalu lalang para pejabat dan warga yang mengurus keperluan.", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Cross Guild") {
             if (outcomeRoll < 25 && sudahBertemuCompanion("Ella")) {
                delayPrint(L"Dari ruangannya, kamu bisa melihat siluet Ella yang sedang memeriksa setumpuk dokumen, sesekali memberi perintah tegas.", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 50) {
                delayPrint(L"kamu mendengar beberapa petualang sedang membual tentang monster yang baru saja mereka kalahkan.", 20);
                delayPrint(L"Suasana Guild selalu ramai dan penuh cerita.", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Papan quest penuh dengan berbagai permintaan, dari yang sepele hingga yang berbahaya.", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Perbelanjaan") {
            if (outcomeRoll < 20) {
                delayPrint(L"kamu menemukan sebuah bros kecil yang berkilau terjatuh di dekat etalase toko perhiasan.", 20);
                int value = 15 + rand() % 26; 
                player.gold += value;
                delayPrint(L"💰 kamu menjualnya dan mendapatkan " + to_wstring(value) + L" Gold!", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 60) {
                delayPrint(L"Para pedagang berteriak menawarkan dagangannya. Aroma roti panggang dan rempah-rempah bercampur di udara.", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"kamu melihat beberapa anak jalanan bermain kejar-kejaran di antara kerumunan.", 20);
                eventKhususTerjadi = true;
            }
        }
    } else if (currentWorld == "Hutan Merah") {
        if (currentSubArea == "Pos Hutan") {
            if (outcomeRoll < 25 && sudahBertemuCompanion("Mars")) {
                delayPrint(L"Mars terlihat sedang mengasah kapaknya dengan tatapan fokus, atau sedang mempelajari peta patroli.", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 60) {
                delayPrint(L"kamu menemukan beberapa jenis beri hutan yang bisa dimakan di sekitar pos.", 20);
                delayPrint(L"(Menambah sedikit bekal perjalanan).", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Suara binatang hutan terdengar dari kejauhan. Angin sejuk berhembus membawa aroma pinus.", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Reruntuhan Kuno") {
             if (outcomeRoll < 30) {
                delayPrint(L"kamu melihat ukiran kuno yang samar di salah satu batu reruntuhan. Sepertinya simbol peradaban yang telah lama hilang.", 20);
                player.exp += 8;
                delayPrint(L"📚 EXP +" + to_wstring(8) + L"!", 20);
                eventKhususTerjadi = true;
             } else {
                delayPrint(L"Reruntuhan ini diselimuti lumut dan tanaman liar. Suasananya sunyi dan sedikit angker.", 20);
                eventKhususTerjadi = true;
             }
        }
    } else if (currentWorld == "Goa Avernix") {
        if (currentSubArea == "Camp Avernix") {
            if (outcomeRoll < 25 && sudahBertemuCompanion("Kinich")) {
                delayPrint(L"Kinich terlihat sedang memberi arahan kepada para penambang sebelum mereka masuk ke goa.", 20);
                delayPrint(L"Ekspresinya tegas seperti biasa.", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 50) {
                delayPrint(L"Beberapa penambang sedang beristirahat sambil membersihkan peralatan mereka yang kotor.", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Udara di sekitar camp berbau belerang dan debu batu bara. Suara dentuman dari dalam goa sesekali terdengar.", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Tambang Terbengkalai") {
            if (outcomeRoll < 20) {
                delayPrint(L"Di antara puing-puing, kamu menemukan sepotong kecil bijih berkualitas rendah.", 20);
                int value = 5 + rand() % 11;
                player.gold += value;
                delayPrint(L"💰 (Senilai " + to_wstring(value) + L" Gold)!", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Lorong tambang ini gelap dan penuh sarang laba-laba. Terasa ada aura tidak menyenangkan.", 20);
                eventKhususTerjadi = true;
            }
        }
    } else if (currentWorld == "Puncak Arcadia") {
        if (currentSubArea == "Taman Norelia") {
            if (outcomeRoll < 25 && sudahBertemuCompanion("Masha")) {
                delayPrint(L"kamu melihat Masha von Aurora sedang membaca buku di bangku taman favoritnya, tampak anggun dan menyendiri.", 20);
                eventKhususTerjadi = true;
            } else if (outcomeRoll < 60) {
                delayPrint(L"Pemandangan kota Arcadia dari atas puncak ini sungguh menakjubkan.", 20);
                delayPrint(L"Angin gunung terasa sejuk dan menyegarkan.", 20);
                eventKhususTerjadi = true;
            } else {
                delayPrint(L"Beberapa bangsawan lain juga terlihat sedang berjalan-jalan menikmati keindahan taman.", 20);
                eventKhususTerjadi = true;
            }
        } else if (currentSubArea == "Bendungan" || currentSubArea == "Bukit Myriad") {
            if (outcomeRoll < 30) {
                 delayPrint(L"Suara gemericik air dari bendungan dan pemandangan lembah hijau menenangkan pikiranmu.", 20);
                 eventKhususTerjadi = true;
            } else {
                 delayPrint(L"kamu melihat beberapa elang terbang tinggi di atas perbukitan. Langit sangat cerah hari ini.", 20);
                 eventKhususTerjadi = true;
            }
        }
    }
    

    if (!eventKhususTerjadi) {
        int genericOutcome = rand() % 3;
        switch(genericOutcome) {
            case 0:
                delayPrint(L"kamu tidak menemukan sesuatu yang istimewa, namun udara segar cukup menyegarkan pikiran.", 20);
                break;
            case 1:
                delayPrint(L"kamu merenung sejenak, memikirkan langkah selanjutnya dalam petualanganmu.", 20);
                player.exp += 2;
                delayPrint(L"📚 EXP +" + to_wstring(2) + L"!", 20);
                break;
            case 2:
                delayPrint(L"Area ini tampak tenang. kamu melanjutkan perjalananmu dengan lebih waspada.", 20);
                break;
        }
    }
    
    subAreasExploredOnceGlobal.insert(uniqueSubAreaKey); 
    printLine();
    waitForEnter();
}


void showWorldMapLocationMenu() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ PETA DUNIA - PILIH WILAYAH TUJUAN ✦✦✦");
    printLine();

    vector<string> availableWorlds;
    wcout << L"Saat ini kamu berada di: " << utf8_to_wstring(currentWorld) << endl;
    wcout << L"Wilayah yang bisa dikunjungi:" << endl;
    printLine(50, L'-');

    int displayIndex = 1;
    for (const auto& pair_world : allWorlds) {
        const string& worldName = pair_world.first;
        if (worldName != currentWorld) {
            wcout << L"  ❖ " << displayIndex++ << L". " << utf8_to_wstring(worldName) << endl;
            availableWorlds.push_back(worldName);
        }
    }

    printLine(50, L'-');
    wcout << L"  ❖ 0. Kembali ke Menu Pilihan Lokasi" << endl;
    printLine(50, L'-');
    wcout << L"Pilih wilayah tujuan (nomor) ✦: ";
    
    int choice = getValidatedChoice(0, static_cast<int>(availableWorlds.size()));

    if (choice == 0) {
        return; 
    }

    if (choice > 0 && static_cast<size_t>(choice) <= availableWorlds.size()) {
        string selectedWorld = availableWorlds[choice - 1];
        string targetStartSubArea = allWorlds[selectedWorld].startSubArea;

        system("cls");
        printLine();
        centerText(L"✈️ PERJALANAN ANTAR WILAYAH ✈️");
        printLine();
        delayPrint(L"kamu mempersiapkan diri untuk melakukan perjalanan ke " + utf8_to_wstring(selectedWorld) + L"...", 30);

        bool canTravelAndActionConsumed = false;

        if (selectedWorld == "Mansion Astra") {
            delayPrint(L"kamu memutuskan untuk segera kembali ke Mansion Astra. Perjalanan ini terasa cepat dan tidak melelahkan.", 20);
            currentWorld = selectedWorld;
            currentSubArea = targetStartSubArea;
            canTravelAndActionConsumed = true; 
        } else {
            if (currentActionsRemaining > 0) {
                delayPrint(L"Perjalanan ini akan menghabiskan 1 poin aksi.", 20);
                currentWorld = selectedWorld;
                currentSubArea = targetStartSubArea;
                consumeAction(); 
                canTravelAndActionConsumed = true;
            } else {
                delayPrint(L"Sayangnya kamu tidak punya cukup poin aksi (0 tersisa) untuk melakukan perjalanan jauh hari ini.", 20);
                delayPrint(L"kamu memutuskan untuk tetap tinggal di " + utf8_to_wstring(currentWorld) + L" (lokasi saat ini).", 20);
                canTravelAndActionConsumed = false; 
            }
        }

        if (canTravelAndActionConsumed) {
            delayPrint(L"kamu telah tiba di " + utf8_to_wstring(currentSubArea) + L", " + utf8_to_wstring(currentWorld) + L".", 30);
            
            ActiveDailyQuestNode* currentQuestNode = activeDailyQuestsHead;
            ActiveDailyQuestNode* prevQuestNode = nullptr;
            int expFromCompletedQuests = 0;

            while (currentQuestNode != nullptr) {
                DailyQuest& quest = currentQuestNode->data;
                bool wasThisQuestCompleted = false;

                if (quest.type == "travel" && quest.taken && !quest.completed) {
                    bool targetLocationReached = false;
                    
                    if (!quest.dungeonName.empty() && currentWorld == quest.dungeonName && currentSubArea == quest.target) {
                        targetLocationReached = true;
                    } else if (quest.dungeonName.empty() && allWorlds.count(currentWorld) && allWorlds.at(currentWorld).subAreas.count(currentSubArea) && currentSubArea == quest.target) {
                        targetLocationReached = true;
                    }

                    if (targetLocationReached) {
                        quest.completed = true;
                        expFromCompletedQuests += quest.expReward;
                        player.gold += quest.goldReward;
                        system("cls"); printLine();
                        centerText(L"🎉 QUEST SELESAI! 🎉"); printLine();
                        delayPrint(L"✓ kamu telah menyelesaikan Quest Harian: " + utf8_to_wstring(quest.title) + L"!", 20);
                        delayPrint(L"  Hadiah: +" + to_wstring(quest.expReward) + L" EXP, +" + to_wstring(quest.goldReward) + L" Gold", 20);
                        printLine(); waitForEnter();
                        wasThisQuestCompleted = true;
                    }
                }

                ActiveDailyQuestNode* nodeToDelete = nullptr;
                if (wasThisQuestCompleted) {
                    nodeToDelete = currentQuestNode;
                    if (prevQuestNode == nullptr) {
                        activeDailyQuestsHead = currentQuestNode->next;
                        currentQuestNode = activeDailyQuestsHead;
                    } else {
                        prevQuestNode->next = currentQuestNode->next;
                        currentQuestNode = prevQuestNode->next;
                    }
                    if (nodeToDelete != nullptr) { 
                         delete nodeToDelete;
                    }
                } else {
                    prevQuestNode = currentQuestNode;
                    currentQuestNode = currentQuestNode->next;
                }
            }

            if (expFromCompletedQuests > 0) {
                handleExperienceAndLevelUp(player, expFromCompletedQuests);
            }
        }
        waitForEnter();
        
    } else if (choice != 0) { 
        delayPrint(L"Pilihan wilayah tidak valid.", 20);
        waitForEnter();
    }
}



void showLocationMenu() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ PILIH LOKASI ✦✦✦");
    printLine();

    vector<string> destinations = locationGraph[currentSubArea];
    for (size_t i = 0; i < destinations.size(); ++i) {
        wcout << L"  " << (i + 1) << L". " << utf8_to_wstring(destinations[i]) << endl;
    }

    size_t worldMapOption = destinations.size() + 1;
    size_t backOption = destinations.size() + 2;

    wcout << L"  " << worldMapOption << L". Ke World Map" << endl;
    wcout << L"  " << backOption << L". Kembali" << endl;

    wcout << L"Pilih tujuan (1-" << backOption << L"): ";
    int choice;
    choice = getValidatedChoice(1, 4); 


    if (choice >= 1 && choice <= destinations.size()) {
        string targetSubArea = destinations[choice - 1];
        unordered_set<string> visited;
        vector<string> travelPath;

        dfsTravel(currentSubArea, targetSubArea, visited, travelPath);

        if (!travelPath.empty() && travelPath.back() == targetSubArea) {
            for (const auto& step : travelPath) {
                wcout << L"➤ Menuju " << utf8_to_wstring(step) << endl;
                this_thread::sleep_for(chrono::milliseconds(300));
            }
            currentSubArea = targetSubArea;
            ActiveDailyQuestNode* currentQuestNode = activeDailyQuestsHead;
ActiveDailyQuestNode* prevQuestNode = nullptr;
int expFromCompletedQuests = 0;

while (currentQuestNode != nullptr) {
    DailyQuest& quest = currentQuestNode->data;
    bool wasThisQuestCompleted = false;

    if (quest.type == "travel" && quest.taken && !quest.completed) {
        bool targetLocationReached = false;

        if (!quest.dungeonName.empty() &&
            currentWorld == quest.dungeonName &&
            currentSubArea == quest.target) {
            targetLocationReached = true;
        }
        else if (quest.dungeonName.empty() &&
                 currentSubArea == quest.target) {
            targetLocationReached = true;
        }

        if (targetLocationReached) {
            quest.completed = true;
            expFromCompletedQuests += quest.expReward;
            player.gold += quest.goldReward;
            delayPrint(L"✓ Quest Harian Selesai: " + utf8_to_wstring(quest.title) + L"!", 20);
            delayPrint(L"  Reward: +" + to_wstring(quest.expReward) + L" EXP, +" + to_wstring(quest.goldReward) + L" Gold", 20);
            wasThisQuestCompleted = true;
        }
    }

    ActiveDailyQuestNode* nodeToDelete = nullptr;
    if (wasThisQuestCompleted) {
        nodeToDelete = currentQuestNode;
        if (prevQuestNode == nullptr) {
            activeDailyQuestsHead = currentQuestNode->next;
            currentQuestNode = activeDailyQuestsHead;
        } else {
            prevQuestNode->next = currentQuestNode->next;
            currentQuestNode = prevQuestNode->next;
        }
        delete nodeToDelete;
    } else {
        prevQuestNode = currentQuestNode;
        currentQuestNode = currentQuestNode->next;
    }
}

if (expFromCompletedQuests > 0) {
    handleExperienceAndLevelUp(player, expFromCompletedQuests);
}
        } else {
            wcout << L"Tidak ada jalur ke lokasi tersebut." << endl;
        }
        waitForEnter();
    } else if (choice == worldMapOption) {
        showWorldMapLocationMenu(); 
    } else if (choice == backOption) {
        return; 
    } else {
        wcout << L"Pilihan tidak valid." << endl;
        waitForEnter();
    }
}





int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    srand(time(0));
    readSaveDataFromFile();
    int choice;
    do {
        showTitleScreen();
        choice = getValidatedChoice(1, 4); 

        
        switch(choice) {
            case 1: {
                initializeGame();
                showBeforePrologue();
                showPrologue();
                inputPlayerName();
                chooseInitialMagicElements(player);
                showTutorial();
                showGameMenu();
                break;
            }
            case 2: {
                loadGame();
                break;
            }
            case 3: {
                system("cls");
                printLine();
                centerText(L"✦✦✦ ABOUT ✦✦✦");
                printLine();
                wcout << endl;
                centerText(L"Text-Based RPG Game");
                centerText(L"Versi 1.0");
                centerText(L"Dibuat dengan C++");
                wcout << endl;
                waitForEnter();
                break;
            }
            case 4: {
                wcout << L"Terima kasih telah bermain!" << endl;
                return 0;
            }
            default: {
                wcout << L"Pilihan tidak valid!" << endl;
                waitForEnter();
                break;          
            }
        }
    } while(choice != 4);
    
    return 0;
}