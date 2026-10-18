# Journal BOTOL

Entrée la plus récente en haut. Pour chaque session : ce qui a été fait, ce qui a été testé et où, les blocages, les décisions de Liamor, la prochaine étape.

---

## 18/10/2026 (fin) — Relecture des réglages et des corrections, benchmark (Claude Code, session cloud)

**Relecture n°2** (réglages mobiles, lanceur, corrections C++ du commit précédent) : 11 constats, tous confirmés par un contradicteur, **aucun bloquant**.

**Corrigé**
- Lanceur `Lancer_BOTOL.bat` : il détecte un éditeur Unreal déjà ouvert (Live Coding bloque alors la compilation), ignore une clé de registre périmée, et fait une pause avant d'ouvrir le `.uproject` si UE 5.8 est introuvable.
- Tactile :
  - un balayage rapide arrivé d'un bloc pendant une image lente n'est plus pris pour un tap ;
  - un doigt levé puis reposé dans la même image ne fait plus sauter la caméra ;
  - le doigt principal est choisi à chaque nouveau contact.
- Déplacements : si l'unité n'est pas elle-même sur le NavMesh (maillage vide, unité hors limites), elle va en ligne droite au lieu d'ignorer l'ordre.
- Bataille de test : disposition en bloc carré, pour que 200 unités tiennent sur le sol de 60 × 60 m.
- Android : appli déclarée comme jeu (`android:appCategory="game"`, paysage gardé sur tablette sous Android 16), affichage autour de l'encoche.
- Commentaires corrigés : OpenGL ES **3.2** en secours (et non 3.1) ; `r.DiscardUnusedQuality` économise la RAM, pas la taille du paquet.
- Correction de l'entrée précédente : une destination hors du NavMesh est refusée ; une destination sur le maillage mais inaccessible mène au point accessible le plus proche.

**Benchmark** : `BENCHMARK_STRATEGIE_MOBILE.md` (17 jeux). Il confirme le paysage, la caméra isométrique fixe, le tap pour sélectionner puis donner l'ordre, et le pincement codé à la main (le pincement natif d'Enhanced Input a un bug en 5.8, UE-392736).

**À faire avant toute publication** : Google Play exige l'API 36 depuis le 31/08/2026 (délai possible jusqu'au 01/11/2026), alors que la doc d'UE 5.8 recommande encore le SDK 35. Faire un build de test en API 36 et vérifier le manifeste généré.

**Toujours pas testé** : aucune compilation (pas d'Unreal dans la session cloud).

---

## 18/10/2026 (suite) — Relecture du code, corrections (Claude Code, session cloud)

**Relecture automatique** (2 relecteurs sur 3 ont abouti ; la contre-vérification a été interrompue par une limite d'utilisation)
- Compilation : **aucune erreur bloquante trouvée**. Signatures moteur, includes, règles UHT, types double/float et BOM UTF-8 vérifiés.
- Comportement en jeu : plusieurs défauts, corrigés ci-dessous.

**Corrigé**
- Avec un NavMesh, une destination hors du maillage est refusée au lieu d'envoyer l'unité en ligne droite à travers les obstacles (voir la correction de l'entrée suivante).
- Taper une unité ennemie : l'unité la rejoint et s'arrête au contact (MoveToActor), au lieu de pousser contre elle.
- Avec une unité sélectionnée, un tap au sol près d'une unité alliée donne bien un ordre (tolérance réduite à 50 cm).
- Fin de pincement en levant le premier doigt : le doigt restant continue de déplacer la vue.
- Tap très bref (appui et relâchement dans la même image) : il n'est plus perdu.
- `IsSelected` renommé `IsUnitSelected` pour ne pas masquer la sélection de l'éditeur.
- `UE_KINDA_SMALL_NUMBER` au lieu de la macro historique ; caméra centrée sur la bataille au lancement.

**Laissé en l'état, volontairement**
- Les cylindres provisoires utilisent chacun un matériau dynamique. Coût négligeable à 5 contre 5 ; les vrais modèles utiliseront des Material Instances. Pour les mesures de performance du jalon M8, tester avec les vrais maillages.

**Toujours pas testé** : aucune compilation (pas d'Unreal dans la session cloud).

---

## 18/10/2026 — Génération du projet Unreal (Claude Code, session cloud)

**Fait**
- Projet `BOTOL.uproject` créé pour UE 5.8, cibles Android et iOS, module C++ `BOTOL`.
- Réglages mobiles dans `Config/` : matériel Mobile et qualité Scalable, rendu forward + MSAA 4x, fonctions PC coupées (Nanite, Lumen, ombres virtuelles, ray tracing, distance fields, textures virtuelles, Substrate), paysage, plein écran, Vulkan + OpenGL ES 3.2 en secours (la clé s'appelle encore bBuildForES31), pas de joysticks virtuels.
- Code C++ :
  - `Game/BotolGameMode` : bataille de test, 5 unités par équipe si le niveau est vide ;
  - `Player/BotolCameraPawn` : caméra isométrique (perspective à champ étroit, ou orthographique au choix) ;
  - `Player/BotolPlayerController` : glisser pour déplacer la vue, pincer pour zoomer, tap pour sélectionner et donner un ordre ;
  - `Units/BotolUnit` : unité en NavWalking, cylindre provisoire coloré tant qu'aucun maillage n'est fourni ;
  - `Data/BotolFactionData`, `Data/BotolUnitData` : factions et unités pilotées par les données.

**Testé**
- Rien de compilé : la session cloud n'a pas Unreal Engine. Le code a été relu, mais la première compilation sur le PC reste à faire.

**Décisions de Liamor (18/10)**
- BOTOL est une application mobile : tout est conçu pour le mobile, en vue 3D isométrique comme les jeux de stratégie mobiles existants.

**Valeurs provisoires**
- Identifiant d'application `com.troisdecors.botol` : à confirmer avant toute publication.
- Paysage et temps réel : réglages par défaut.
- Toutes les statistiques d'unités sont des valeurs de test.

**Prochaine étape**
- Session 1 du `README.md` sur le PC : compiler, créer `L_TestBataille`, jouer dans l'éditeur, puis lancer sur le téléphone et noter les mesures ici.
