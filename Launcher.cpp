#include "Launcher.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Launcher::Launcher() {
    joueur = NULL;
}

Launcher::~Launcher() {
    if (joueur != NULL) {
        delete joueur;
    }
}

void Launcher::lancerJeu() {
    srand(time(NULL));
    initialiser();
    menuPrincipal();
    afficherFin();
}

void Launcher::initialiser() {
    construireCatalogue(actions);

    std::string nomJoueur;
    std::cout << "=== ALTERDUNE ===" << std::endl;
    std::cout << "Nom du personnage : ";
    std::cin >> nomJoueur;

    joueur = new Player(nomJoueur, 100);

    chargerFichiers();

    for (int i = 0; i < (int)items.size(); i++) {
        joueur->ajouterItem(items[i]);
    }

    afficherResumeDebut();
}

void Launcher::chargerFichiers() {
    items = CsvLoader::lireItems("items.csv");
    monstres = CsvLoader::lireMonsters("monsters.csv", actions);
}

void Launcher::afficherResumeDebut() {
    std::cout << "\n--- Bienvenue, " << joueur->getNom() << " ---" << std::endl;
    joueur->afficher();
    joueur->afficherInventaire();
}

void Launcher::menuPrincipal() {
    while (joueur->estVivant() && joueur->getVictoires() < 10) {
        std::cout << "\n==============================" << std::endl;
        std::cout << "      ALTERDUNE - Menu" << std::endl;
        std::cout << "  Victoires : " << joueur->getVictoires() << "/10" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "  [1] Bestiaire" << std::endl;
        std::cout << "  [2] Combattre" << std::endl;
        std::cout << "  [3] Stats" << std::endl;
        std::cout << "  [4] Items" << std::endl;
        std::cout << "  [5] Quitter" << std::endl;
        std::cout << "  Choix : ";

        int choix;
        std::cin >> choix;

        if (choix == 1) {
            std::cout << "\n=== Bestiaire ===" << std::endl;
            if (bestiaire.size() == 0) {
                std::cout << "Aucun monstre vaincu pour l'instant." << std::endl;
            }

            for (int i = 0; i < (int)bestiaire.size(); i++) {
                std::cout << i + 1 << ". " << bestiaire[i].getNom()
                          << " [" << bestiaire[i].categorieEnTexte() << "]"
                          << " HP max : " << bestiaire[i].getHpMax();

                if (bestiaire[i].getEpargne()) {
                    std::cout << " - Epargne";
                } else {
                    std::cout << " - Tue";
                }

                std::cout << std::endl;
            }
        }
        else if (choix == 2) {
            if (monstres.size() == 0) {
                std::cout << "Aucun monstre disponible." << std::endl;
            } else {
                int index = rand() % monstres.size();
                Monster adversaire = monstres[index];

                bool gagne = combat(adversaire);

                if (gagne) {
                    bestiaire.push_back(adversaire);
                } else {
                    if (!joueur->estVivant()) {
                        std::cout << "Game Over." << std::endl;
                        return;
                    }
                }
            }
        }
        else if (choix == 3) {
            joueur->afficherStats();
        }
        else if (choix == 4) {
            joueur->afficherInventaire();
            std::cout << "Utiliser un item ? (numero, 0 pour annuler) : ";
            int choixItem;
            std::cin >> choixItem;

            if (choixItem != 0) {
                joueur->utiliserItem(choixItem - 1);
            }
        }
        else if (choix == 5) {
            std::cout << "Au revoir !" << std::endl;
            return;
        }
        else {
            std::cout << "Choix invalide." << std::endl;
        }
    }
}

bool Launcher::combat(Monster& monstre) {
    std::cout << "\n============================" << std::endl;
    std::cout << "COMBAT : " << joueur->getNom() << " vs " << monstre.getNom() << std::endl;
    std::cout << "============================" << std::endl;

    while (joueur->estVivant() && monstre.estVivant()) {
        std::cout << "\n" << joueur->getNom() << " : " << joueur->getHp()
                  << "/" << joueur->getHpMax() << " HP" << std::endl;

        std::cout << monstre.getNom() << " : " << monstre.getHp()
                  << "/" << monstre.getHpMax() << " HP" << std::endl;

        std::cout << "Mercy : " << monstre.getMercy()
                  << "/" << monstre.getObjectifMercy() << std::endl;

        std::cout << "\n[1] FIGHT   [2] ACT   [3] ITEM   [4] MERCY" << std::endl;
        std::cout << "Choix : ";

        int choix;
        std::cin >> choix;

        bool joueurAgit = true;

        if (choix == 1) {
            int degats = rand() % (monstre.getHpMax() + 1);
            monstre.prendreDegats(degats);

            if (degats == 0) {
                std::cout << "Vous attaquez mais ratez !" << std::endl;
            } else {
                std::cout << "Vous infligez " << degats << " degats a "
                          << monstre.getNom() << " !" << std::endl;
            }

            if (!monstre.estVivant()) {
                std::cout << monstre.getNom() << " est vaincu !" << std::endl;
                monstre.setTue(true);
                monstre.setEpargne(false);
                joueur->ajouterVictoire(true);
                return true;
            }
        }
        else if (choix == 2) {
            std::vector<std::string> acts = monstre.getActionsDispo();

            std::cout << "\nActions disponibles :" << std::endl;
            for (int i = 0; i < (int)acts.size(); i++) {
                const Action* a = trouverAction(actions, acts[i]);
                if (a != NULL) {
                    std::cout << "[" << i + 1 << "] " << a->getId() << std::endl;
                }
            }

            std::cout << "Choix : ";
            int choixAct;
            std::cin >> choixAct;

            if (choixAct >= 1 && choixAct <= (int)acts.size()) {
                const Action* a = trouverAction(actions, acts[choixAct - 1]);
                if (a != NULL) {
                    std::cout << a->getTexte() << std::endl;
                    monstre.ajouterMercy(a->getImpact());
                    std::cout << "Mercy : " << monstre.getMercy()
                              << "/" << monstre.getObjectifMercy() << std::endl;
                }
            } else {
                std::cout << "Choix invalide." << std::endl;
                joueurAgit = false;
            }
        }
        else if (choix == 3) {
            joueur->afficherInventaire();

            if (joueur->getNbItems() == 0) {
                std::cout << "Inventaire vide !" << std::endl;
                joueurAgit = false;
            } else {
                std::cout << "Quel item utiliser ? (0 pour annuler) : ";
                int choixItem;
                std::cin >> choixItem;

                if (choixItem == 0) {
                    joueurAgit = false;
                } else {
                    bool ok = joueur->utiliserItem(choixItem - 1);
                    if (!ok) {
                        joueurAgit = false;
                    }
                }
            }
        }
        else if (choix == 4) {
            if (monstre.mercyEstPlein()) {
                std::cout << monstre.getNom() << " est epargne !" << std::endl;
                monstre.setTue(false);
                monstre.setEpargne(true);
                joueur->ajouterVictoire(false);
                return true;
            } else {
                std::cout << "Mercy insuffisant." << std::endl;
                joueurAgit = false;
            }
        }
        else {
            std::cout << "Choix invalide." << std::endl;
            joueurAgit = false;
        }

        if (joueurAgit && monstre.estVivant()) {
            monstre.attaquer(*joueur);

            if (!joueur->estVivant()) {
                std::cout << "\nDEFAITE ! Vous avez ete vaincu..." << std::endl;
                return false;
            }
        }
    }

    return false;
}

void Launcher::afficherFin() {
    if (joueur->getVictoires() >= 10) {
        std::cout << "\n============================" << std::endl;
        std::cout << "10 victoires atteintes !" << std::endl;
        std::cout << "FIN : " << joueur->getTypeFin() << std::endl;
        std::cout << "============================" << std::endl;
    }
}

