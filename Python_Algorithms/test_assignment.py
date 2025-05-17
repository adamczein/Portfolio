import os
import sys
import unittest
from abc import ABC
from unittest import TestCase
from unittest.mock import MagicMock, patch

from accessoire import Accessoire, TypeAccessoire
from animal import Animal, calcul_meilleur_animal
from elements_tiktok import ElementViral, Musique, Filtre
from main import main
from mammifere import Chat, LongueurPoils
from oiseau import Cockatiel
from reptile import Serpent
from tiktok import TikTok, CompteTikTok


class TestElementViral(TestCase):
    def test_score_viral_abstraite(self):
        self.assertTrue(issubclass(ElementViral, ABC), "La classe ElementViral n'est pas abstraite.")
        self.assertTrue(ElementViral.score_viral.__isabstractmethod__, "La méthode score_viral n'est pas abstraite.")


class TestMusique(TestCase):
    def test_attributs(self):
        musique = Musique("Black Smoke Rising", 88670598)
        self.assertTrue(hasattr(musique, 'titre'), "La classe Musique n'a pas d'attribut public 'titre'.")
        self.assertTrue(hasattr(musique, 'nb_ecoutes'), "La classe Musique n'a pas d'attribut public 'nb_ecoutes'.")

    def test_score_viral(self):
        musique = Musique("Never Gonna Give You Up", 481755911)
        score_viral = musique.score_viral()
        self.assertIsInstance(score_viral, int, msg="Musique.score_viral doit être un int.")
        self.assertAlmostEqual(score_viral, 48175, msg="La valeur du score viral est erronée.")


class TestFiltre(TestCase):
    def test_attributs_filtre(self):
        filtre = Filtre("#NoFilter", 123456789)
        self.assertTrue(hasattr(filtre, 'nom'), "La classe Filtre n'a pas d'attribut public 'nom'.")
        self.assertTrue(hasattr(filtre, 'nb_utilisations'),
                        "La classe Filtre n'a pas d'attribut public 'nb_utilisations'.")

    def test_score_viral_filtre(self):
        filtre = Filtre("L'espèce de filtre qui montre si t'as une main stable", 9999999999)
        score_viral = filtre.score_viral()
        self.assertIsInstance(score_viral, int, msg="Filtre.score_viral doit être un int.")
        self.assertAlmostEqual(score_viral, 199999, msg="La valeur du score viral est erronée.")


class TestAccessoire(TestCase):
    def test_constructeur(self):
        try:
            Accessoire("Boots with the fur", 10, TypeAccessoire.CHAUSSURES)
        except TypeError:
            self.fail("Le constructeur de Accessoire n'a pas été implanté correctement.")

    def test_attributs_accessoire(self):
        accessoire = Accessoire("Boots with the fur", 10, TypeAccessoire.CHAUSSURES)
        self.assertTrue(hasattr(accessoire, 'nom'), "La classe Accessoire n'a pas d'attribut public 'nom'.")
        self.assertTrue(hasattr(accessoire, 'type_accessoire'),
                        "La classe Accessoire n'a pas d'attribut public 'type_accessoire'.")
        self.assertTrue(hasattr(accessoire, 'niveau_mignonnerie'),
                        "La classe Accessoire n'a pas d'attribut public 'niveau_mignonnerie'.")

    def test_str(self):
        accessoire = Accessoire("Couronne", 20, TypeAccessoire.BIJOU)
        self.assertEqual(
            str(accessoire),
            "type : BIJOU, nom : Couronne, niveau de mignonnerie : 20",
            msg="La représentation en string de Accessoire n'est pas comme attendue.")

    def test_score_viral_chapeau(self):
        accessoire = Accessoire("Haut-de-forme", 15, TypeAccessoire.CHAPEAU)
        self.assertAlmostEqual(accessoire.score_viral(), 225000)

    def test_score_viral_chaussures(self):
        accessoire = Accessoire("Bottes de pluie", 12, TypeAccessoire.CHAUSSURES)
        self.assertAlmostEqual(accessoire.score_viral(), 144000)

    def test_score_viral_bijou(self):
        accessoire = Accessoire("Collier de macaroni", 40, TypeAccessoire.BIJOU)
        self.assertAlmostEqual(accessoire.score_viral(), 320000)

    def test_score_viral_vetement(self):
        accessoire = Accessoire("Costume d'abeille", 40, TypeAccessoire.VETEMENT)
        self.assertAlmostEqual(accessoire.score_viral(), 400000)


class TestAnimal(TestCase):
    def test_add(self):
        accessoire = Accessoire("Costume d'abeille", 40, TypeAccessoire.VETEMENT)
        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        addition = terreur + accessoire

        self.assertIsInstance(addition,
                              int,
                              msg="Le résultat de l'addition entre un accessoire et un animal doit être un int.")
        self.assertEqual(addition, 400000, msg="La valeur de l'addition est erronée.")

    def test_iadd(self):
        accessoire = Accessoire("Costume d'abeille", 40, TypeAccessoire.VETEMENT)
        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        terreur += accessoire

        self.assertListEqual(terreur.liste_accessoires,
                             [accessoire],
                             msg="L'accessoire n'a pas été ajouté la liste de l'animal")

    def test_iadd_chaussures(self):
        accessoire = Accessoire("Bottes de pluie", 10, TypeAccessoire.CHAUSSURES)
        snek = Serpent("Danger Noodle", True, True)
        snek += accessoire

        self.assertListEqual(snek.liste_accessoires,
                             [],
                             msg="Un accessoire de type CHAUSSURES ne peut être ajouté à un animal sans pattes.")

    def test_crier_abstraite(self):
        self.assertTrue(issubclass(Animal, ABC), "La classe Animal n'est pas abstraite")
        self.assertTrue(Animal.crier.__isabstractmethod__, "La méthode crier n'est pas abstraite")

    def test_score_viral_animal(self):
        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        accessoire1 = Accessoire("Costume d'abeille", 40, TypeAccessoire.VETEMENT)
        accessoire2 = Accessoire("Chapeau d'abeille", 50, TypeAccessoire.CHAPEAU)
        # Syntaxe à ne pas reproduire à la maison
        terreur.liste_accessoires = [accessoire1, accessoire2]

        self.assertIsInstance(terreur.score_viral(), int, msg="Animal.score_viral doit être un int.")
        self.assertAlmostEqual(terreur.score_viral(), 1150000, msg="La valeur du score viral est erronée.")

    def test_calcul_meilleur_animal(self):
        accessoire1 = Accessoire("Costume d'abeille", 40, TypeAccessoire.VETEMENT)
        accessoire2 = Accessoire("Chapeau d'abeille", 50, TypeAccessoire.CHAPEAU)

        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        snek = Serpent("Danger Noodle", True, True)

        # Syntaxe à ne pas reproduire à la maison
        terreur.liste_accessoires = [accessoire1]
        snek.liste_accessoires = [accessoire2]

        nom, score = calcul_meilleur_animal([terreur, snek])
        self.assertEqual(nom, "Danger Noodle")
        self.assertAlmostEqual(score, 750000)


class TestMammifere(TestCase):
    def test_constructeur_chat(self):
        try:
            Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        except TypeError:
            self.fail("Le constructeur de Chat n'a pas été implanté correctement.")

    def test_str_mammifere(self):
        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        attendu = "Le Chat Milo le terrible a 4 pattes et des poils COURTS."
        self.assertEqual(str(terreur), attendu,
                         msg="La représentation en string de Mammifere n'est pas comme attendue.")

    def test_attributs_chat(self):
        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        self.assertTrue(hasattr(terreur, 'nom'), "La classe Chat n'a pas d'attribut public 'nom'.")
        self.assertTrue(hasattr(terreur, 'nb_pattes'), "La classe Chat n'a pas d'attribut public 'nb_pattes'.")
        self.assertTrue(hasattr(terreur, 'longueur_poils'),
                        "La classe Chat n'a pas d'attribut public 'longueur_poils'.")
        self.assertTrue(hasattr(terreur, 'couleur'), "La classe Chat n'a pas d'attribut public 'couleur'.")

    def test_crier_chat(self):
        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        self.assertEqual(terreur.crier(), "Miaou", msg="Le cri du Chat doit être 'Miaou'")


class TestOiseau(TestCase):
    def test_constructeur_cockatiel(self):
        try:
            Cockatiel("Kevin l'oiseau rare", 2)
        except TypeError:
            self.fail("Le constructeur de Cockatiel n'a pas été implanté correctement.")

    def test_attributs_cockatiel(self):
        kevin = Cockatiel("Kevin l'oiseau rare", 2)
        self.assertTrue(hasattr(kevin, 'nom'), "La classe Cockatiel n'a pas d'attribut public 'nom'.")
        self.assertTrue(hasattr(kevin, 'nb_pattes'), "La classe Cockatiel n'a pas d'attribut public 'nb_pattes'.")
        self.assertTrue(hasattr(kevin, 'chante'), "La classe Cockatiel n'a pas d'attribut public 'chante'.")

    def test_str_chant(self):
        zazu = Cockatiel("Zazu", 2)
        attendu = "Le Cockatiel Zazu chante."
        self.assertEqual(str(zazu), attendu,
                         msg="La représentation en string de Oiseau n'est pas comme attendue.")

    def test_str_sans_chant(self):
        kevin = Cockatiel("Kevin l'oiseau rare", 2)
        # Syntaxe à ne pas reproduire à la maison
        kevin.chante = False
        attendu = "Le Cockatiel Kevin l'oiseau rare ne chante pas."
        self.assertEqual(str(kevin), attendu,
                         msg="La représentation en string de Oiseau n'est pas comme attendue.")

    def test_crier_oiseau_chant(self):
        zazu = Cockatiel("Zazu", 2)
        attendu = "Ba de ya, say that you remember. Ba de ya, dancing in September."
        self.assertEqual(zazu.crier(), attendu,
                         msg="Le cri d'un Oiseau qui chante n'est comme attendu.")

    def test_crier_oiseau_sans_chant(self):
        kevin = Cockatiel("Kevin l'oiseau rare", 2)
        # Syntaxe à ne pas reproduire à la maison
        kevin.chante = False
        attendu = "cuicui"
        self.assertEqual(kevin.crier(), attendu,
                         msg="Le cri d'un Oiseau qui ne chante pas n'est comme attendu.")


class TestReptile(TestCase):
    def test_constructeur_serpent(self):
        try:
            Serpent("Danger Noodle", True, True)
        except TypeError:
            self.fail("Le constructeur de Serpent n'a pas été implanté correctement.")

    def test_attributs_serpent(self):
        snek = Serpent("Noodle", True, False)
        self.assertTrue(hasattr(snek, 'nom'), "La classe Serpent n'a pas d'attribut public 'nom'.")
        self.assertTrue(hasattr(snek, 'nb_pattes'), "La classe Serpent n'a pas d'attribut public 'nb_pattes'.")
        self.assertEqual(snek.nb_pattes, 0, "La classe Serpent ne doit pas avoir de pattes.")
        self.assertTrue(hasattr(snek, 'est_nocturne'), "La classe Serpent n'a pas d'attribut public 'est_nocturne'.")
        self.assertTrue(hasattr(snek, 'est_venimeux'), "La classe Serpent n'a pas d'attribut public 'est_venimeux'.")

    def test_str_nocturne(self):
        snek = Serpent("Noodle", True, False)
        attendu = "Le Serpent Noodle est nocturne."
        self.assertEqual(super(Serpent, snek).__str__(), attendu,
                         msg="La représentation en string d'un Reptile diurne n'est pas comme attendue.")

    def test_str_diurne(self):
        snek = Serpent("Noodle", False, False)
        attendu = "Le Serpent Noodle est diurne."
        self.assertEqual(super(Serpent, snek).__str__(), attendu,
                         msg="La représentation en string d'un Reptile diurne n'est pas comme attendue.")

    @patch("reptile.Reptile.__str__")
    def test_str_serpent_venimeux(self, mock_reptile_str):
        snek = Serpent("Danger Noodle", True, True)

        mock_reptile_str.return_value = "Reptile.__str__"
        attendu = "Reptile.__str__ Il est venimeux."

        self.assertEqual(str(snek), attendu,
                         msg="La représentation en string d'un Serpent venimeux n'est pas comme attendue.")

    @patch("reptile.Reptile.__str__")
    def test_str_serpent_non_venimeux(self, mock_reptile_str):
        snek = Serpent("Noodle", True, False)

        mock_reptile_str.return_value = "Reptile.__str__"
        attendu = "Reptile.__str__ Il n'est pas venimeux."

        self.assertEqual(str(snek), attendu,
                         msg="La représentation en string d'un Serpent non venimeux n'est pas comme attendue.")

    def test_crier_serpent(self):
        snek = Serpent("Danger Noodle", True, True)
        self.assertEqual(snek.crier(), "sssss", msg="Le cri du Serpent doit être 'sssss'")


class TestTikTok(TestCase):
    def test_constructeur_tiktok(self):
        try:
            TikTok("Toe Beans")
        except TypeError:
            self.fail("Le constructeur de TikTok n'a pas été implanté correctement.")

    def test_attributs_tiktok(self):
        tiktok = TikTok("Toe Beans")
        self.assertTrue(hasattr(tiktok, 'titre'), "La classe TikTok n'a pas d'attribut public 'titre'.")
        self.assertTrue(hasattr(tiktok, 'musique'), "La classe TikTok n'a pas d'attribut public 'musique'.")
        self.assertTrue(hasattr(tiktok, 'filtre'), "La classe TikTok n'a pas d'attribut public 'filtre'.")
        # Syntaxe à ne pas reproduire à la maison
        self.assertTrue(hasattr(tiktok, '_TikTok__animaux'), "La classe TikTok n'a pas d'attribut privé 'animaux'.")

    def test_ajouter_animal(self):
        tiktok = TikTok("Milo essaye de manger le laptop d'un chargé de INF1007")
        terreur = Chat("Milo le terrible", LongueurPoils.COURTS, "Noir et blanc")
        tiktok.ajouter_animal(terreur)
        # Syntaxe à ne pas reproduire à la maison
        self.assertListEqual(tiktok._TikTok__animaux, [terreur],
                             msg="L'animal n'a pas bien été ajouté à la liste des animaux du TikTok.")

    @patch("tiktok.TikTok.vues")
    def test_lt(self, mock_vues):
        tiktok1 = TikTok("TikTok cool")
        tiktok2 = TikTok("TikTok encore plus cool")

        # Syntaxe à ne pas reproduire à la maison
        tiktok1.vues = 10
        tiktok2.vues = 20

        self.assertLess(tiktok1, tiktok2, msg="L'opérateur < n'a pas bien été surchargé.")
        self.assertGreater(tiktok2, tiktok1, msg="L'opérateur < n'a pas bien été surchargé.")

    @patch("tiktok.TikTok.vues")
    def test_str_tiktok(self, mock_vues):
        tiktok = TikTok("Milo l'abeille essaye de manger le laptop d'un chargé de INF1007")

        # Syntaxe à ne pas reproduire à la maison
        tiktok.vues = 10

        attendu = "Milo l'abeille essaye de manger le laptop d'un chargé de INF1007 (10 vues)"
        self.assertEqual(str(tiktok), attendu,
                         msg="La représentation en string d'un TikTok n'est pas comme attendue.")

    def test_vues_tiktok(self):
        tiktok = TikTok("La magie des MagicMock")

        # Syntaxe à ne pas reproduire à la maison
        mock_animal = MagicMock()
        mock_animal.score_viral.return_value = 200
        tiktok._TikTok__animaux = [mock_animal]
        tiktok.musique = MagicMock()
        tiktok.musique.score_viral.return_value = 100
        tiktok.filtre = MagicMock()
        tiktok.filtre.score_viral.return_value = 10

        self.assertAlmostEqual(tiktok.vues, 310)


class TestCompteTikTok(TestCase):
    def test_constructeur_compte(self):
        try:
            CompteTikTok("NosAmisLesAnimaux")
        except TypeError:
            self.fail("Le constructeur de CompteTikTok n'a pas été implanté correctement.")

    def test_attributs_compte(self):
        compte_tiktok = CompteTikTok("NosAmisLesAnimaux")
        self.assertTrue(hasattr(compte_tiktok, 'identifiant'),
                        "La classe CompteTikTok n'a pas d'attribut public 'identifiant'.")
        # Syntaxe à ne pas reproduire à la maison
        self.assertTrue(hasattr(compte_tiktok, '_CompteTikTok__tiktoks'),
                        "La classe CompteTikTok n'a pas d'attribut privé 'tiktoks'.")

    def test_len_compte(self):
        compte_tiktok = CompteTikTok("NosAmisLesAnimaux")
        # Syntaxe à ne pas reproduire à la maison
        compte_tiktok._CompteTikTok__tiktoks = [TikTok("Cookie est cute")]
        self.assertEqual(len(compte_tiktok), 1, msg="opérateur len est mal surchargé.")

    def test_iadd_compte(self):
        compte_tiktok = CompteTikTok("NosAmisLesAnimaux")
        tiktok = TikTok("Cookie est encore une fois cute")
        compte_tiktok += tiktok

        # Syntaxe à ne pas reproduire à la maison
        self.assertListEqual(compte_tiktok._CompteTikTok__tiktoks, [tiktok],
                             msg="opérateur += est mal surchargé.")

    def test_vues_compte(self):
        compte_tiktok = CompteTikTok("NosAmisLesAnimaux")

        # Syntaxe à ne pas reproduire à la maison
        tiktok1 = MagicMock()
        tiktok1.vues = 19
        tiktok2 = MagicMock()
        tiktok2.vues = 23
        compte_tiktok._CompteTikTok__tiktoks = [tiktok1, tiktok2]

        self.assertEqual(compte_tiktok.vues, 42,
                         msg="Le compte n'a pas le nombre de vues attendues.")

    @patch("tiktok.TikTok.vues")
    def test_tiktoks_plus_populaires(self, mock_vues):
        compte_tiktok = CompteTikTok("NosAmisLesAnimaux")
        tiktok1 = TikTok("Milo l'abeille essaye de manger le laptop d'un chargé de INF1007")
        tiktok2 = TikTok("Snek snek snek")
        tiktok3 = TikTok("Toe Beans")

        tiktok1.vues = 100
        tiktok2.vues = 25
        tiktok3.vues = 50
        # Syntaxe à ne pas reproduire à la maison
        compte_tiktok._CompteTikTok__tiktoks = [tiktok1, tiktok2, tiktok3]

        tiktoks_plus_populaires = compte_tiktok.tiktoks_plus_populaires()
        self.assertListEqual(tiktoks_plus_populaires, [tiktok1, tiktok3, tiktok2],
                             msg="La liste triée par popularité des TikToks du compte n'est pas bonne.")


class TestMain(TestCase):

    def test_main(self):
        compte_tiktok = main()
        self.assertEqual(compte_tiktok.identifiant, 'PolyAnimalerie', msg="Le nom du compte n'est pas celui prévu.")
        self.assertAlmostEqual(compte_tiktok.vues, 474175, msg="Le nombre de vues n'est pas celui attendu.")
        # Syntaxe à ne pas reproduire à la maison
        self.assertAlmostEqual(len(compte_tiktok._CompteTikTok__tiktoks), 3,
                               msg="Il n'y a pas trois tiktoks dans le compte.")


if __name__ == '__main__':
    if not os.path.exists('logs'):
        os.mkdir('logs')
    with open('logs/tests_results.txt', 'w') as f:
        loader = unittest.TestLoader()
        suite = loader.loadTestsFromModule(sys.modules[__name__])
        unittest.TextTestRunner(f, verbosity=2).run(suite)
