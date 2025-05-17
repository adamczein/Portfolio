from abc import abstractmethod, ABC
from typing import List, Tuple

from accessoire import Accessoire, TypeAccessoire
from elements_tiktok import ElementViral


# TODO Je suis abstraite et j'hérite de ElementViral
class Animal(ElementViral,ABC):

    # TODO Implantez mon constructeur
    def __init__(self, nom : str, nb_pattes : int) -> None:
        self.nom = nom
        self.nb_pattes = nb_pattes
        self.liste_accessoires = []

    def __add__(self, accessoire: Accessoire) -> int:
        # TODO Retournez le score viral de l'animal plus celui de l'accessoire
        return int(Animal.score_viral(self) + Accessoire.score_viral(accessoire))



    def __iadd__(self, accessoire: Accessoire) -> 'Animal':
        # TODO Ajoutez l'accessoire à la liste de l'animal. Retournez l'animal en question
        #  Attention! Un animal n'ayant aucune patte ne peut enfiler des chaussures
        if  self.nb_pattes == 0 and accessoire.type_accessoire == TypeAccessoire.CHAUSSURES:
            print("Vous ne pouvez pas mettre de chaussures à un animal sans pieds")
            return self

        else :

            self.liste_accessoires.append(accessoire)
            return self



    @abstractmethod
    def crier(self) -> str:
        # TODO Rendez-moi abstraite
        pass

    def score_viral(self) -> int:
        # TODO Retournez la somme du score viral des accessoires présents dans la liste d'accessoires de l'animal
        somme_score_viral = 0
        for accessoire in self.liste_accessoires:
            somme_score_viral += int(accessoire.score_viral())

        return somme_score_viral



def calcul_meilleur_animal(animaux: List[Animal]) -> Tuple[str, int]:
    # TODO Retournez le nom et le score viral de l'animal ayant le score le plus haut
        meilleur_score = -1
        nom = ""
        for animal in animaux:
            score_animal = animal.score_viral()
            if meilleur_score < score_animal:
                nom = animal.nom
                meilleur_score = score_animal

        return nom, meilleur_score

