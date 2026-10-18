# BOTOL — Projet Unreal Engine 5.8 mobile

Ce dossier **est** le projet Unreal de **BOTOL — Battle of the Ocean's Legacy** : une application mobile de stratégie en vue 3D isométrique, distincte de WOTOL. Il s'ouvre directement dans Unreal Engine 5.8 sur le PC (section 4).

| Fichier | Rôle |
|---|---|
| `Lancer_BOTOL.bat` | Double-clic : compile BOTOL et ouvre Unreal Engine 5.8 |
| `BOTOL.uproject` | Le projet Unreal (UE 5.8, cibles Android et iOS) |
| `Config/` | Réglages moteur, jeu et entrées, optimisés pour le mobile |
| `Source/BOTOL/` | Code C++ : caméra isométrique, contrôles tactiles, unités, données de faction |
| `README.md` | Ce plan : décisions, réglages mobiles, session 1 pas à pas, jalons |
| `CLAUDE.md` | Consignes pour Claude Code en local |
| `JOURNAL.md` | Journal des sessions de travail |
| `BENCHMARK_STRATEGIE_MOBILE.md` | Benchmark de 17 jeux de stratégie mobiles : caméra, orientation, gestes, contrôle des unités, mise en œuvre UE 5.8 |
| `AUDIT_REUTILISATION_WOTOL.md` | Grille pour trier ce qui passe de WOTOL à BOTOL |
| `.gitignore` / `.gitattributes` | Git + Git LFS pour Unreal |

Rédigé à partir de la page Notion BOTOL (02/09/2026), du journal de bord, du document « ChatGPT & CLAUDE » et des consignes de Liamor du 18/10/2026. Tout ce qui n'y figure pas est marqué **proposition** ou **provisoire**.

---

## 1. Ce qui est déjà décidé

> **Confirmé par Liamor le 18/10/2026 :** BOTOL est une **application mobile**, et tout y est pensé pour le mobile : interface, contrôles au doigt, durée des parties. Ce n'est pas un portage de WOTOL PC. La vue est en **3D isométrique**, comme dans les jeux de stratégie mobiles existants. C'était la direction de départ.

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

**Base : un projet C++ écrit sur mesure, sans modèle Unreal.**
La variante *Strategy* du modèle *Top Down* d'Unreal gère le tactile, mais en partie seulement, d'après le benchmark (`BENCHMARK_STRATEGIE_MOBILE.md`, section 6) : pas de zoom par pincement (le second doigt trace un cadre de sélection), une sélection qui s'ajoute toujours à la précédente, et aucune limite de carte. Le geste de pincement natif d'Enhanced Input a de plus un bug en 5.8 (UE-392736). Le projet contient donc sa propre caméra isométrique et ses contrôles tactiles en C++, avec un pincement calculé à la main : Claude Code peut tout lire et modifier. Seuls le niveau de test et les Data Assets se créent dans l'éditeur.

**Gestion de versions : Git + Git LFS.**
Pour l'instant, le projet vit dans le dépôt `Test-vid-o-` (branche `ccr-c8633fac-ff92q6`). À terme, il ira dans un dépôt privé dédié « BOTOL ». Tu travailles seul sur BOTOL et Claude Code fonctionne avec Git. Perforce, recommandé le 04/10 pour WOTOL, se justifie surtout quand plusieurs personnes modifient les mêmes `.uasset`. Vérifie le quota LFS gratuit de l'hébergeur : il se remplit vite avec des modèles 3D et des textures.

**Ce qui est déjà réglé dans le projet pour le mobile**

| Domaine | Réglage | Fichier |
|---|---|---|
| Cible | Matériel *Mobile*, qualité *Scalable* | `Config/DefaultEngine.ini` |
| Rendu | Rendu *forward* mobile, anticrénelage MSAA 4x, éclairage précalculé autorisé, HDR mobile gardé pour l'ambiance | `DefaultEngine.ini` |
| Fonctions PC coupées | Nanite, Lumen, réflexions, ombres virtuelles, *distance fields*, ray tracing, textures virtuelles, Substrate | `DefaultEngine.ini` |
| Effets coupés par défaut | Exposition automatique, flou de mouvement, occlusion ambiante, *lens flare* | `DefaultEngine.ini` |
| Android | Paysage avec rotation auto, plein écran immersif, Vulkan + OpenGL ES 3.2 en secours, appli déclarée comme jeu (paysage gardé sur tablette sous Android 16), affichage autour de l'encoche, arm64, identifiant provisoire `com.troisdecors.botol` | `DefaultEngine.ini` |
| iOS | Paysage uniquement, identifiant provisoire identique | `DefaultEngine.ini` |
| Entrées | Pas de joysticks virtuels ; dans l'éditeur, la souris imite un doigt | `Config/DefaultInput.ini` |
| Paquet | Shaders partagés, compression, pas de fichiers de debug embarqués | `Config/DefaultGame.ini` |
| Unités | Déplacement *NavWalking* (pas de test du sol à chaque image), pas de Tick d'acteur, animation calculée seulement si visible | `Source/BOTOL/Units/` |
| Contrôles | Aucun événement de clic par acteur : les doigts sont lus directement, sans trace inutile | `Source/BOTOL/Player/` |

**Rendu mobile : ne compter ni sur Nanite ni sur Lumen.**
Selon Epic, Lumen sur mobile reste expérimental, réservé aux Android haut de gamme, et ne fonctionne pas sur iOS. Je n'ai trouvé aucun support officiel de Nanite sur mobile. En pratique : géométrie classique avec des LOD, éclairage simple, préréglage *Scalable*.

---

## 3. Réglages par défaut et points encore ouverts

**Réglages par défaut retenus pour avancer.** Ils se déduisent de la consigne du 18/10 (« comme les jeux de stratégie mobiles existants »). Il suffit de le dire pour en changer un.

- **Temps réel**, comme la grande majorité des jeux de stratégie mobiles en 3D isométrique, et comme WOTOL.
- **Écran en paysage**, réglage provisoire. Il sera confirmé ou corrigé par le benchmark des jeux mobiles, avant que l'interface soit dessinée (jalon M2).

**Points ouverts, qui ne bloquent pas la session 1 :**

1. **Appareil de test de référence :** quel téléphone Android as-tu sous la main ? Les budgets de performance seront mesurés dessus.
2. **À qui appartient BOTOL : 3DÉCORS, toi, ou une future société ?** Ça détermine au nom de qui ouvrir les comptes développeur et quel identifiant d'application (*package name*) choisir. Cet identifiant ne peut plus changer une fois l'application publiée sur Google Play. Attention, un segment ne peut pas commencer par un chiffre : `com.3decors.botol` est invalide, mais `com.troisdecors.botol` fonctionne.
3. **Modèle économique :** toujours ouvert. Une piste à étudier, pas une décision : Aquiloris et Noxéens gratuits, les trois autres factions vendues à l'unité, comme Polytopia vend ses tribus.

---

## 4. Session 1 — ouvrir le projet sur le PC (pas à pas)

But : le projet compile, une bataille de test tourne dans l'éditeur, puis sur ton téléphone Android.

### 4.1 Prérequis

- [ ] Unreal Engine **5.8.x**, la même version que WOTOL.
- [ ] Visual Studio 2022 avec la charge de travail « Développement de jeux en C++ » (normalement déjà installé pour WOTOL).
- [ ] Android Studio et le NDK **dans les versions qu'Epic indique pour la 5.8**, sur la page *Android Development Requirements*. Ensuite, lance `Engine\Extras\Android\SetupAndroid.bat` depuis le dossier d'installation d'Unreal.
- [ ] Sur le téléphone : options développeur activées, débogage USB autorisé, téléphone branché et accepté.
- [ ] Git et Git LFS installés.

### 4.2 Mettre le dossier BOTOL sur le Bureau

1. Télécharge le projet (connecté à GitHub) : **https://github.com/liamor95/Test-vid-o-/archive/refs/heads/ccr-c8633fac-ff92q6.zip**
2. Avant d'ouvrir le ZIP : clic droit sur le fichier → **Propriétés** → coche **Débloquer** → **OK**. Sinon Windows bloquera le lanceur.
3. Ouvre le ZIP, puis le dossier qu'il contient, et **glisse le dossier `BOTOL` sur le Bureau**.

**Attention à OneDrive.** Si le chemin de ton Bureau contient `OneDrive` (par exemple `C:\Users\...\OneDrive\Bureau`), ne mets pas le projet dessus : OneDrive synchroniserait en continu les milliers de fichiers qu'Unreal génère, et ça bloque la compilation. Dans ce cas, mets le dossier `BOTOL` dans `C:\Projets\`, puis fais un clic droit sur `Lancer_BOTOL.bat` → **Envoyer vers → Bureau (créer un raccourci)**.

### 4.3 Ouvrir BOTOL en double-cliquant

Dans le dossier `BOTOL`, double-clique sur **`Lancer_BOTOL.bat`**. Il trouve Unreal Engine 5.8, compile BOTOL (quelques minutes la première fois), puis ouvre l'éditeur sur le projet.

- Si Windows affiche « Windows a protégé votre ordinateur » : **Informations complémentaires → Exécuter quand même**.
- Si la compilation échoue, la fenêtre reste ouverte : envoie à Claude les premières lignes qui contiennent `error`.
- **Autre méthode**, comme pour WOTOL : double-clique sur `BOTOL.uproject` et réponds **Oui** quand Unreal propose de recompiler le module BOTOL.

*Test :* l'éditeur s'ouvre sur un niveau vide, sans message d'erreur.

### 4.4 Créer le niveau de test

1. **File → New Level → Basic** : un niveau avec du sol, une lumière et un ciel.
2. Ajoute un grand sol pour la bataille : panneau **Place Actors → Shapes → Plane**, glisse-le dans le niveau, puis dans *Details* mets **Location** à `(0, 0, 0)` et **Scale** à `(60, 60, 1)`. Ça fait 60 × 60 m.
3. Ajoute la navigation : **Place Actors** → cherche **Nav Mesh Bounds Volume** → glisse-le dans le niveau → **Location** `(0, 0, 0)`, **Scale** `(30, 30, 2)`. Appuie sur **P** : le sol doit devenir vert. Appuie de nouveau sur **P** pour masquer.
4. **File → Save Current Level As** → crée le dossier `BOTOL/Maps` dans le Content Browser → nom `L_TestBataille`.
5. **Edit → Project Settings → Maps & Modes** : mets **Editor Startup Map** et **Game Default Map** sur `L_TestBataille`.
6. Lance **Play**. Tu dois voir 5 cylindres bleus (ton équipe) et 5 rouges (l'IA), vus de biais en isométrique.
   - clic maintenu et glisser : la vue se déplace ;
   - molette : zoom ;
   - clic sur un cylindre bleu : il est sélectionné (anneau jaune au sol) ;
   - clic au sol : il y va, en contournant les obstacles grâce au NavMesh.
7. Ferme le jeu et sauvegarde tout (**Ctrl+Shift+S**). Si le projet est suivi par Git (pas le cas avec le ZIP) :
   ```
   git add BOTOL
   git commit -m "BOTOL : niveau de test"
   git push
   ```

*Test :* le niveau `L_TestBataille` s'ouvre tout seul au prochain lancement de l'éditeur.

**Pour changer le nombre d'unités ou brancher les factions :** clic droit dans le Content Browser → **Blueprint Class** → cherche `BotolGameMode` → nom `BP_BotolGameMode`. Ouvre-le, règle *Test Units Per Team*, *Player Faction* et *Enemy Faction*, puis choisis-le comme **Default GameMode** dans *Maps & Modes*.

### 4.5 Premier lancement sur le téléphone

1. **Project Settings → Platforms → Android** : clique sur **Accept SDK License**. L'identifiant provisoire `com.troisdecors.botol` est déjà rempli.
2. Dans la barre d'outils : **Platforms → Android** → ton téléphone → **Launch**. Si Unreal propose plusieurs formats de texture, prends **ASTC**, le format des téléphones récents.
3. Sur le téléphone : un doigt qui glisse déplace la vue, deux doigts qui pincent zooment, un tap sélectionne ou donne l'ordre de déplacement.
4. Ouvre la console avec un tap à quatre doigts, puis entre `stat fps`, puis `stat unit`.
5. Note dans `JOURNAL.md` : le modèle du téléphone, les images par seconde, et les temps *Game*, *Draw* et *GPU*.

*C'est fini quand :* le projet compile, la bataille de test tourne dans l'éditeur et sur le téléphone, les mesures sont notées, et le tout est commité.

---

## 5. Jalons du prototype Aquiloris contre Noxéens

L'ordre suit la Phase 2 de Notion. Chaque jalon ne compte comme terminé qu'une fois testé **sur le téléphone**, pas seulement dans l'éditeur.

| # | Jalon | État au 18/10/2026 | C'est fini quand |
|---|---|---|---|
| M0 | Projet, Git, premier lancement Android | **Projet généré**, à compiler et lancer (section 4) | Section 4 terminée |
| M1 | Données de faction et d'unité | **Code prêt** (`BotolFactionData`, `BotolUnitData`). Reste à créer les Data Assets Aquiloris et Noxéens dans l'éditeur | Ajouter une faction = ajouter un fichier de données, sans toucher au code. Thalassidras, Muréniens et Pirates Abyssaux pourront suivre plus tard sans réécriture |
| M2 | Caméra et contrôles tactiles | **Code prêt** : caméra isométrique, glisser, pincer, tap pour sélectionner et donner un ordre. À tester sur le téléphone | Déplacer la vue, zoomer, sélectionner et donner un ordre au doigt, sans souris |
| M3 | Combat de base | À faire | Deux unités s'affrontent et l'une meurt, avec des valeurs lues dans les données |
| M4 | IA ennemie | À faire | L'IA déplace ses unités et attaque toute seule |
| M5 | Victoire et défaite | À faire | Une partie se termine et affiche un résultat |
| M6 | Écran de préparation et retour | À faire | La boucle complète, étapes 1 à 7, tourne sans redémarrer l'application |
| M7 | Première progression simple | À faire | Une récompense obtenue est conservée d'une partie à l'autre |
| M8 | Mesure de performances | À faire | Le pire cas mesuré sur le téléphone de référence (nombre d'unités à l'écran) tient l'objectif d'images par seconde que tu auras fixé |

Organisation du code :

```
Source/BOTOL/
  Game/     mode de jeu (bataille de test)
  Player/   caméra isométrique + contrôles tactiles
  Units/    unité de bataille
  Data/     Data Assets de faction et d'unité
  (à venir : Combat/, AI/, UI/, Progression/)
Content/BOTOL/
  Maps/   Factions/Aquiloris/   Factions/Noxeens/   UI/   Audio/
```

---

## Sources

- Notion : page « BOTOL — Battle of the Ocean's Legacy » (02/09/2026) et « Journal de bord ».
- Drive : document « ChatGPT & CLAUDE » (moteur WOTOL 5.8 du 25/07/2026, recommandation Perforce du 04/10/2026, relevé de l'Aquilance).
- [Epic — Android Development Requirements](https://dev.epicgames.com/documentation/unreal-engine/android-development-requirements-for-unreal-engine)
- [Epic — Building iOS projects on Windows (page 5.2)](https://dev.epicgames.com/documentation/en-us/unreal-engine/building-ios-projects-on-windows-in-unreal-engine?application_version=5.2)
- [Epic — Remote builds for iOS](https://dev.epicgames.com/documentation/en-us/unreal-engine/creating-remote-builds-of-unreal-engine-projects-for-ios)
- [Epic — Lumen on mobile](https://dev.epicgames.com/documentation/unreal-engine/using-lumen-global-illumination-on-mobile-in-unreal-engine)
- [Google Play — Exigences de test pour les nouveaux comptes personnels](https://support.google.com/googleplay/android-developer/answer/14151465?hl=en)
- [Google Play — Informations requises pour créer un compte (D-U-N-S)](https://support.google.com/googleplay/android-developer/answer/13628312?hl=en)
