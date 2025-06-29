#include <string>
#include <vector>

class Date {
    private:
        int annee, mois, jour;

        bool estBissextile(int) const;
        int JoursEnMois(int, int) const;
        bool estValide(int, int, int) const;
    public:
        Date();
        Date(int, int, int);

        void operator+=(int);
        bool operator==(const Date&) const;
        friend std::ostream& operator<<(std::ostream&, const Date&);

        bool operator<(const Date&) const;
};

const Date operator+(Date d, int nb);

class Personne {
    protected:
        std::string nom;

        bool estValide(const std::string &) const;
    public:
        Personne();
        Personne(const std::string&);

        bool operator==(const Personne&) const;

        std::string getNom() const;
};

class Professeur : public Personne {
    private:
        std::string specialisation;
        int xp_en_annees;

        bool estValide(const std::string&, const std::string&, int) const;
    public:
        Professeur();
        Professeur(const std::string&, const std::string&, int);

        friend std::ostream& operator<<(std::ostream&, const Professeur&);

        int getXp() const;
};

class Cours {
    private:
        std::string nom;
        Professeur enseignant;
        std::vector<Personne> etudiants;
        Date debut;

        bool estValide(const std::string&) const;
    public:
        Cours(const std::string&, const Professeur&, const Date&);

        bool operator==(const Cours&) const;
        void ajouterEtudiant(const Personne&);
        void afficherEtudiant() const;
        friend std::ostream& operator<<(std::ostream&, const Cours&);
        bool profEstAssigne(const Professeur&) const;
        bool profEstDisponible(const Date&);


        std::string getNom() const;
        int getNbEtudiants() const;
        std::vector<Personne> getEtudiants() const;
};

class Ecole {
    private:
        std::string nom;
        std::vector<Cours> cours;
        std::vector<Professeur> professeurs;
    public:
        Ecole(const std::string&);

        void ajouterCours(const Cours&);
        void ajouterProfesseur(const Professeur&);
        void afficherCoursEtProfesseurs() const;
        int nbTotalEtudiants() const;
        void supprimerCours(const std::string&);
        friend std::ostream& operator<<(std::ostream&, const Ecole&);
        void afficherProfesseur10xp() const;
        Cours coursAvecPlusEtudiants() const;
};