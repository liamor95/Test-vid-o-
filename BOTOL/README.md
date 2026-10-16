# BOTOL — Kit de démarrage du projet mobile

Ce dossier prépare la création du projet **BOTOL — Battle of the Ocean's Legacy** en local, sur le PC, dans un **nouveau projet Unreal Engine 5 dédié au mobile**. Rien ici n'est du code de jeu : c'est le plan à valider avant d'ouvrir l'éditeur, plus les fichiers à copier dans le futur dépôt BOTOL.

| Fichier | Rôle |
|---|---|
| `README.md` | Ce plan : décisions acquises, choix proposés, arbitrages, session 1 pas à pas, jalons |
| `CLAUDE.md` | Consignes pour Claude Code en local, à copier à la racine du projet BOTOL |
| `AUDIT_REUTILISATION_WOTOL.md` | Grille pour trier ce qui passe de WOTOL à BOTOL |
| `.gitignore` / `.gitattributes` | Fichiers Git + Git LFS pour un projet UE5, à copier à la racine du projet BOTOL |

Rédigé le 16/10/2026 à partir de la page Notion BOTOL (02/09/2026), du journal de bord et du document « ChatGPT & CLAUDE ». Tout ce qui n'y figure pas est marqué **proposition** ou **à arbitrer**.

---

## 1. Ce qui est déjà décidé

Source : page Notion BOTOL du 02/09/2026, sauf mention contraire.

- BOTOL est un **projet distinct**. On ne convertit, n'écrase et ne supprime jamais rien dans WOTOL.
- Même univers, mêmes cinq factions, même lore. Les mécaniques WOTOL servent d'inspiration, pas de copie.
- Caméra 3D isométrique ou quasi fixe, interface tactile pensée dès le départ pour téléphone et tablette.
- Narration surtout textuelle (fenêtres qu'on fait défiler au toucher), peu ou pas de doublage.
- Premier prototype jouable : **Aquiloris contre Noxéens, en solo contre l'IA**, avec une boucle courte et complète.
- Architecture extensible aux cinq factions, sans coder tout de suite les cinq effectifs.
- Pas de serveur, de matchmaking ni de multijoueur avant que le solo soit validé sur de vrais appareils.
- Une mécanique définie pour une faction doit pouvoir s'appliquer de façon cohérente aux autres (règle validée pour WOTOL le 07/09/2026, reprise ici).
- Mode guidé disponible sur demande : Blueprint par Blueprint, nœud par nœud, valeur par valeur, avec un test après chaque étape.

La boucle du prototype, telle qu'écrite dans Notion :

1. Choisir une faction disponible.
2. Préparer ses unités et sa composition.
3. Entrer dans une bataille courte.
4. Commander les unités au toucher.
5. Affronter une IA.
6. Obtenir un résultat, une récompense ou une progression.
7. Revenir à l'écran de préparation et recommencer.

---

## 2. Choix techniques proposés (à valider)

**Moteur : Unreal Engine 5.8.x, la même version que WOTOL.**
WOTOL est officiellement en 5.8 depuis le 25/07/2026. L'outil *Migrate* d'Unreal copie des assets vers une version égale ou plus récente, jamais vers une version plus ancienne. Si BOTOL tournait sur une version plus vieille que WOTOL, il ne pourrait plus recevoir ses assets. Côté Google Play, Epic indique qu'il faut au moins UE 5.7 pour publier ou mettre à jour une application.

**Code : C++ pour les systèmes, Blueprint pour le contenu et les réglages.**
C'est déjà le fonctionnement de WOTOL. Ça compte pour une raison pratique : Claude Code sait lire et écrire du C++, mais **pas** les `.uasset` (Blueprints, widgets, matériaux), qui sont des fichiers binaires. Dans un projet 100 % Blueprint, Claude ne pourrait que te guider et tu ferais toutes les manipulations à la main.
*Contrepartie :* d'après la documentation d'Epic, compiler un projet C++ pour iOS exige un Mac (Xcode). Un projet uniquement Blueprint peut être empaqueté pour iOS depuis Windows, mais cette page date de la 5.2 et doit être revérifiée pour la 5.8.

**Plateforme : Android d'abord, iOS ensuite.**
Sous Windows, on construit et on teste sur Android sans matériel supplémentaire. iOS attendra que le prototype tienne debout et qu'un Mac soit disponible (achat d'occasion, prêt ou Mac en location dans le cloud).

**Modèle de départ : *Top Down*, variante *Strategy* (disponible depuis UE 5.6).**
D'après Epic, cette variante fournit déjà une caméra orthographique isométrique avec zoom et déplacement, la sélection de plusieurs unités et leur déplacement en groupe. C'est le plus proche des étapes 3 et 4 de la boucle.
*Attention :* la variante repose sur un **déplacement par grille** et ses contrôles sont prévus pour la souris et le clavier. La grille est une décision de game design qui n'est pas prise (voir section 3), et le tactile sera à refaire.

**Gestion de versions : un nouveau dépôt Git privé « BOTOL » avec Git LFS.**
Tu travailles seul sur BOTOL et Claude Code fonctionne avec Git. Perforce, recommandé le 04/10 pour WOTOL, se justifie surtout quand plusieurs personnes modifient les mêmes `.uasset`. Vérifie le quota LFS gratuit de l'hébergeur : il se remplit vite avec des modèles 3D et des textures.

**Rendu mobile : ne compter ni sur Nanite ni sur Lumen.**
Selon Epic, Lumen sur mobile reste expérimental, réservé aux Android haut de gamme, et ne fonctionne pas sur iOS. Je n'ai trouvé aucun support officiel de Nanite sur mobile. En pratique : géométrie classique avec des LOD, éclairage simple, préréglage *Scalable*.

---

## 3. Arbitrages à faire avant de coder

Ces points ne sont pas décidés. Claude ne doit pas les trancher à ta place.

1. **Temps réel ou tour par tour ?** WOTOL est en temps réel. La page BOTOL ne le précise pas. C'est la décision qui pèse le plus sur la suite :
   - le tour par tour colle mieux au tactile et aux parties courtes, c'est le modèle de Polytopia ;
   - il rend un futur multijoueur beaucoup moins cher, puisque des parties asynchrones n'ont pas besoin de serveurs temps réel ;
   - le temps réel reste plus fidèle à l'esprit de WOTOL.
2. **Déplacement sur grille ou libre ?** La variante *Strategy* part sur une grille.
3. **Écran en paysage ou en portrait ?**
4. **Appareil de test de référence :** quel téléphone Android as-tu sous la main ? Les budgets de performance seront mesurés dessus.
5. **À qui appartient BOTOL : 3DÉCORS, toi, ou une future société ?** Ça détermine au nom de qui ouvrir les comptes développeur et quel identifiant d'application (*package name*) choisir. Cet identifiant ne peut plus changer une fois l'application publiée sur Google Play. Attention, un segment ne peut pas commencer par un chiffre : `com.3decors.botol` est invalide, mais `com.troisdecors.botol` fonctionne.
6. **Modèle économique :** toujours ouvert. Une piste à étudier, pas une décision : Aquiloris et Noxéens gratuits, les trois autres factions vendues à l'unité, comme Polytopia vend ses tribus.

---

## 4. Session 1 — créer le projet (pas à pas)

But : avoir un projet BOTOL vide qui démarre sur ton téléphone Android, sauvegardé dans Git. Pas de gameplay à ce stade.

### 4.1 Prérequis

- [ ] Unreal Engine **5.8.x**, la même version que WOTOL.
- [ ] Visual Studio 2022 avec la charge de travail « Développement de jeux en C++ » (normalement déjà installé pour WOTOL).
- [ ] Android Studio et le NDK **dans les versions qu'Epic indique pour la 5.8**, sur la page *Android Development Requirements*. Ensuite, lance `Engine\Extras\Android\SetupAndroid.bat` depuis le dossier d'installation d'Unreal.
- [ ] Sur le téléphone : options développeur activées, débogage USB autorisé, téléphone branché et accepté.
- [ ] Git et Git LFS installés (`git lfs install`).

### 4.2 Créer le projet

1. Lance UE 5.8 et choisis **Games → Top Down**.
2. Variante : **Strategy**.
3. Type de projet : **C++**.
4. Plateforme cible : **Mobile**. Préréglage de qualité : **Scalable**.
5. Contenu de démarrage : **non**. Ray tracing : **non**.
6. Emplacement : un dossier **à part**, jamais à l'intérieur du dossier WOTOL. Mets-le sur le disque rapide C:, comme le projet WOTOL (D: est le disque externe qui contient les sources d'assets dans `D:\WOTOL`). Par exemple : `C:\Projets\BOTOL`.
7. Nom du projet : `BOTOL`.

*Test :* le projet s'ouvre, tu lances *Play* dans l'éditeur, la caméra isométrique et la sélection d'unités du modèle fonctionnent à la souris.

### 4.3 Premier commit, avant toute autre chose

1. Ferme l'éditeur.
2. Copie `.gitignore`, `.gitattributes` et `CLAUDE.md` de ce dossier à la racine du projet, à côté de `BOTOL.uproject`.
3. Dans un terminal, à la racine du projet :
   ```
   git init
   git lfs install
   git add .gitattributes .gitignore
   git commit -m "Configuration Git et LFS"
   git add .
   git commit -m "Projet BOTOL initial (Top Down Strategy, mobile, UE 5.8)"
   ```
4. Crée un dépôt **privé** BOTOL sur GitHub et pousse-le.

*Test :* `git lfs ls-files` liste bien les `.uasset` et `.umap`. Le dépôt ne contient ni `Binaries/`, ni `Intermediate/`, ni `Saved/`, ni `DerivedDataCache/`.

### 4.4 Premier lancement sur le téléphone

1. **Project Settings → Platforms → Android** : accepte la licence du SDK. Ne remplis l'identifiant d'application qu'une fois le point 5 de la section 3 tranché ; garde une valeur provisoire d'ici là.
2. Dans la barre d'outils : **Platforms → Android →** ton téléphone **→ Launch**.
3. Sur le téléphone, ouvre la console (tape à quatre doigts dans une version de développement) et entre `stat fps`, puis `stat unit`.
4. Note les chiffres dans `JOURNAL.md` : modèle du téléphone, images par seconde, temps de jeu et de rendu (*Game* / *Draw* / *GPU*).

*C'est fini quand :* le modèle tourne sur ton téléphone, les mesures de départ sont notées, et le tout est commité.

---

## 5. Jalons du prototype Aquiloris contre Noxéens

L'ordre suit la Phase 2 de Notion. Chaque jalon ne compte comme terminé qu'une fois testé **sur le téléphone**, pas seulement dans l'éditeur.

| # | Jalon | C'est fini quand |
|---|---|---|
| M0 | Projet créé, Git, premier lancement Android | Section 4 terminée |
| M1 | Données de faction et d'unité, pilotées par les données | Ajouter une faction = ajouter un fichier de données, sans toucher au code. Aquiloris et Noxéens sont créés ; Thalassidras, Muréniens et Pirates Abyssaux pourront suivre plus tard sans réécriture |
| M2 | Caméra et contrôles tactiles | Déplacer la vue, zoomer, sélectionner et donner un ordre au doigt, sans souris |
| M3 | Combat de base | Deux unités s'affrontent et l'une meurt, avec des valeurs lues dans les données |
| M4 | IA ennemie | L'IA déplace ses unités et attaque toute seule |
| M5 | Victoire et défaite | Une partie se termine et affiche un résultat |
| M6 | Écran de préparation et retour | La boucle complète, étapes 1 à 7, tourne sans redémarrer l'application |
| M7 | Première progression simple | Une récompense obtenue est conservée d'une partie à l'autre |
| M8 | Mesure de performances | Le pire cas mesuré sur le téléphone de référence (nombre d'unités à l'écran) tient l'objectif d'images par seconde que tu auras fixé |

La structure de code prévue pour M1, à valider avant de l'écrire :

```
Source/BOTOL/
  Core/         mode de jeu, état de partie, contrôleur joueur
  Factions/     données de faction (un Data Asset par faction)
  Units/        acteur d'unité + données d'unité
  Combat/       dégâts, cibles, portée
  AI/           IA ennemie
  Input/        contrôles tactiles
  UI/           écrans et interface de bataille
  Progression/  sauvegarde et récompenses
Content/BOTOL/
  Factions/Aquiloris/   Factions/Noxeens/
  Maps/   UI/   Audio/   Core/
```

Le contenu du modèle de départ reste dans son propre dossier (`Variant_Strategy/`). On le remplace petit à petit, sans le mélanger au contenu BOTOL.

---

## Sources

- Notion : page « BOTOL — Battle of the Ocean's Legacy » (02/09/2026) et « Journal de bord ».
- Drive : document « ChatGPT & CLAUDE » (moteur WOTOL 5.8 du 25/07/2026, recommandation Perforce du 04/10/2026, relevé de l'Aquilance).
- [Epic — Android Development Requirements](https://dev.epicgames.com/documentation/unreal-engine/android-development-requirements-for-unreal-engine)
- [Epic — Updated game templates for UE 5.6 (variantes Strategy / Twin Stick)](https://www.unrealengine.com/news/updated-game-templates-for-unreal-engine-5-6available-now)
- [Epic — Variants in game templates](https://dev.epicgames.com/documentation/unreal-engine/variants-in-game-templates)
- [Epic — Building iOS projects on Windows (page 5.2)](https://dev.epicgames.com/documentation/en-us/unreal-engine/building-ios-projects-on-windows-in-unreal-engine?application_version=5.2)
- [Epic — Remote builds for iOS](https://dev.epicgames.com/documentation/en-us/unreal-engine/creating-remote-builds-of-unreal-engine-projects-for-ios)
- [Epic — Lumen on mobile](https://dev.epicgames.com/documentation/unreal-engine/using-lumen-global-illumination-on-mobile-in-unreal-engine)
- [Google Play — Exigences de test pour les nouveaux comptes personnels](https://support.google.com/googleplay/android-developer/answer/14151465?hl=en)
- [Google Play — Informations requises pour créer un compte (D-U-N-S)](https://support.google.com/googleplay/android-developer/answer/13628312?hl=en)
