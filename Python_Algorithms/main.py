from animal import calcul_meilleur_animal
from elements_tiktok import FILTRE_FESTIF, MUSIQUE_SEPTEMBER, MUSIQUE_BEZOS_I, FILTRE_ETOILES, MUSIQUE_CHRISTMAS, \
    FILTRE_RALENTI
from mammifere import Chat, LongueurPoils
from oiseau import Cockatiel
from reptile import Serpent
from accessoire import Accessoire, TypeAccessoire
from tiktok import TikTok, CompteTikTok


def main() -> CompteTikTok:
    # TODO : Creer un objet Chat qui s'appelle Wako, avec 4 pattes à poils courts roux
    wako = Chat("Wako",LongueurPoils.COURTS, "roux",  4)

    # TODO : Afficher Wako
    print(wako)

    # TODO : Creer un objet Serpent qui s'appelle Bob, qui est diurne et qui n'est pas venimeux
    bob = Serpent("Bob", True, False)

    # TODO : Afficher Bob
    print(bob)

    # TODO : Creer un objet Cockatiel qui s'appelle Cookie avec 2 pattes
    cookie = Cockatiel("Cookie", 2)


    # TODO : Afficher cookie
    print(cookie)

    # TODO : Creer un objet Accessoire de type chapeau avec un niveau de mignonnerie de 4
    chapeau = Accessoire("chapeau", 4, TypeAccessoire.CHAPEAU)

    # TODO : Creer un objet Accessoire de type chaussures avec un niveau de mignonnerie de 6
    chaussures = Accessoire("chaussures", 6, TypeAccessoire.CHAUSSURES)

    # TODO : Ajouter (+=) les chaussures à Wako
    wako += chaussures

    # TODO : Ajouter (+=) les chaussures à Bob
    bob += chaussures

    # TODO : Ajouter (+=) le chapeau à Bob
    bob += chapeau

    animaux = [wako, bob, cookie]
    # TODO: Dans une boucle, faites crier les animaux
    for animal in animaux:
        print(animal.crier())

    # TODO : Trouver quel animal est le meilleur
    meilleur_animal, score = ..., ...
    print(f"L'animal le plus mignon est {meilleur_animal} avec un score de {score}")

    # TODO: Créer un compte TikTok avec l'identifiant "PolyAnimalerie"
    compte = CompteTikTok("PolyAnimalerie")
# TODO: Créer un premier TikTok avec Wako et ajoutez le au compte
    #  Titre: "Wako est prêt pour Noël"
    #  Chanson: All I Want for Christmas is You
    #  Filtre: Ralenti
    #  UTILISEZ LES CONSTANTES DE elements_tiktok.py
    tiktok1 = TikTok("Wako est prêt pour Noël")
    tiktok1.ajouter_animal(wako)
    tiktok1.filtre = FILTRE_RALENTI
    tiktok1.musique = MUSIQUE_CHRISTMAS
    compte += tiktok1


    # TODO: Créer un deuxième TikTok avec Bob et ajoutez le au compte
    #  Titre: "Bob porte un chapeau"
    #  Chanson: Bezos I
    #  Filtre: Étoiles
    #  UTILISEZ LES CONSTANTES DE elements_tiktok.py
    tiktok2 = TikTok("Bob porte un chapeau")
    tiktok2.ajouter_animal(bob)
    tiktok2.filtre = FILTRE_ETOILES
    tiktok2.musique = MUSIQUE_BEZOS_I
    compte += tiktok2
    # TODO: Créer un troisième TikTok avec Wako et Cookie et ajoutez le au compte
    #  Titre: "Cookie chante à Wako qui ne veut rien savoir"
    #  Chanson: September
    #  Filtre: Festif
    #  UTILISEZ LES CONSTANTES DE elements_tiktok.py
    tiktok3 = TikTok("Cookie chante à Wako qui ne veut rien savoir")
    tiktok3.ajouter_animal(cookie)
    tiktok3.ajouter_animal(wako)
    tiktok3.filtre = FILTRE_FESTIF
    tiktok3.musique = MUSIQUE_SEPTEMBER
    compte += tiktok3
    # TODO Affichez le nombre de vues du troisième TikTok
    vues_tiktok_3 = tiktok3.vues
    print("Le troisième TikTok a", vues_tiktok_3, "vues")

    # TODO: Affichez le nombre de TikTok dans le compte
    nombre_tiktok_compte = len(compte)
    print("Le compte TikTok", compte.identifiant, "contient", nombre_tiktok_compte, "TikToks")

    # TODO: Affichez le nombre total de vues du compte
    vues_compte = compte.vues
    print("Le compte TikTok", compte.identifiant, "a", vues_compte, "vues")

    # TODO: Affichez la liste des TikTok en ordre de vues
    tiktoks_plus_populaires = compte.tiktoks_plus_populaires()
    print(tiktoks_plus_populaires)

    return compte


if __name__ == '__main__':
    compte = main()
    for tiktok in compte.tiktoks_plus_populaires():
        print(tiktok.to_json())