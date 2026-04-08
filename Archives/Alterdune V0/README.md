# ALTERDUNE – Mini RPG en C++

## Structure du projet
```
ALTERDUNE/
├── src/
│   ├── main.cpp
│   ├── Entity.h / .cpp       ← classe abstraite
│   ├── Player.h / .cpp       ← hérite Entity
│   ├── Monster.h / .cpp      ← hérite Entity
│   ├── Item.h / .cpp
│   ├── ActAction.h / .cpp    ← catalogue statique
│   └── FileLoader.h / .cpp   ← lecture CSV
├── data/
│   ├── items.csv
│   └── monsters.csv
└── README.md
```

## Compilation (VS Code Terminal)

### Méthode rapide (un seul terminal)
```bash
g++ -std=c++17 src/*.cpp -o alterdune
```

### Lancement
```bash
./alterdune          # Linux / macOS
alterdune.exe        # Windows
```
> Le programme doit être lancé depuis le dossier ALTERDUNE/ pour trouver data/

## Configurer VS Code

1. Ouvrir le dossier `ALTERDUNE/` avec VS Code
2. Installer l'extension **C/C++** (Microsoft)
3. `Ctrl+Shift+B` → choisir **g++ build active file** ou créer un `tasks.json` :

```json
{
  "tasks": [{
    "type": "cppbuild",
    "label": "Build ALTERDUNE",
    "command": "/usr/bin/g++",
    "args": ["-std=c++17", "${workspaceFolder}/src/*.cpp", "-o", "${workspaceFolder}/alterdune"],
    "group": { "kind": "build", "isDefault": true }
  }]
}
```

## Justifications des choix (pour TD11-12)

| Choix | Raison |
|-------|--------|
| `Entity` abstraite avec `display()=0` | Force chaque sous-classe à implémenter son affichage (polymorphisme) |
| `Player` et `Monster` héritent `Entity` | Partagent name/hp/hpMax sans duplication de code |
| `ActAction` avec catalogue statique | Un seul catalogue partagé, pas de copie, identique à ce que décrit l'énoncé |
| `FileLoader` séparé | Sépare la responsabilité de lecture/parsing du reste du jeu |
| `rollDamage` avec `<random>` | Conforme à la consigne (eviter rand(), utiliser `<random>`) |
