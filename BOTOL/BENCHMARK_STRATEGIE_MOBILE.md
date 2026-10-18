# Benchmark stratégie mobile pour BOTOL

*Document de référence du 2026-10-18, établi à partir de cinq rapports de recherche et de leurs contre-vérifications. La mention « (non vérifié) » signale une affirmation que la contre-vérification n'a pu ni confirmer ni réfuter. « (déduction) » et « (estimation) » ont leur sens courant. Les recommandations sont des propositions et attendent la décision de Liamor. La méthode et ses trous sont décrits en section 7.*

## 1. Conclusion

Les jeux de stratégie mobiles qui marchent ne font presque jamais piloter les unités une par une. Il y a deux grandes manières de faire. Dans la première, le joueur pose ses unités dans une zone autorisée et l'IA les mène (Clash of Clans, Clash Royale, Boom Beach). Dans la seconde, il commande trois ou quatre escouades par « toucher l'escouade, toucher la destination », puis le combat se règle seul (Bad North, Iron Marines).

La caméra garde un angle fixe. On la déplace au doigt et on zoome en pinçant, dans des limites étroites. Les batailles durent 3 à 5 minutes, et les commandes qu'on touche souvent sont en bas de l'écran, sous les pouces. L'orientation dépend de la forme du terrain : paysage pour un champ large, portrait pour un couloir vertical qu'on voit en entier.

Pour BOTOL, je recommande donc le paysage, trois ou quatre escouades commandées au toucher, une caméra isométrique fixe et des batailles de 3 à 4 minutes. La caméra peut être orthographique au départ, comme dans le modèle Strategy d'UE 5.8. Il faut quand même la comparer à une perspective serrée, à cause du brouillard sous-marin.

Le risque le plus urgent est ailleurs. Google Play exige l'API 36 depuis le 31 août 2026 ([Android Developers](https://developer.android.com/google/play/requirements/target-sdk)), alors que la documentation d'UE 5.8 recommande encore le SDK 35 ([Epic](https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine)). C'est à tester dès M0.

## 2. Tableau comparatif

| Jeu | Studio | Orientation | Caméra | Contrôle des unités | Durée de bataille | Moteur |
|---|---|---|---|---|---|---|
| Clash of Clans (2012, actif) | Supercell | Paysage | Isométrique, angle fixe ; on glisse et on pince (sources tierces) | On pose les troupes depuis une barre, puis l'IA les mène ; sorts et héros comme leviers | 30 s de repérage + 3 min (attaque multijoueur du village principal ; d'autres modes ont d'autres formats) | Titan, moteur maison (non vérifié) |
| Boom Beach (2014, actif) | Supercell | Paysage | Isométrique, même aspect que Clash of Clans | Débarquement sur les plages, puis IA ; la fusée éclairante rassemble toute l'armée | 40 s de préparation + 4 min (non vérifié) | Titan (non vérifié) |
| Clash Royale (2016, actif) | Supercell | Portrait, à une main | Arène entière visible, sans déplacement (observation non sourcée) | Cartes posées sur sa moitié (zone élargie quand une tour adverse tombe), puis IA | 3 min + jusqu'à 2 min de prolongation | Titan (non vérifié) |
| Brawl Stars (2018, actif) | Supercell | Paysage depuis mars 2018, portrait avant | Vue plongeante, angle non sourcé | Un seul héros au joystick (hors du modèle de BOTOL) | Environ 3 min (non vérifié) | Titan (non vérifié) |
| Clash Mini (arrêté en 2024, non vérifié) | Supercell | Non sourcée | Combats en 3D, plusieurs angles pour les actions spéciales | Placement sur une grille, puis combat automatique | Moins de 5 min | Non sourcé |
| Rise of Kingdoms (2018, actif) | Lilith Games | Non sourcée | Zoom continu en pinçant, de la ville à la région puis au monde | Jusqu'à 5 marches, chacune menée par un commandant | Pas de partie : monde persistant | Non sourcé |
| Warpath (fin 2020) | Lilith Games | Non sourcée | Base et combat sur la même carte | Contrôle direct ou trajet automatique (non vérifié) | Non sourcée | Non sourcé |
| Age of Empires Mobile (2024) | TiMi Studio Group (Tencent) avec World's Edge | Non sourcée | Non sourcée | Jusqu'à 5 troupes menées par un héros ; contrôle direct facultatif, jeu très automatisé | Pas de partie : monde persistant | Non identifié |
| Command & Conquer: Rivals (2018, presque à l'abandon) | Redwood Studios (EA) | Portrait (source faible, non vérifié) | Carte entière à l'écran, grille d'hexagones | Contrôle direct total : on touche l'unité, puis la case ; deck de 6 (non vérifié) | 3 à 5 min, jamais plus de 10 | Non sourcé |
| Iron Marines (2017) et Invasion (2022) | Ironhide Game Studio | Non sourcée | Non sourcée | Contrôle direct de 3 unités et d'un héros au début ; on touche, puis on glisse | Sessions courtes, durée non chiffrée | Unity (non vérifié) |
| Whiteout Survival | Century Games | Portrait (non vérifié) | 3D à angle fixe (non vérifié) ; base à disposition fixe | On compose une équipe de héros, puis le combat est surtout automatique | Non chiffrée | Non trouvé |
| Last War: Survival (2023) | First Fun HK, puis FUNFLY | Portrait (non vérifié) | Non sourcée | Mini-jeu de couloir très simple et cœur 4X automatique (non vérifié) | Non chiffrée | Non trouvé |
| Kingshot (2025) | Century Games | Portrait (non vérifié) | Non sourcée | Gestion passive et défense de tours où le joueur intervient (une seule source) | Non chiffrée | Non trouvé |
| Bad North (sur mobile en 2019) | Plausible Concept (3 personnes) ; portage par Amber Studio | Non sourcée | 3D plongeante sur une petite île ; on la fait tourner et on zoome au doigt | Jusqu'à 4 escouades : on touche l'escouade, puis la case ; combat automatique ; ralenti à la sélection | « Courtes », non chiffrées | Unity probable (non vérifié) |
| Northgard mobile (2021) | Shiro Games (environ 60 personnes) ; portage par Playdigious | Non sourcée | Non sourcée pour le mobile | Gestion de colonie et unités (version PC) | Non sourcée | Heaps.io (Haxe), moteur maison |
| Kingdom Rush (de 2011 à KR6 en 2026) | Ironhide Game Studio | Non sourcée | 2D vue de haut, selon les souvenirs du chercheur (non vérifié) | Défense de tours et un héros qu'on déplace (non vérifié) | Non sourcée | Non sourcé |
| Rusted Warfare (de 2011 à iOS en 2020) | Corroding Games (très petite équipe) | Non sourcée | « Zoom stratégique » | RTS classique : base, nombreuses unités, sélection au cadre à deux doigts ou par appui long | Non sourcée | Non sourcé |

Les sources de chaque ligne sont regroupées par jeu dans la section 8. « Non sourcé » veut dire que la recherche n'a rien trouvé, pas que l'information n'existe pas. Aucune source ne donne l'angle exact de la caméra ni le type de projection, pour aucun des dix-sept jeux.

## 3. Ce qui converge, ce qui diverge

### Ce que presque tout le monde fait

**On donne peu d'ordres et l'IA fait le reste.** Dans Clash of Clans, une troupe posée ne reçoit plus aucun ordre ([ludusnovus](https://ludusnovus.net/2015/08/29/you-cant-control-clash-of-clans/)). Dans Clash Royale, elle avance seule vers les tours adverses ([Wikipedia](https://en.wikipedia.org/wiki/Clash_Royale)). Bad North passe pour un jeu de contrôle direct, mais il se résume à toucher l'escouade puis la case ; les soldats se battent seuls dès qu'un ennemi est à portée ([LadiesGamers](https://ladiesgamers.com/bad-north-jotunn-edition-review-nintendo-switch/)). Iron Marines, le plus proche d'un RTS sur PC, fonctionne pareil : l'unité rejoint le point visé et tire sur tout ce qui passe à portée ([Stately Play](https://statelyplay.com/2017/09/21/review-iron-marines/)).

Le nombre de groupes reste petit partout :

- jusqu'à 4 escouades dans Bad North ([Xbox Tavern](https://www.xboxtavern.com/bad-north-review)) ;
- 5 troupes dans Age of Empires Mobile ([App Store](https://apps.apple.com/us/app/6476261995/id6476261995)) ;
- 5 marches au plus dans Rise of Kingdoms ([site de fans](https://riseofkingdomsguides.com/rise-of-kingdoms-troop-capacity-and-march-queue-guide/)) ;
- 3 unités et un héros au début d'Iron Marines ([TouchArcade](https://toucharcade.com/2017/09/13/iron-marines-first-impressions-pretty-close-to-a-mobile-version-of-starcraft/)).

**On sait toujours si un toucher est permis.** Clash of Clans interdit de poser des troupes dans une zone rouge autour des bâtiments ([wiki de fans](https://clashofclans.fandom.com/wiki/Traps)). Boom Beach ne laisse débarquer que sur les plages ([Wikipedia](https://en.wikipedia.org/wiki/Boom_Beach)). Clash Royale limite la plupart des troupes à sa propre moitié de l'arène, mais la zone s'étend chez l'adversaire quand une de ses tours tombe. Quelques cartes, comme le Mineur, se posent partout ([wiki de fans](https://clashroyale.fandom.com/wiki/Miner) ; correction issue de la contre-vérification, non revérifiée en ligne). L'idée à retenir : la zone autorisée peut s'agrandir pendant la bataille et récompenser une percée.

**La caméra ne tourne pas, ou presque.** Clash of Clans et Boom Beach ont le même aspect isométrique ([BHS Blueprint](https://bhsblueprint.org/hall-of-fame/2015/01/12/app-review-boom-beach/)). Le zoom en pinçant et le déplacement au doigt n'y sont décrits que par des sources tierces ([forum Apple Developer](https://developer.apple.com/forums/thread/78904)). Rise of Kingdoms a consacré 90 jours à un zoom continu qui passe sans rupture de la ville au monde ([site officiel](https://rok.lilith.com/)). Whiteout Survival a une base à disposition fixe, ce qui évite de manipuler la caméra pour construire ([Naavik](https://naavik.co/deep-dives/four-x-evolution-2/)).

Seule exception notable : Bad North, où l'on fait tourner l'île parce que les ennemis arrivent de tous les côtés ([TouchArcade](https://toucharcade.com/?p=259983)). Apple recommande par ailleurs de déplacer la caméra en touchant directement l'écran plutôt qu'avec un stick virtuel ([Apple HIG](https://developer.apple.com/design/human-interface-guidelines/game-controls)).

**Les batailles sont courtes et ont une durée maximale.**

- Clash of Clans : 30 s de repérage puis 3 minutes ([LowEndMac, 2015](https://lowendmac.com/2015/introduction-to-clash-of-clans-part-6-doing-battle/), [Giant Bomb](https://www.giantbomb.com/games/3030-40108/)).
- Clash Royale : 3 minutes et jusqu'à 2 minutes de prolongation. L'élixir, la ressource qui paie les cartes, arrive deux puis trois fois plus vite en fin de partie ([support officiel](https://support.clashroyale.com/hc/en-us/articles/49484936933403-Elixir)).
- C&C Rivals : 3 à 4 minutes visées, environ 5 en pratique, jamais plus de 10 ([Gamecloud](https://gamecloud.net.au/features/opinion/why-command-conquer-rivals-is-actually-really-fun), [TechNave](https://technave.com/gadget/Command-and-Conquer-Rivals-review-A-surprisingly-fun-RTS-mobile-game-13392.html), [PhoneArena](https://www.phonearena.com/news/Command-and-Conquer-Rivals-review_id111518)).
- Clash Mini : moins de 5 minutes annoncées ([fiche de la boutique](https://www.apkmirror.com/apk/supercell/clash-mini/clash-mini-1-1143-2-release)).
- Boom Beach : 4 minutes après 40 s de préparation, avec un chronomètre qui ne démarre qu'au premier ordre ([wiki de fans](https://boombeach.fandom.com/wiki/Attacking), non vérifié).

**Ce qu'on touche souvent est en bas de l'écran.**

- Clash of Clans a sa barre de déploiement en bas. Depuis juin 2021, on peut en régler la taille et la passer sur deux rangées ([Supercell](https://supercell.com/en/games/clashofclans/blog/game-updates/quality-of-life-improvements-june21)).
- Boom Beach place les armes de la canonnière en bas à droite ([PocketGamer](https://www.pocketgamer.com/boom-beach/the-boom-beach-gunboat-guide-flares)).
- Clash Royale place la main de cartes en bas ([PocketGamer](https://www.pocketgamer.com/clash-royale/review/)).
- Age of Empires Mobile place son bouton de sélection multiple sur le bord gauche ([guide tiers](https://aoemobileguides.com/age-of-empires-mobile-auto-battle-guide/)).

**Une ressource empêche de marteler l'écran.** L'élixir de Clash Royale se recharge avec le temps et plafonne à 10 ([Wikipedia](https://en.wikipedia.org/wiki/Clash_Royale)). Dans Boom Beach, chaque arme de la canonnière coûte de l'énergie, et ce coût augmente à chaque usage dans la même bataille ([PocketGamer](https://www.pocketgamer.com/boom-beach/the-boom-beach-gunboat-guide-flares)). Dans les deux cas, chaque toucher compte.

**On ne trace pas de cadre de sélection au doigt.** Age of Empires Mobile réserve la sélection par rectangle au PC, avec Alt et un glissé ([guide tiers](https://www.magicgameworld.com/age-of-empires-mobile-pc-edition-controls-guide/)) ; ses gestes exacts sur mobile ne sont pas sourcés. Rusted Warfare propose un cadre tracé à deux doigts ou un cercle qui grandit par appui long ([DroidGamers](https://www.droidgamers.com/news/new-rts-game-for-android-rusted-warfare-has-a-lot-of-potential/)). Des joueurs s'en plaignent : le pincement sélectionne des unités au lieu de zoomer ([forum EA](https://forums.ea.com/discussions/command-and-conquer-franchise-en/suggestion-bring-red-alert-to-mobile-with-two-finger-box-select/13624253)).

### Les vrais choix

**Paysage ou portrait.** Clash of Clans et Boom Beach sont en paysage, héritage de la stratégie « tablette d'abord » de Supercell en 2012. Clash Royale a été conçu pour un téléphone tenu à la verticale, à une main ([PocketGamer.biz](https://www.pocketgamer.biz/comment-and-opinion/62882/how-portrait-mode-trumped-tablet-first-gaming/)). Brawl Stars est passé du portrait au paysage en mars 2018, pendant son lancement test, en même temps qu'il adoptait le joystick seul ([Newsweek](https://www.newsweek.com/entertainment/video-games/brawl-stars-update-landscape-controls-upgrade-system-new-mode-838786)). TouchArcade estimait alors que le jeu avait « besoin de beaucoup d'ajustements » pour bien fonctionner ainsi ([TouchArcade](https://toucharcade.com/2018/03/21/brawl-stars-landscape-balance-update-attempts-to-improve-long-range-brawlers/)).

Les jeux de gestion et de conquête (4X) les plus rentables du moment, Whiteout Survival, Last War et Kingshot, se jouent en portrait, mais aucune source lue ne le dit (non vérifié). C&C Rivals serait aussi en portrait, d'après une simple étiquette sur un site d'avis ([minireview](https://minireview.io/tower-rush/command-conquer-rivals-pvp), non vérifié). Pour les jeux de stratégie en temps réel (RTS) à contrôle direct, le paysage est probable, mais aucune source ne l'écrit.

La règle qui s'en dégage est plus étroite qu'on ne le croit (déduction). Le portrait convient pour poser des unités sur un terrain étroit et vertical, ou pour un combat presque automatique. Il convient mal pour sélectionner et déplacer des groupes sur un grand terrain.

**Commander ou laisser faire.** Les 4X à monde persistant automatisent beaucoup. C'est le premier reproche fait à Age of Empires Mobile : on clique sur « attaquer », on regarde, et le plus gros effectif gagne ([Digital Trends](https://digitaltrends.com/?p=3723459), [Gaming.net](https://www.gaming.net/reviews/age-of-empires-mobile-review-ios-android/)). Warpath se fait reprocher qu'au début, laisser les unités viser seules suffit ([Global Games Forum](https://globalgamesforum.com/features/warpath-is-a-mobile-throwback-to-military-rts-classics)). À l'inverse, EA vendait C&C Rivals sur un contrôle « à 100 % des unités à tout moment », contre le modèle « poser puis regarder » ([CGMagazine](https://www.cgmagonline.com/newswire/ea-announces-command-conquer-rivals-launches-worldwide-december-4)).

L'arrêt de Clash Mini, où le combat est entièrement automatique, laisse penser qu'une bonne préparation ne suffit pas. Mais son héritier dans Clash Royale, le mode Merge Tactics, a contribué à la bonne année 2025 du jeu sans offrir plus de contrôle en combat ([mobilegamer.biz](https://mobilegamer.biz/supercell-boss-laments-coasting-mobile-industry-as-clash-royale-stars-in-2025-results/)). C'est donc une hypothèse, pas une leçon.

**Caméra mobile ou arène entière.** Clash Royale et C&C Rivals montrent tout le terrain sans déplacer la caméra ([blackpawn](https://blackpawn.com/blog/2019/03/command-and-conquer-rivals/), [Wayward Strategy](https://waywardstrategy.com/2018/07/03/guest-post-callum-mccole-cc-rivals-first-impressions/)). Cela supprime tous les gestes de caméra pendant le combat, au prix d'une carte plus petite. Clash of Clans, Boom Beach et Bad North obligent à déplacer la vue et à zoomer.

**Faire tourner la vue.** Bad North le permet ; presque tous les autres, non. Tout dépend d'où viennent les attaques.

**Jeu payant ou gratuit.** Les 4X gratuits rapportent des sommes énormes : plus de 3,5 milliards de dollars dépensés par les joueurs de Rise of Kingdoms, selon une estimation brute de Sensor Tower, avant la commission des boutiques ([Pocket Gamer](https://pocketgamer.com/rise-of-kingdoms/3-5bn-milestone)). Chez les petites équipes, le jeu payant domine :

- Bad North coûte 3,99 $ sur iOS et 4,99 $ sur Android, sans achat intégré ([TouchArcade](https://toucharcade.com/2019/10/18/toucharcade-game-of-the-week-bad-north-jotunn-edition), [Droid Life](https://www.droid-life.com/?p=234705)) ;
- Iron Marines: Invasion coûte 4,99 $ ([Pocket Gamer](https://www.pocketgamer.com/iron-marines-invasion/sept-8/)) ;
- Rusted Warfare n'a pas de microtransactions ([App Store](https://apps.apple.com/app/id1514329124)) ;
- Kingdom Rush 6, sorti le 24 septembre 2026, coûte 6,99 $ sur mobile, avec des achats intégrés ([Pocket Gamer](https://www.pocketgamer.com/kingdom-rush-6-genesis/pre-registration-now-open/)).

**Solo ou joueur contre joueur.** Greg Black, designer de C&C Rivals, explique que le revenu par joueur ne couvrait pas les coûts : il aurait fallu beaucoup plus de joueurs et un coût d'acquisition plus bas ([interview](https://cncrivals.blogspot.com/2022/02/part-2-interview-with-lead-gameplay.html)). Le choix « solo contre une IA » de BOTOL évite ce piège précis. Même les jeux tournés vers le jeu en ligne gardent un mode contre l'IA. Clash Royale a son mode d'entraînement contre un bot ([support officiel](https://support.clashroyale.com/hc/en-us/articles/49484905512219-Training-Camp-Practice-Mode)), et Supercell a dû rendre ces bots meilleurs en octobre 2023 ([Supercell](https://supercell.com/en/games/clashroyale/blog/release-notes/app-store-update-october-23-2023)).

Une nuance sur la « 3D isométrique ». Clash of Clans et Clash Royale utiliseraient surtout des images 2D précalculées qui imitent la 3D (non vérifié). Les références les plus proches de ce que BOTOL fera en 3D temps réel sous UE5 sont donc plutôt Bad North, Brawl Stars ou Clash Mini.

## 4. Recommandations pour BOTOL

Rien ici n'est décidé. Aucune de ces propositions ne crée d'unité, de nom ou de règle officielle pour BOTOL.

### 4.1 Orientation : paysage

**Proposition à valider par Liamor : garder le paysage et le verrouiller.**

La boucle de BOTOL demande de commander les unités au toucher pendant la bataille. Tous les jeux étudiés qui font cela sur un terrain un peu large sont, selon toute probabilité, en paysage. Ceux qui sont en portrait montrent un couloir vertical en entier (Clash Royale, peut-être C&C Rivals) ou ont un combat surtout automatique (les 4X de Century Games et de FUNFLY).

Le paysage donne de la largeur pour voir plusieurs flancs. Il permet de tenir le téléphone à deux mains, avec les portraits d'escouades sous un pouce et les commandes spéciales sous l'autre, sans couvrir le terrain. Un terrain isométrique en losange remplit aussi mieux un écran large (déduction).

En échange, le paysage sacrifie le jeu à une main, dans les transports ou dans une file d'attente. C'est la raison pour laquelle Supercell a conçu Clash Royale en portrait ([PocketGamer.biz](https://www.pocketgamer.biz/comment-and-opinion/62882/how-portrait-mode-trumped-tablet-first-gaming/)). Il perd aussi la proximité naturelle avec les vidéos verticales des réseaux sociaux, un avantage plausible du portrait mais non démontré.

Le portrait, lui, sacrifierait la largeur du champ de bataille et la commande de groupes sur plusieurs flancs. Il aggraverait aussi le problème du doigt qui cache l'action, déjà signalé sur téléphone dans Iron Marines ([Steam](https://steamcommunity.com/app/931280/discussions/0/1679189548074169792/)).

Un cas ferait changer d'avis. Si Liamor décide que le terrain de bataille est un couloir étroit qu'on voit en entier, avec un affrontement d'un bout à l'autre, le portrait devient le meilleur choix. L'orientation doit donc être tranchée en même temps que la forme du terrain, et avant de produire l'interface. Brawl Stars a changé d'orientation tard, avec un rééquilibrage et une polémique à la clé ([TouchArcade](https://toucharcade.com/2018/03/21/brawl-stars-landscape-balance-update-attempts-to-improve-long-range-brawlers/)). Le moyen le moins cher de confirmer est une scène de combat en blocs gris, jouée sur un vrai téléphone dans les deux formats, au début de M2.

Deux contraintes de plateforme vont avec ce choix. Sous Android 16, pour une app qui cible l'API 36, le verrouillage d'orientation est ignoré sur les écrans dont le plus petit côté fait au moins 600 dp, sauf pour les apps déclarées comme jeux avec `android:appCategory` ([Android Developers](https://developer.android.com/about/versions/16/behavior-changes-16)). Et Apple demande que même un jeu verrouillé en paysage gère bien le redimensionnement ([Apple HIG](https://developer.apple.com/design/human-interface-guidelines/layout)).

### 4.2 Caméra

**Proposition à valider par Liamor.**

*Projection.* Partir de la caméra orthographique du modèle Strategy d'UE 5.8, puisque c'est le choix d'Epic pour une variante prévue pour le tactile ([code du modèle](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPawn.cpp)). Prévoir en M2 une comparaison, sur un vrai téléphone Android, avec une caméra en perspective à champ de vision étroit, montée sur un bras de caméra. Le critère qui doit trancher est le rendu sous-marin : brouillard, effets d'image et ombres. Epic documente des problèmes connus de l'orthographique : un décalage entre la position de la caméra et l'origine réelle de la vue, et un plan de découpe proche qui perturbe l'éclairage ([Epic](https://dev.epicgames.com/documentation/en-us/unreal-engine/orthographic-camera-in-unreal-engine)).

*Angle.* Fixe. Aucune source ne donne l'angle d'un seul jeu étudié. Le modèle Epic fait défiler la vue avec une rotation de -45° autour de l'axe vertical, inscrite en dur dans le code ([code](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPlayerController.cpp)). L'inclinaison, elle, est réglée dans un Blueprint qui n'a pas été lu. L'angle de BOTOL se choisira au test, selon un seul critère : les unités doivent rester lisibles au zoom le plus éloigné.

*Zoom.* Un zoom continu en pinçant, avec un minimum et un maximum, plutôt que des crans. Rise of Kingdoms montre l'intérêt d'un zoom fluide ([site officiel](https://rok.lilith.com/)). Les valeurs du modèle (largeur de vue de 1000 à 2500) sont un point de départ ([code](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPlayerController.h)). Le curseur de zoom du modèle peut rester comme alternative accessible. Pour une bataille courte dans une arène, rien ne justifie une vue « monde ».

*Rotation.* Aucune dans le prototype, par défaut. Si le terrain de BOTOL est attaqué de plusieurs côtés à la fois, la rotation devient nécessaire, comme dans Bad North. Elle pourrait alors passer par des pas de 90° sur des boutons, plus simples à rendre lisibles qu'une rotation libre (déduction).

*Limites et hauteur.* La caméra ne doit pas pouvoir sortir de la carte. Elle doit être assez haute pour que le doigt ne cache pas l'action. Aucun jeu étudié ne montre comment garder lisibles des unités à des profondeurs différentes : c'est un problème propre à BOTOL, à traiter en M2, par exemple avec un repère ou une ombre au sol sous chaque unité.

### 4.3 Gestes tactiles

**Proposition à valider par Liamor.**

| Geste | Effet proposé | D'où vient l'idée |
|---|---|---|
| Toucher une escouade ou son portrait | La sélectionne et remplace la sélection en cours ; le temps ralentit tant qu'aucun ordre n'est donné | Bad North : ralenti automatique dès la sélection, levé au premier ordre ([Windows Central](https://www.windowscentral.com/bad-north-xbox-one-windows-pc-review), [Xbox Tavern](https://www.xboxtavern.com/bad-north-review)) ; sélection par portrait dans Iron Marines ([Stately Play](https://statelyplay.com/2017/09/21/review-iron-marines/)) |
| Toucher le sol quand une escouade est sélectionnée | Ordre de déplacement, avec un repère au point visé qui reste visible autour du doigt | Bad North, Iron Marines, C&C Rivals |
| Toucher un ennemi | Ordre d'attaque ; le toucher « s'aimante » sur l'ennemi le plus proche dans un petit rayon | Iron Marines ([Hardlockup](https://hardlockup.wordpress.com/2017/09/20/iron-marines-review/)) ; dans Boom Beach, un toucher juste à côté de la cible envoie les troupes au mauvais endroit ([PocketGamer](https://www.pocketgamer.com/boom-beach/how-to-storm-the-shore-22-tips-for-beginner-boom-b/)) |
| Glisser un doigt sur le terrain | Déplace la caméra, au-delà d'un petit seuil de distance | Modèle Strategy d'UE 5.8, recommandation d'Apple |
| Pincer à deux doigts | Zoom continu, avec un minimum et un maximum | Rise of Kingdoms, Bad North |
| Toucher deux fois une escouade | Sélectionne toutes les escouades | Iron Marines (double toucher pour grouper, non vérifié) ; le modèle UE sélectionne tout ce qui est à l'écran |
| Toucher un bouton de capacité | Déclenche la capacité de l'escouade sélectionnée | Héros de Clash of Clans ([Clash Ninja](https://www.clash.ninja/guides/what-is-hero-equipment)) |
| Glisser une icône de la barre vers le terrain, ou la toucher puis toucher le terrain | Pose une unité, seulement si BOTOL garde une phase de déploiement pendant la bataille | Clash Royale ([PocketGamer](https://www.pocketgamer.com/clash-royale/review/)) ; le second geste n'est pas vérifié |
| Appui long sur une escouade | Affiche ses infos, sans donner d'ordre | Apple propose le double toucher et l'appui long comme variantes d'une même action ([Apple HIG](https://developer.apple.com/design/human-interface-guidelines/game-controls)) |

À exclure : la sélection par cadre, le tracé de chemin au doigt, et tout autre geste à deux doigts que le pincement. Point à corriger dans le modèle Epic : en 5.8, un toucher ajoute toujours l'unité à la sélection existante ([code](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPlayerController.cpp)). On ne peut donc pas remplacer une sélection par une autre au doigt.

### 4.4 Modèle de contrôle des unités

**Proposition à valider par Liamor.** Il y a trois options réalistes. Chacune coûte quelque chose à un développeur seul.

**A. Contrôle direct d'escouades, comme Bad North ou Iron Marines.** Le joueur commande trois ou quatre escouades, qui se battent seules à portée. C'est la lecture la plus littérale de « commander les unités au toucher ». Le modèle Strategy d'UE 5.8 fournit déjà la sélection, l'ordre de déplacement et la répartition des unités autour du point visé ([code](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyUnit.cpp)).

Ce que cette option sacrifie : du temps de développement et de test. Il faut écrire tout le comportement de combat, que le modèle ne contient pas. Il faut notamment que les unités attaquent en se déplaçant, faute de quoi elles « traversent les embuscades », comme dans Iron Marines: Invasion ([Common Sense Media](https://www.commonsensemedia.org/app-reviews/iron-marines-invasion)). Il faut aussi régler les cas limites de déplacement et gérer le doigt qui cache la vue. Enfin, l'équilibrage doit rendre le contrôle manuel vraiment payant, sinon on retombe dans le travers de Warpath.

**B. Déploiement puis IA, comme Clash of Clans ou Clash Royale.** Le joueur pose ses unités depuis une barre dans une zone autorisée. Chacune suit ensuite une règle de cible simple : le bâtiment le plus proche, les défenses d'abord, etc. ([wiki de fans](https://clashofclans.fandom.com/wiki/Barbarian)). Les gestes sont les plus simples possibles. L'adversaire peut être une base qui se défend seule, ce qui demande peu d'IA ennemie.

Ce que cette option sacrifie : la sensation de commander une fois l'unité posée. Tout repose alors sur la variété des unités et des terrains, donc sur beaucoup de contenu à produire seul (déduction). Et le risque du joueur qui regarde au lieu de jouer, reproché à Age of Empires Mobile, est réel.

**C. Ordre indirect par balise, comme la fusée éclairante de Boom Beach.** On combine un déploiement et un seul ordre de ralliement : toute l'armée marche vers le point touché sans attaquer en chemin, puis l'IA reprend la main ([PocketGamer](https://www.pocketgamer.com/boom-beach/the-boom-beach-gunboat-guide-flares)). L'ordre est payé avec une ressource dont le coût augmente à chaque usage. C'est un seul geste, sans sélection, et la ressource empêche de marteler l'écran.

Ce que cette option sacrifie : la tactique fine. Avec un seul levier, la profondeur risque d'être mince, et l'IA des unités doit tout faire le reste du temps.

**Recommandation : commencer par A, limité à trois escouades, en M2 et M3.** C est déjà un cas particulier de A : un ralliement revient à « tout sélectionner » puis « déplacer », ce que le modèle Epic sait déjà faire. Si le contrôle direct ne fonctionne pas bien sur téléphone, le repli vers C coûte peu. B reste le plan de secours si les deux échouent aux tests. La préparation des unités avant la bataille (choix et composition) est compatible avec les trois options.

### 4.5 Interface

**Proposition à valider par Liamor.** En paysage, le centre de l'écran reste au champ de bataille. Les portraits d'escouades vont en bas à gauche, comme le bouton de sélection d'Age of Empires Mobile. Les capacités et les ordres spéciaux vont en bas à droite, comme les armes de Boom Beach. En haut, on trouve le chronomètre et la condition de victoire, affichée en permanence, plus un coin pour la pause et les menus. Apple recommande justement les commandes fréquentes près des pouces et les menus en haut ([Apple HIG](https://developer.apple.com/design/human-interface-guidelines/game-controls)).

Toute l'interface va dans une zone de sécurité qui évite l'encoche, les bords arrondis et la barre d'accueil. Les commandes fréquentes doivent mesurer au moins 48 dp sur Android et 44 × 44 pt sur iOS ; les menus, au moins 28 × 28 pt ([Android](https://developer.android.com/guide/topics/ui/accessibility/apps), [Apple](https://developer.apple.com/design/human-interface-guidelines/accessibility)). Un réglage de taille de la barre, comme celui que Supercell a ajouté à Clash of Clans en 2021, coûte peu et couvre à la fois les téléphones et les tablettes. Une option pour inverser gauche et droite au profit des gauchers serait une simple proposition à évaluer.

Il faut tester sur le plus petit téléphone visé, pas sur une tablette. PocketGamer juge Northgard trop petit sur iPhone, même avec l'interface réglée au plus grand ([PocketGamer](https://www.pocketgamer.com/articles/086410/northgard-review/)).

### 4.6 Durée cible d'une bataille

**Proposition à valider par Liamor : 3 à 4 minutes de bataille, 5 minutes au maximum.** Un court temps d'observation d'environ 30 s précède la bataille, et le chronomètre ne démarre qu'au premier ordre, comme dans Boom Beach (non vérifié). Une seule condition de victoire simple et visible rend la partie lisible sur petit écran : dans Boom Beach, seule la destruction du quartier général fait gagner ([PocketGamer](https://www.pocketgamer.com/boom-beach/how-to-storm-the-shore-22-tips-for-beginner-boom-b/)). Je n'ai trouvé aucun chiffre sourcé sur la durée d'une boucle complète, de la préparation à la récompense.

## 5. Pièges à éviter

- **Automatiser au point que le joueur regarde.** C'est la critique numéro un d'Age of Empires Mobile ([Digital Trends](https://digitaltrends.com/?p=3723459)).
- **Laisser le ciblage automatique suffire pour gagner.** Si BOTOL automatise une partie du combat, le placement et les forces et faiblesses entre unités doivent rendre l'intervention du joueur nécessaire, ce que Warpath n'obtient pas au début ([Global Games Forum](https://globalgamesforum.com/features/warpath-is-a-mobile-throwback-to-military-rts-classics)).
- **Des unités qui n'attaquent pas en marchant.** C'est reproché à Iron Marines: Invasion ([Common Sense Media](https://www.commonsensemedia.org/app-reviews/iron-marines-invasion)). Il faut distinguer « se déplacer » de « se déplacer en attaquant », ou faire attaquer par défaut.
- **Le doigt qui cache l'action.** Un joueur le signale dans les niveaux difficiles d'Iron Marines sur téléphone ([Steam](https://steamcommunity.com/app/931280/discussions/0/1679189548074169792/)).
- **Le toucher qui tombe juste à côté de la cible.** Dans Boom Beach, un tir posé près d'une tourelle sans la toucher envoie les troupes au mauvais endroit ([PocketGamer](https://www.pocketgamer.com/boom-beach/how-to-storm-the-shore-22-tips-for-beginner-boom-b/)).
- **Une interface pensée pour la tablette.** Northgard sur iPhone le montre ([PocketGamer](https://www.pocketgamer.com/articles/086410/northgard-review/)).
- **Des gestes qui se marchent dessus.** Dans Rusted Warfare, le pincement sélectionne au lieu de zoomer ([forum EA](https://forums.ea.com/discussions/command-and-conquer-franchise-en/suggestion-bring-red-alert-to-mobile-with-two-finger-box-select/13624253)).
- **Changer d'orientation en cours de route.** Brawl Stars l'a payé ([TouchArcade](https://toucharcade.com/2018/03/21/brawl-stars-landscape-balance-update-attempts-to-improve-long-range-brawlers/)).
- **Renvoyer au début après un échec en fin de mission.** TouchArcade le reproche à Iron Marines ([TouchArcade](https://toucharcade.com/2017/09/15/iron-marines-review-starcraft-for-mobile/)). Avec des batailles de 3 à 4 minutes, c'est moins grave, mais il faut y penser si les missions s'allongent.
- **Dépendre d'une foule de joueurs.** C&C Rivals avait besoin de beaucoup de monde en ligne pour tenir ([Greg Black](https://cncrivals.blogspot.com/2022/02/part-2-interview-with-lead-gameplay.html)). Selon mobilegamer.biz, le jeu tourne aujourd'hui « en pilote automatique » ([mobilegamer.biz](https://mobilegamer.biz/fans-were-so-unhappy-with-command-and-conquer-rivals-that-ea-quickly-remastered-the-original-and-then-released-its-source-code/)).
- **Des publicités qui montrent un autre jeu.** Les pubs de Last War mettent en avant un mini-jeu et ne montrent jamais la construction de la ville, qui occupe pourtant le plus de temps de jeu ([MAF](https://maf.ad/en/blog/last-war-survival/), [FoxData](https://foxdata.com/en/blogs/how-last-war-survival-raked-in-16-billion-in-a-mere-18-months/)). Le régulateur publicitaire britannique aurait déjà sanctionné Playrix pour des publicités trompeuses ([Segwise](https://segwise.ai/blog/fake-ads-and-mobile-gaming-how-studios-balance-clickbait-gameplay-integrity-and-profitability-cm7j2hc9s00bvip0l0r4k59lw.md), non vérifié).
- **Des chargements longs sur les Android modestes.** Supercell aurait ramené ceux de Brawl Stars de 35 s à 5 ou 6 s, parce qu'ils raccourcissaient les sessions ([Supercell](https://supercell.com/en/news/titan-game-engine/), non vérifié).

Côté moteur, trois pièges reviennent en section 6. Le modèle Epic ne doit pas être gardé tel quel. Il ne faut pas compter sur le pincement natif d'Enhanced Input en 5.8. Et il ne faut pas copier la configuration de Cropout, l'exemple de jeu de stratégie publié par Epic.

## 6. Mise en œuvre dans UE 5.8

**Réserves de version.** UE 5.8 est sorti le 17 juin 2026 ([notes de version](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-8-release-notes), [WN Hub](https://wnhub.io/news/engines/item-51157)). Epic la présente comme la dernière version majeure prévue d'UE5, une 5.9 restant possible. UE6 est annoncé en accès anticipé pour fin 2027, selon la presse ([Inven Global](https://labs.invenglobal.com/articles/22900/unreal-engine-6-to-feature-fundamental-overhaul-targeting-early-access-release-by-late-2027)) : une migration est donc à prévoir vers 2028.

Le modèle Strategy a été lu dans des copies publiques sur GitHub, pas dans le dépôt d'Epic. La version 5.8 a été recoupée sur deux dépôts indépendants. Les Blueprints, et donc l'inclinaison de la caméra, n'ont pas pu être lus. Un correctif 5.8.x peut changer tout ce qui suit.

### M0 : création du projet et réglages de plateforme

Créer le projet depuis le modèle Top Down en C++, variante Strategy. Cette variante existe depuis la 5.6 ([Epic](https://www.unrealengine.com/en-US/news/updated-game-templates-for-unreal-engine-5-6available-now)). Elle contient :

- une caméra orthographique montée sur un pion qui glisse sur un plan horizontal ;
- un contrôleur qui gère à la fois la souris et le tactile ;
- des unités de type `ACharacter` pilotées par un `AAIController`, qui se déplacent sur un maillage de navigation (navmesh) et se répartissent autour du point visé grâce à des requêtes EQS (nouveau en 5.8) ;
- un widget de commandes mobiles placé dans une zone de sécurité ([code](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPlayerController.cpp), [second dépôt](https://github.com/Rumsse/beavers-game/blob/main/Source/Beavers/Variant_Strategy/StrategyPlayerController.cpp)).

Attention : Epic décrit cette variante comme fondée sur un « déplacement sur grille » ([Epic](https://www.unrealengine.com/en-US/news/updated-game-templates-for-unreal-engine-5-6available-now)), mais le code n'a aucune grille. Il n'y a pas non plus de combat, de brouillard de guerre ni de mini-carte. S'il en faut, il faudra les construire.

**Android.**

- Orientation `SensorLandscape`, comme dans l'exemple Unreal de Google ([TrivialKart](https://github.com/android/games-samples/blob/main/trivialkart/trivialkart_unreal/Config/DefaultEngine.ini)).
- Déclarer l'app comme jeu avec `android:appCategory="game"`, via les « Extra Tags for <application> » ([Epic](https://dev.epicgames.com/documentation/en-us/unreal-engine/how-to-use-android-manifest-control-in-unreal-engine-projects)), puis vérifier que l'attribut figure bien dans le manifeste généré.
- Activer `bUseDisplayCutout`.

**iOS.** Accepter les deux sens du paysage et refuser le portrait. Les noms de clés ont été relevés dans des configurations anciennes et sont à vérifier dans les réglages du projet en 5.8 ([exemple de configuration](https://github.com/Tencent/sluaunreal/blob/HEAD/Config/DefaultEngine.ini)). `UIRequiresFullScreen` est déprécié depuis iOS et iPadOS 26 ([Apple](https://developer.apple.com/documentation/bundleresources/information-property-list/uirequiresfullscreen)).

**Conformité Google Play, le point bloquant.**

- Google Play impose l'API 36 aux nouvelles apps et aux mises à jour depuis le 31 août 2026, avec une prolongation possible jusqu'au 1er novembre 2026 ([Android Developers](https://developer.android.com/google/play/requirements/target-sdk)). La page d'Epic pour UE 5.8 recommande encore le SDK 35 (NDK r27c, compilation minimale en SDK 34, installation minimale en SDK 26) ([Epic](https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine)). Il faut faire un build de test en API 36 dès M0 et suivre les correctifs 5.8.x.
- Les pages mémoire de 16 Ko sont prises en charge à partir d'UE 5.6. Google refusera les mises à jour sans cette prise en charge après le 1er février 2027 ([Android Developers](https://developer.android.com/guide/practices/page-sizes), [Unreal sur Android](https://developer.android.com/games/engines/unreal/unreal-on-android)).
- Sous Android 16, pour une app en API 36, le geste retour ne passe plus par `onBackPressed` ni par `KEYCODE_BACK` ([Android 16](https://developer.android.com/about/versions/16/behavior-changes-16)) : il faut tester les menus.
- Unreal utilise Vulkan par défaut et se replie sur OpenGL ES 3.2 ([Android Developers](https://developer.android.com/games/engines/unreal/unreal-on-android)).

**Mise à l'échelle de l'interface.** Régler la mise à l'échelle sur le plus petit côté de l'écran, avec une référence à 1080 px, comme dans Cropout ([configuration](https://github.com/ellie-me/vcs-demo-unreal/blob/master/Config/DefaultEngine.ini), [Epic](https://www.unrealengine.com/en-US/blog/cropout-casual-rts-game-sample-project)). Ne pas copier le reste de cette configuration : la copie lue cible le SDK 31 et autorise le portrait.

### M2 : caméra et tactile

**Caméra.** Garder la caméra orthographique du modèle : largeur de vue de 1500 au départ, zoom entre 1000 et 2500 ([code](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPawn.cpp)). Tester le réglage « Update Ortho Planes », qu'Epic présente comme le moyen d'éviter des problèmes de découpe et d'éclairage alors que le modèle le désactive, ainsi que les variables `r.Ortho.*` ([Epic](https://dev.epicgames.com/documentation/en-us/unreal-engine/orthographic-camera-in-unreal-engine)). Faire ces essais avec le brouillard sous-marin, puis comparer avec une perspective serrée. Les toits du niveau d'exemple utilisent un matériau qui laisse voir derrière eux ([Epic](https://dev.epicgames.com/documentation/unreal-engine/top-down-template-in-unreal-engine)) ; c'est une piste utile pour un décor sous-marin dense.

**Pincement.** Le modèle n'en a pas : le zoom tactile passe par un curseur, et le second doigt sert à tracer le cadre de sélection ([widget](https://github.com/jakemartin/stratocracy/blob/master/Content/Variant_Strategy/UI/WBP_StrategyMobileControls.uasset), [contexte d'entrée](https://github.com/jakemartin/stratocracy/blob/master/Content/Variant_Strategy/Input/IMC_Strategy_Touch.uasset)). Il faut calculer le pincement soi-même, à partir de l'écart entre les deux doigts. Le geste de pincement natif d'Enhanced Input a une régression en 5.8 : l'action reste active après qu'on a relâché les doigts (bug UE-392736, signalé en août 2026, aucun correctif trouvé) ([Epic Issues](https://issues.unrealengine.com/issue/UE-392736), [forum](https://forums.unrealengine.com/t/enhanced-input-gesture-keys-pinch-rotate-flick-never-release-after-touch-ends-regression-in-5-8/2745006)).

**Déplacement de la vue.** Dans le modèle, le défilement démarre après 0,15 s d'appui. Il n'a aucune limite de carte, et un garde-fou de 0,1 s évite qu'un toucher en fin de glissé devienne un ordre ([code](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPlayerController.cpp)). Il faut ajouter un seuil de distance, des limites de carte et une légère inertie. En 5.6 et 5.7, Epic détectait déjà le toucher simple et le double toucher à la main, parce que les déclencheurs d'Enhanced Input « fonctionnent différemment » en tactile ([code 5.7](https://github.com/977908569/GameUpdate/blob/main/Source/GameUpdate/Variant_Strategy/StrategyPlayerController.cpp)). Garder cette approche, avec des seuils réglables.

**Sélection et ralenti.** Remplacer la sélection additive du modèle. Le ralenti au moment de la sélection passe par `SetGlobalTimeDilation` ([Epic](https://dev.epicgames.com/documentation/unreal-engine/BlueprintAPI/Utilities/Time/SetGlobalTimeDilation)). D'après la communauté, les animations d'interface UMG n'y sont pas soumises ([forum](https://answers.unrealengine.com/questions/544659/view.html)). Les calculs faits à chaque image doivent utiliser le temps écoulé depuis l'image précédente.

**Interface.** Tout mettre dans des zones de sécurité, avec les tailles minimales de la section 4.5. Tester l'affichage bord à bord sur Android 16 et l'option développeur qui simule une encoche. Pour le SDK 35, le mode d'encoche « ALWAYS » est le seul autorisé, et la sensibilité au toucher peut être plus faible dans la zone de l'encoche ([Android Developers](https://developer.android.com/develop/ui/views/layout/display-cutout)).

**Mesures.** Dès le premier build Android, noter `stat unit` et `stat unitmax`. La console s'ouvre par un toucher à quatre doigts ([Android Developers](https://developer.android.com/games/engines/unreal/unreal-memory-usage)).

### M3 : combat

**Unités.** Garder des unités de type `ACharacter` avec un `AAIController`, comme dans le modèle, et fixer l'effectif en le mesurant sur l'appareil Android le plus faible visé. Aucun chiffre sourcé n'existe. Remplacer tout de suite deux appels coûteux du modèle : le « tout sélectionner » qui passe par `GetAllActorsOfClass`, et le recalcul de la sélection par cadre à chaque image dans le HUD ([HUD](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/UI/StrategyHUD.cpp)). Le cadre et le texte « Selected » sont dessinés directement sur l'écran sans tenir compte de la densité de pixels : mieux vaut un repère au sol ou de l'UMG.

**Modèles 3D.** Sur mobile, un maillage animé est limité par défaut à 75 os par section. Ce plafond est réglable par plateforme, et la commande `SkeletalMeshReport` permet de vérifier les modèles ([Epic](https://dev.epicgames.com/documentation/en-us/unreal-engine/skeletal-mesh-rendering-paths-in-unreal-engine)). Prévoir des niveaux de détail dès la création des modèles, et des maillages instanciés pour le décor répété (proposition).

### M4 : IA adverse et boucle complète (libellé à confirmer)

Les rapports ne donnent pas le contenu exact de M4. Je range ici ce qui suit logiquement le combat : l'IA adverse, l'écran de résultat et le retour à la préparation. À recaler sur le vrai périmètre du jalon.

Le choix d'architecture de l'IA (StateTree ou Behavior Tree, avec des requêtes EQS) n'est pas sourcé par ce benchmark. StateTree serait déjà activé dans une copie 5.8 du modèle ([uproject](https://github.com/jakemartin/stratocracy/blob/master/Stratocracy.uproject)). Un précédent compte : Supercell a dû rendre ses bots de Clash Royale plus combatifs pour que le mode solo garde de l'intérêt ([Supercell](https://supercell.com/en/games/clashroyale/blog/release-notes/app-store-update-october-23-2023)).

### M8 : performances

**Profils d'appareils.** Définir trois profils Android (bas, moyen, haut) qui jouent sur la résolution de rendu (`r.MobileContentScaleFactor`, par exemple 0,8 et 1,0), les groupes de qualité `sg.*`, les ombres et la distance de vue. C'est ce que fait la copie de Cropout ([profils](https://github.com/ellie-me/vcs-demo-unreal/blob/master/Config/DefaultDeviceProfiles.ini)). Ajouter une réserve de textures adaptée à la mémoire de l'appareil et la compression ASTC ([Android Developers](https://developer.android.com/games/engines/unreal/unreal-reduce-memory)).

**Chaleur du téléphone.** Le plugin ADPF de Google abaisse la qualité graphique quand le téléphone chauffe. Son dépôt est archivé depuis le 19 juin 2026, et sa compatibilité avec la 5.8 n'est pas confirmée ([Android Developers](https://developer.android.com/games/engines/unreal/unreal-adpf), [GitHub](https://github.com/android/adpf-unreal-plugin)).

**Grands effectifs.** Ne passer à l'animation précalculée dans des textures (plugin AnimToTexture, [démo](https://github.com/leejeonghun/AnimToTextureDemo)) ou à Mass que si le profilage montre que le coût de chaque unité est le vrai frein. Mass reste qualifié d'expérimental et change souvent ([MassSample](https://github.com/Megafunk/MassSample)). Une refonte est évoquée pour la 5.8 sur le forum d'Epic ([forum](https://forums.unrealengine.com/t/mass-entity-5-8-preview/2733180)), mais son statut officiel n'a pas été trouvé. C'est un risque pour un développeur seul.

**Mesure.** Utiliser Unreal Insights avec les canaux `default,counters`, Perfetto pour la mémoire réellement occupée (la mémoire anonyme plus la mémoire d'échange, critique pour la stabilité) ([Android Developers](https://developer.android.com/games/engines/unreal/unreal-memory-usage)), et Android GPU Inspector pour le rendu ([Android Developers](https://developer.android.com/games/engines/engines-overview)). Se fixer aussi un budget de temps de chargement.

**Précédent.** Même un jeu aussi dépouillé que Bad North a demandé un vrai travail mobile. Amber Studio a dû augmenter la fréquence d'images et simplifier les shaders, avec deux ingénieurs plus un troisième pour les performances ([Amber](https://amberstudio.com/work_post/bad-north)).

## 7. Limites du benchmark

**Méthode.** Les recherches ont été très gênées. La lecture directe des pages (WebFetch) a échoué presque partout, et le quota de recherches web, partagé entre les agents, s'est épuisé en cours de route. La plupart des faits viennent donc d'extraits renvoyés par le moteur de recherche, pas de pages lues en entier.

Pour trois segments sur cinq (Supercell, RTS à contrôle direct, 4X en portrait), la contre-vérification n'a pu faire aucune recherche. Elle s'est appuyée sur des connaissances arrêtées à juin 2026, d'où le grand nombre de « (non vérifié) ». Le segment des petites équipes a été contre-vérifié en ligne. Pour le segment technique, le code du modèle Epic et les pages de Google et d'Apple ont été lus directement, mais la documentation Epic n'a été vue qu'à travers des extraits.

**Ce qui reste non vérifié.**

- L'orientation de la plupart des jeux, à contrôler sur les captures des boutiques.
- L'angle et la projection de la caméra, pour tous les jeux.
- Le moteur de la plupart des jeux. Un fichier d'installation Android se vérifie en regardant ses bibliothèques : `libunity.so` signe Unity, `libUnreal.so` signe Unreal.
- La disposition précise des interfaces.
- Les durées de Boom Beach.
- Les nouveautés Supercell de 2026 : la refonte de l'interface de Clash of Clans annoncée en octobre, et les « Squad Leaders » de Boom Beach en mars ([Supercell](https://boombeach.supercell.com/en/news/blog/march-major-update/)). Ces derniers pourraient contredire le constat selon lequel Supercell ne fait jamais commander d'unités une par une.
- Le statut de Clash Mini et de Squad Busters.
- Les revenus, qui sont des estimations de cabinets d'analyse. Certains classements relayés par la presse risquent de confondre le classement mondial avec celui des seuls jeux chinois hors de Chine.
- Côté UE 5.8 : la prise en charge de l'API 36, l'ajout automatique de `appCategory`, la connexion d'Unreal Insights à un téléphone Android, le statut de Mass et la compatibilité d'ADPF.

**Segments et sujets manquants.** Les cinq segments ont donné des résultats (segments sans résultat : aucun). Plusieurs pistes n'ont pas été explorées :

- Top War ;
- les adaptations tactiles de vrais RTS en 3D (Company of Heroes, Total War) ;
- Warcraft Rumble, dont le statut est à vérifier ;
- Call of Dragons et Lords Mobile ;
- Sea of Conquest, un 4X naval proche du thème marin ;
- des jeux de très petites équipes : Galcon 2, d'un développeur seul ([Wikipedia](https://en.wikipedia.org/wiki/Galcon_2)), Mushroom Wars 2 ([Wikipedia](https://en.wikipedia.org/wiki/Mushroom_Wars_2)) et Mindustry ([Wikipedia](https://en.wikipedia.org/wiki/Mindustry)) ;
- des jeux au tour par tour en vue isométrique, en guise de repli si le temps réel s'avère trop coûteux au toucher.

Aucun jeu de stratégie mobile sous Unreal n'a été cherché sérieusement. Le seul cas proche trouvé, TINY METAL, est au tour par tour, sous UE4, et n'est sorti que sur PC et consoles ([Epic](https://www.unrealengine.com/developer-interviews/exploring-the-tactics-behind-tiny-metal)).

D'autres sujets ne sont pas traités :

- la lisibilité d'unités placées à des profondeurs différentes, propre à BOTOL ;
- la conception de l'IA adverse ;
- les effets réellement disponibles dans le rendu mobile d'Unreal (brouillard, effets d'image) ;
- des données de durée de session ;
- des données de marché sur la stratégie mobile payante.

**Petites équipes.** Le segment mélange de vraies micro-équipes (Bad North, Rusted Warfare) et des studios moyens : Shiro Games comptait environ 60 personnes en 2022 ([Cathay Capital](https://www.cathaycapital.com/shiro-games-welcomes-cathay-capital-hints-at-two-new-projects/)), et Ironhide environ 50, selon des annuaires non officiels ([Coresignal](https://coresignal.com/discover/gaming/uruguay/)). Leurs leçons ne s'appliquent pas toutes à un développeur seul.

## 8. Sources

**Supercell : Clash of Clans, Boom Beach, Clash Royale, Brawl Stars, Clash Mini**
- [PocketGamer.biz : portrait contre tablette d'abord](https://www.pocketgamer.biz/comment-and-opinion/62882/how-portrait-mode-trumped-tablet-first-gaming/)
- [Supercell : améliorations de juin 2021 (Clash of Clans)](https://supercell.com/en/games/clashofclans/blog/game-updates/quality-of-life-improvements-june21)
- [LowEndMac : bataille dans Clash of Clans (2015)](https://lowendmac.com/2015/introduction-to-clash-of-clans-part-6-doing-battle/)
- [Giant Bomb : Clash of Clans](https://www.giantbomb.com/games/3030-40108/)
- [ludusnovus : You can't control Clash of Clans](https://ludusnovus.net/2015/08/29/you-cant-control-clash-of-clans/)
- [Wiki Clash of Clans : pièges et zone rouge](https://clashofclans.fandom.com/wiki/Traps)
- [Wiki Clash of Clans : Barbare](https://clashofclans.fandom.com/wiki/Barbarian)
- [Clash Ninja : équipements de héros](https://www.clash.ninja/guides/what-is-hero-equipment)
- [Supercell : le moteur Titan](https://supercell.com/en/news/game-engine-called-titan/)
- [Supercell : Titan et le chargement de Brawl Stars](https://supercell.com/en/news/titan-game-engine/)
- [BHS Blueprint : critique de Boom Beach](https://bhsblueprint.org/hall-of-fame/2015/01/12/app-review-boom-beach/)
- [Forum Apple Developer : zoom façon Clash of Clans](https://developer.apple.com/forums/thread/78904)
- [Wikipedia : Boom Beach](https://en.wikipedia.org/wiki/Boom_Beach)
- [PocketGamer : guide des fusées éclairantes de Boom Beach](https://www.pocketgamer.com/boom-beach/the-boom-beach-gunboat-guide-flares)
- [PocketGamer : 22 conseils pour Boom Beach](https://www.pocketgamer.com/boom-beach/how-to-storm-the-shore-22-tips-for-beginner-boom-b/)
- [Wiki Boom Beach : attaquer](https://boombeach.fandom.com/wiki/Attacking)
- [Supercell : mise à jour de Boom Beach de mars 2026](https://boombeach.supercell.com/en/news/blog/march-major-update/)
- [Wikipedia : Clash Royale](https://en.wikipedia.org/wiki/Clash_Royale)
- [Support Clash Royale : élixir](https://support.clashroyale.com/hc/en-us/articles/49484936933403-Elixir)
- [Support Clash Royale : mode d'entraînement](https://support.clashroyale.com/hc/en-us/articles/49484905512219-Training-Camp-Practice-Mode)
- [Supercell : bots de Clash Royale (octobre 2023)](https://supercell.com/en/games/clashroyale/blog/release-notes/app-store-update-october-23-2023)
- [PocketGamer : critique de Clash Royale](https://www.pocketgamer.com/clash-royale/review/)
- [Wiki Clash Royale : Mineur](https://clashroyale.fandom.com/wiki/Miner)
- [mobilegamer.biz : Clash Royale en 2025, Merge Tactics](https://mobilegamer.biz/supercell-boss-laments-coasting-mobile-industry-as-clash-royale-stars-in-2025-results/)
- [Newsweek : Brawl Stars passe au paysage](https://www.newsweek.com/entertainment/video-games/brawl-stars-update-landscape-controls-upgrade-system-new-mode-838786)
- [TouchArcade : Brawl Stars en paysage](https://toucharcade.com/2018/03/21/brawl-stars-landscape-balance-update-attempts-to-improve-long-range-brawlers/)
- [Game World Observer : arrêt de Clash Mini](https://gameworldobserver.com/2024/03/15/clash-mini-shutdown-supercell-no-new-games-in-five-years)
- [APKMirror : fiche de Clash Mini](https://www.apkmirror.com/apk/supercell/clash-mini/clash-mini-1-1143-2-release)

**RTS mobiles à contrôle direct : Rise of Kingdoms, Warpath, Age of Empires Mobile, C&C Rivals, Iron Marines**
- [Rise of Kingdoms : site officiel](https://rok.lilith.com/)
- [Guide de fans : file de marches de Rise of Kingdoms](https://riseofkingdomsguides.com/rise-of-kingdoms-troop-capacity-and-march-queue-guide/)
- [Pocket Gamer : Rise of Kingdoms à 3,5 milliards de dollars](https://pocketgamer.com/rise-of-kingdoms/3-5bn-milestone)
- [Pocket Tactics : Warpath sur iOS](https://www.pockettactics.com/warpath/ios)
- [player.one : contrôle dans Warpath](https://www.player.one/warpath-mobile-139527)
- [BlueStacks : guide de Warpath pour débutants](https://www.bluestacks.com/blog/game-guides/warpath/wp-beginners-guide-en.html)
- [Global Games Forum : Warpath](https://globalgamesforum.com/features/warpath-is-a-mobile-throwback-to-military-rts-classics)
- [Age of Empires : lancement mondial du jeu mobile](https://www.ageofempires.com/news/a-brand-new-take-on-a-strategy-classic-age-of-empires-mobile-launches-worldwide/)
- [App Store : Age of Empires Mobile](https://apps.apple.com/us/app/6476261995/id6476261995)
- [Pocket Tactics : interview sur Age of Empires Mobile](https://www.pockettactics.com/age-of-empires-mobile/interview)
- [Guide tiers : sélection multiple dans Age of Empires Mobile](https://aoemobileguides.com/age-of-empires-mobile-auto-battle-guide/)
- [Guide tiers : commandes PC d'Age of Empires Mobile](https://www.magicgameworld.com/age-of-empires-mobile-pc-edition-controls-guide/)
- [Digital Trends : critique d'Age of Empires Mobile](https://digitaltrends.com/?p=3723459)
- [Gaming.net : critique d'Age of Empires Mobile](https://www.gaming.net/reviews/age-of-empires-mobile-review-ios-android/)
- [CGMagazine : lancement de C&C Rivals](https://www.cgmagonline.com/newswire/ea-announces-command-conquer-rivals-launches-worldwide-december-4)
- [Interview de Greg Black (C&C Rivals)](https://cncrivals.blogspot.com/2022/02/part-2-interview-with-lead-gameplay.html)
- [mobilegamer.biz : C&C Rivals](https://mobilegamer.biz/fans-were-so-unhappy-with-command-and-conquer-rivals-that-ea-quickly-remastered-the-original-and-then-released-its-source-code/)
- [PhoneArena : critique de C&C Rivals](https://www.phonearena.com/news/Command-and-Conquer-Rivals-review_id111518)
- [Gamecloud : C&C Rivals](https://gamecloud.net.au/features/opinion/why-command-conquer-rivals-is-actually-really-fun)
- [TechNave : critique de C&C Rivals](https://technave.com/gadget/Command-and-Conquer-Rivals-review-A-surprisingly-fun-RTS-mobile-game-13392.html)
- [blackpawn : C&C Rivals](https://blackpawn.com/blog/2019/03/command-and-conquer-rivals/)
- [Wayward Strategy : premières impressions sur C&C Rivals](https://waywardstrategy.com/2018/07/03/guest-post-callum-mccole-cc-rivals-first-impressions/)
- [minireview : fiche de C&C Rivals](https://minireview.io/tower-rush/command-conquer-rivals-pvp)
- [TouchArcade : premières impressions sur Iron Marines](https://toucharcade.com/2017/09/13/iron-marines-first-impressions-pretty-close-to-a-mobile-version-of-starcraft/)
- [TouchArcade : critique d'Iron Marines](https://toucharcade.com/2017/09/15/iron-marines-review-starcraft-for-mobile/)
- [Hardlockup : critique d'Iron Marines](https://hardlockup.wordpress.com/2017/09/20/iron-marines-review/)
- [Stately Play : critique d'Iron Marines](https://statelyplay.com/2017/09/21/review-iron-marines/)
- [Steam : discussion sur les contrôles d'Iron Marines](https://steamcommunity.com/app/931280/discussions/0/1679189548074169792/)
- [Common Sense Media : Iron Marines Invasion](https://www.commonsensemedia.org/app-reviews/iron-marines-invasion)
- [Pocket Gamer : sortie d'Iron Marines Invasion](https://www.pocketgamer.com/iron-marines-invasion/sept-8/)
- [TouchArcade : annonce d'Iron Marines Invasion (juin 2022)](https://toucharcade.com/2022/06/02/iron-marines-invasion-mobile-release-date-rts-preorder-ios-preregister-google-play-ironhide/)
- [Wikipedia : Iron Marines](https://en.wikipedia.org/wiki/Iron_Marines)
- [El Observador : Ironhide et Iron Marines](https://www.elobservador.com.uy/nota/iron-marines-uruguayos-defensores-de-la-galaxia-2017917500)
- [WN Hub : Ironhide et l'adaptation des contrôles](https://wnhub.io/news/other/item-14983)
- [Coresignal : effectif d'Ironhide (estimation)](https://coresignal.com/discover/gaming/uruguay/)

**4X mobiles en portrait : Whiteout Survival, Last War, Kingshot**
- [Naavik : l'évolution des 4X](https://naavik.co/deep-dives/four-x-evolution-2/)
- [App Store : Whiteout Survival](https://apps.apple.com/FR/app/id6443575749)
- [Sensor Tower : classement de mars 2025](https://sensortower.com/blog/top-10-worldwide-mobile-games-by-revenue-and-downloads-in-march-2025)
- [Wikipedia : Last War: Survival](https://en.wikipedia.org/wiki/Last_War:_Survival_Game)
- [Sensor Tower : classement de juillet 2025](https://sensortower.com/blog/top-10-worldwide-mobile-games-by-revenue-and-downloads-in-july-2025)
- [MAF : publicités de Last War](https://maf.ad/en/blog/last-war-survival/)
- [FoxData : Last War](https://foxdata.com/en/blogs/how-last-war-survival-raked-in-16-billion-in-a-mere-18-months/)
- [Segwise : publicités trompeuses](https://segwise.ai/blog/fake-ads-and-mobile-gaming-how-studios-balance-clickbait-gameplay-integrity-and-profitability-cm7j2hc9s00bvip0l0r4k59lw.md)
- [Outlook Respawn : Kingshot](https://respawn.outlookindia.com/gaming/gaming-news/century-games-kingshot-hits-500m-revenue-in-2025)
- [Appfigures : Kingshot](https://app.appfigures.com/resources/insights/kingshot-500m-revenue-century-games)
- [Gamigion : panorama des 4X](https://www.gamigion.com/4x/)

**Petites équipes : Bad North, Northgard, Kingdom Rush, Rusted Warfare**
- [Bad North : équipe](https://badnorth.com/team)
- [Nintendo UK : interview sur Bad North](https://www.nintendo.co.uk/News/2018/April/Interview-Taking-on-hordes-of-invading-Vikings-in-Bad-North-1368315.html)
- [Amber Studio : portage de Bad North](https://amberstudio.com/work_post/bad-north)
- [PocketGamer.biz : Plausible Concept](https://www.pocketgamer.biz/interview/68638/indie-spotlight-plausible-concept-on-bad-north/)
- [Xbox Tavern : critique de Bad North](https://www.xboxtavern.com/bad-north-review)
- [Steam : nombre d'escouades dans Bad North](https://steamcommunity.com/app/688420/discussions/0/2686880925149048060)
- [Windows Central : critique de Bad North](https://www.windowscentral.com/bad-north-xbox-one-windows-pc-review)
- [TouchArcade : critique de Bad North sur iOS](https://toucharcade.com/?p=259983)
- [TouchArcade : jeu de la semaine, Bad North](https://toucharcade.com/2019/10/18/toucharcade-game-of-the-week-bad-north-jotunn-edition)
- [TouchArcade : sortie de Bad North sur iOS et Android](https://toucharcade.com/2019/10/03/bad-north-jotunn-edition-ios-android-release-date-preorder)
- [LadiesGamers : Bad North au tactile](https://ladiesgamers.com/bad-north-jotunn-edition-review-nintendo-switch/)
- [Droid Life : Bad North sur Android](https://www.droid-life.com/?p=234705)
- [PlayTracker : moteur de Bad North](https://playtracker.net/quest/game/58520)
- [Haxe : les outils de Shiro Games](https://haxe.org/blog/shirogames-stack/)
- [Cathay Capital : Shiro Games](https://www.cathaycapital.com/shiro-games-welcomes-cathay-capital-hints-at-two-new-projects/)
- [PocketGamer : critique de Northgard sur mobile](https://www.pocketgamer.com/articles/086410/northgard-review/)
- [TouchArcade : sortie de Northgard sur iOS](https://toucharcade.com/2021/04/13/northgard-mobile-out-now-ios-price-free-dlc-roadmap-playdigious-shiro-games/)
- [TouchArcade : multijoueur de Northgard](https://toucharcade.com/2021/09/16/northgard-multiplayer-update-release-date-ios-android-cross-platform-play-game-modes-playdigious/)
- [Ironhide : historique de Kingdom Rush](https://ironhidegames.com/News/Details/109)
- [Game Developer : Kingdom Rush 6](https://www.gamedeveloper.com/press-release/ironhide-announces-kingdom-rush-6-genesis-td-steam-demo-mobile-pre-orders-new-trailer-and-september-24-launch-date)
- [Pocket Gamer : sortie de Kingdom Rush 6](https://www.pocketgamer.com/kingdom-rush-6-genesis/out-now-on-ios-and-android/)
- [Pocket Gamer : prix de Kingdom Rush 6](https://www.pocketgamer.com/kingdom-rush-6-genesis/pre-registration-now-open/)
- [Wikipedia : Rusted Warfare](https://en.wikipedia.org/wiki/Rusted_Warfare)
- [App Store : Rusted Warfare](https://apps.apple.com/app/id1514329124)
- [DroidGamers : Rusted Warfare](https://www.droidgamers.com/news/new-rts-game-for-android-rusted-warfare-has-a-lot-of-potential/)
- [Forum EA : sélection à deux doigts](https://forums.ea.com/discussions/command-and-conquer-franchise-en/suggestion-bring-red-alert-to-mobile-with-two-finger-box-select/13624253)
- [Epic : TINY METAL](https://www.unrealengine.com/developer-interviews/exploring-the-tactics-behind-tiny-metal)
- [Wikipedia : Galcon 2](https://en.wikipedia.org/wiki/Galcon_2)
- [Wikipedia : Mushroom Wars 2](https://en.wikipedia.org/wiki/Mushroom_Wars_2)
- [Wikipedia : Mindustry](https://en.wikipedia.org/wiki/Mindustry)

**Technique : Unreal Engine 5.8, Android, iOS**
- [Epic : notes de version d'UE 5.8](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-8-release-notes)
- [WN Hub : sortie d'UE 5.8](https://wnhub.io/news/engines/item-51157)
- [Inven Global : UE6](https://labs.invenglobal.com/articles/22900/unreal-engine-6-to-feature-fundamental-overhaul-targeting-early-access-release-by-late-2027)
- [Epic : modèles de jeu mis à jour en 5.6](https://www.unrealengine.com/en-US/news/updated-game-templates-for-unreal-engine-5-6available-now)
- [Epic : modèle Top Down](https://dev.epicgames.com/documentation/unreal-engine/top-down-template-in-unreal-engine)
- [Modèle Strategy 5.8 : StrategyPlayerController.cpp](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPlayerController.cpp)
- [Modèle Strategy 5.8 : StrategyPlayerController.h](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPlayerController.h)
- [Modèle Strategy 5.8 : StrategyPawn.cpp](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyPawn.cpp)
- [Modèle Strategy 5.8 : StrategyUnit.cpp](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/StrategyUnit.cpp)
- [Modèle Strategy 5.8 : StrategyHUD.cpp](https://github.com/jakemartin/stratocracy/blob/master/Source/Stratocracy/Variant_Strategy/UI/StrategyHUD.cpp)
- [Modèle Strategy 5.8 : widget mobile](https://github.com/jakemartin/stratocracy/blob/master/Content/Variant_Strategy/UI/WBP_StrategyMobileControls.uasset)
- [Modèle Strategy 5.8 : entrées tactiles](https://github.com/jakemartin/stratocracy/blob/master/Content/Variant_Strategy/Input/IMC_Strategy_Touch.uasset)
- [Modèle Strategy 5.8 : fichier de projet](https://github.com/jakemartin/stratocracy/blob/master/Stratocracy.uproject)
- [Second dépôt 5.8 (recoupement)](https://github.com/Rumsse/beavers-game/blob/main/Source/Beavers/Variant_Strategy/StrategyPlayerController.cpp)
- [Modèle Strategy 5.7](https://github.com/977908569/GameUpdate/blob/main/Source/GameUpdate/Variant_Strategy/StrategyPlayerController.cpp)
- [Epic : caméra orthographique](https://dev.epicgames.com/documentation/en-us/unreal-engine/orthographic-camera-in-unreal-engine)
- [Epic Issues : UE-392736](https://issues.unrealengine.com/issue/UE-392736)
- [Forum Unreal : régression des gestes en 5.8](https://forums.unrealengine.com/t/enhanced-input-gesture-keys-pinch-rotate-flick-never-release-after-touch-ends-regression-in-5-8/2745006)
- [Epic : SetGlobalTimeDilation](https://dev.epicgames.com/documentation/unreal-engine/BlueprintAPI/Utilities/Time/SetGlobalTimeDilation)
- [Forum Unreal : ralenti et UMG](https://answers.unrealengine.com/questions/544659/view.html)
- [Epic : prérequis Android](https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine)
- [Epic : contrôle du manifeste Android](https://dev.epicgames.com/documentation/en-us/unreal-engine/how-to-use-android-manifest-control-in-unreal-engine-projects)
- [Epic : rendu des maillages animés](https://dev.epicgames.com/documentation/en-us/unreal-engine/skeletal-mesh-rendering-paths-in-unreal-engine)
- [Epic : Cropout](https://www.unrealengine.com/en-US/blog/cropout-casual-rts-game-sample-project)
- [Cropout : DefaultEngine.ini (copie tierce)](https://github.com/ellie-me/vcs-demo-unreal/blob/master/Config/DefaultEngine.ini)
- [Cropout : profils d'appareils (copie tierce)](https://github.com/ellie-me/vcs-demo-unreal/blob/master/Config/DefaultDeviceProfiles.ini)
- [Google : TrivialKart, configuration Unreal](https://github.com/android/games-samples/blob/main/trivialkart/trivialkart_unreal/Config/DefaultEngine.ini)
- [Configuration publique : clés d'orientation iOS](https://github.com/Tencent/sluaunreal/blob/HEAD/Config/DefaultEngine.ini)
- [MassSample](https://github.com/Megafunk/MassSample)
- [Forum Unreal : Mass en 5.8](https://forums.unrealengine.com/t/mass-entity-5-8-preview/2733180)
- [Démo AnimToTexture](https://github.com/leejeonghun/AnimToTextureDemo)
- [Android Developers : API cible pour Google Play](https://developer.android.com/google/play/requirements/target-sdk)
- [Android Developers : pages de 16 Ko](https://developer.android.com/guide/practices/page-sizes)
- [Android Developers : Unreal sur Android](https://developer.android.com/games/engines/unreal/unreal-on-android)
- [Android Developers : changements d'Android 16](https://developer.android.com/about/versions/16/behavior-changes-16)
- [Android Developers : encoches](https://developer.android.com/develop/ui/views/layout/display-cutout)
- [Android Developers : accessibilité et zones tactiles](https://developer.android.com/guide/topics/ui/accessibility/apps)
- [Android Developers : mémoire sous Unreal](https://developer.android.com/games/engines/unreal/unreal-memory-usage)
- [Android Developers : réduire la mémoire sous Unreal](https://developer.android.com/games/engines/unreal/unreal-reduce-memory)
- [Android Developers : ADPF pour Unreal](https://developer.android.com/games/engines/unreal/unreal-adpf)
- [GitHub : plugin ADPF pour Unreal](https://github.com/android/adpf-unreal-plugin)
- [Android Developers : outils pour moteurs de jeu](https://developer.android.com/games/engines/engines-overview)
- [Apple HIG : commandes de jeu](https://developer.apple.com/design/human-interface-guidelines/game-controls)
- [Apple HIG : accessibilité](https://developer.apple.com/design/human-interface-guidelines/accessibility)
- [Apple HIG : mise en page](https://developer.apple.com/design/human-interface-guidelines/layout)
- [Apple : UIRequiresFullScreen](https://developer.apple.com/documentation/bundleresources/information-property-list/uirequiresfullscreen)
