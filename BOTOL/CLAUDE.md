# CLAUDE.md — BOTOL (projet mobile)

À lire avant toute intervention sur ce dépôt. BOTOL — Battle of the Ocean's Legacy est un jeu de stratégie mobile qui se passe dans l'univers de WOTOL. Liamor définit la vision, les mécaniques, les choix visuels et les validations. Claude est un copilote technique.

## Règles absolues

1. **Ne jamais modifier, déplacer, convertir ni supprimer quoi que ce soit dans le projet WOTOL.** Il vit dans un autre dossier et un autre dépôt. Pour en récupérer un asset, utiliser *Migrate* depuis WOTOL vers BOTOL, ce qui copie l'asset sans toucher à la source.
2. **Ne rien inventer comme décision officielle :** ni lore, ni nom d'unité ou de bâtiment, ni mécanique, ni chiffre d'équilibrage. Faire une proposition clairement marquée « proposition », et attendre la validation explicite de Liamor.
3. **Pas de serveur, de matchmaking, de backend ni de multijoueur** tant que la boucle solo n'est pas validée sur un vrai téléphone.
4. **Pas de monétisation codée** (boutique, achats intégrés, pubs) tant que le modèle économique n'est pas décidé.
5. Un système simple testé de bout en bout vaut mieux que plusieurs fonctionnalités à moitié faites.

## Stack

- Unreal Engine **5.8.x**, la même version que WOTOL. Ne jamais changer de version sans l'accord de Liamor.
- C++ pour les systèmes, Blueprint pour le contenu et les réglages.
- Android en premier. iOS plus tard, ce qui demandera un Mac pour compiler le C++.
- Git + Git LFS. Les `.uasset` et `.umap` passent par LFS (voir `.gitattributes`).

## Ce que Claude peut et ne peut pas faire

- Claude **peut** lire et écrire le C++ (`Source/`), les fichiers `.ini` (`Config/`), les fichiers `.Build.cs`, les scripts et la documentation.
- Claude **ne peut pas** ouvrir ni modifier les `.uasset` et `.umap` : Blueprints, widgets, matériaux, cartes, Data Assets. Pour ces fichiers, il passe en **mode guidé** et décrit chaque manipulation dans l'éditeur : quel fichier ouvrir, quel nœud ajouter, quelle broche relier à quelle autre, quelle valeur régler, et quel test faire ensuite.
- Claude ne peut ni compiler ni lancer le jeu. Après chaque modification du C++, il faut que Liamor compile, lance une partie dans l'éditeur et, pour toute étape qui clôt un jalon, teste sur le téléphone.

## Mode guidé

Quand Liamor demande à apprendre ou à faire lui-même :
- un Blueprint à la fois, une fonction à la fois, un nœud à la fois ;
- pour chaque nœud : ses entrées, ses sorties, l'ordre exact des connexions et les valeurs à régler ;
- un test à faire après chaque étape ;
- une phrase courte qui explique le rôle de chaque élément ;
- ne rien implémenter à sa place tant qu'il ne l'a pas demandé.

## Contraintes mobiles

- Ne s'appuyer ni sur Nanite ni sur Lumen. Utiliser des maillages classiques avec LOD et un éclairage simple.
- Chaque asset importé de WOTOL doit être vérifié pour le mobile : nombre de triangles, LOD, taille des textures, complexité des matériaux. Exemple réel, relevé du 13/08/2026 : l'Aquilance de WOTOL faisait 461 546 triangles, avec Nanite désactivé et un seul LOD. Elle ne peut pas aller telle quelle sur un téléphone.
- Les décisions de performance se prennent sur des mesures faites sur le téléphone de référence (`stat fps`, `stat unit`), jamais d'après le PC de développement.
- L'interface est pensée pour le doigt : des zones tactiles larges, les informations essentielles visibles et rien de surchargé.

## Architecture

- **Pilotée par les données.** Une faction ou une unité = un fichier de données (Data Asset). Ajouter une faction ne doit demander aucune modification du code.
- Une mécanique définie pour une faction doit pouvoir s'appliquer de façon cohérente aux autres. Aucune règle propre aux Aquiloris codée en dur.
- Premier prototype : Aquiloris contre Noxéens seulement. Les trois autres factions (Thalassidras, Muréniens, Pirates Abyssaux) arriveront plus tard, sans réécrire l'architecture.
- Le contenu du modèle de départ reste dans `Content/Variant_Strategy/`. Le contenu BOTOL va dans `Content/BOTOL/`.

## Points ouverts — ne pas trancher

Temps réel ou tour par tour ; déplacement sur grille ou libre ; paysage ou portrait ; propriétaire de BOTOL et identifiant d'application ; modèle économique ; appareil minimum. Voir le `README.md` du kit de démarrage.

## Traçabilité

Après chaque session, ajouter une entrée datée en haut de `JOURNAL.md` avec :
- ce qui a été fait et les fichiers touchés ;
- ce qui a été testé, où (éditeur ou téléphone) et le résultat ;
- les blocages et les décisions prises par Liamor ;
- la prochaine étape.

Objectif : que Claude Code, Codex ou ChatGPT puissent reprendre sans tout relire. Commits courts, en français, un sujet par commit.
