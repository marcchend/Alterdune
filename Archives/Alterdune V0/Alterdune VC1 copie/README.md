# ALTERDUNE – Projet C++ POO

## Structure du projet
```
ALTERDUNE/
├── src/
│   ├── main.cpp          ← point d'entrée, menu, combat
│   ├── Entity.h/.cpp     ← classe abstraite (base commune)
│   ├── Player.h/.cpp     ← hérite Entity
│   ├── Monster.h/.cpp    ← hérite Entity
│   ├── Item.h/.cpp       ← objet utilisable
│   ├── ActAction.h/.cpp  ← actions ACT + catalogue
│   └── FileLoader.h/.cpp ← lecture des fichiers CSV
└── data/
    ├── items.csv
    └── monsters.csv
```

## Compilation et lancement

Ouvrez un terminal dans le dossier ALTERDUNE/, puis :

```bash
g++ -std=c++17 src/*.cpp -o alterdune
./alterdune
```

Sur Windows avec MinGW :
```bash
g++ -std=c++17 src/*.cpp -o alterdune.exe
alterdune.exe
```

> Important : lancez le programme depuis le dossier ALTERDUNE/
> pour qu'il trouve les fichiers data/

## Configurer VS Code (tasks.json)

Créez `.vscode/tasks.json` :
```json
{
  "version": "2.0.0",
  "tasks": [{
    "label": "Build ALTERDUNE",
    "type": "shell",
    "command": "g++",
    "args": ["-std=c++17", "src/*.cpp", "-o", "alterdune"],
    "group": { "kind": "build", "isDefault": true }
  }]
}
```
Puis `Ctrl+Shift+B` pour compiler.

## Justifications des choix (pour le TD11-12)

| Concept POO       | Où ?              | Pourquoi ce choix ?                                                  |
|-------------------|-------------------|----------------------------------------------------------------------|
| Classe abstraite  | `Entity`          | Empêche d'instancier une entité générique ; force Player et Monster à implémenter `display()` |
| Méthode virtuelle pure | `Entity::display()` | Le `= 0` oblige chaque classe fille à la redéfinir |
| Héritage          | `Player`, `Monster` | Évite de dupliquer name/hp/hpMax dans les deux classes |
| `override`        | `Player::display()`, `Monster::display()` | Le compilateur vérifie qu'on redéfinit bien une méthode virtuelle |
| Composition       | `Player` possède `vector<Item>` | Un joueur *a* des items, il n'*est pas* un item |
| Passage par `&`   | `runCombat`, `useOn`, `attack` | Modifie l'objet original sans copie inutile |
| Passage par valeur | `Monster` dans `runCombat` | Chaque combat repart d'un monstre frais |
| `enum Category`   | `Monster.h`       | Plus lisible et sûr que des entiers (0, 1, 2) |
| `FileLoader` séparé | `FileLoader.h/.cpp` | Séparation des responsabilités : le jeu ne sait pas comment lire les CSV |
