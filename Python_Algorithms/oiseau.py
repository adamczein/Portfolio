from abc import ABC
from typing import List

from animal import Animal


# TODO Je suis abstraite et j'hérite de Animal
class Oiseau(Animal, ABC):

    # TODO Implantez mon constructeur
    #  def __init__(self, ...) -> None:
    def __init__(self, nom : str, nb_pattes : int, chante : bool):
        self.nom = nom
        self.nb_pattes = nb_pattes
        self.chante = chante
        self.liste_accessoires = []



    def __str__(self) -> str:
        # TODO Je dois retournez une chaine de caractère semblable à :
        #  Le TYPE_OISEAU NOM_OISEAU chante.
        if self.chante == True:

        #ou

            return "Le " + type(self).__name__ + " " + self.nom + " chante."
        #  Le TYPE_OISEAU NOM_OISEAU ne chante pas.
        if self.chante == False:

            return "Le " + type(self).__name__ + " " + self.nom + " ne chante pas."

        pass

    def crier(self) -> str:
        # TODO Je dois retourner "cuicui" si je ne chante pas.
        if self.chante  == False:

            return "cuicui"
        #  Sinon, retournez les deux premières phrases du refrain de September:
        #  Ba de ya, say that you remember. Ba de ya, dancing in September.

        else:
            return "Ba de ya, say that you remember. Ba de ya, dancing in September."



# TODO J'hérite de Oiseau
class Cockatiel(Oiseau):
    # TODO Implantez mon constructeur
    #  def __init__(self, ...) -> None:
    def __init__(self, nom:str, nb_pattes: int):
        super(Cockatiel, self).__init__(nom, nb_pattes, True)
        self.nom = nom
        self.nb_pattes = nb_pattes






