#include "gestion_cours.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

bool Date::estBissextile(int annee) const {
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

int Date::JoursEnMois(int annee, int mois) const {
    switch (mois) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return estBissextile(annee) ? 29 : 28;
        default:
            return 0;
    }
}

bool Date::estValide(int annee, int mois, int jour) const {
    if (jour <= 0) throw std::invalid_argument("Les jours ne sont pas nuls ou négatifs.");
    if (mois <= 0) throw std::invalid_argument("Les mois ne sont pas nuls ou négatifs.");
    if (annee <= 0) throw std::invalid_argument("Les années ne sont pas nulles ou négatives.");

    if (mois < 1 || mois > 12) throw std::invalid_argument("Les mois doivent être compris entre 1 et 12.");

    int JoursMax = JoursEnMois(annee, mois);
    if (jour > JoursMax) {
        throw std::invalid_argument("Le jour " + std::to_string(jour) + " est hors de portée pour le mois donné " + std::to_string(mois) + ".");
    }

    return true;
}

Date::Date() {
    std::time_t timestamp = std::time(NULL);
    struct std::tm datetime = *localtime(&timestamp);

    annee = datetime.tm_year;
    mois = datetime.tm_mon;
    jour = datetime.tm_mday;
}

Date::Date(int y, int m, int d) { 
    if (!estValide(y, m, d));
    annee = y; mois = m; jour = d;
}

void Date::operator+=(int nb) {
    jour += nb;

    while (jour > JoursEnMois(annee, mois)) {
        jour -= JoursEnMois(annee, mois);
        mois++;
        if (mois == 13) {
            mois = 1;
            annee++;
        }
    }
}

bool Date::operator==(const Date& autre) const {
    return (jour == autre.jour && mois == autre.mois && annee == autre.annee);
}

std::ostream& operator<<(std::ostream &os, const Date &d) {
    os << d.jour << '/' << d.mois << '/' << d.annee;
    return os;
}

bool Date::operator<(const Date &autre) const {
    if (annee < autre.annee) {
        return true;
    } else if (annee == autre.annee) {
        if (mois < autre.mois) {
            return true;
        } else if (mois == autre.mois) {
            return jour < autre.jour;
        }
    }
    return false;
}

const Date operator+(Date d, int nb) {
    d += nb;
    return d;
}

bool Personne::estValide(const std::string &n) const {
    if (n.empty()) throw std::invalid_argument("Le nom de la personne est vide.");

    return true;
}

Personne::Personne() { nom = "Inconnu"; }

Personne::Personne(const std::string& n) {
    if (!estValide(n));
    nom = n;
}

bool Personne::operator==(const Personne& autre) const {
    return (nom == autre.nom);
}

std::string Personne::getNom() const { return nom; }

bool Professeur::estValide(const std::string &n, const std::string &sp, int xp) const {
    if (!Personne::estValide(n));
    if (sp.empty()) throw std::invalid_argument("La spécialisation du professeur est vide.");
    if (xp < 0) throw std::invalid_argument("L'expérience en années ne peut pas être négative.");

    return true;
}

Professeur::Professeur() {
    specialisation = "Inconnu";
    xp_en_annees = 0;
}

Professeur::Professeur(const std::string& n, const std::string& sp, int xp) {
    if (!estValide(n, sp, xp));
    nom = n;
    specialisation = sp;
    xp_en_annees = xp;
}

std::ostream &operator<<(std::ostream &os, const Professeur &p) {
    os << "+-------------------------------+" << std::endl;
    os << "|        Professeur Info        |" << std::endl;
    os << "+-------------------------------+" << std::endl;
    os << "Nom: " << p.nom << std::endl;
    os << "Spécialisation: " << p.specialisation << std::endl;
    os << "Expérience en années: " << p.xp_en_annees << std::endl;
    os << "+-------------------------------+" << std::endl;
    return os;
}

int Professeur::getXp() const { return xp_en_annees; }

bool Cours::estValide(const std::string &n) const {
    if (n.empty()) throw std::invalid_argument("Le nom du cours est vide.");

    return true;
}

Cours::Cours(const std::string &n, const Professeur &p, const Date &d) : enseignant(p), debut(d) {
    if (!estValide(n));
    nom = n;
}

bool Cours::operator==(const Cours &autre) const { return (nom == autre.nom); }

void Cours::ajouterEtudiant(const Personne &etu) {
    for (const auto& etudiant_index : etudiants) {
        if(etu.getNom() == etudiant_index.getNom()) throw std::invalid_argument("L'étudiant \"" + etudiant_index.getNom() + "\" est déjà inscrit a ce cours.");
    }
    etudiants.push_back(etu);
}

void Cours::afficherEtudiant() const {
    size_t index = 1;
    for (const auto& etudiant_index : etudiants) {
        std::cout << "\t" << index << ". " << etudiant_index.getNom() << std::endl;
        index++;
    }
}

bool Cours::profEstAssigne(const Professeur &p) const { return enseignant == p; }

bool Cours::profEstDisponible(const Date &d) {
    if(!(debut < d)) throw std::invalid_argument("La date est avant le debut du cours.");
    if(!(d < debut + 365)) throw std::invalid_argument("La date est hors portee de l'annee scolaire");

    Date temp_date = debut;
    while(temp_date < d && temp_date < debut + 365) { temp_date += 7; }

    return temp_date == d;
}

std::ostream &operator<<(std::ostream &os, const Cours &c) {
    os << "+------------------------------------------------+" << std::endl;
    os << "|                   Cours Info                   |" << std::endl;
    os << "+------------------------------------------------+" << std::endl;
    os << "Nom: " << c.nom << std::endl;
    os << "Enseignant: " << c.enseignant.getNom() << std::endl;
    os << "Date de début: " << c.debut << std::endl;
    os << "Liste des étudiants:" << std::endl;
    c.afficherEtudiant();
    os << "+------------------------------------------------+" << std::endl;
    return os;
}

std::string Cours::getNom() const { return nom; }

int Cours::getNbEtudiants() const { return etudiants.size(); }

std::vector<Personne> Cours::getEtudiants() const { return etudiants; }

Ecole::Ecole(const std::string &n) : nom(n) {}

void Ecole::ajouterCours(const Cours &c) {
    for (const auto& cours_index : cours) {
        if(c.getNom() == cours_index.getNom()) throw std::invalid_argument("Le cours \"" + cours_index.getNom() + "\" existe déjà.");
    }
    cours.push_back(c);
}

void Ecole::ajouterProfesseur(const Professeur &prof) {
    for (const auto& professeur_index : professeurs) {
        if(prof == professeur_index) throw std::invalid_argument("Le professeur \"" + professeur_index.getNom() + "\" existe déjà.");
    }
    professeurs.push_back(prof);
}

void Ecole::afficherCoursEtProfesseurs() const {
    size_t index = 1;
    std::cout << "Les cours de l'école: " << std::endl;
    for (const auto& cours_index : cours) {
        std::cout << "\t" << index << "." << std::endl;
        std::cout << cours_index;
        index++;
    }
    index = 1;
    std::cout << std::endl << "Les professeurs de l'école: " << std::endl;
    for (const auto& professeur_index : professeurs) {
        std::cout << "\t" << index << ". " << professeur_index.getNom() << std::endl;
        std::cout << professeur_index;
        index++;
    }
}

int Ecole::nbTotalEtudiants() const {
    std::vector<Personne> etudiant_comptes;

    for (const auto& cours_index : cours) {
        for (const auto& etudiant : cours_index.getEtudiants()) {
        bool compte_deja = false;
            for (const auto& etudiant_compte : etudiant_comptes) {
                if (etudiant_compte == etudiant) { 
                    compte_deja = true;
                    break;
                }
            }
            
            if (!compte_deja) {
                etudiant_comptes.push_back(etudiant);
            }
        }
    }
    return etudiant_comptes.size();
}

void Ecole::supprimerCours(const std::string &n) {
    for (auto cours_iterateur = cours.begin(); cours_iterateur != cours.end(); cours_iterateur++) {
        if (cours_iterateur->getNom() == n) {
            cours.erase(cours_iterateur);
            std::cout << "Le cours \"" << n << "\" a été supprimé.\n";
            return;
        }
    }
    std::cout << "Le cours \"" << n << "\" n'existe pas.\n";
}

std::ostream &operator<<(std::ostream &os, const Ecole &e) {
    os << "+------------------------------------------------+" << std::endl;
    os << "|                   Ecole Info                   |" << std::endl;
    os << "+------------------------------------------------+" << std::endl;
    e.afficherCoursEtProfesseurs();
    os << "+------------------------------------------------+" << std::endl;
    return os;
}

void Ecole::afficherProfesseur10xp() const {
    size_t index = 1;
    for (const auto& professeur_index : professeurs) {
        if(professeur_index.getXp() == 10) {
            std::cout << "\t" << index << ". " << professeur_index.getNom() << std::endl;
            index++;
        }
    }
    if(index == 1) std::cout << " Aucun proffeseur avec exactement 10 annees d'experiences." << std::endl;
}

Cours Ecole::coursAvecPlusEtudiants() const {
    if (cours.empty()) throw std::runtime_error("Il n'y a pas de cours dans l'école.");

    const Cours* coursMax = &cours[0];

    for (const auto& c : cours) {
        if (c.getNbEtudiants() > coursMax->getNbEtudiants()) coursMax = &c;
    }

    return *coursMax;
}