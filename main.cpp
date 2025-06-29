#include "gestion_cours.cpp"
#include <thread>
#include <chrono>

void SysClear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

namespace Choix {
    void Vide(std::string donnee) {
        SysClear();
        std::cout << "\033[33mAucun "<< donnee << " enregistre.\033[0m" << std::endl;
        std::cout << "Le programme va retourner au menu precedent dans 5 secondes...";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    void Invalide() {
        std::cout << " \033[31mErreur:\033[0m Choix invalide!";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void Retourner() {
        char retourner_choix;
        std::cout << "Voulez-vous retourner maintenant au menu precedent ? (Y/n): " << std::endl;
        std::cout << std::string(4, ' ') << "- Y ou y entraine un retour automatique au menu precedent." << std::endl;
        std::cout << std::string(4, ' ') << "- un autre caractere entraine un retour retarde au menu precedent par 10 secondes." << std::endl;
        std::cout << std::string(4, ' ') << "- Si vous souhaitez rester ici, n'entrez rien!" << std::endl;
        std::cin >> retourner_choix;
        if (retourner_choix != 'Y' && retourner_choix != 'y') std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    void Ressayer(bool& estValide, const std::exception& e) {
        std::cerr << std::endl << " \033[31mErreur:\033[0m " << e.what() << std::endl;

        char ReessayerChoix;
        std::cout << "Voulez-vous reessayer ? (Y/n): ";
        std::cin >> ReessayerChoix;
        if (ReessayerChoix != 'Y' && ReessayerChoix != 'y') estValide = true;
    }
}

void MenuEnseignants(std::vector<Professeur>& p) {
    int continueChoix;
    do {
        SysClear();
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "|                  Menu Enseignants                  |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "| 1. Ajouter un enseignant                           |" << std::endl;
        std::cout << "| 2. Afficher les informations                       |" << std::endl;
        std::cout << "|\033[34m 3. Retour au Menu Principal\033[0m                        |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;

        std::cout << std::endl << "+----------------------------------------------------+" << std::endl;

        std::cout << "Choisir une option: [1, 2, 3]" << std::endl;
        std::cout << "*----------------------------------------------------*" << std::endl;

        std::cin >> continueChoix;

        switch (continueChoix) {
        case 1: {
            bool estValide = false;
            while(!estValide) {
                SysClear();
                std::string nom, specialisation;
                int xp;
                std::cout << "Entrez le nom de l'enseignant: ";
                std::cin.ignore(); // Ignore le retour à la ligne après une entree precedente
                std::getline(std::cin, nom);
                std::cout << "Entrez le nombre d'experience en annees: ";
                std::cin >> xp;
                std::cout << "Entrez la specialisation: ";
                std::cin.ignore(); // Ignore le retour à la ligne après une entree precedente
                std::getline(std::cin, specialisation);
                try {
                    Professeur nouveau_prof(nom, specialisation, xp);

                    p.push_back(nouveau_prof);
                    std::cout << std::endl << " \033[32mProfesseur ajoute avec succès!\033[0m";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    estValide = true;
                } catch (const std::exception& e) {
                    Choix::Ressayer(estValide, e);
                }
            }
            break;
        }
        case 2: {
            SysClear();
            if (p.empty()) {
                Choix::Vide("Enseignant");
            } else {
                std::cout << "Liste des enseignants:" << std::endl;
                for (size_t i = 0; i < p.size(); i++) {
                    std::cout << i + 1 << "." << std::endl << p[i] << std::endl;
                }
                Choix::Retourner();  
            }
            break;
        }
        case 3:
            return;
        default:
            Choix::Invalide();
        }
    } while (continueChoix != 3);
}

void MenuEtudiants(std::vector<Personne>& etu) {
    int continueChoix;
    do {
        SysClear();
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "|                   Menu Etudiants                   |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "| 1. Ajouter un etudiant                             |" << std::endl;
        std::cout << "| 2. Afficher les informations                       |" << std::endl;
        std::cout << "|\033[34m 3. Retour au Menu Principal\033[0m                        |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;

        std::cout << std::endl << "+----------------------------------------------------+" << std::endl;

        std::cout << "Choisir une option: [1, 2, 3]" << std::endl;
        std::cout << "*----------------------------------------------------*" << std::endl;

        std::cin >> continueChoix;

        switch (continueChoix) {
        case 1: {
            bool estValide = false;
            while(!estValide) {
                SysClear();
                std::string nom;
                std::cout << "Entrez le nom de l'etudiant: ";
                std::cin.ignore(); // Ignore le retour à la ligne après une entree precedente
                std::getline(std::cin, nom);
                try {
                    Personne nouveau_etu(nom);

                    etu.push_back(nouveau_etu);
                    std::cout << std::endl << " \033[32mEtudiant ajoute avec succès!\033[0m";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    estValide = true;
                } catch (const std::exception& e) {
                    Choix::Ressayer(estValide, e);
                }
            }
            break;
        }
        case 2: {
            SysClear();
            if (etu.empty()) {
                Choix::Vide("Etudiant");
            } else {
                std::cout << "Liste des etudiants:" << std::endl;
                for (size_t i = 0; i < etu.size(); i++) {
                    std::cout << std::string(4, ' ') << i + 1 << ". "<< etu[i].getNom() << std::endl;
                }
                Choix::Retourner();
            }
            break;
        }
        case 3:
            return;
        default:
            Choix::Invalide();
        }
    } while(continueChoix != 3);
}

void MenuCours(std::vector<Cours>& c, std::vector<Personne>& etu, std::vector<Professeur>& p) {
    int continueChoix;
    do {
        SysClear();
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "|                     Menu Cours                     |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "| 1. Creer un cours                                  |" << std::endl;
        std::cout << "| 2. Ajouter les etudiants                           |" << std::endl;
        std::cout << "| 3. Afficher les cours                              |" << std::endl;
        std::cout << "| 4. Verifier l'assignation d'un prof a un cours     |" << std::endl;
        std::cout << "| 5. Verifier la disponibilite d'un prof a une date  |" << std::endl;
        std::cout << "|\033[34m 6. Retour au Menu Principal\033[0m                        |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;

        std::cout << std::endl << "+----------------------------------------------------+" << std::endl;

        std::cout << "Choisir une option: [1, 2, 3, 4, 5, 6]" << std::endl;
        std::cout << "*----------------------------------------------------*" << std::endl;

        std::cin >> continueChoix;
        switch (continueChoix) {
        case 1: {
            if(p.empty()) {
                Choix::Vide("Enseignant");
                break;
            }
            bool estValide = false;
            while(!estValide) {
                SysClear();
                std::string nom;
                int professeur_index, m, d, y;
                std::cout << "Entrez le nom du cours: ";
                std::cin.ignore(); // Ignore le retour à la ligne après une entree precedente
                std::getline(std::cin, nom);

                std::cout << "Choisir l'enseignant à assigner à ce cours: " << std::endl;
                for (size_t i = 0; i < p.size(); i++) {
                    std::cout << std::string(4, ' ') << i + 1 << ". " << p[i].getNom() << std::endl;
                }
                do {
                    std::cin >> professeur_index;
                    if (professeur_index < 1 || professeur_index > p.size()) {
                        std::cout << " \033[31mErreur:\033[0m Indice invalide, veuillez choisir un numero valide entre 1 et " << p.size() << "." << std::endl;
                    }
                } while (professeur_index < 1 || professeur_index > p.size());

                std::cout << "Entrez la date du debut du cours:" << std::endl;
                std::cout << std::string(4, ' ') << "- Entrez le jour:" << std::endl;
                std::cin >> d;
                std::cout << std::string(4, ' ') << "- Entrez le mois:" << std::endl;
                std::cin >> m;
                std::cout << std::string(4, ' ') << "- Entrez l'annee:" << std::endl;
                std::cin >> y;

                try {
                    Date nouveau_date(y, m, d);
                    std::cout << std::endl << " \033[32mDate cree avec succès!\033[0m";

                    Cours nouveau_cours(nom, p[professeur_index - 1], nouveau_date);

                    c.push_back(nouveau_cours);
                    std::cout << std::endl << " \033[32mCours ajoute avec succès!\033[0m";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    estValide = true;
                }
                catch(const std::exception& e) {
                    Choix::Ressayer(estValide, e);
                }
            }
            break;
        }
        case 2: {
            if(etu.empty()) {
                Choix::Vide("Etudiant");
                break;
            }
            bool estValide = false;
            while(!estValide) {
                SysClear();
                int cours_index, etudiant_index;
                std::cout << "Choisir le cours dont vous allez ajouter des etudiants:" << std::endl;
                for (size_t i = 0; i < c.size(); i++) {
                    std::cout << std::string(4, ' ') << i + 1 << ". " << c[i].getNom() << std::endl;
                }
                do {
                    std::cin >> cours_index;
                    if (cours_index < 1 || cours_index > p.size()) {
                        std::cout << " \033[31mErreur:\033[0m Indice invalide, veuillez choisir un numero valide entre 1 et " << p.size() << "." << std::endl;
                    }
                } while (cours_index < 1 || cours_index > p.size());

                std::cout << "Choisir les etudiants a ajouter au cours:" << std::endl;
                for (size_t i = 0; i < etu.size(); i++) {
                    std::cout << std::string(4, ' ') << i + 1 << ". " << etu[i].getNom() << std::endl;
                }
                std::cout << std::endl << " \033[33mEntrez 0 si vous voulez ajouter tous les etudiants a ce cours.\033[0m" << std::endl;
                do {
                    std::cin >> etudiant_index;
                    if (etudiant_index < 0 || cours_index > p.size()) {
                        std::cout << " \033[31mErreur:\033[0m Indice invalide, veuillez choisir un numero valide entre 0 et " << p.size() << "." << std::endl;
                    }    
                } while (etudiant_index < 0 || etudiant_index > p.size());

                try {
                    if(etudiant_index == 0) {
                        for (size_t i = 0; i < etu.size(); i++) {
                            c[cours_index - 1].ajouterEtudiant(etu[i]);
                        }
                        std::cout << std::endl << " \033[32mTous les Etudiants sont ajoutes au cours avec succes!\033[0m";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    } else {
                            c[cours_index - 1].ajouterEtudiant(etu[etudiant_index - 1]);
                            std::cout << std::endl << " \033[32mEtudiant ajoute au cours avec succes!\033[0m";
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                    estValide = true;
                } catch(const std::exception& e) {
                    Choix::Ressayer(estValide, e);
                }
            }
            break;
        }
        case 3: {
            SysClear();
            if (c.empty()) {
                Choix::Vide("Cours");
            } else {
                std::cout << "Liste des cours:" << std::endl;
                for (size_t i = 0; i < c.size(); i++) {
                    std::cout << i + 1 << "." << std::endl << c[i] << std::endl;
                }
                Choix::Retourner();  
            }
            break;
        }
        case 4: {
            SysClear();
            if (p.empty()) {
                Choix::Vide("Enseignant");
            } else if (c.empty()) {
                Choix::Vide("Cours");
            } else {
                int cours_index, professeur_index;
                std::cout << "Choisir le cours:" << std::endl;
                for (size_t i = 0; i < c.size(); i++) {
                    std::cout << std::string(4, ' ') << i + 1 << ". "<< c[i].getNom() << std::endl;
                }

                do {
                    std::cin >> cours_index;
                    if (cours_index < 1 || cours_index > p.size()) {
                        std::cout << " \033[31mErreur:\033[0m Indice invalide, veuillez choisir un numero valide entre 1 et " << p.size() << "." << std::endl;
                    }
                } while (cours_index < 1 || cours_index > p.size());

                std::cout << "Choisir le professeur:" << std::endl;
                for (size_t i = 0; i < p.size(); i++) {
                    std::cout << std::string(4, ' ') << i + 1 << ". "<< p[i].getNom() << std::endl;
                }

                do {
                    std::cin >> professeur_index;
                    if (professeur_index < 1 || professeur_index > p.size()) {
                        std::cout << " \033[31mErreur:\033[0m Indice invalide, veuillez choisir un numero valide entre 1 et " << p.size() << "." << std::endl;
                    }
                } while (professeur_index < 1 || professeur_index > p.size());

                if(c[cours_index - 1].profEstAssigne(p[professeur_index - 1])) {
                    std::cout << " \033[32mLe professeur est bien assigne a ce cours!\033[0m";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                } else {
                    std::cout << " \033[33mLe professeur n'est pas assigne a ce cours!\033[0m";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            }
            break;
        }
        case 5: {
            if (p.empty()) {
                Choix::Vide("Enseignant");
            } else if (c.empty()) {
                Choix::Vide("Cours");
            } else {
                bool estValide = false;
                while(!estValide) {
                    SysClear();
                    std::cout << " \033[33mA noter\033[0m : Ce programme verifie la disponibilite d'un professeur pour un cours" << std::endl
                        << std::string(4,  ' ') << "en prenant sa date de debut donnee et l'incremente par 7" << std::endl;
                    std::cout << " !!! Les jours feries ne sont pas prises en compte comme exception" << std::endl;

                    int cours_index;
                    std::cout << "Choisir le cours:" << std::endl;
                    for (size_t i = 0; i < c.size(); i++) {
                        std::cout << std::string(4, ' ') << i + 1 << ". "<< c[i].getNom() << std::endl;
                    }

                    do {
                        std::cin >> cours_index;
                        if (cours_index < 1 || cours_index > p.size()) {
                            std::cout << " \033[31mErreur:\033[0m Indice invalide, veuillez choisir un numero valide entre 1 et " << p.size() << "." << std::endl;
                        }
                    } while (cours_index < 1 || cours_index > p.size());

                    int y, m, d;
                    std::cout << "Entrez la date:" << std::endl;
                    std::cout << std::string(4, ' ') << "- Entrez le jour:" << std::endl;
                    std::cin >> d;
                    std::cout << std::string(4, ' ') << "- Entrez le mois:" << std::endl;
                    std::cin >> m;
                    std::cout << std::string(4, ' ') << "- Entrez l'annee:" << std::endl;
                    std::cin >> y;

                    try {
                        Date nouveau_date(y, m, d);
                        std::cout << std::endl << " \033[32mDate cree avec succès!\033[0m";

                        if(c[cours_index - 1].profEstDisponible(nouveau_date)) {
                            std::cout << std::endl << " \033[32mLe professeur est disponible pour enseigner ce cours a cette date!\033[0m";
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        } else {
                            std::cout << std::endl << " \033[33mLe professeur n'est pas disponible pour enseigner ce cours a cette date!\033[0m";
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        }
                        estValide = true;
                    }
                    catch(const std::exception& e) {
                        Choix::Ressayer(estValide, e);
                    }
                }
            }
            break;
        }
        case 6:
            return;
        default:
            Choix::Invalide();
        }
    } while (continueChoix != 6);
}

void MenuEcole(Ecole& e, std::vector<Cours>& c, std::vector<Personne>& etu, std::vector<Professeur>& p) {
    int continueChoix;
    do {
        SysClear();
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "|                     Menu Ecole                     |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "| 1. Transferer les Cours                            |" << std::endl;
        std::cout << "| 2. Transferer les Enseignants                      |" << std::endl;
        std::cout << "| 3. Afficher les informations                       |" << std::endl;
        std::cout << "| 4. Afficher le nombre total des etudiants          |" << std::endl;
        std::cout << "| 5. Supprimer un Cours                              |" << std::endl;
        std::cout << "| 6. Afficher les Enseignants avec 10 annees xp      |" << std::endl;
        std::cout << "| 7. Afficher le cours avec le plus d'Etudiants      |" << std::endl;
        std::cout << "|\033[34m 8. Retour au Menu Principal\033[0m                        |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;

        std::cout << std::endl << "+----------------------------------------------------+" << std::endl;

        std::cout << "Choisir une option: [1, 2, 3, 4, 5, 6, 7, 8]" << std::endl;
        std::cout << "*----------------------------------------------------*" << std::endl;

        std::cin >> continueChoix;
        switch (continueChoix) {
        case 1: {
            if (c.empty()) {
                Choix::Vide("Cours");
            } else {
                SysClear();
                try {
                    for (size_t i = 0; i < c.size(); i++) {
                    e.ajouterCours(c[i]);
                    }
                    c.clear();
                    std::cout << std::endl << " \033[32mTous les Cours enregistrees sont transferees a l'ecole avec succes!\033[0m";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
            }
            break;
        }
        case 2: {
            if (p.empty()) {
                Choix::Vide("Enseignants");
            } else {
                SysClear();
                try {
                    for (size_t i = 0; i < p.size(); i++) {
                        e.ajouterProfesseur(p[i]);
                    }
                    p.clear();
                    std::cout << std::endl << " \033[32mTous les Enseignants enregistrees sont transferees a l'ecole avec succes!\033[0m";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
            }
            break;
        }
        case 3: {
            SysClear();
            std::cout << e;
            Choix::Retourner();
            break;
        }
        case 4: {
            SysClear();
            std::cout << "Le nombre total des etudiants de l'ecole est: \033[32m" << e.nbTotalEtudiants() << "\033[0m" << std::endl;
            Choix::Retourner();
            break;
        }
        case 5: {
            SysClear();
            std::string nom;
            std::cout << std::endl << "Entrez le nom du cours: ";
            std::cin.ignore(); // Ignore le retour à la ligne après une entree precedente
            std::getline(std::cin, nom);
            e.supprimerCours(nom);
            Choix::Retourner();
            break;
        }
        case 6: {
            SysClear();
            std::cout << "Les Enseignants avec 10 annees d'expérience:" << std::endl;
            e.afficherProfesseur10xp();
            Choix::Retourner();

            break;
        }
        case 7: {
            SysClear();
            try {
                std::string nom = e.coursAvecPlusEtudiants().getNom();
                std::cout << "Le nom est: " << nom << std::endl;
                Choix::Retourner();
            } catch(const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }       
            break;
        }
        case 8:
            return;
        default:
            Choix::Invalide();
        }
    } while(continueChoix != 8);

}

void MenuPrincipal(Ecole& e, std::vector<Cours>& c, std::vector<Personne>& etu, std::vector<Professeur>& p) {
    int continueChoix;
    do {
        SysClear();
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "|                   Menu Principal                   |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;
        std::cout << "| 1. Gestion des Enseignants                         |" << std::endl;
        std::cout << "| 2. Gestion des Etudiants                           |" << std::endl;
        std::cout << "| 3. Gestion des Cours                               |" << std::endl;
        std::cout << "| 4. Gestion de l'Ecole                              |" << std::endl;
        std::cout << "|\033[1;31m 5. Quitter\033[0m                                         |" << std::endl;
        std::cout << "+----------------------------------------------------+" << std::endl;

        std::cout << std::endl << "+----------------------------------------------------+" << std::endl;

        std::cout << "Choisir une option: [1, 2, 3, 4, 5]" << std::endl;
        std::cout << "*----------------------------------------------------*" << std::endl;

        std::cin >> continueChoix;
        switch (continueChoix) {
        case 1:
            MenuEnseignants(p);
            break;
        case 2:
            MenuEtudiants(etu);
            break;
        case 3:
            MenuCours(c, etu, p);
            break;
        case 4:
            MenuEcole(e, c, etu, p);
            break;
        case 5:
            exit;
            break;
        default:
            Choix::Invalide();
        }
    } while (continueChoix != 5);
    
}

void Bienvenue() {
    Ecole etablissement("Ecole");
    std::vector<Cours> cours;
    std::vector<Personne> etudiants;
    std::vector<Professeur> professeurs;
    std::cout << std::string(32, ' ') << "\033[34m\033[1m"  << "Bienvenue dans le Programme de..." << "\033[0m" << std::endl;
    std::cout << std::string(8, ' ') << "  _____           _   _                   _" << std::endl;
    std::cout << std::string(8, ' ') << " / ____|         | | (_)                 | |" << std::endl;
    std::cout << std::string(8, ' ') << "| |  __  ___  ___| |_ _  ___  _ __     __| |" << std::endl;
    std::cout << std::string(8, ' ') << "| | |_ |/ _ \\/ __| __| |/ _ \\| '_ \\   / _` |/ _ \\/ __|  / __/ _ \\| | | | '__/ __|" << std::endl;
    std::cout << std::string(8, ' ') << "| |__| |  __/\\__ \\ |_| | (_) | | | | | (_| |  __/\\__ \\ | (_| (_) | |_| | |  \\__ \\" << std::endl;
    std::cout << std::string(8, ' ') << " \\_____|\\___||___/\\__|_|\\___/|_| |_|  \\__,_|\\___||___/  \\___\\___/ \\__,_|_|  |___/" << std::endl;
    std::cout << std::endl << std::string(40, ' ') << "\033[32m\033[1m" << "pour votre ecole!" << "\033[0m" << std::endl;
    std::cout << std::string(6, ' ') << "*" << std::string(83, '-') << "*" << std::endl;
    std::cout << std::string(8, ' ') << "Realisee par:" << std::endl;
    std::cout << std::string(10, ' ') << "+" << std::string(2, ' ') << "T. Adam" << std::endl;
    std::cout << std::string(6, ' ') << "*" << std::string(83, '-') << "*" << std::endl;

    char continueChoix;
    std::cout << std::endl << "Souhaitez-vous continuer? (Y/n): ";
    std::cin >> continueChoix;

    if (continueChoix == 'Y' || continueChoix == 'y') {
        MenuPrincipal(etablissement, cours, etudiants, professeurs);
    } else {
        std::cout << "Merci et à bientôt!";
    }
}

int main(void) {
    Bienvenue();
   
    return 0;
}