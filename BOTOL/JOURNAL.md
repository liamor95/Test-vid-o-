# Journal BOTOL

Entrée la plus récente en haut. Pour chaque session : ce qui a été fait, ce qui a été testé et où, les blocages, les décisions de Liamor, la prochaine étape.

---

## 18/10/2026 (suite) — Relecture du code, corrections (Claude Code, session cloud)

**Relecture automatique** (2 relecteurs sur 3 ont abouti ; la contre-vérification a été interrompue par une limite d'utilisation)
- Compilation : **aucune erreur bloquante trouvée**. Signatures moteur, includes, règles UHT, types double/float et BOM UTF-8 vérifiés.
- Comportement en jeu : plusieurs défauts, corrigés ci-dessous.

**Corrigé**
- Avec un NavMesh, une destination inaccessible est refusée au lieu d'envoyer l'unité en ligne droite à travers les obstacles.
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
- Réglages mobiles dans `Config/` : matériel Mobile et qualité Scalable, rendu forward + MSAA 4x, fonctions PC coupées (Nanite, Lumen, ombres virtuelles, ray tracing, distance fields, textures virtuelles, Substrate), paysage, plein écran, Vulkan + ES 3.1, pas de joysticks virtuels.
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
