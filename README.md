# Project 2 — 5 hand poker (C++ / Qt)

A simple **5 hand poker (five-card draw)** game implemented with clean C++ OOP and a Qt Widgets GUI. It follows the spec: bankroll, bet 1–5, deal 5 cards, choose holds, draw once, evaluate the hand, adjust bankroll, and allow cash-out.

> This repo contains only source code (headers + .cpp) and a PlantUML diagram for submission; no IDE/build outputs.

---

## Tech Stack

- **C++17**
- **Qt 6 (Qt Widgets)** for GUI
- **CMake** for builds
- **MSVC (Visual Studio 2022 Build Tools)** on Windows

---

## Project Structure

```
project2_asaifnoorian/
├─ include/
│  ├─ card.h          # Card (rank 2..14, suit)
│  ├─ deck.h          # 52-card deck, shuffle/deal
│  ├─ hand.h          # 5-card hand container
│  ├─ player.h        # bankroll, addCoins, canBet, win/lose
│  ├─ evaluator.h     # evaluate hand -> name + multiplier
│  └─ game.h          # (optional console loop; not used by GUI)
├─ src/
│  ├─ deck.cpp
│  ├─ hand.cpp
│  ├─ player.cpp
│  └─ evaluator.cpp
├─ gui_qt/
│  ├─ MainWindow.h    # Qt GUI controller
│  ├─ MainWindow.cpp  # UI layout + event flow
│  └─ main_qt.cpp     # Qt entrypoint
├─ class-diagram.puml # PlantUML class diagram
└─ CITATIONS.md
```

---

## Build & Run (Windows, **MSVC + Qt 6**)

### Prerequisites

- Qt 6.x **MSVC 2022 64-bit** (e.g., `C:\Qt\6.9.1\msvc2022_64`)
- Visual Studio 2022 **Build Tools** (C++ workload)
- CMake 3.22+

### 1) Open the right shell

Use **Developer PowerShell for VS 2022** (sets up `cl`, `link`, MSBuild).

### 2) Configure (first time)

```powershell
$qtRoot = "C:\Qt.9.1\msvc2022_64"   # <-- set to your Qt path
cd $HOME\Desktop\project2_asaifnoorian
mkdir build_vs; cd build_vs
cmake -S ..\gui_qt -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="$qtRoot"
```

### 3) Build

```powershell
cmake --build . --config Release
```

### 4) Run

```powershell
$env:Path = "$qtRootin;$env:Path"
.\Release\project2_asaifnoorian.exe
```

If you get a platform/DLL error, deploy Qt next to the exe:

```powershell
& "$qtRootin\windeployqt.exe" --release --compiler-runtime .\Release\project2_asaifnoorian.exe
.\Release\project2_asaifnoorian.exe
```

### Alternative: Qt Creator

- Open `gui_qt/CMakeLists.txt` → choose the **MSVC 2022 64-bit** Kit → Configure → Build → Run.

> **MinGW path (optional):** install `Qt 6.x MinGW 64-bit`, open the “Qt for MinGW” shell, then configure with `-G "Ninja"` or `-G "MinGW Makefiles"` and use the MinGW `bin` in PATH. Use the matching `CMAKE_PREFIX_PATH=C:\Qt.x\mingw_64`.

---

## How to Play

1. **Insert Coins** — add to your bankroll.
2. **Place Bet (1–5)** — can’t exceed bankroll; you place it **before** the deal.
3. **Deal** — five cards appear (**your hand**). Toggle **Hold** under any cards you want to keep.
4. **Draw** — replaces non-held cards, evaluates the hand, updates **Payout** and **Coins Remaining**.
5. **Next Hand** — click **Deal** again (bet can be changed before the next deal).
6. **Cash Out** any time to exit.

A “Dealt: …” line also shows your cards as text (e.g., `A♠ 10♥ 7♣ 7♦ K♣`).

---

## Payout Table

| Hand            | Pays (per 1 coin) |
| --------------- | ----------------- |
| Royal Flush     | 250×              |
| Straight Flush  | 50×               |
| Four of a Kind  | 25×               |
| Full House      | 9×                |
| Flush           | 6×                |
| Straight        | 4×                |
| Three of a Kind | 3×                |
| Two Pair        | 2×                |
| Jacks or Better | 1×                |
| No Hand         | 0×                |

Rules notes:

- Straights support **A-low** (`A-2-3-4-5`) and **A-high** (`10-J-Q-K-A`).
- Deck re-shuffled before each game.

---

## Design Overview

- **Card** — rank (2..14, Ace=14), suit; helpers for display strings.
- **Deck** — owns 52 `Card`s, `shuffle()`, `deal()`.
- **Hand** — fixed-size array of 5 cards; add/replace with hold mask.
- **Player** — bankroll, `canBet()`, `win()`, `lose()`.
- **HandEvaluator** — evaluates a hand and returns `{name, multiplier, rank}`.
- **MainWindow** — Qt GUI: bet controls, deal/draw, hold toggles, payout display.

See `class-diagram.puml` for the UML diagram.

---

## Troubleshooting

- **“Could not find Qt6Config.cmake”**  
  `CMAKE_PREFIX_PATH` must point to the Qt kit root (e.g., `C:\Qt.9.1\msvc2022_64`).

- **“Failed to load platform plugin 'windows'”**  
  Run `windeployqt` as shown above or ensure `qwindows.dll` is under `Release\platforms\`.

- **Bet buttons disabled**  
  That’s by design after dealing; change bet **before** the next deal.

---

## License & Credits

See **CITATIONS.md** for libraries/tools and AI assistance.  
You may add an OSS license (e.g., MIT) if publishing publicly.

---
