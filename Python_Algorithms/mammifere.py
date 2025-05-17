from abc import ABC, abstractmethod
from enum import Enum
from typing import List

from animal import Animal


class LongueurPoils(Enum):
    RASES = 0
    COURTS = 1
    LONGS = 2

    def __str__(self):
        return self.name


# TODO Je suis abstraite et j'hérite de Animal
class Mammifere(Animal,ABC):
    # TODO Implantez mon constructeur
    #  def __init__(self, ...) -> None:
    def __init__(self,nom : str, nb_pattes : int, longueur_poils : LongueurPoils):
        self.nom = nom
        self.nb_pattes = nb_pattes
        self.longueur_poils = longueur_poils
        self.liste_accessoires = []



    def __str__(self) -> str:
        # TODO Je dois retournez une chaine de caractère semblable à :
        #  Le TYPE_MAMMIFERE NOM_MAMMIFERE a NB_PATTES pattes et des poils LONGUEUR_POILS.
        return "Le " + type(self).__name__ +" " + str(self.nom) + " a " + str(self.nb_pattes)+ " pattes et des poils " + str(self.longueur_poils) + "."
        pass


# TODO J'hérite de Mammifere
class Chat(Mammifere):

    # TODO Implantez mon constructeur
    #  def __init__(self, ...) -> None:
    def __init__(self, nom, longueur_poils, couleur: str ,nb_pattes = 4):

        Mammifere.__init__(self, nom, nb_pattes, longueur_poils)
        self.couleur = couleur

    def crier(self) -> str:
        # TODO Retournez le cri du chat: Miaou
        return "Miaou"
