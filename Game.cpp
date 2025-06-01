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

// Struktur Data Utama
struct Item {
    string name;
    string type;
    int value; // Mungkin nilai jual dasar atau nilai generik
    string description;
    int statRequirement;
    int price; // Harga beli dari toko
};

struct Weapon {
    string name;
    int attackPower;
    int strengthRequired;
    int intelligenceRequired;
    string description; // Deskripsi akan dalam Bahasa Indonesia
    bool equipped;
    int price; // Harga beli dari penempa
    string requiredStoryFlagKey; // Kunci flag cerita yang dibutuhkan, misal "blacksmith_tier1_unlocked"
    int requiredStoryFlagValue;  // Nilai flag yang dibutuhkan, misal 1 (untuk true/terbuka)
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
    string id;                      // Unique ID, e.g., "FIREBALL_1"
    string name;                    // Display name, e.g., "Bola Api"
    string description;
    string elementType;             // "Fire", "Ice", etc.
    int tier;                       // 1, 2, atau 3
    int manaCost;
    int basePower;                 // For damage or heal
    string targetType;              // "SingleEnemy", "AllEnemies", "Self", "Ally"
    bool isEnchantment;             // True if this spell enchants a weapon
    int enchantTurns;               // Duration of enchantment
    int enchantAttackBonus;         // Bonus attack if enchantment
    vector<string> prerequisites;   // List of spell IDs required to learn this
    // bool unlockedByPlayer = false; // We will manage this via player.knownSpells
};

struct ActiveEnchantment {
    string spellId;
    string spellName; // For display or easier reference
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

// Di dekat definisi struct lainnya
struct ActiveRuneEffect {
    string spellId;         // ID dari spell yang menerapkan rune (misal, "FIRE_EXPLOSIVE_RUNE_2")
    string spellName;       // Nama spell untuk ditampilkan
    string elementType;     // Tipe elemen dari damage rune
    int damageOnTrigger;    // Damage yang diberikan saat rune meledak/aktif
    int turnsUntilTrigger;  // Hitungan mundur giliran sampai rune aktif
    // bool triggerOnHit;   // Opsional: jika rune aktif saat musuh diserang (bisa ditambahkan nanti)
    // bool triggered;      // Untuk memastikan hanya aktif sekali (jika diperlukan)

    ActiveRuneEffect(string id = "", string name = "", string eType = "None", int dmg = 0, int turns = 0)
        : spellId(id), spellName(name), elementType(eType), damageOnTrigger(dmg), turnsUntilTrigger(turns) {}
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
    vector<Item*> inventory;
    vector<Weapon*> weapons;
    // vector<Magic*> knownMagic; // OLD: To be replaced
    Weapon* equippedWeapon;

    long long expToNextLevel; // Changed to long long to avoid overflow with higher levels
    int skillPoints;
    vector<string> unlockedMagicElements; // Names of elements like "Fire", "Ice"
    vector<string> knownSpells;         // IDs of learned MagicSpell
    vector<ActiveEnchantment> activeEnchantments;
    vector<ActiveHoTEffect> activeHoTs;
};

struct MagicElement {
    string name; // "Fire", "Thunder", etc.
    string description;
    map<string, MagicSpell> spells; // Key is spellId, value is the MagicSpell object
                                    // Tier and branching are handled by MagicSpell.tier and prerequisites
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

    // Status Effects
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
    vector<ActiveRuneEffect> activeRunes; // Tambahkan ini jika belum

    // Constructor Lengkap dengan default arguments
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
    int level;
    int hp;
    int maxHp;
    int loyalty;
    string personality;
    string description;
    vector<string> abilities;
    bool met;
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
    string type; // "ascending" atau "descending"
    int currentFloor = 1;
    int maxUnlockedFloor = 1;
    bool printAsBasement = false;

    map<int, vector<string>> floorEnemies; // daftar nama enemy per lantai
    map<int, string> miniBosses;
    map<int, string> finalBoss;
    vector<int> storyLockedFloors;
    map<int, CampArea> campAreas;
    vector<int> visitedCampAreas;
};

unordered_map<string, WorldArea> allWorlds;
unordered_map<string, Dungeon> allDungeons;
unordered_map<string, Enemy> enemyDatabase;
unordered_map<string, bool> defeatedBosses;
unordered_map<string, vector<wstring>> asciiArtMap;
string currentWorld = "Mansion Astra";
string currentSubArea = "Kamar Weiss";

// Global Variables
Character player;
vector<Companion> companions;
vector<Item> allItems;
vector<Weapon> allWeapons;
vector<Magic> allMagic;
unordered_map<string, Item*> itemDatabase;
unordered_map<string, Weapon*> weaponDatabase;
unordered_map<string, Magic*> magicDatabase;
unordered_map<string, int> storyFlags;
unordered_map<string, int> companionRelations;
map<string, Location> worldMap;
map<string, MagicElement> allMagicElements;
queue<GameEvent> scheduledEvents;
stack<Character> playerStateHistory;
Quest* questHead = nullptr;
const double BASE_XP = 7.0;
const double XP_EXPONENT = 1.1;
const vector<int> MAGIC_ELEMENT_UNLOCK_LEVELS = {20, 40, 60, 80, 100}; 
int currentDay = 1;
bool gameRunning = true;
string currentLocation = "Noble's Room";
// Function Declarations
void delayPrint(const wstring& text, int delayMs = 10);
void printLine(int len = 100, wchar_t ch = L'═');
void centerText(const wstring& text, int width = 100);
void showTitleScreen();
void showBeforePrologue();
void showPrologue();
void inputPlayerName();
void showTutorial();
void initializeGame();
void showGameMenu();
void exploreArea();
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
void showCalendar();
void showDiaryMenu();
void setupWorldAreas();
bool startBattle(Enemy& baseEnemy);
void displayEnemyASCII(const string& enemyName);
void loadEnemyASCIIFromFile(const string& filename);


// Utility Functions
wstring utf8_to_wstring(const string& str_utf8) {
    // Menggunakan using namespace std; maka std:: tidak diperlukan lagi
    if (str_utf8.empty()) {
        return wstring();
    }
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str_utf8[0], (int)str_utf8.length(), NULL, 0);
    if (size_needed == 0) {
        // Anda mungkin ingin mencatat error di sini atau melempar exception
        // DWORD error = GetLastError();
        // wcout << L"MultiByteToWideChar failed to calculate size. Error: " << error << endl;
        return wstring(); // Kembalikan string kosong atau tangani error dengan tepat
    }
    wstring wstr_to(size_needed, 0);
    int chars_converted = MultiByteToWideChar(CP_UTF8, 0, &str_utf8[0], (int)str_utf8.length(), &wstr_to[0], size_needed);
    if (chars_converted == 0) {
        // DWORD error = GetLastError();
        // wcout << L"MultiByteToWideChar failed to convert. Error: " << error << endl;
        return wstring(); // Kembalikan string kosong atau tangani error dengan tepat
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
    wcout << L"Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), L'\n');
    cin.get();
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
    wcout << L"Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), L'\n');
    cin.get();
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
        cin >> choice;
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
    cin.ignore();
}

// Modify inputPlayerName()
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
    // If previous cin was >> int, then ignore newline
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, realName);
    
    player.name = "Weiss von Astra (" + realName + ")";
    
    wcout << endl;
    delayPrint(L"Baiklah, " + utf8_to_wstring(realName) + L"...", 20);
    delayPrint(L"Sekarang kau adalah Weiss von Astra!", 20);
    delayPrint(L"Tapi jiwamu tetap " + utf8_to_wstring(realName) + L"!", 20);
}

void showTutorial() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ TUTORIAL & OBJECTIVES ✦✦✦");
    printLine();
    wcout << endl;
    
    delayPrint(L"=== TUJUAN UTAMA ===", 20);
    delayPrint(L"✦ 1. BERTAHAN HIDUP - Hindari kematian seperti di novel asli!", 20);
    delayPrint(L"✦ 2. DERAIL THE PLOT - Ubah alur cerita sesuai keinginanmu!", 20);
    delayPrint(L"✦ 3. BECOME POWERFUL - Kuasai sihir dan jadi yang terkuat!", 20);
    delayPrint(L"✦ 4. FIND DECENT TEA - Temukan teh yang layak di dunia ini!", 20);
    wcout << endl;
    
    delayPrint(L"=== KONTROL GAME ===", 20);
    delayPrint(L"✦ CEK SEKITAR - Eksplorasi lingkungan dan temukan item", 20);
    delayPrint(L"✦ BUKA DIARY - Akses menu sistem (status, inventory, dll)", 20);
    delayPrint(L"✦ PILIH LOKASI - Pergi ke tempat lain", 20);
    wcout << endl;
    
    delayPrint(L"=== TIPS BERTAHAN HIDUP ===", 20);
    delayPrint(L"✦ Tingkatkan stats dengan EXP", 20);
    delayPrint(L"✦ Pelajari sihir untuk melawan musuh", 20);
    delayPrint(L"✦ Bangun hubungan dengan companion", 20);
    delayPrint(L"✦ Perhatikan event yang dijadwalkan", 20);
    wcout << endl;
    
    printLine();
    wcout << L"Siap memulai petualangan? Tekan Enter...";
    cin.get();
}

// Calculates EXP needed for the next level
long long calculateExpToNextLevel(int currentLevel) {
    if (currentLevel <= 0) return static_cast<long long>(BASE_XP); // Should not happen if level starts at 1
    return static_cast<long long>(floor(BASE_XP * pow(static_cast<double>(currentLevel), XP_EXPONENT)));
}

void initializeSpellsForElement(MagicElement& element) {
    // === FIRE ELEMENT (Diperluas) ===
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
        f1_3.elementType = "Fire"; f1_3.tier = 1; f1_3.manaCost = 12; f1_3.basePower = 5; // DoT damage per turn
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
        f2_2.elementType = "Fire"; f2_2.tier = 2; f2_2.manaCost = 28; f2_2.basePower = 35; // Plus strong DoT
        f2_2.targetType = "SingleEnemy"; f2_2.isEnchantment = false; f2_2.prerequisites = {"FIRE_IGNITE_1"}; element.spells[f2_2.id] = f2_2;

        f2_3.id = "FIRE_INTENSE_BURN_2"; f2_3.name = "Intense Burn"; f2_3.description = "Meningkatkan damage dari efek terbakar (DoT) yang sudah ada pada target.";
        f2_3.elementType = "Fire"; f2_3.tier = 2; f2_3.manaCost = 25; f2_3.basePower = 10; // Boosts existing DoT damage
        f2_3.targetType = "SingleEnemy"; f2_3.isEnchantment = false; f2_3.prerequisites = {"FIRE_IGNITE_1"}; element.spells[f2_3.id] = f2_3;

        f2_4.id = "FIRE_BLAZING_SOUL_2"; f2_4.name = "Blazing Soul"; f2_4.description = "Meningkatkan kekuatan sihir api (Intelligence) pengguna untuk sementara waktu.";
        f2_4.elementType = "Fire"; f2_4.tier = 2; f2_4.manaCost = 20; f2_4.basePower = 0;
        f2_4.targetType = "Self"; f2_4.isEnchantment = true; f2_4.enchantTurns = 4; f2_4.prerequisites = {"FIRE_EMBER_1"}; element.spells[f2_4.id] = f2_4;

        f2_5.id = "FIRE_EXPLOSIVE_RUNE_2"; f2_5.name = "Explosive Rune"; f2_5.description = "Menanam rune api pada target yang akan meledak setelah beberapa giliran.";
        f2_5.elementType = "Fire"; f2_5.tier = 2; f2_5.manaCost = 18; f2_5.basePower = 50; // Damage on explosion
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
        f3_4.elementType = "Fire"; f3_4.tier = 3; f3_4.manaCost = 55; f3_4.basePower = 40; // Initial damage, plus strong DoT
        f3_4.targetType = "SingleEnemy"; f3_4.isEnchantment = false; f3_4.prerequisites = {"FIRE_EXPLOSIVE_RUNE_2"}; element.spells[f3_4.id] = f3_4;

        f3_5.id = "FIRE_INFERNO_PILLAR_3"; f3_5.name = "Inferno Pillar"; f3_5.description = "Memanggil pilar api raksasa untuk menghanguskan satu target dengan damage masif.";
        f3_5.elementType = "Fire"; f3_5.tier = 3; f3_5.manaCost = 80; f3_5.basePower = 150;
        f3_5.targetType = "SingleEnemy"; f3_5.isEnchantment = false; f3_5.prerequisites = {"FIRE_METEOR_STRIKE_3", "FIRE_PHOENIX_BLESSING_3"}; element.spells[f3_5.id] = f3_5;
    }
    // === ICE ELEMENT (Adjusted) ===
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
    // === THUNDER ELEMENT (Adjusted) ===
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
        t1_3.elementType = "Thunder"; t1_3.tier = 1; t1_3.manaCost = 13; t1_3.basePower = 6; // DoT damage
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
        t3_2.elementType = "Thunder"; t3_2.tier = 3; t3_2.manaCost = 68; t3_2.basePower = 30; // Multi-hit
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
    // === WIND ELEMENT (Adjusted) ===
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
        w3_1.elementType = "Wind"; w3_1.tier = 3; w3_1.manaCost = 60; w3_1.basePower = 50; // Plus strong DoT
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
        w3_5.elementType = "Wind"; w3_5.tier = 3; w3_5.manaCost = 88; w3_5.basePower = 130; // Multi-hit or high damage
        w3_5.targetType = "SingleEnemy"; w3_5.isEnchantment = false; w3_5.prerequisites = {"WIND_TORNADO_OF_DESTRUCTION_3", "WIND_SKY_LORDS_WRATH_3"}; element.spells[w3_5.id] = w3_5;
    }
    // === DARK ELEMENT (Adjusted) ===
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
    // === LIGHT ELEMENT (Adjusted) ===
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

// Initialize Game Data
void initializeGame() {
    srand(time(nullptr));   
    setupWorldAreas();

    // Setup Player
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
    player.inventory.clear(); // Pastikan inventory kosong di awal
    player.weapons.clear();
    
    allItems = {
        // Nama, Tipe, Nilai Jual (opsional), Deskripsi, Syarat Stat, Harga Beli
        {"Health Potion", "consumable", 25, "Memulihkan 50 HP.", 0, 100},
        {"Mana Potion", "consumable", 20, "Memulihkan 30 Mana.", 0, 100},
        {"Big Health Potion", "consumable", 60, "Memulihkan 150 HP dengan cepat.", 0, 275},
        {"Big Mana Potion", "consumable", 50, "Memulihkan 100 Mana dengan cepat.", 0, 275},
        {"Smoke Bomb", "consumable", 50, "Menjamin kabur dari pertarungan non-boss.", 0, 150},
        {"Earl Grey Tea", "consumable", 10, "Secangkir teh yang nikmat. Akhirnya!", 0, 50},
        {"Minor Strength Elixir", "consumable", 60, "Sedikit meningkatkan Kekuatan untuk sementara.", 0, 250},
        {"Minor Focus Elixir", "consumable", 60, "Sedikit meningkatkan Intelijensia untuk sementara.", 0, 250}
    };

    // Setup Weapons 
    allWeapons = {
        // Name, ATK, STR_REQ, INT_REQ, Description (Indonesian), Equipped, Price, FlagKey, FlagValue
        {"Noble's Sword", 25, 5, 0, "Pedang turun temurun keluarga Weiss, lebih untuk pertarungan.", false, 750, "spesific_quest_completed", 0},

        // Blacksmith Tier 0 (Always available or very early unlock)
        {"Rusty Shortsword", 12, 5, 0, "Bilah terlupakan, lebih baik daripada tangan kosong.", false, 150, "no_flag", 0},
        {"Training Sword", 18, 8, 0, "Pedang standar untuk berlatih tebasan dasar.", false, 300, "no_flag", 0},
        {"Steel Dagger", 15, 3, 0, "Belati baja tajam dan ringan, cocok untuk serangan cepat.", false, 250, "no_flag", 0},
        {"Iron Kukri", 19, 7, 0, "Pedang melengkung dari besi, tebasannya cukup baik.", false, 350, "no_flag", 0},
        {"Light War Hammer", 20, 10, 0, "Palu tumpul ringan, efektif melawan armor sederhana.", false, 400, "no_flag", 0},

        // Blacksmith Tier 1 (Example: unlocked by storyFlags["blacksmith_tier1_unlocked"] = 1)
        {"Iron Longsword", 30, 12, 0, "Pedang panjang dari besi yang kokoh dan dapat diandalkan.", false, 1200, "blacksmith_tier1_unlocked", 1},
        {"Steel Kite Shield (Weapon)", 10, 15, 0, "Perisai yang juga bisa digunakan untuk memukul. (Dihitung sebagai senjata)", false, 1000, "blacksmith_tier1_unlocked", 1},
        {"Reinforced Staff", 28, 0, 20, "Tongkat yang diperkuat dengan lilitan logam.", false, 1100, "blacksmith_tier1_unlocked", 1},
        {"Cavalry Sword", 32, 14, 0, "Pedang lurus yang biasa digunakan pasukan berkuda.", false, 1500, "blacksmith_tier1_unlocked", 1},
        {"Steel War Axe", 35, 16, 0, "Kapak dari baja, membutuhkan kekuatan lebih untuk ayunan kuat.", false, 1700, "blacksmith_tier1_unlocked", 1},

        // Blacksmith Tier 2 (Example: unlocked by storyFlags["blacksmith_tier2_unlocked"] = 1)
        {"Knight's Arming Sword", 45, 18, 5, "Pedang seimbang yang pantas untuk seorang kesatria.", false, 3500, "blacksmith_tier2_unlocked", 1},
        {"Elven Thinblade", 40, 15, 10, "Bilah ringan dan cepat buatan peri, meningkatkan kelincahan.", false, 4000, "blacksmith_tier2_unlocked", 1},
        {"Battlemage's Rod", 38, 5, 25, "Gada dirancang untuk penyihir yang bertarung di garis depan.", false, 3200, "blacksmith_tier2_unlocked", 1},
        {"Bastard Flamberge", 48, 20, 0, "Pedang dengan bilah bergelombang, menakutkan dan mematikan.", false, 5000, "blacksmith_tier2_unlocked", 1},
        {"Moonlit Spellblade", 42, 17, 22, "Pedang yang bersinar lembut, dialiri energi bulan.", false, 5500, "blacksmith_tier2_unlocked", 1},

        // Blacksmith Tier 3 (Example: unlocked by storyFlags["blacksmith_tier3_unlocked"] = 1)
        {"Executioner's Greatsword", 70, 28, 0, "Pedang raksasa yang dirancang untuk kekuatan mentah.", false, 10000, "blacksmith_tier3_unlocked", 1},
        {"Crystal-Core Blade", 60, 22, 15, "Bilah dengan inti kristal yang dialiri sihir.", false, 12000, "blacksmith_tier3_unlocked", 1},
        {"Archmage's War Staff", 55, 10, 40, "Tongkat ampuh untuk sihir ofensif kuat dan pertarungan jarak dekat.", false, 9000, "blacksmith_tier3_unlocked", 1},
        {"Rune-Shatterer Claymore", 65, 25, 20, "Ditempa khusus untuk menetralkan atau menghancurkan sihir.", false, 15000, "blacksmith_tier3_unlocked", 1},
        {"Stormbringer Replica", 75, 30, 10, "Pedang legendaris yang konon bisa memanggil petir.", false, 18000, "blacksmith_tier3_unlocked", 1},

        // Contoh senjata unik, mungkin dari quest atau drop langka
        {"Lumanaire MoonSword", 99, 70, 50, "Pedang sihir kuat, tidak umum dijual.", false, 20000, "specific_quest_completed", 1}
    };
    
    
    itemDatabase.clear();
    for(auto& item : allItems) {
        itemDatabase[item.name] = &item;
    }
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

    // Setup Companions
    companions = {
        {"Seraphina", 1, 80, 80, 50, "Tsundere", "A noble lady with complicated feelings", {"Healing Magic", "Sword Skills"}, false},
        {"Marcus", 1, 120, 120, 30, "Loyal Knight", "Your devoted bodyguard", {"Shield Bash", "Taunt"}, true},
        {"Luna", 1, 60, 60, 70, "Mysterious Mage", "A girl with hidden powers", {"Dark Magic", "Stealth"}, false}
    };
    
    // Initialize relations
    for(auto& comp : companions) {
        companionRelations[comp.name] = comp.loyalty;
    }
    
    // Setup initial quests
    Quest* quest1 = new Quest{"Avoid Death Flags", "Don't die like a typical villain", false, 100, nullptr};
    Quest* quest2 = new Quest{"Find Decent Tea", "Locate Earl Grey in this fantasy world", false, 50, nullptr};
    Quest* quest3 = new Quest{"Derail the Plot", "Prevent the protagonist from following the story", false, 200, nullptr};
    
    quest1->next = quest2;
    quest2->next = quest3;
    questHead = quest1;
    
    // Setup scheduled events
    scheduledEvents.push({"Magic Academy Entrance", "Time to enroll and meet the protagonist", 30, false});
    scheduledEvents.push({"Annual Magic Tournament", "Where villains typically lose", 60, false});
    scheduledEvents.push({"Royal Ball", "Social event with plot significance", 90, false});
    
    // Initialize story flags
    storyFlags["met_protagonist"] = 0;
    storyFlags["discovered_tea"] = 0;
    storyFlags["plot_derailed"] = 0;
    storyFlags["learned_forbidden_magic"] = 0;

    //Blacksmith Flags
    storyFlags["blacksmith_tier1_unlocked"] = 0;
    storyFlags["blacksmith_tier2_unlocked"] = 0;
    storyFlags["blacksmith_tier3_unlocked"] = 0;



 // --- Common Enemies: Level 1-5 ---
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

    // --- Common Enemies: Level 6-10 ---
    enemyDatabase["KoboldPathguard"] =       {"Kobold Pathguard", 6, 60, 60, 22, 8, 30, 15, 10, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CaveLurker"] =            {"Cave Lurker", 6, 55, 55, 24, 6, 32, 16, 10, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AnimatedSword"] =         {"Animated Sword", 7, 70, 70, 28, 12, 40, 20, 10, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["UmbralCrawler"] =         {"Umbral Crawler", 8, 65, 65, 30, 7, 42, 20, 10, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AncientSentryFragment"] = {"Ancient Sentry Fragment", 9, 80, 80, 32, 15, 50, 25, 10, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ShadowPup"] =             {"Shadow Pup" , 9, 60, 60, 35, 8, 48, 24, 14, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Common Enemies: Level 11-15 ---
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

    // --- Common Enemies: Level 16-20 ---
    enemyDatabase["CorruptedCherub"] =       {"Corrupted Cherub", 16, 90, 90, 40, 12, 120, 55, 24, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["KoboldDigger"] =          {"Kobold Digger", 17, 100, 100, 42, 16, 130, 60, 23, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ObsidianRazorfiend"] =    {"Obsidian Razorfiend", 18, 90, 90, 42, 12, 150, 70, 24, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["PhantomWarrior"] =        {"Phantom Warrior", 19, 140, 140, 45, 15, 160, 75, 23, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AltarGuardian"] =         {"Altar Guardian", 19, 150, 150, 48, 22, 170, 80, 26, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Common Enemies: Level 21-25 ---
    enemyDatabase["CharredSalamander"] =     {"Charred Salamander", 21, 150, 150, 50, 20, 200, 90, 28, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ForestSpider"] =          {"Forest Spider", 21, 140, 140, 48, 18, 190, 85, 28, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["StoneLionCub"] =          {"Stone Lion Cub", 22, 160, 160, 55, 25, 220, 100, 30, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["RiverSerpent"] =          {"River Serpent", 23, 170, 170, 52, 20, 230, 105, 30, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SkeletonSoldierElite"] =  {"Skeleton Soldier Elite", 24, 180, 180, 58, 30, 250, 115, 30, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LesserGargoyle"] =        {"Lesser Gargoyle", 25, 180, 180, 55, 25, 280, 130, 32, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DeepDwellerBrute"] =      {"Deep Dweller Brute", 25, 200, 200, 60, 28, 270, 125, 34, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Common Enemies: Level 26-30 ---
    enemyDatabase["HieroglyphicAnimator"] =  {"Hieroglyphic Animator", 26, 190, 190, 50, 30, 290, 135, 36, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LeaderBanditThug"] =      {"Leader Bandit Thug", 27, 210, 210, 62, 26, 310, 140, 36, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["FearHound"] =             {"Fear Hound", 28, 180, 180, 58, 22, 330, 150, 39, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["FallenTempleJusticar"] =  {"Fallen Temple Justicar", 29, 220, 220, 65, 35, 350, 160, 39, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["OrcGruntElite"] =         {"Orc Grunt Elite", 30, 250, 250, 70, 30, 380, 170, 42, false, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["RockGolemShard"] =        {"Rock Golem Shard", 30, 230, 230, 60, 40, 370, 165, 42, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Common Enemies: Level 31-35 ---
    enemyDatabase["MoltenCoreElemental"] =   {"Molten Core Elemental", 31, 280, 280, 65, 40, 410, 180, 44, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["ShadowedSunCleric"] =     {"Shadowed Sun Cleric", 32, 240, 240, 60, 30, 430, 190, 44, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GuardianSpirit"] =        {"Guardian Spirit", 33, 250, 250, 65, 30, 450, 200, 48, false, false, 0, 0, 0, 0, 0, "Magical", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AbyssalRitualist"] =      {"Abyssal Ritualist", 34, 250, 250, 70, 32, 520, 240, 48, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CrystalGolemCore"] =      {"Crystal Golem Core", 35, 300, 300, 70, 45, 550, 250, 50, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["HarpyMatriarch"] =        {"Harpy Matriarch", 35, 260, 260, 68, 28, 500, 230, 50, false, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Common Enemies: Level 36-40 ---
    enemyDatabase["LavaBehemothWhelp"] =     {"Lava Behemoth Whelp", 36, 320, 320, 75, 42, 600, 270, 52, false, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["HellishDevilBat"] =       {"Hellish Devil Bat", 37, 220, 220, 72, 30, 620, 280, 52, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SeraphicEcho"] =          {"Seraphic Echo", 38, 280, 280, 75, 38, 650, 290,54, false, false, 0, 0, 0, 0, 0, "Celestial", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AncientCarnivorousPlant"]={"Ancient Carnivorous Plant", 39, 340, 340, 78, 35, 680, 300, 54, false, false, 0, 0, 0, 0, 0, "Plant", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CorruptedArchonAcolyte"]={"Corrupted Archon Acolyte", 40, 300, 300, 80, 40, 720, 310, 55, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Common Enemies: Level 41-45 ---
    enemyDatabase["AbyssalWatcher"] =        {"Abyssal Watcher", 41, 330, 330, 75, 38, 650, 300, 57, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["InfernalVanguard"] =      {"Infernal Vanguard", 42, 360, 360, 82, 48, 780, 340, 58, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SunstoneSentinel"] =      {"Sunstone Sentinel", 42, 350, 350, 80, 40, 700, 320,58, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DivineConstructSentry"] = {"Divine Construct Sentry", 43, 380, 380, 85, 50, 800, 350, 57, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["DarkWolfAlpha"] =         {"Dark Wolf Alpha", 44, 370, 370, 88, 40, 850, 370, 59, false, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["SoulLeechWisp"] =         {"Soul Leech Wisp", 45, 330, 330, 78, 42, 920, 400,60, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Common Enemies: Level 46-49 ---
    enemyDatabase["EchoOfALostSaint"] =      {"Echo of a Lost Saint", 46, 350, 350, 80, 45, 950, 420, 61, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["YoungPitFiend"] =         {"Young Pit Fiend", 47, 400, 400, 90, 50, 1000, 450, 61, false, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["TimelessTempleSentinel"] ={"Timeless Temple Sentinel", 49, 450, 450, 95, 55, 1100, 500, 63, false, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AvernusDeathKnight"] =    {"Avernus Death Knight", 49, 460, 460, 98, 58, 1150, 520, 63, false, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Mini-Bosses ---
    enemyDatabase["AncientGolemSentry"] =    {"Ancient Golem Sentry", 12, 300, 300, 50, 20, 250, 120, 18, true, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GreaterSkeletonLord"] =   {"Greater Skeleton Lord", 24, 600, 600, 70, 30, 700, 300, 36, true, false, 0, 0, 0, 0, 0, "Undead", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["StoneColossusFragment"] = {"Stone Colossus Fragment", 36, 1000, 1000, 90, 45, 1500, 600, 40, true, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["CorruptedArchon"] =       {"Corrupted Archon", 48, 1500, 1500, 120, 55, 3000, 1000, 53, true, false, 0, 0, 0, 0, 0, "Dark", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["GiantCaveCrawler"] =      {"Giant Cave Crawler", 12, 280, 280, 55, 18, 240, 110, 18, true, false, 0, 0, 0, 0, 0, "Beast", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["UnderdarkOverseer"] =     {"Underdark Overseer", 24, 550, 550, 75, 28, 680, 290, 36, true, false, 0, 0, 0, 0, 0, "Humanoid", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["LavaBehemothSpawn"] =     {"Lava Behemoth Spawn", 36, 950, 950, 95, 42, 1450, 580, 40, true, false, 0, 0, 0, 0, 0, "Elemental", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["HeraldOfTheAbyss"] =      {"Herald of the Abyss", 48, 1400, 1400, 125, 52, 2900, 950, 53, true, false, 0, 0, 0, 0, 0, "Demon", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Final Bosses ---
    enemyDatabase["AvatarOfTheForgottenDeity"] = {"Avatar of the Forgotten Deity", 60, 5000, 5000, 200, 80, 10000, 5000, 80, true, false, 0, 0, 0, 0, 0, "Divine", {}, 0, 0, 0, 0, false, 0, false, 0, {}};
    enemyDatabase["AvernusCoreGuardian"] =      {"Avernus Core Guardian", 60, 4800, 4800, 210, 75, 9800, 4800, 80, true, false, 0, 0, 0, 0, 0, "Construct", {}, 0, 0, 0, 0, false, 0, false, 0, {}};

    // --- Dungeon 1: Ancient Temple (Ascending) ---
    Dungeon ancientTemple;
    ancientTemple.name = "Ancient Temple";
    ancientTemple.type = "ascending";
    ancientTemple.printAsBasement = false;
    ancientTemple.storyLockedFloors = {11, 21, 31, 41}; // Contoh lantai terkunci
    for (int i : {5, 15, 25, 35, 45}) { ancientTemple.campAreas[i] = CampArea{i}; }

    for (int i = 1; i <= 50; ++i) {
        ancientTemple.floorEnemies[i].clear(); // Pastikan kosong sebelum diisi
        // SEGMENT 1: Lantai 1-9 (Menuju MB Lvl 12 "AncientGolemSentry" di Lantai 10)
        if (i >= 1 && i <= 3) {     // Common Lvl 1-2
            ancientTemple.floorEnemies[i] = {"Slime", "GiantRat", "StoneSprite"};
        } else if (i >= 4 && i <= 6) { // Common Lvl 3-5
            ancientTemple.floorEnemies[i] = {"TempleRatSwarm", "TempleGuardDog", "DustMephit"};
        } else if (i >= 7 && i <= 9) { // Common Lvl 5-9
            ancientTemple.floorEnemies[i] = {"AnimatedSword", "AncientSentryFragment","LostPilgrimSpirit", "ShadowPup"};
        } else if (i == 10) { ancientTemple.miniBosses[i] = "AncientGolemSentry"; }

        // SEGMENT 2: Lantai 11-19 (Menuju MB Lvl 24 "GreaterSkeletonLord" di Lantai 20)
        else if (i >= 11 && i <= 13) { // Common Lvl 11-12
            ancientTemple.floorEnemies[i] = {"GuardianOrb", "GoblinRockthrower", "TempleAcolyte", "LesserImpVariant"};
        } else if (i >= 14 && i <= 16) { // Common Lvl 13-16
            ancientTemple.floorEnemies[i] = {"DarkCultInitiate", "TempleKnightAspirant", "WildBoarStrong", "CorruptedCherub"};
        } else if (i >= 17 && i <= 19) { // Common Lvl 17-19
            ancientTemple.floorEnemies[i] = {"KoboldDiggerElite", "ObsidianRazorfiend", "PhantomWarrior", "AltarGuardianMinor"};
        } else if (i == 20) { ancientTemple.miniBosses[i] = "GreaterSkeletonLord"; }

        // SEGMENT 3: Lantai 21-29 (Menuju MB Lvl 36 "StoneColossusFragment" di Lantai 30)
        else if (i >= 21 && i <= 23) { // Common Lvl 21-23
            ancientTemple.floorEnemies[i] = {"CharredSalamander", "ForestSpiderVariant", "StoneLionCub", "RiverSerpentVariant"};
        } else if (i >= 24 && i <= 26) { // Common Lvl 24-26
            ancientTemple.floorEnemies[i] = {"SkeletonSoldierElite", "LesserGargoyle", "DeepDwellerBrute", "HieroglyphicAnimator"};
        } else if (i >= 27 && i <= 29) { // Common Lvl 27-29
            ancientTemple.floorEnemies[i] = {"BanditThugLeader", "FearHound", "FallenTempleJusticar"};
        } else if (i == 30) { ancientTemple.miniBosses[i] = "StoneColossusFragment"; }

        // SEGMENT 4: Lantai 31-39 (Menuju MB Lvl 48 "CorruptedArchon" di Lantai 40)
        else if (i >= 31 && i <= 33) { // Common Lvl 30-33
            ancientTemple.floorEnemies[i] = {"OrcGruntElite", "RockGolemShardStrong", "MoltenCoreElemental", "ShadowedSunCleric", "GuardianSpirit"};
        } else if (i >= 34 && i <= 36) { // Common Lvl 34-36
            ancientTemple.floorEnemies[i] = {"AbyssalRitualist", "CrystalGolemCore", "HarpyFledglingMatriarch", "LavaBehemothWhelp"};
        } else if (i >= 37 && i <= 39) { // Common Lvl 37-39
            ancientTemple.floorEnemies[i] = {"HellishBatSwarm", "SeraphicEcho", "CarnivorousPlantAncient"};
        } else if (i == 40) { ancientTemple.miniBosses[i] = "CorruptedArchon"; }

        // SEGMENT 5: Lantai 41-49 (Menuju FB Lvl 60 "AvatarOfTheForgottenDeity" di Lantai 50)
        else if (i >= 41 && i <= 43) { // Common Lvl 40-43
            ancientTemple.floorEnemies[i] = {"CorruptedArchonAcolyte", "AbyssalWatcherMinor", "InfernalVanguard", "DivineConstructSentry"};
        } else if (i >= 44 && i <= 46) { // Common Lvl 44-46
            ancientTemple.floorEnemies[i] = {"DarkWolfAlpha", "SoulLeechWisp", "EchoOfALostSaint"};
        } else if (i >= 47 && i <= 49) { // Common Lvl 47-49
            ancientTemple.floorEnemies[i] = {"YoungPitFiend", "TimelessTempleSentinel", "AvernusDeathKnight"}; // AvernusDeathKnight mungkin lebih cocok di Goa, ganti jika perlu
                                                                                                               // Ganti "AvernusDeathKnight" dengan varian Temple yang kuat, misal "CelestialKnightRemnant"
            ancientTemple.floorEnemies[i] = {"YoungPitFiend", "TimelessTempleSentinel", "SeraphicEcho"}; // Menggunakan Seraphic Echo lagi untuk tema temple
        } else if (i == 50) { ancientTemple.finalBoss[i] = "AvatarOfTheForgottenDeity"; }
    }
    allDungeons["Ancient Temple"] = ancientTemple;


    // --- Dungeon 2: Goa Avernix (Descending) ---
    Dungeon goaAvernix;
    goaAvernix.name = "Goa Avernix";
    goaAvernix.type = "ascending";
    goaAvernix.printAsBasement = true;
    goaAvernix.storyLockedFloors = {11, 21, 31, 41}; // Contoh
    for (int i : {5, 15, 25, 35, 45}) { goaAvernix.campAreas[i] = CampArea{i}; }

    for (int i = 1; i <= 50; ++i) {
        goaAvernix.floorEnemies[i].clear(); // Pastikan kosong sebelum diisi
        // SEGMENT 1: Lantai B1-B9 (Menuju MB Lvl 12 "GiantCaveCrawler" di Lantai B10)
        if (i >= 1 && i <= 3) {     // Common Lvl 1-2
            goaAvernix.floorEnemies[i] = {"GiantRat", "FeralGoblinGrunt", "GiantCaveCricket"};
        } else if (i >= 4 && i <= 6) { // Common Lvl 3-6
            goaAvernix.floorEnemies[i] = {"KoboldScavenger", "GlowShroomCluster", "CaveLurker", "KoboldPathguard"};
        } else if (i >= 7 && i <= 9) { // Common Lvl 7-9
            goaAvernix.floorEnemies[i] = {"AnimatedSword", "UmbralCrawler", "ShadowPup"}; // Animated Sword mungkin kurang pas di goa, ganti jika perlu
                                                                                                // Ganti dengan: {"UmbralCrawler", "ShadowPupVariant", "AncientSentryFragment"} (jika fragmen kuno ada di goa)
            goaAvernix.floorEnemies[i] = {"UmbralCrawler", "ShadowPupVariant", "KoboldPathguard"}; // Lebih banyak kobold
        } else if (i == 10) { goaAvernix.miniBosses[i] = "GiantCaveCrawler"; }

        // SEGMENT 2: Lantai B11-B19 (Menuju MB Lvl 24 "UnderdarkOverseer" di Lantai B20)
        else if (i >= 11 && i <= 13) { // Common Lvl 11-13
            goaAvernix.floorEnemies[i] = {"GoblinRockthrower", "YoungCaveTroll", "LesserImpVariant", "DarkCultInitiate"};
        } else if (i >= 14 && i <= 16) { // Common Lvl 14-16
            goaAvernix.floorEnemies[i] = {"WildBoarStrong", "BroodCavernSpider", "CorruptedCherub" }; // Cherub mungkin kurang pas di goa
                                                                                                    // Ganti "CorruptedCherub" dengan misal "ObsidianRazorfiend" (Lvl 18) atau "DeepSpiderHatchling" (Lvl 17)
            goaAvernix.floorEnemies[i] = {"WildBoarStrong", "BroodCavernSpider", "DeepSpiderHatchling" };
        } else if (i >= 17 && i <= 19) { // Common Lvl 17-19
            goaAvernix.floorEnemies[i] = {"KoboldDiggerElite", "ObsidianRazorfiend", "PhantomWarrior"}; // PhantomWarrior mungkin kurang pas
                                                                                                      // Ganti dengan: {"KoboldDiggerElite", "ObsidianRazorfiend", "AltarGuardianMinor" (jika ada altar gelap)}
            goaAvernix.floorEnemies[i] = {"KoboldDiggerElite", "ObsidianRazorfiend", "BroodCavernSpider"};
        } else if (i == 20) { goaAvernix.miniBosses[i] = "UnderdarkOverseer"; }

        // SEGMENT 3: Lantai B21-B29 (Menuju MB Lvl 36 "LavaBehemothSpawn" di Lantai B30)
        else if (i >= 21 && i <= 23) { // Common Lvl 21-23
            goaAvernix.floorEnemies[i] = {"CharredSalamander", "ForestSpiderVariant", "StoneLionCub"}; // StoneLionCub kurang pas
                                                                                                     // Ganti dengan: {"CharredSalamander", "ForestSpiderVariant", "RiverSerpentVariant"}
            goaAvernix.floorEnemies[i] = {"CharredSalamander", "ForestSpiderVariant", "MagmaWriggler"};
        } else if (i >= 24 && i <= 26) { // Common Lvl 24-26
            goaAvernix.floorEnemies[i] = {"SkeletonSoldierElite", "DeepDwellerBrute", "BanditThugLeader"};
        } else if (i >= 27 && i <= 29) { // Common Lvl 27-29
            goaAvernix.floorEnemies[i] = {"FearHound", "OrcGruntElite", "RockGolemShardStrong"};
        } else if (i == 30) { goaAvernix.miniBosses[i] = "LavaBehemothSpawn"; }

        // SEGMENT 4: Lantai B31-B39 (Menuju MB Lvl 48 "HeraldOfTheAbyss" di Lantai B40)
        else if (i >= 31 && i <= 33) { // Common Lvl 31-33
            goaAvernix.floorEnemies[i] = {"MoltenCoreElemental", "ShadowedSunCleric", "GuardianSpirit"}; // SunCleric & GuardianSpirit kurang pas
                                                                                                        // Ganti dengan: {"MoltenCoreElemental", "AbyssalRitualist", "FearHound"}
            goaAvernix.floorEnemies[i] = {"MoltenCoreElemental", "AbyssalRitualist", "DeepDwellerBrute"};
        } else if (i >= 34 && i <= 36) { // Common Lvl 34-36
            goaAvernix.floorEnemies[i] = {"AbyssalRitualist", "CrystalGolemCore", "HarpyFledglingMatriarch", "LavaBehemothWhelp"}; // Harpy & CrystalGolem kurang pas
                                                                                                               // Ganti dengan: {"AbyssalRitualist", "LavaBehemothWhelp", "MoltenCoreElemental"}
            goaAvernix.floorEnemies[i] = {"AbyssalRitualist", "LavaBehemothWhelp", "HellishBatSwarm"};
        } else if (i >= 37 && i <= 39) { // Common Lvl 37-39
            goaAvernix.floorEnemies[i] = {"HellishBatSwarm", "SeraphicEcho", "CarnivorousPlantAncient"}; // SeraphicEcho kurang pas
                                                                                                        // Ganti dengan: {"HellishBatSwarm", "CarnivorousPlantAncient", "AbyssalRitualist"}
            goaAvernix.floorEnemies[i] = {"HellishBatSwarm", "CarnivorousPlantAncient", "CorruptedArchonAcolyte"}; // ArchonAcolyte kurang pas
            goaAvernix.floorEnemies[i] = {"HellishBatSwarm", "CarnivorousPlantAncient", "YoungPitFiend" }; // YoungPitFiend (Lvl 47) terlalu tinggi untuk segmen ini
            goaAvernix.floorEnemies[i] = {"HellishBatSwarm", "CarnivorousPlantAncient", "FearHound" }; // Re-use FearHound
        } else if (i == 40) { goaAvernix.miniBosses[i] = "HeraldOfTheAbyss"; }

        // SEGMENT 5: Lantai B41-B49 (Menuju FB Lvl 60 "AvernusCoreGuardian" di Lantai B50)
        else if (i >= 41 && i <= 43) { // Common Lvl 41-43
            goaAvernix.floorEnemies[i] = {"AbyssalWatcherMinor", "InfernalVanguard", "DivineConstructSentry"}; // DivineConstructSentry kurang pas
                                                                                                              // Ganti dengan: {"AbyssalWatcherMinor", "InfernalVanguard", "MoltenCoreElemental"}
            goaAvernix.floorEnemies[i] = {"AbyssalWatcherMinor", "InfernalVanguard", "DarkWolfAlpha"};
        } else if (i >= 44 && i <= 46) { // Common Lvl 44-46
            goaAvernix.floorEnemies[i] = {"DarkWolfAlpha", "SoulLeechWisp", "EchoOfALostSaint"}; // Echo kurang pas
                                                                                               // Ganti dengan: {"DarkWolfAlpha", "SoulLeechWisp", "InfernalVanguard"}
            goaAvernix.floorEnemies[i] = {"DarkWolfAlpha", "SoulLeechWisp", "YoungPitFiend"}; // YoungPitFiend (Lvl 47) cocok di akhir segmen
        } else if (i >= 47 && i <= 49) { // Common Lvl 47-49
            goaAvernix.floorEnemies[i] = {"YoungPitFiend", "TimelessTempleSentinel", "AvernusDeathKnight"}; // TempleSentinel kurang pas
                                                                                                          // Ganti dengan: {"YoungPitFiend", "AvernusDeathKnight", "InfernalVanguard"}
            goaAvernix.floorEnemies[i] = {"YoungPitFiend", "AvernusDeathKnight", "SoulLeechWisp"};
        } else if (i == 50) { goaAvernix.finalBoss[i] = "AvernusCoreGuardian"; }
    }
    allDungeons["Goa Avernix"] = goaAvernix;
    loadEnemyASCIIFromFile("enemy.txt");
    initializeMagicSystem();


}

void showItemShop() {
    int choice;
    vector<Item*> shopStock;

    // Populate shop stock - ambil semua item yang punya harga > 0 dari itemDatabase
    for (auto const& [name, itemPtr] : itemDatabase) {
        if (itemPtr->price > 0) { // Jika item punya harga, diasumsikan bisa dijual
            shopStock.push_back(itemPtr);
        }
    }
    // Urutkan untuk tampilan yang konsisten
    sort(shopStock.begin(), shopStock.end(), [](Item* a, Item* b){
        if (a->type != b->type) return a->type < b->type; // Urutkan berdasarkan tipe dulu
        return a->name < b->name; // Lalu berdasarkan nama
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

        cin >> choice;
        if (cin.fail() || choice < 0 || choice > static_cast<int>(shopStock.size())) { // Perbaikan validasi
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
                char confirm_char; // Ubah nama variabel untuk menghindari konflik
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
            wcout << L"Tekan Enter untuk kembali ke toko...";
            if(cin.peek() == '\n') cin.ignore(); // Membersihkan newline dari input char
            cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            // cin.get(); // Tidak perlu cin.get() ganda jika sudah ignore max
        } else if (choice != 0) {
            delayPrint(L"Pilihan tidak valid.", 20);
            wcout << L"Tekan Enter untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            // cin.get(); // Tidak perlu cin.get() ganda jika sudah ignore max
        }
         // Tunggu input Enter di akhir loop jika bukan keluar
        if (choice != 0) {
            if(cin.peek() != '\n') { // Jika buffer belum bersih (misal setelah cin >> char dan tidak ada ignore yang cukup)
                 cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            } else { // Jika hanya ada newline, consume
                 cin.ignore();
            }
        }


    } while (choice != 0);
    delayPrint(L"Terima kasih sudah berkunjung!", 20);
    wcout << L"Tekan Enter untuk melanjutkan...";
    if(cin.peek() == '\n') cin.ignore();
    // cin.get(); // Ini akan menunggu Enter terakhir sebelum keluar fungsi
}

void showBlacksmith() {
    int choice;
    vector<Weapon*> availableWeapons;

    do {
        availableWeapons.clear();
        for (auto& weapon : allWeapons) { // Iterasi dari allWeapons global
            bool isUnlocked = false;
            if (weapon.requiredStoryFlagKey == "no_flag" || weapon.requiredStoryFlagKey.empty()) {
                isUnlocked = true;
            } else if (storyFlags.count(weapon.requiredStoryFlagKey) && storyFlags.at(weapon.requiredStoryFlagKey) >= weapon.requiredStoryFlagValue) {
                isUnlocked = true;
            }

            if (isUnlocked && weapon.price > 0) {
                availableWeapons.push_back(&weapon); // Tambahkan pointer ke senjata
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
        printLine(80, L'─'); // Perlebar garis untuk info senjata

        if (availableWeapons.empty()) {
            wcout << L"Maaf, sepertinya belum ada senjata yang cocok untuk Anda saat ini." << endl;
            wcout << L"Kembalilah lagi nanti jika sudah lebih berpengalaman." << endl;
        } else {
            for (size_t i = 0; i < availableWeapons.size(); ++i) {
                wcout << L" ❖ " << (i + 1) << L". " << padRight(utf8_to_wstring(availableWeapons[i]->name), 28) // Sesuaikan padding
                      << L" ATK: " << setw(3) << availableWeapons[i]->attackPower
                      << L" | STR Req: " << setw(2) << availableWeapons[i]->strengthRequired
                      << L" | INT Req: " << setw(2) << availableWeapons[i]->intelligenceRequired
                      << L" - Harga: " << setw(5) << right << availableWeapons[i]->price << L" G" << endl; // Harga rata kanan
                wcout << L"      └─ " << utf8_to_wstring(availableWeapons[i]->description) << endl;
            }
        }
        printLine(80, L'─');
        wcout << L" ❖ 0. Keluar dari Penempa" << endl;
        printLine(80, L'─');
        wcout << L"Pilih senjata untuk dibeli ✦: ";

        cin >> choice;
         if (cin.fail() || choice < 0 || choice > static_cast<int>(availableWeapons.size())) { // Perbaikan validasi
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
                char confirm_char_weapon; // Variabel berbeda
                cin >> confirm_char_weapon;
                if (tolower(confirm_char_weapon) == 'y') {
                    player.gold -= selectedWeapon->price;
                    player.weapons.push_back(selectedWeapon); // Tambahkan pointer
                    delayPrint(L"✅ Pembelian berhasil! " + utf8_to_wstring(selectedWeapon->name) + L" ditambahkan ke gudang senjata Anda.", 20);
                } else {
                    delayPrint(L"Pembelian dibatalkan.", 20);
                }
            } else {
                delayPrint(L"❌ Emas Anda tidak cukup untuk membeli senjata ini.", 20);
            }
            wcout << L"Tekan Enter untuk kembali ke penempa...";
            if(cin.peek() == '\n') cin.ignore(); // Membersihkan newline dari input char
            cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            // cin.get(); // Tidak perlu ganda
        } else if (choice != 0) {
            delayPrint(L"Pilihan tidak valid.", 20);
            wcout << L"Tekan Enter untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            // cin.get(); // Tidak perlu ganda
        }
        // Tunggu input Enter di akhir loop jika bukan keluar
        if (choice != 0) {
             if(cin.peek() != '\n') {
                 cin.ignore(numeric_limits<streamsize>::max(), L'\n');
            } else {
                 cin.ignore();
            }
        }

    } while (choice != 0);
    delayPrint(L"Hati-hati di jalan, Tuan Muda!", 20);
    wcout << L"Tekan Enter untuk melanjutkan...";
    if(cin.peek() == '\n') cin.ignore();
    // cin.get(); // Tunggu Enter terakhir
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

                // Automatically learn Tier 1 spells of the new element
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
                // Give a free skill point for the new element or guide to skill tree
                character.skillPoints++;
                delayPrint(L"  Kamu mendapatkan 1 Skill Point tambahan!", 20);
                break; // Unlock one element per milestone level achieved in one go
            }
        }
    }
}

void levelUpCharacter(Character& character) {
    character.level++;
    centerText(L" ");
    printLine(); // Garis horizontal
    centerText(L"✦ LEVEL UP! ✦");
    printLine();

    delayPrint(L"📈 Selamat! Kamu mencapai Level " + to_wstring(character.level) + L"!", 30);
    delayPrint(L"═══════════════════════════════════════════════", 5);

    // Stat increases (simple example)
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

    unlockNewMagicElementIfNeeded(character); // Cek element baru

    printLine(); // Penutup visual
}


void handleExperienceAndLevelUp(Character& character, int expGained) {
    if (expGained <= 0) return;

    character.exp += expGained;
    bool leveledUp = false;
    while (character.exp >= character.expToNextLevel) {
        character.exp -= character.expToNextLevel;
        levelUpCharacter(character);
        leveledUp = true; // To ensure subsequent expToNextLevel is for the new level
    }

    if (!leveledUp) { // If no level up, just show current EXP status
        delayPrint(L"Total EXP: " + to_wstring(character.exp) + L"/" + to_wstring(character.expToNextLevel), 20);
    }
}

bool canLearnSpell(const Character& character, const MagicSpell& spell) {
    // Check tier requirement based on player level
    if (spell.tier == 2 && character.level < 30) return false; // Tier 2 unlocks at Lvl 15
    if (spell.tier == 3 && character.level < 60) return false; // Tier 3 unlocks at Lvl 30

    // Check prerequisites
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
    string elementOfSpell;

    // Find the spell in allMagicElements
    for (const auto& elemPair : allMagicElements) {
        if (elemPair.second.spells.count(spellIdToLearn)) {
            spellToLearn = &elemPair.second.spells.at(spellIdToLearn);
            elementOfSpell = elemPair.first;
            break;
        }
    }

    if (!spellToLearn) {
        delayPrint(L"❌ Spell tidak ditemukan!", 20);
        return;
    }

    // Check if element is unlocked
    bool elementUnlocked = false;
    for(const string& unlockedElem : character.unlockedMagicElements) {
        if (unlockedElem == spellToLearn->elementType) {
            elementUnlocked = true;
            break;
        }
    }
    if (!elementUnlocked) {
        delayPrint(L"❌ Kamu belum membuka elemen " + utf8_to_wstring(spellToLearn->elementType) + L"!", 20);
        return;
    }

    // Check if already known
    for (const string& knownSpellId : character.knownSpells) {
        if (knownSpellId == spellIdToLearn) {
            delayPrint(L"❌ Kamu sudah mempelajari spell ini!", 20);
            return;
        }
    }

    if (character.skillPoints < 1) { // Assuming 1 SP per spell
        delayPrint(L"❌ Skill Point tidak cukup!", 20);
        return;
    }

    if (!canLearnSpell(character, *spellToLearn)) {
        delayPrint(L"❌ Persyaratan untuk mempelajari spell ini belum terpenuhi (level atau prerequisite spell).", 20);
        return;
    }

    character.knownSpells.push_back(spellIdToLearn);
    character.skillPoints -= 1;
    delayPrint(L"✨ Selamat! Kamu telah mempelajari: " + utf8_to_wstring(spellToLearn->name) + L"!", 20);
    delayPrint(L"  Sisa Skill Point: " + to_wstring(character.skillPoints), 20);
}

void displayElementSkillTree(Character& character, const string& elementName) {
    if (!allMagicElements.count(elementName)) return;
    const MagicElement& element = allMagicElements.at(elementName);

    map<int, vector<const MagicSpell*>> spellsByTier;
    for(const auto& spellPair : element.spells) {
        spellsByTier[spellPair.second.tier].push_back(&spellPair.second);
    }
    // Sort spells within each tier by name or ID for consistent display
    for (auto& tierPair : spellsByTier) {
        sort(tierPair.second.begin(), tierPair.second.end(), [](const MagicSpell* a, const MagicSpell* b){
            return a->id < b->id; // Or a->name < b->name
        });
    }


    vector<const MagicSpell*> learnableSpellsList; // For user selection by number

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

        for (int tier = 1; tier <= 3; ++tier) { // Assuming max 3 tiers
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
                        displayStr += L"    "; // Indent if not selectable by number
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
                            // Find prereq name
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
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; // Invalid choice
        }

        if (choice == 0) {
            canGoBack = true;
        } else if (choice > 0 && choice <= learnableSpellsList.size()) {
            learnSpell(character, learnableSpellsList[choice-1]->id);
            wcout << L"Tekan Enter untuk lanjut...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Consume the choice input newline
        } else {
            wcout << L"Pilihan tidak valid. Tekan Enter...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}


// Menampilkan detail spell dan pilihan unlock
bool showSpellDetailAndMaybeUnlock(Character& character, const MagicSpell& spell) {
    auto allSpells = getAllSpells();
    wstring line = L"════════════════════════════════════════════════════════════════════════════";
    system("cls");
    wcout << line << endl;
    centerText(utf8_to_wstring("✦ DETAIL SKILL: " + spell.name));
    wcout << line << endl;
    wcout << L"MP Cost     : " << spell.manaCost << endl;
    wcout << L"Power       : " << spell.basePower << endl;
    wcout << L"Deskripsi   : " << utf8_to_wstring(spell.description) << endl;

    if (!spell.prerequisites.empty()) {
        wcout << L"Prasyarat   : ";
        for (const string& pre : spell.prerequisites) {
            wcout << utf8_to_wstring(allSpells[pre].name) << L"  ";
        }
        wcout << endl;
    }

    bool unlocked = find(character.knownSpells.begin(), character.knownSpells.end(), spell.id) != character.knownSpells.end();
    wcout << L"Status      : " << (unlocked ? L"✅ Dimiliki" : L"🔒 Belum dimiliki") << endl;
    if (!unlocked) {
        wcout << L"Skill Point : " << character.skillPoints << endl;

        bool prereqMet = all_of(spell.prerequisites.begin(), spell.prerequisites.end(),
                                [&](const string& pre) {
                                    return find(character.knownSpells.begin(), character.knownSpells.end(), pre) != character.knownSpells.end();
                                });

        if (prereqMet && character.skillPoints > 0) {
            wcout << L"\nKamu bisa mempelajari skill ini. Gunakan 1 Skill Point? (y/n): ";
            char input;
            cin >> input;
            if (input == 'y' || input == 'Y') {
                character.knownSpells.push_back(spell.id);
                character.skillPoints--;
                wcout << L"\n✅ Skill berhasil dipelajari!" << endl;
            }
        } else if (!prereqMet) {
            wcout << L"\n✖ Belum memenuhi prasyarat." << endl;
        } else {
            wcout << L"\n✖ Skill Point tidak mencukupi." << endl;
        }
    }

    wcout << L"\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
    return true;
}

// Menampilkan cabang spell secara rekursif dan beri nomor
void displaySpellRecursive(const MagicSpell& spell, const map<string, MagicSpell>& allSpells,
                            const unordered_set<string>& knownSpells,
                            vector<const MagicSpell*>& selectableList,
                            int indent = 0, int& counter = *(new int(1))) {
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

// Menampilkan skill tree dengan interaksi dan unlock
void showSkillTreeMenu(Character& character) {
    int choice;
    do {
        system("cls");
        printLine();
        centerText(L"✦✦✦ SKILL TREE UTAMA ✦✦✦");
        printLine();
        wcout << L"Pilih elemen untuk melihat skill tree:" << endl;

        vector<string> unlockedElementsSorted = character.unlockedMagicElements;
        sort(unlockedElementsSorted.begin(), unlockedElementsSorted.end());

        for (size_t i = 0; i < unlockedElementsSorted.size(); ++i) {
            wcout << L"  ❖ " << (i + 1) << L". " << utf8_to_wstring(unlockedElementsSorted[i]) << endl;
        }
        wcout << L"  ❖ 0. Kembali ke Diary" << endl;
        printLine(50, L'─');
        wcout << L"Pilih menu ✦: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        if (choice > 0 && choice <= unlockedElementsSorted.size()) {
            string selectedElement = unlockedElementsSorted[choice - 1];
            const auto& elementData = allMagicElements[selectedElement];

            unordered_set<string> known(character.knownSpells.begin(), character.knownSpells.end());
            vector<const MagicSpell*> selectable;
            int counter = 1;

            system("cls");
            printLine();
            centerText(utf8_to_wstring("✦ SKILL TREE: " + selectedElement));
            printLine();

            for (const auto& [id, spell] : elementData.spells) {
                if (spell.prerequisites.empty()) {
                    displaySpellRecursive(spell, elementData.spells, known, selectable, 0, counter);
                }
            }

            printLine();
            wcout << L"Masukkan nomor skill untuk melihat detail (0 untuk kembali): ";
            int spellChoice;
            cin >> spellChoice;

            if (!cin.fail() && spellChoice > 0 && spellChoice <= selectable.size()) {
                showSpellDetailAndMaybeUnlock(character, *selectable[spellChoice - 1]);
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (choice != 0);
}


void setupWorldAreas() {
    // Mansion Astra
    WorldArea mansion;
    mansion.name = "Mansion Astra";
    mansion.startSubArea = "Kamar Weiss";
    mansion.subAreas = {
        {"Kamar Weiss", { "Kamar Weiss", {"Cek Sekitar", "Membuka Diary", "Pilih Lokasi"} }},
        {"Dapur Mansion", { "Dapur Mansion", {"Cek Sekitar", "Bicara dengan Companion", "Membuka Diary", "Pilih Lokasi"} }},
        {"Taman Floresia", { "Taman Floresia", {"Cek Sekitar", "Bicara dengan Companion", "Membuka Diary", "Pilih Lokasi"} }},
        {"Lorong Panjang", { "Lorong Panjang", {"Cek Sekitar", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Mansion Astra"] = mansion;

    // Kota Arcadia
    WorldArea arcadia;
    arcadia.name = "Kota Arcadia";
    arcadia.startSubArea = "Balai Kota";
    arcadia.subAreas = {
        {"Cross Guild", { "Cross Guild", {"Cek Sekitar", "Quest Board", "Bicara dengan Companion", "Buka Diary", "Pilih Lokasi"} }},
        {"Perbelanjaan", { "Perbelanjaan", {"Cek Sekitar", "Item Shop", "Penempa Besi", "Buka Diary", "Pilih Lokasi"} }},
        {"Balai Kota", { "Balai Kota", {"Cek Sekitar", "Cek Berita Kota", "Bicara dengan Companion", "Buka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Kota Arcadia"] = arcadia;

    // Hutan Merah
    WorldArea hutan;
    hutan.name = "Hutan Merah";
    hutan.startSubArea = "Pos Hutan";
    hutan.subAreas = {
        {"Pos Hutan", { "Pos Hutan", {"Cek Sekitar", "Bicara dengan Companion", "Membuka Diary", "Pilih Lokasi"} }},
        {"Reruntuhan Kuno", { "Reruntuhan Kuno", {"Cek Sekitar", "Masuk ke Ancient Temple (Dungeon)", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Hutan Merah"] = hutan;

    // Goa Avernix
    WorldArea goa;
    goa.name = "Goa Avernix";
    goa.startSubArea = "Camp Avernix";
    goa.subAreas = {
        {"Camp Avernix", { "Camp Avernix", {"Cek Sekitar", "Masuk ke Goa Avernix (Dungeon)", "Bicara dengan Companion", "Membuka Diary", "Pilih Lokasi"} }},
        {"Tambang Terbengkalai", { "Tambang Terbengkalai", {"Cek Sekitar", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Goa Avernix"] = goa;

    // Puncak Patung Pahlawan Negara
    WorldArea puncak;
    puncak.name = "Puncak Patung Pahlawan Negara";
    puncak.startSubArea = "Taman Norelia";
    puncak.subAreas = {
        {"Taman Norelia", { "Taman Norelia", {"Cek Sekitar", "Bicara dengan Companion", "Membuka Diary", "Pilih Lokasi"} }},
        {"Bukit Myriad", { "Bukit Myriad", {"Cek Sekitar", "Lawan Vallen", "Membuka Diary", "Pilih Lokasi"} }}
    };
    allWorlds["Puncak Patung Pahlawan Negara"] = puncak;
    
}


// Pastikan fungsi utf8_to_wstring sudah ada di atas fungsi ini
// wstring utf8_to_wstring(const string& str_utf8) { ... }

void loadEnemyASCIIFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        wcout << L"❌ Gagal membuka file ASCII enemy: " << utf8_to_wstring(filename).c_str() << endl;
        // Anda mungkin ingin menambahkan return di sini jika file gagal dibuka,
        // atau setidaknya memberi tahu pengguna dengan lebih jelas.
        // Contoh: system("pause"); return;
        return;
    }

    string line;
    string currentNameKey = "";       // Nama musuh yang sedang diproses (key untuk map)
    vector<wstring> currentArtLines; // Baris-baris ASCII art untuk currentNameKey

    while (getline(file, line)) {
        string trimmedLineForTag = trim(line); // Trim hanya untuk deteksi tag dan baris struktur

        if (trimmedLineForTag.length() > 1 && trimmedLineForTag.front() == '[' && trimmedLineForTag.back() == ']') {
            // Ini adalah tag nama musuh, contoh: [Kobold Pathguard]

            // 1. Simpan art untuk musuh sebelumnya (jika ada)
            if (!currentNameKey.empty() && !currentArtLines.empty()) {
                asciiArtMap[currentNameKey] = currentArtLines;
                // wcout << L"[DEBUG] Saved art for: [" << utf8_to_wstring(currentNameKey) << L"] with " << currentArtLines.size() << L" lines." << endl;
            }

            // 2. Siapkan untuk musuh baru
            currentArtLines.clear(); // Kosongkan buffer art untuk musuh baru
            string extractedName = trimmedLineForTag.substr(1, trimmedLineForTag.length() - 2);
            currentNameKey = trim(extractedName); // Nama musuh baru, sudah di-trim
            // wcout << L"[DEBUG] New enemy tag found: [" << utf8_to_wstring(currentNameKey) << L"]" << endl;

        } else { 
            // Ini bukan tag nama musuh, berarti ini adalah baris ASCII art atau baris kosong pemisah
            if (!currentNameKey.empty()) { // Hanya tambahkan art jika kita sudah punya nama musuh aktif
                // Tambahkan baris ASLI (line, bukan trimmedLineForTag) ke currentArtLines.
                // Ini penting untuk menjaga spasi/formatting di dalam ASCII art.
                // Baris kosong (line.empty()) juga akan ditambahkan sebagai wstring kosong,
                // yang akan menjaga baris baru pada art.
                currentArtLines.push_back(utf8_to_wstring(line));
            }
            // Jika currentNameKey kosong (misalnya, baris kosong di awal file sebelum tag pertama),
            // baris ini akan diabaikan, yang mana sudah benar.
        }
    }

    // Simpan art untuk musuh terakhir di file (setelah loop selesai)
    if (!currentNameKey.empty() && !currentArtLines.empty()) {
        asciiArtMap[currentNameKey] = currentArtLines;
        // wcout << L"[DEBUG] Saved art for last enemy: [" << utf8_to_wstring(currentNameKey) << L"] with " << currentArtLines.size() << L" lines." << endl;
    }

    file.close();
    // wcout << L"[DEBUG] Total unique enemy arts loaded: " << asciiArtMap.size() << endl;
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




// Helper to get spell details (you might want to make masterSpellList for this)
const MagicSpell* getSpellDetails(const string& spellId) {
    for (const auto& elemPair : allMagicElements) {
        if (elemPair.second.spells.count(spellId)) {
            return &elemPair.second.spells.at(spellId);
        }
    }
    return nullptr;
}

// Process end-of-turn effects like enchantments
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

    // Header
    wcout << L"╔" << wstring(totalWidth - 2, L'═') << L"╗" << endl;
    centerText(L"✦✦✦  PERTARUNGAN DIMULAI  ✦✦✦", totalWidth);
    wcout << L"╚" << wstring(totalWidth - 2, L'═') << L"╝" << endl;

    // Status Player dan Musuh
    wcout << L"👤 Kamu  ♥ HP: " << character.hp << L"/" << character.maxHp
          << L"  ♦ Mana: " << character.mana << L"/" << character.maxMana
          << setw(15) << L""
          << L"☠ " << utf8_to_wstring(enemy.name)
          << L"  ♥ HP: " << enemy.hp << L"/" << enemy.maxHp << endl;

    // Buff Aktif
    if (!character.activeEnchantments.empty()) {
        wcout << L"  🔮 Buffs: ";
        for (size_t i = 0; i < character.activeEnchantments.size(); ++i) {
            wcout << utf8_to_wstring(character.activeEnchantments[i].spellName)
                  << L"(" << character.activeEnchantments[i].remainingTurns << L")";
            if (i < character.activeEnchantments.size() - 1) wcout << L", ";
        }
        wcout << endl;
    }

    // ASCII musuh
    displayEnemyASCII(enemy.name);

    // Battle log
    wcout << L"╟" << wstring(totalWidth - 2, L'─') << L"╢" << endl;
    if (battleLog.empty()) {
        centerText(L"» Apa yang ingin kamu lakukan?", totalWidth);
    } else {
        for (const auto& line : battleLog) {
            centerText(L"» " + line, totalWidth);
        }
    }

    // Aksi
    wcout << L"╟" << wstring(totalWidth - 2, L'─') << L"╢" << endl;
    centerText(L"❖ 1. ⚔ Serang   ❖ 2. ✹ Magic   ❖ 3. ⊕ Item   ❖ 4. 🛡 Bertahan   ❖ 5. ➤ Kabur", totalWidth);
    printLine();
}

void processPlayerHoTs(Character& character, vector<wstring>& battleLogMessages) {
    if (!character.activeHoTs.empty()) {
        bool processedHot = false;
        for (auto it = character.activeHoTs.begin(); it != character.activeHoTs.end(); ) {
            if (character.hp < character.maxHp) { // Hanya heal jika HP tidak penuh
                int actualHeal = min(it->healPerTurn, character.maxHp - character.hp);
                character.hp += actualHeal;
                if (!processedHot) { // Tambahkan header hanya jika ada HoT yang aktif
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

// Modifikasi processEndOfPlayerTurn untuk memanggil processPlayerHoTs
void processEndOfPlayerTurn(Character& character, vector<wstring>& battleLogMessages) { // Tambahkan battleLogMessages
    // Proses Enchantment
    for (auto it = character.activeEnchantments.begin(); it != character.activeEnchantments.end(); ) {
        it->remainingTurns--;
        if (it->remainingTurns <= 0) {
            wstring enchEndLog = L"Efek '" + utf8_to_wstring(it->spellName) + L"' telah berakhir.";
            delayPrint(enchEndLog, 20); // Bisa juga dimasukkan ke battleLog
            battleLogMessages.push_back(enchEndLog);
            it = character.activeEnchantments.erase(it);
        } else {
            ++it;
        }
    }
    // Proses HoT
    processPlayerHoTs(character, battleLogMessages); // Panggil fungsi HoT
}



bool startBattle(Enemy& baseEnemy) {
    Enemy enemy = baseEnemy;
    // Reset status musuh untuk pertarungan ini
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
    bool playerRevivedThisBattle = false; // Flag untuk memastikan revive hanya sekali per pertarungan jika mekanismenya begitu

    while (player.hp > 0 && enemy.hp > 0) {
        battleLogMessages.clear();

        // --- PROSES EFEK BERKELANJUTAN MUSUH (DoT & Rune Meledak) ---
        if (enemy.hp > 0) {
            bool processedPersistentEffectHeader = false;
            // Proses DoT
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
            // Proses Rune
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
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); choice = 99; }

        // --- Kalkulasi Stat Pemain Final dengan SEMUA Buff ---
        int playerBaseAttackPower = player.strength + (player.equippedWeapon ? player.equippedWeapon->attackPower : 0);
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
        int finalPlayerIntelligence = player.intelligence + totalPlayerIntelligenceBonus;
        double finalPlayerCritChance = 0.05 + totalPlayerCritChanceBonus; // Base crit 5%

        // --- Kalkulasi Stat Musuh Final (dengan debuff) ---
        int currentEnemyAttack = enemy.attack;
        if (enemy.attackDebuffDuration > 0) { currentEnemyAttack = max(0, enemy.attack - enemy.attackDebuffValue); }
        int finalEnemyPhysicalDefense = max(0, enemy.defense - enemy.physicalDefenseDebuffValue);
        int finalEnemyMagicDefense = max(0, enemy.magicDefense - enemy.magicDefenseDebuffValue);

        int baseDamageToPlayer = max(0, currentEnemyAttack - finalPlayerDefense);
        int enemyBaseAccuracy = 95;
        int enemyHitChance = max(40, min(95, enemyBaseAccuracy - finalPlayerEvasion - enemy.accuracyDebuffValue));

        wstring turnActionLog;

        switch (choice) {
            case 1: { // Serang Biasa
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

                // Efek on-hit dari enchantment senjata
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
            case 2: { // Gunakan Magic
                if (player.knownSpells.empty()) {
                    battleLogMessages.push_back(L"Kamu tidak tahu spell apapun!");
                    continue; 
                }

                wcout << L"\n═════════════════════════════════════════════════════════════\n";
                wcout << L"                  ✹✹✹ PILIHAN MAGIC ✹✹✹                     \n";
                wcout << L"═════════════════════════════════════════════════════════════\n";
                int spellIdx_display = 1;
                vector<const MagicSpell*> displayedSpells_battle; // Vector untuk spell yang ditampilkan dan bisa dipilih

                for (const string& spellId : player.knownSpells) {
                    const MagicSpell* spell = getSpellDetails(spellId); // Ambil detail spell
                    if (spell) {
                        displayedSpells_battle.push_back(spell); // Tambahkan ke daftar yang akan dipilih
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
                    // continue; // Jika ingin pemain memilih lagi
                    break;    // Atau giliran hangus
                }
                if (magicChoice_input == 0) { // Pemain memilih batal
                    // continue; // Jika ingin pemain memilih lagi
                    break;    // Atau giliran hangus
                }

                // --- DEKLARASI DAN INISIALISASI chosenSpell YANG BENAR ---
                const MagicSpell* chosenSpell = displayedSpells_battle[magicChoice_input - 1];

                if (chosenSpell && player.mana >= chosenSpell->manaCost) {
                    player.mana -= chosenSpell->manaCost;
                    // 'turnActionLog' sebaiknya diisi di sini jika belum
                    turnActionLog = L"➤ Kamu menggunakan " + utf8_to_wstring(chosenSpell->name) + L"!";
                    delayPrint(turnActionLog, 20); // Tampilkan aksi utama
                    battleLogMessages.push_back(turnActionLog); // Tambahkan ke log utama untuk giliran ini

                    // ---- MULAI LOGIKA EFEK SPELL ----
                       if (chosenSpell->isEnchantment) {
                            bool alreadyActive = false; int enchIndex = -1;
                            for(size_t i=0; i < player.activeEnchantments.size(); ++i){ if(player.activeEnchantments[i].spellId == chosenSpell->id){ enchIndex = i; alreadyActive = true; break; }}
                            ActiveEnchantment newEnch(chosenSpell->id, chosenSpell->name, chosenSpell->enchantTurns, chosenSpell->enchantAttackBonus);
                            // Set bonus spesifik berdasarkan ID spell
                            if(chosenSpell->id == "FIRE_FLAME_WEAPON_1") newEnch.attackBonus = 8; // Attack bonus dari spell definition
                            else if(chosenSpell->id == "ICE_ICY_EDGE_1") newEnch.attackBonus = 9;
                            else if(chosenSpell->id == "THUNDER_CHARGE_WEAPON_1") newEnch.attackBonus = 9;
                            else if(chosenSpell->id == "WIND_AERO_BLADE_1") newEnch.attackBonus = 7;
                            else if(chosenSpell->id == "DARK_INFUSED_BLADE_1") newEnch.attackBonus = 8;
                            else if(chosenSpell->id == "LIGHT_RADIANT_WEAPON_1") newEnch.attackBonus = 7;
                            else if(chosenSpell->id == "THUNDER_VOLTAIC_EDGE_2") { newEnch.attackBonus = 20; newEnch.agilityBonus = 10 + finalPlayerAgility/15; }
                            else if(chosenSpell->id == "WIND_TEMPEST_BLADES_2") { newEnch.attackBonus = 19; newEnch.agilityBonus = 8 + finalPlayerAgility/18;}
                            else if(chosenSpell->id == "DARK_SOUL_EATER_WEAPON_2") newEnch.attackBonus = 15; // MP Drain on hit dihandle di case 1
                            else if(chosenSpell->id == "LIGHT_DIVINE_EDGE_2") { newEnch.attackBonus = 22; newEnch.defenseBonus = 5 + player.level/5; }
                            else if(chosenSpell->id == "THUNDER_MJOLNIR_AWAKENING_3") newEnch.attackBonus = 50; // Stun on hit dihandle di case 1
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

                        } else { // Mantra non-enchantment
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
                                        if (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" || chosenSpell->id == "WIND_ZEPHYRS_DANCE_3") { // Multi-hit
                                            int hits = (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" ? (2 + rand()%3) : (3 + rand()%2) ); // Conduit 2-4, Zephyr 3-4
                                            int damagePerHitCalc = (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" ? chosenSpell->basePower + finalPlayerIntelligence/2 : chosenSpell->basePower/2 + finalPlayerIntelligence/3);
                                            int damagePerHit = max(0,(int)(damagePerHitCalc - effectiveEnemyMagicDefense));
                                            totalDamageToEnemy = 0;
                                            battleLogMessages.push_back(L"  " + utf8_to_wstring(chosenSpell->name) + L" mengenai " + to_wstring(hits) + L" kali!");
                                            for(int i=0; i<hits; ++i) { enemy.hp -= damagePerHit; totalDamageToEnemy += damagePerHit; battleLogMessages.push_back(L"    ↳ Serangan ke-" + to_wstring(i+1) + L": " + to_wstring(damagePerHit) + L" damage!"); if(enemy.hp <= 0) break;}
                                            magicDamage = totalDamageToEnemy; // Update magicDamage untuk life leech dll.
                                        } else { enemy.hp -= totalDamageToEnemy; battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" terkena " + to_wstring(totalDamageToEnemy) + L" magic damage!");}
                                    if (totalDamageToEnemy > 0 && !(chosenSpell->id == "FIRE_IGNITE_1" || chosenSpell->id == "THUNDER_STATIC_FIELD_1" /*spell DoT murni lainnya*/)) {
                                        enemy.hp -= totalDamageToEnemy; // Terapkan total damage yang sudah dihitung
                                        battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" terkena " + to_wstring(totalDamageToEnemy) + L" " + utf8_to_wstring(chosenSpell->elementType) + L" damage!");
                                    } else if (totalDamageToEnemy == 0 && chosenSpell->basePower > 0) {
                                        battleLogMessages.push_back(L"  Serangan " + utf8_to_wstring(chosenSpell->name) + L" tidak memberikan damage (mungkin di-resist atau defense terlalu tinggi).");
                            }
                                    }
                                // --- Implementasi Stun LENGKAP ---
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
                                // --- AKHIR STUN ---

                                // --- FEAR ---
                                if (chosenSpell->id == "DARK_NIGHTMARE_BLAST_2" && !enemy.isFeared && rand()%100 < 40) { // 40% chance
                                    enemy.isFeared = true; enemy.fearDuration = 2; // Misal 2 giliran
                                    battleLogMessages.push_back(L"  👻 " + utf8_to_wstring(enemy.name) + L" diliputi ketakutan!");
                                }
                                // --- SILENCE ---
                                if (chosenSpell->id == "WIND_SILENCING_GUST_2" && !enemy.isSilenced && rand()%100 < 60) { // 60% chance
                                    enemy.isSilenced = true; enemy.silenceDuration = 2; // Misal 2 giliran
                                    battleLogMessages.push_back(L"  🔇 " + utf8_to_wstring(enemy.name) + L" terkena Silence!");
                                }
                                // --- DEBUFF ATTACK ---
                                if (chosenSpell->id == "DARK_CURSE_OF_FATIGUE_1") {
                                    enemy.attackDebuffValue = max(enemy.attackDebuffValue, 5 + finalPlayerIntelligence/10); // Ambil yang terbesar jika sudah ada debuff
                                    enemy.attackDebuffDuration = max(enemy.attackDebuffDuration, 3); // Ambil durasi terlama
                                    battleLogMessages.push_back(L"  ⚔ Serangan " + utf8_to_wstring(enemy.name) + L" melemah!");
                                }
                                // --- DEBUFF ACCURACY ---
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
                                // --- DEBUFF DEFENSE ---
                                if (chosenSpell->id == "THUNDER_MAGNETIC_OVERLOAD_2" || chosenSpell->id == "THUNDER_SKY_SOVEREIGNS_FURY_3") {
                                    int mDefDebuffVal = (chosenSpell->id == "THUNDER_MAGNETIC_OVERLOAD_2" ? 15 : 20) + finalPlayerIntelligence / 8;
                                    int mDefDebuffDur = (chosenSpell->id == "THUNDER_MAGNETIC_OVERLOAD_2" ? 3 : 4);
                                    enemy.magicDefenseDebuffValue = max(enemy.magicDefenseDebuffValue, mDefDebuffVal);
                                    enemy.magicDefenseDebuffDuration = max(enemy.magicDefenseDebuffDuration, mDefDebuffDur);
                                    battleLogMessages.push_back(L"  🧲 Pertahanan sihir " + utf8_to_wstring(enemy.name) + L" melemah!");
                                    if (chosenSpell->id == "THUNDER_SKY_SOVEREIGNS_FURY_3") { // Juga lemahkan defense fisik
                                        enemy.physicalDefenseDebuffValue = max(enemy.physicalDefenseDebuffValue, 15 + finalPlayerIntelligence / 8);
                                        enemy.physicalDefenseDebuffDuration = max(enemy.physicalDefenseDebuffDuration, 4);
                                    }
                                } else if (chosenSpell->id == "DARK_CURSE_OF_VULNERABILITY_2" || chosenSpell->id == "DARK_ETERNAL_NIGHT_CURSE_3") {
                                    enemy.physicalDefenseDebuffValue = max(enemy.physicalDefenseDebuffValue, (chosenSpell->id == "DARK_CURSE_OF_VULNERABILITY_2" ? 20 : 25) + finalPlayerIntelligence / 8);
                                    enemy.physicalDefenseDebuffDuration = max(enemy.physicalDefenseDebuffDuration, 4);
                                    enemy.magicDefenseDebuffValue = max(enemy.magicDefenseDebuffValue, (chosenSpell->id == "DARK_CURSE_OF_VULNERABILITY_2" ? 10 : 15) + finalPlayerIntelligence / 10);
                                    enemy.magicDefenseDebuffDuration = max(enemy.magicDefenseDebuffDuration, 4);
                                    battleLogMessages.push_back(L"  ☠️ " + utf8_to_wstring(enemy.name) + L" menjadi sangat rentan!");
                                    if (chosenSpell->id == "DARK_ETERNAL_NIGHT_CURSE_3") { // Juga debuff stat lain
                                        enemy.attackDebuffValue = max(enemy.attackDebuffValue, 10 + finalPlayerIntelligence/8);
                                        enemy.attackDebuffDuration = max(enemy.attackDebuffDuration, 4);
                                        battleLogMessages.push_back(L"  ☠️ Kekuatan dan kegesitannya juga menurun drastis!");
                                    }
                                }

                                // --- DOT ---
                                if (chosenSpell->id == "FIRE_IGNITE_1" || chosenSpell->id == "THUNDER_STATIC_FIELD_1" || chosenSpell->id == "FIRE_ENGULFING_FLAMES_2" || chosenSpell->id == "FIRE_VOLCANIC_ERUPTION_3" || chosenSpell->id == "WIND_TORNADO_OF_DESTRUCTION_3") {                                 bool dotExists = false;
                                int dotDmg = chosenSpell->basePower; // Ambil basePower sebagai dasar damage DoT
                                int dotTurns = 3; // Durasi default

                                if (chosenSpell->id == "FIRE_IGNITE_1") { dotDmg = 5 + finalPlayerIntelligence / 5; dotTurns = 3;}
                                else if (chosenSpell->id == "THUNDER_STATIC_FIELD_1") { dotDmg = 6 + finalPlayerIntelligence / 5; dotTurns = 4;}
                                else if (chosenSpell->id == "FIRE_ENGULFING_FLAMES_2") { dotDmg = (magicDamage > 0 ? magicDamage/3 : 10) + 8 + finalPlayerIntelligence/3; dotTurns = 3;}
                                else if (chosenSpell->id == "FIRE_VOLCANIC_ERUPTION_3") { dotDmg = (magicDamage > 0 ? magicDamage/3 : 15) + 12 + finalPlayerIntelligence/3; dotTurns = 4;}
                                else if (chosenSpell->id == "WIND_TORNADO_OF_DESTRUCTION_3") { dotDmg = (magicDamage > 0 ? magicDamage/3 : 20) + 15 + finalPlayerIntelligence/3; dotTurns = 3;}
                                else if (chosenSpell->id == "DARK_FIELD_OF_DESPAIR_3") { dotDmg = 10 + finalPlayerIntelligence/4; dotTurns = 4; /* MP Drain & stat debuff juga */ battleLogMessages.push_back(L"  Aura keputusasaan menguras MP musuh!"); }
                                else if (chosenSpell->id == "DARK_ETERNAL_NIGHT_CURSE_3") { dotDmg = 15 + finalPlayerIntelligence/4; dotTurns = 4; /* Efek lain sudah di atas */ }

                                for (auto& dot : enemy.activeDoTs) {
                                    if (dot.spellId == chosenSpell->id) { // Jika DoT sejenis sudah ada
                                        dot.remainingTurns = max(dot.remainingTurns, dotTurns); // Ambil durasi terlama
                                        dot.damagePerTurn = max(dot.damagePerTurn, dotDmg);     // Ambil damage terkuat
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
                                // --- RUNE ---
                                if (chosenSpell->id == "FIRE_EXPLOSIVE_RUNE_2") { int runeDamage = chosenSpell->basePower + finalPlayerIntelligence/2; // Scaling
                                int runeTurns = 2 + rand()%2; // 2-3 giliran
                                bool runeExists = false;
                                for(auto& r : enemy.activeRunes) {
                                    if(r.spellId == chosenSpell->id) {
                                        r.turnsUntilTrigger = runeTurns; // Refresh timer
                                        r.damageOnTrigger = max(r.damageOnTrigger, runeDamage); // Ambil damage terkuat
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
                                // --- LIFE LEECH & MP DRAIN (Spell) ---
                                if (chosenSpell->id == "DARK_MINOR_DRAIN_1" || chosenSpell->id == "DARK_LIFE_TAP_2" || chosenSpell->id == "LIGHT_CONSECRATED_STRIKE_2") {
                                int totalDamageDealt = magicDamage; // Jika bukan multihit, pakai magicDamage
                                if (chosenSpell->id == "THUNDER_STORM_CONDUIT_3" || chosenSpell->id == "WIND_ZEPHYRS_DANCE_3") {
                                }
                                int drainedHp = 0;
                                if(chosenSpell->id == "DARK_MINOR_DRAIN_1") drainedHp = totalDamageDealt / 2;
                                else if(chosenSpell->id == "DARK_LIFE_TAP_2") drainedHp = totalDamageDealt; // 100% leech
                                else if(chosenSpell->id == "LIGHT_CONSECRATED_STRIKE_2") drainedHp = totalDamageDealt / 3;

                                if (drainedHp > 0 && enemy.hp > 0) { // Hanya leech jika musuh masih hidup setelah damage
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
                        } else if (chosenSpell->targetType == "Self") { // Healing, Self Dispel
                        if (chosenSpell->basePower > 0 && chosenSpell->id != "LIGHT_DIVINE_RENEWAL_3" && chosenSpell->id != "LIGHT_PURIFICATION_1") {
                            int healAmount = chosenSpell->basePower + finalPlayerIntelligence / 2;
                            player.hp = min(player.maxHp, player.hp + healAmount);
                            battleLogMessages.push_back(L"  Kamu memulihkan " + to_wstring(healAmount) + L" HP!");
                        }
                        if (chosenSpell->id == "LIGHT_PURIFICATION_1" || chosenSpell->id == "LIGHT_DIVINE_RENEWAL_3") {
                            // player.activeDebuffs.clear(); // Jika ada sistem debuff pada player
                            battleLogMessages.push_back(L"  ✨ Semua efek negatif ringan telah dimurnikan darimu!");
                            if (chosenSpell->id == "LIGHT_DIVINE_RENEWAL_3") { // Heal besar juga
                                int healAmount = chosenSpell->basePower + finalPlayerIntelligence;
                                player.hp = min(player.maxHp, player.hp + healAmount);
                                battleLogMessages.push_back(L"  Dan kamu memulihkan " + to_wstring(healAmount) + L" HP secara masif!");
                            }
                        }
                    }
                        }
                    // Tambahkan delayPrint untuk efek terakhir yang signifikan jika perlu
                    if (!battleLogMessages.empty() && turnActionLog != battleLogMessages.back() && battleLogMessages.back().find(L"➤ Kamu menggunakan") == wstring::npos ) {
                         delayPrint(battleLogMessages.back(), 20);
                    }

                } else if (chosenSpell) { // MP tidak cukup
                    battleLogMessages.push_back(L"MP tidak cukup untuk " + utf8_to_wstring(chosenSpell->name) + L"!");
                    continue;
                } else { // chosenSpell adalah nullptr (seharusnya tidak terjadi jika validasi input benar)
                     battleLogMessages.push_back(L"Pilihan magic tidak valid (internal error).");
                     continue;
                }
                break;
            }
            case 3: { // Item
                turnActionLog = L"Menggunakan item... (Logika dasar item)";
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                // Contoh: Jika punya Health Potion dan menggunakannya
                // if (player.inventory memiliki Health Potion) {
                //    player.hp = min(player.maxHp, player.hp + 50);
                //    battleLogMessages.push_back(L"Kamu menggunakan Health Potion, memulihkan 50 HP!");
                //    hapus Health Potion dari inventory
                // } else { battleLogMessages.push_back(L"Kamu tidak punya item itu!"); continue; } // Jika gagal, jangan habiskan giliran
                system("pause"); // Sementara
                break; // Habiskan giliran setelah pakai item
            }
            case 4: { // Bertahan
                turnActionLog = L"➤ Kamu memilih untuk bertahan. Damage musuh berikutnya akan dikurangi!";
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                break;
            }
            case 5: { // Kabur
                if (enemy.isBoss) {
                    turnActionLog = L"➤ Tidak bisa kabur dari Boss!";
                } else if (rand() % 100 < (50 + finalPlayerAgility / 2) ) { // Gunakan finalPlayerAgility
                    turnActionLog = L"➤ Kamu berhasil kabur!";
                    delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                    processEndOfPlayerTurn(player, battleLogMessages);
                    drawBattleScreen(enemy, player, battleLogMessages);
                    wcout << L"\nTekan Enter untuk lanjut..."; cin.ignore(numeric_limits<streamsize>::max(), '\n'); if(cin.peek()=='\n') cin.ignore(); cin.get();
                    return false;
                } else {
                    turnActionLog = L"➤ Gagal kabur!";
                }
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                break;
            }
            default:
                turnActionLog = L"Aksi tidak valid.";
                delayPrint(turnActionLog, 20); battleLogMessages.push_back(turnActionLog);
                continue; // Ulangi input pemain, tidak menghabiskan giliran
        } // Akhir switch

        if (enemy.hp <= 0) { enemy.hp = 0; }
        else { // Giliran Musuh
            if (choice >=1 && choice <=5 && choice !=3) { // Hanya jika pemain melakukan aksi valid yang menghabiskan giliran
                if (enemy.isStunned && enemy.stunDuration > 0) {
                    battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" masih STUN!");
                    enemy.stunDuration--;
                    if (enemy.stunDuration == 0) { enemy.isStunned = false; battleLogMessages.push_back(L"  " + utf8_to_wstring(enemy.name) + L" pulih dari STUN."); }
                } else if (enemy.isFeared && enemy.fearDuration > 0) {
                    if (rand() % 100 < 50) { // 50% chance musuh gagal aksi karena Fear
                        battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" terlalu takut untuk bergerak!");
                    } else { // Musuh berhasil mengatasi Fear giliran ini
                        if (rand() % 100 < enemyHitChance) {
                            int actualDamageToPlayer = baseDamageToPlayer;
                            if (choice == 4) { actualDamageToPlayer /= 2; } // Pemain bertahan
                            // PENERAPAN SHIELD PEMAIN & RETALIATE
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
                            if (playerRetaliateDamage > 0 && !playerIsPhysicallyImmune && baseDamageToPlayer > 0 ) { // Retaliate jika damage asli ada (sebelum shield)
                                enemy.hp -= playerRetaliateDamage;
                                battleLogMessages.push_back(L"  ⚔️ " + utf8_to_wstring(enemy.name) + L" terkena damage balasan " + to_wstring(playerRetaliateDamage) + L"!");
                                if (enemy.hp <= 0) { enemy.hp = 0; }
                            }
                        } else { battleLogMessages.push_back(L"➤ Serangan " + utf8_to_wstring(enemy.name) + L" meleset!"); }
                    }
                } else if (enemy.isSilenced && enemy.silenceDuration > 0) {
                    battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" terbungkam!");
                    // Jika musuh punya AI untuk sihir, di sini dia akan gagal. Karena tidak, dia tetap serang fisik.
                    if (rand() % 100 < enemyHitChance) { /* ... serangan fisik musuh dengan shield check & retaliate ... */ } else { /* ... meleset ... */ }
                } else { // Musuh menyerang normal
                    if (rand() % 100 < enemyHitChance) {
                        int actualDamageToPlayer = baseDamageToPlayer;
                        if (choice == 4) { actualDamageToPlayer /= 2; }
                        if (playerIsPhysicallyImmune) { /* ... Immune ... */ actualDamageToPlayer = 0;}
                        else { for(auto& ench : player.activeEnchantments) { if (ench.shieldHp > 0) { /* ... Shield logic ... */ break;}}}
                        if (actualDamageToPlayer > 0) { player.hp -= actualDamageToPlayer; }
                        battleLogMessages.push_back(L"➤ " + utf8_to_wstring(enemy.name) + L" menyerangmu! Damage diterima: " + to_wstring(actualDamageToPlayer));
                        if (playerRetaliateDamage > 0 && !playerIsPhysicallyImmune && baseDamageToPlayer > 0) { /* ... Retaliate ... */ }
                    } else { battleLogMessages.push_back(L"➤ Serangan " + utf8_to_wstring(enemy.name) + L" meleset!"); }
                }
            }
        }
        if (player.hp <= 0) { player.hp = 0; }

        // --- PROSES AKHIR GILIRAN ---
        if (player.hp > 0 && (choice >=1 && choice <=5 && choice !=3) ) {
             processEndOfPlayerTurn(player, battleLogMessages); // Proses buff/HoT pemain
        }
        // Proses durasi debuff musuh
        if (enemy.attackDebuffDuration > 0) { enemy.attackDebuffDuration--; if (enemy.attackDebuffDuration == 0) { enemy.attackDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" serangannya normal kembali."); }}
        if (enemy.accuracyDebuffDuration > 0) { enemy.accuracyDebuffDuration--; if (enemy.accuracyDebuffDuration == 0) { enemy.accuracyDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" pandangannya normal kembali."); }}
        if (enemy.physicalDefenseDebuffDuration > 0) { enemy.physicalDefenseDebuffDuration--; if (enemy.physicalDefenseDebuffDuration == 0) { enemy.physicalDefenseDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" pertahanan fisiknya normal kembali."); }}
        if (enemy.magicDefenseDebuffDuration > 0) { enemy.magicDefenseDebuffDuration--; if (enemy.magicDefenseDebuffDuration == 0) { enemy.magicDefenseDebuffValue = 0; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" pertahanan sihirnya normal kembali."); }}
        if (enemy.fearDuration > 0) { enemy.fearDuration--; if (enemy.fearDuration == 0) { enemy.isFeared = false; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" tidak lagi ketakutan."); }}
        if (enemy.silenceDuration > 0) { enemy.silenceDuration--; if (enemy.silenceDuration == 0) { enemy.isSilenced = false; battleLogMessages.push_back(utf8_to_wstring(enemy.name) + L" tidak lagi terbungkam."); }}
        // Rune tidak berkurang durasinya di sini, tapi di awal giliran atau saat trigger lain.
        // --- AKHIR PROSES AKHIR GILIRAN ---

        if (player.hp <= 0 || enemy.hp <= 0) { /* Loop akan berhenti */ }
        else {
            drawBattleScreen(enemy, player, battleLogMessages);
            wcout << L" << Tekan Enter Untuk Melanjutkan Ke Turn Selanjutnya <<";
            cin.ignore();
            cin.get();
        }
    } // Akhir battle loop

    // --- HASIL PERTARUNGAN ---
    if (player.hp <= 0 && !playerRevivedThisBattle) { // Hanya proses revive jika belum revive di pertarungan ini
        for (auto it = player.activeEnchantments.begin(); it != player.activeEnchantments.end(); ) {
            if (it->hasRevive) {
                player.hp = player.maxHp / 2; // Revive dengan 50% HP
                battleLogMessages.push_back(L"✨ Dengan kekuatan " + utf8_to_wstring(it->spellName) + L", kamu bangkit kembali!");
                playerRevivedThisBattle = true; // Tandai sudah revive
                it = player.activeEnchantments.erase(it); // Hapus buff revive setelah digunakan
                // Tidak perlu ++it karena erase mengembalikan iterator ke elemen berikutnya
                // Jika ingin tetap di loop (meskipun ini di akhir battle): continue; atau break; dari loop ini
                break; // Hanya satu efek revive yang aktif per kematian
            } else {
                ++it;
            }
        }
    }

    drawBattleScreen(enemy, player, battleLogMessages); // Tampilkan kondisi final
    if (player.hp <= 0) {
            system("cls");
            printLine(); 
            centerText(L"⚔️ PERTEMPURAN SELESAI! ⚔️");
            printLine();
            delayPrint(L"",10); delayPrint(L"❌ Kamu telah dikalahkan...", 50);
            printLine();
    } else {
        if (enemy.hp <=0) {
            printLine(); 
            centerText(L"⚔️ PERTEMPURAN SELESAI! ⚔️");
            printLine();
            wcout << L"✅ Musuh " << utf8_to_wstring(enemy.name) << L" telah dikalahkan!\n";
            wcout << L"🎉 Kamu mendapatkan: " << to_wstring(enemy.goldDrop) << L" Gold 💰 dan " << to_wstring(enemy.expReward) << L" EXP 📚.\n";
            printLine();
            player.gold += enemy.goldDrop;
            wcout << "<< Tekan Enter Untuk Berpindah Ke Selanjutnya";
            cin.get();
            handleExperienceAndLevelUp(player, enemy.expReward);
            printLine();
        } else if (playerRevivedThisBattle && enemy.hp > 0) {
            delayPrint(L" Kamu bangkit, namun musuh masih berdiri. Pertarungan berakhir untuk saat ini.", 40);
        }
    }
    cin.clear();
    // Membersihkan sisa buffer input dengan lebih aman
    if (cin.rdbuf()->in_avail() > 0) { // Cek jika ada sisa di buffer
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else if (cin.peek() == '\n' && cin.peek() != EOF) { // Jika hanya newline
         cin.ignore();
    }
    return (player.hp > 0);
}


// Diary System Functions
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

void showCompanionList() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ COMPANION LIST ✦✦✦");
    printLine();
    
    for(int i = 0; i < companions.size(); i++) {
        wcout << L"    ❖ " << i+1 << L". " << companions[i].name.c_str();
        if(companions[i].met) {
            wcout << L" [MET]";
        } else {
            wcout << L" [UNKNOWN]";
        }
        wcout << endl;
    }
    wcout << L"    ❖ 0. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih companion ✦: ";
}


void showCompanionDetail(Companion& companion) {
    system("cls");
    printLine();
    centerText(L"✦✦✦ DETAIL COMPANION ✦✦✦");
    printLine();
    
    wcout << L"Nama: " << companion.name.c_str() << endl;
    if(companion.met) {
        wcout << L"Level: " << companion.level << endl;
        wcout << L"HP: " << companion.hp << L"/" << companion.maxHp << endl;
        wcout << L"Loyalty: " << companionRelations[companion.name] << L"/100" << endl;
        wcout << L"Personality: " << companion.personality.c_str() << endl;
        wcout << L"Deskripsi: " << companion.description.c_str() << endl;
    } else {
        wcout << L"Status: Belum bertemu" << endl;
        wcout << L"Info: ???" << endl;
    }
    printLine();
    wcout << L"    ❖ 1. Kembali" << endl;
    printLine(50, L'─');
    wcout << L"Pilih aksi ✦: ";
}

void enterDungeon(string dungeonName) {
    Dungeon& dungeon = allDungeons[dungeonName];
    bool inDungeon = true;
    if (!dungeon.visitedCampAreas.empty()) {
    wcout << L"Kamu pernah mencapai lantai " << dungeon.visitedCampAreas.back() << L".\n";
    wcout << L"❖ 1. Mulai dari lantai 1\n❖ 2. Mulai dari Camp terakhir\nPilih: ";
    int startChoice;
    cin >> startChoice;
    if (startChoice == 2) {
        dungeon.currentFloor = dungeon.visitedCampAreas.back();
    }
}

    while (inDungeon) {
        system("cls");
        printLine();
        wstring title = L"🏛️  " + wstring(dungeon.name.begin(), dungeon.name.end()) +
                L" - Lantai " + formatDungeonFloor(dungeon, dungeon.currentFloor);
        centerText(title); 
        if (dungeon.campAreas.count(dungeon.currentFloor)) {
            centerText(L"🏕️  CAMP AREA");
        } else {
            centerText(L"⚔️  AREA BERBAHAYA");
        }
        printLine();

        // Story lock check
        if (find(dungeon.storyLockedFloors.begin(), dungeon.storyLockedFloors.end(), dungeon.currentFloor) != dungeon.storyLockedFloors.end()) {
            centerText(L"❌ Ada tembok tinggi yang menghalangi jalan selanjutnya ");
            centerText(L"        Mungkin progress cerita akan membukanya!         ");
            printLine();
            wcout << L"Tekan Enter untuk keluar dari dungeon..."; cin.ignore(); cin.get();
            return;
        }

        // Cek Camp Area
        if (dungeon.campAreas.count(dungeon.currentFloor)) {
            CampArea& camp = dungeon.campAreas[dungeon.currentFloor];
            camp.visited = true;
            if (find(dungeon.visitedCampAreas.begin(), dungeon.visitedCampAreas.end(), camp.floor) == dungeon.visitedCampAreas.end()) {
                dungeon.visitedCampAreas.push_back(camp.floor);
            }
            wcout << L"Kamu tiba di Camp Area lantai " << camp.floor << L". Di sini kamu aman." << endl;
            printLine(60, L'─');
            wcout << L"❖ 1. Istirahat (tersisa " << (2 - camp.restUsed) << L" kali)" << endl;
            wcout << L"❖ 2. Lanjut ke lantai berikutnya" << endl;
            wcout << L"❖ 3. Kembali ke lantai sebelumnya" << endl;
            wcout << L"❖ 4. Buka Diary" << endl;
            wcout << L"❖ 0. Keluar dari dungeon" << endl;
            printLine(60, L'─');
            wcout << L"Pilih aksi ✦: ";

            int campChoice;
            cin >> campChoice;

            switch (campChoice) {
                case 1:
                    if (camp.restUsed < 2) {
                        player.hp = player.maxHp;
                        player.mana = player.maxMana;
                        camp.restUsed++;
                        delayPrint(L"Kamu beristirahat di dekat api unggun. Semua HP dan Mana dipulihkan.");
                    } else {
                        delayPrint(L"Kamu sudah menggunakan 2x istirahat di lantai ini.");
                    }
                    break;
                case 2:
                    dungeon.currentFloor ++;
                    break;
                case 3:
                    dungeon.currentFloor --;
                    break;
                case 4:
                    showDiaryMenu();
                    break;
                case 0:
                    return;
                default:
                    delayPrint(L"Aksi tidak dikenali.");
                    break;
            }
        } else {
            wcout << L"Kamu berada di lantai " << formatDungeonFloor(dungeon, dungeon.currentFloor)
                  << L" dari " << dungeon.name.c_str() << L"." << endl;
            printLine(60, L'─');
            wcout << L"❖ 1. Eksplorasi lantai" << endl;
            wcout << L"❖ 2. Lanjut ke lantai berikutnya" << endl;
            wcout << L"❖ 3. Kembali ke lantai sebelumnya" << endl;
            wcout << L"❖ 4. Gunakan item" << endl;
            printLine(60, L'─');
            wcout << L"Pilih aksi ✦: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    delayPrint(L"(Encounter musuh belum diimplementasikan)");
                    break;
                case 2: {
                    dungeon.currentFloor ++;
                    if (dungeon.campAreas.count(dungeon.currentFloor)) {
                        delayPrint(L"Area aman. Tidak ada musuh.");
                        break;
                    }
                    string enemyName;
                    string floorKey = dungeon.name + "_F" + to_string(dungeon.currentFloor);
                    if (dungeon.miniBosses.count(dungeon.currentFloor) && !defeatedBosses[floorKey]) {
                        enemyName = dungeon.miniBosses[dungeon.currentFloor];
                    } else if (dungeon.finalBoss.count(dungeon.currentFloor) && !defeatedBosses[floorKey]) {
                        enemyName = dungeon.finalBoss[dungeon.currentFloor];
                    } else {
                        enemyName = dungeon.floorEnemies[dungeon.currentFloor][rand() % dungeon.floorEnemies[dungeon.currentFloor].size()];
                    }

                    if (enemyDatabase.count(enemyName)) {
                        bool survived = startBattle(enemyDatabase[enemyName]);
                        if (!survived) return;
                        if (enemyDatabase[enemyName].isBoss) {
                            defeatedBosses[floorKey] = true;
                        }
                    } else {
                        delayPrint(L"Musuh tidak ditemukan.");
                    }
                    break; }
                case 3:
                    if (dungeon.currentFloor == 1) {
                        delayPrint(L"Kamu telah kembali ke lantai awal dungeon dan keluar.");
                        return;
                    } else {
                        dungeon.currentFloor --;
                        if (dungeon.campAreas.count(dungeon.currentFloor)) {
                        delayPrint(L"Area aman. Tidak ada musuh.");
                        break;
                    }
                    string enemyName;
                    string floorKey = dungeon.name + "_F" + to_string(dungeon.currentFloor);
                    if (dungeon.miniBosses.count(dungeon.currentFloor) && !defeatedBosses[floorKey]) {
                        enemyName = dungeon.miniBosses[dungeon.currentFloor];
                    } else if (dungeon.finalBoss.count(dungeon.currentFloor) && !defeatedBosses[floorKey]) {
                        enemyName = dungeon.finalBoss[dungeon.currentFloor];
                    } else {
                        enemyName = dungeon.floorEnemies[dungeon.currentFloor][rand() % dungeon.floorEnemies[dungeon.currentFloor].size()];
                    }

                    if (enemyDatabase.count(enemyName)) {
                        bool survived = startBattle(enemyDatabase[enemyName]);
                        if (!survived) return;
                        if (enemyDatabase[enemyName].isBoss) {
                            defeatedBosses[floorKey] = true;
                        }
                    } else {
                        delayPrint(L"Musuh tidak ditemukan.");
                    }
                    }
                    break;
                case 4:
                    showItemList(); // Panggil sistem item kamu
                    break;
                default:
                    delayPrint(L"Aksi tidak valid.");
                    break;
            }
        }

        wcout << L"\nTekan Enter untuk lanjut..."; cin.ignore(); cin.get();
    }
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
        
        cin >> choice;
        
        switch(choice) {
            case 1: {
                // Status Karakter
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
                wcout << L"Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }
            case 2: {
                // Inventory System
                int invChoice;
                do {
                    showInventoryCategory();
                    cin >> invChoice;
                    
                    if(invChoice == 1) {
                        // Item List
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
                                    
                                    if(detailChoice == 1 && selectedItem->type == "consumable") {
                                        wcout << L"Item " << selectedItem->name.c_str() << L" digunakan!" << endl;
                                        // Apply item effect here
                                        if(selectedItem->name == "Health Potion") {
                                            player.hp = min(player.maxHp, player.hp + 50);
                                        } else if(selectedItem->name == "Mana Potion") {
                                            player.mana = min(player.maxMana, player.mana + 30);
                                        }
                                        player.inventory.erase(player.inventory.begin() + itemChoice - 1);
                                        detailChoice = 2; // Go back
                                        itemChoice = 0; // Refresh item list
                                    }
                                } while(detailChoice != 2);
                            }
                        } while(itemChoice != 0);
                    } else if(invChoice == 2) {
                        // Weapon List
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
                                            // Check requirements
                                            if(player.strength >= selectedWeapon->strengthRequired && 
                                               player.intelligence >= selectedWeapon->intelligenceRequired) {
                                                // Unequip current weapon if any
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
                                        wcout << L"Tekan Enter untuk melanjutkan...";
                                        cin.ignore();
                                        cin.get();
                                    }
                                } while(detailChoice != 2);
                            }
                        } while(weaponChoice != 0);
                    }
                } while(invChoice != 3);
                break;
            }
            case 5: {
                // Companion List
                int compChoice;
                do {
                    showCompanionList();
                    cin >> compChoice;
                    
                    if(compChoice > 0 && compChoice <= companions.size()) {
                        int detailChoice;
                        do {
                            showCompanionDetail(companions[compChoice-1]);
                            cin >> detailChoice;
                        } while(detailChoice != 1);
                    }
                } while(compChoice != 0);
                break;
            }
            case 6: {
                // Calendar
                int calChoice;
                do {
                    showCalendar();
                    cin >> calChoice;
                } while(calChoice != 1);
                break;
            }
            case 3:
            case 4:
                showSkillTreeMenu(player);
                break;
            case 7:
            case 8:
                wcout << L"Fitur belum diimplementasikan. Tekan Enter...";
                cin.ignore();
                cin.get();
                break;
        }
    } while(choice != 9 && choice != 0);
    
    if(choice == 0) {
        gameRunning = false;
    }
}

// Main Game Loop
void showGameMenu() {
    int choice;
    do {
        system("cls");
        printLine();
        centerText(L"✦✦✦ " + wstring(currentSubArea.begin(), currentSubArea.end()) + L" - " + wstring(currentWorld.begin(), currentWorld.end()) + L" ✦✦✦");
        printLine();
        wcout << L"Lokasi: " << currentSubArea.c_str() << L" di " << currentWorld.c_str() << endl;
        wcout << L"Hari: " << currentDay << endl;
        printLine();    
        const auto& actions = allWorlds[currentWorld].subAreas[currentSubArea].actions;
        for (int i = 0; i < actions.size(); ++i) {
            wcout << L"❖ " << i + 1 << L". " << actions[i].c_str() << endl;
        }
        printLine(50, L'─');
        wcout << L"Pilih aksi ✦: ";
        
        cin >> choice;
        cin.ignore(); // Penting untuk menghindari masalah newline saat pakai cin.get()

        if (choice > 0 && choice <= actions.size()) {
            string action = actions[choice - 1];

            if (action == "Cek Sekitar") {
                exploreArea();
            } else if (action == "Membuka Diary" || action == "Buka Diary") {
                showDiaryMenu();
            } else if (action == "Pilih Lokasi") {
                showLocationMenu();
            } else if (action == "Bicara dengan Companion") {
                wcout << L"(Fitur obrolan companion belum diimplementasikan)" << endl;
                wcout << L"Tekan Enter untuk kembali..."; cin.get();
            } else if (action == "Quest Board") {
                wcout << L"(Quest Board belum tersedia)" << endl;
                wcout << L"Tekan Enter untuk kembali..."; cin.get();
            } else if (action == "Item Shop") {
                showItemShop();
            } else if (action == "Penempa Besi") {
                showBlacksmith();
            } else if (action == "Cek Berita Kota") {
                wcout << L"Koran hari ini memuat berita tentang pahlawan misterius..." << endl;
                wcout << L"Tekan Enter untuk kembali..."; cin.get();
            } else if (action == "Masuk ke Ancient Temple (Dungeon)") {
                enterDungeon("Ancient Temple");
            } else if (action == "Masuk ke Goa Avernix (Dungeon)") {
                enterDungeon("Goa Avernix");
            } else if (action == "Lawan Vallen") {
                wcout << L"(Pertarungan dengan Vallen belum tersedia atau belum memenuhi syarat)" << endl;
                wcout << L"Tekan Enter untuk kembali..."; cin.get();
            } else {
                wcout << L"Aksi belum dikenali!" << endl;
                wcout << L"Tekan Enter untuk kembali..."; cin.get();
            }
        } else {
            wcout << L"Pilihan tidak valid!" << endl;
            wcout << L"Tekan Enter untuk melanjutkan...";
            cin.get();
        }

            } while(gameRunning && choice != 0);
        }

void exploreArea() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ EKSPLORASI AREA ✦✦✦");
    printLine();
    
    wcout << L"Kamu melihat-lihat sekitar " << currentSubArea.c_str() << L" di " << currentWorld.c_str() << L"..." << endl;

    
    // Random encounter atau item discovery
    int randomEvent = rand() % 3;
    
    switch(randomEvent) {
        case 0:
            wcout << L"Kamu menemukan sebuah item tersembunyi!" << endl;
            if(rand() % 2 == 0) {
                player.inventory.push_back(&allItems[0]); // Health Potion
                wcout << L"Health Potion ditambahkan ke inventory!" << endl;
            } else {
                player.inventory.push_back(&allItems[1]); // Mana Potion
                wcout << L"Mana Potion ditambahkan ke inventory!" << endl;
            }
            break;
        case 1:
            wcout << L"Kamu mendapatkan sedikit experience dari observasi..." << endl;
            player.exp += 10;
            wcout << L"EXP +10!" << endl;
            break;
        case 2:
            wcout << L"Tidak ada yang menarik di area ini..." << endl;
            wcout << L"Mungkin coba area lain?" << endl;
            break;
    }
    
    wcout << L"Tekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void showLocationMenu() {
    system("cls");
    printLine();
    centerText(L"✦✦✦ PILIH LOKASI ✦✦✦");
    printLine();

    wcout << L"❖ 1. Area Lain di " << currentWorld.c_str() << endl;
    wcout << L"❖ 2. World Map" << endl;
    wcout << L"❖ 0. Batal" << endl;
    printLine(50, L'─');
    wcout << L"Pilih opsi ✦: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        // Tampilkan sub-area di world sekarang
        const auto& subAreas = allWorlds[currentWorld].subAreas;
        int idx = 1;
        vector<string> subAreaList;
        system("cls");
        printLine();
        centerText(L"✦ SUB AREA - " + wstring(currentWorld.begin(), currentWorld.end()) + L" ✦");
        printLine();
        for (const auto& [name, _] : subAreas) {
            wcout << L"❖ " << idx++ << L". " << name.c_str();
            if (name == currentSubArea) wcout << L" [SEKARANG]";
            wcout << endl;
            subAreaList.push_back(name);
        }
        wcout << L"❖ 0. Kembali" << endl;
        printLine(50, L'─');
        wcout << L"Pilih sub-area ✦: ";
        int subChoice;
        cin >> subChoice;
        if (subChoice > 0 && subChoice <= subAreaList.size()) {
            currentSubArea = subAreaList[subChoice - 1];
        }
    } else if (choice == 2) {
        // Tampilkan world map
        int idx = 1;
        vector<string> worldList;
        system("cls");
        printLine();
        centerText(L"✦ WORLD MAP ✦");
        printLine();
        for (const auto& [name, world] : allWorlds) {
            wcout << L"❖ " << idx++ << L". " << name.c_str();
            if (name == currentWorld) wcout << L" [SEKARANG]";
            wcout << endl;
            worldList.push_back(name);
        }
        wcout << L"❖ 0. Batal" << endl;
        printLine(50, L'─');
        wcout << L"Pilih world ✦: ";
        int worldChoice;
        cin >> worldChoice;
        if (worldChoice > 0 && worldChoice <= worldList.size()) {
            currentWorld = worldList[worldChoice - 1];
            currentSubArea = allWorlds[currentWorld].startSubArea;
        }
    }
}


int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    int choice;
    do {
        showTitleScreen();
        cin >> choice;
        
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
                wcout << L"Load Game belum diimplementasikan." << endl;
                wcout << L"Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
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
                wcout << L"Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }
            case 4: {
                wcout << L"Terima kasih telah bermain!" << endl;
                return 0;
            }
            default: {
                wcout << L"Pilihan tidak valid!" << endl;
                wcout << L"Tekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
                break;          
            }
        }
    } while(choice != 4);
    
    return 0;
}