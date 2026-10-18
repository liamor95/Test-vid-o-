# Journal BOTOL

Entrée la plus récente en haut. Pour chaque session : ce qui a été fait, ce qui a été testé et où, les blocages, les décisions de Liamor, la prochaine étape.

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
