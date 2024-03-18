#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Animal {
protected:
    string name;
    int age;
    string species;

public:
    Animal(const string& name, int age, const string& species)
        : name(name), age(age), species(species) {}

    string getName() const { return name; }
    int getAge() const { return age; }
    string getSpecies() const { return species; }

    void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", Species: " << species << endl;
    }
};

class AnimalNode {
public:
    Animal* animal;
    AnimalNode* next;


    AnimalNode(Animal* animal) : animal(animal), next(nullptr) {}
};

class SpeciesList {
public:
    string species;
    AnimalNode* head;


    SpeciesList(const string& species) : species(species), head(nullptr) {}


    void insertAnimal(Animal* animal) {
        AnimalNode* newNode = new AnimalNode(animal);
        newNode->next = head;
        head = newNode;
    }


    ~SpeciesList() {
        AnimalNode* current = head;
        while (current) {
            AnimalNode* next = current->next;
            delete current->animal;
            delete current;
            current = next;
        }
    }
};


void readAnimalDetails(const string& filename, vector<SpeciesList*>& speciesLists) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Unable to open " << filename << endl;
        return;
    }

    string name, species;
    int age;


    while (inputFile >> name >> age >> species) {

        Animal* newAnimal = new Animal(name, age, species);


        SpeciesList* speciesList = nullptr;
        for (auto& list : speciesLists) {
            if (list->species == species) {
                speciesList = list;
                break;
            }
        }


        if (!speciesList) {
            speciesList = new SpeciesList(species);
            speciesLists.push_back(speciesList);
        }


        speciesList->insertAnimal(newAnimal);
    }

    inputFile.close();
}

int main() {
    string inputFile = "arrivingAnimals.txt";

    vector<SpeciesList*> speciesLists;
    readAnimalDetails(inputFile, speciesLists);

    for (auto& speciesList : speciesLists) {
        cout << "Species: " << speciesList->species << endl;
        AnimalNode* current = speciesList->head;
        while (current) {
            current->animal->displayInfo();
            current = current->next;
        }
        cout << endl;
    }

    for (auto& list : speciesLists) {
        delete list;
    }

    return 0;
}
