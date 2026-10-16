# Audit de réutilisation WOTOL → BOTOL

Phase 1 de la roadmap Notion : inventorier les éléments de WOTOL et classer chacun dans **une seule** des quatre catégories. L'audit se fait **avant** de migrer quoi que ce soit, et il ne commence qu'à partir du jalon M1.

| Statut | Signification |
|---|---|
| **Direct** | Passe tel quel dans BOTOL |
| **À adapter** | Utilisable après un travail limité (LOD, décimation, textures réduites, matériau simplifié, interface remise à l'échelle) |
| **À refaire** | La référence visuelle ou de design est conservée, l'asset est recréé (Blender, Meshy) |
| **Inutile** | Hors du périmètre mobile ou du premier prototype |

## Points à vérifier pour chaque asset

- **Triangles et LOD :** combien de triangles, combien de niveaux de détail, et l'asset dépend-il de Nanite ?
- **Textures :** quelle résolution, et combien de textures par matériau ?
- **Matériau :** nombre d'instructions, transparence, effets coûteux.
- **Dépendance au code WOTOL :** un Blueprint dont la classe parente est une classe C++ de WOTOL **ne s'ouvrira pas** dans BOTOL tant que cette classe n'existe pas. *Migrate* copie les assets, pas le code C++. Les maillages, textures, sons et la plupart des matériaux migrent sans problème.
- **Prototype :** l'élément sert-il au combat Aquiloris contre Noxéens ? Si non, il attend.

## Grille

| Élément | Type | Faction | Emplacement dans WOTOL | Triangles / LOD | Textures | Dépend du code WOTOL ? | Prototype ? | Statut | Notes |
|---|---|---|---|---|---|---|---|---|---|
| Aquilance | Unité | Aquiloris | à compléter | 461 546 / 1 LOD, Nanite désactivé (relevé du 13/08/2026) | à compléter | à vérifier | oui | À adapter ou à refaire | Trop lourde pour un téléphone : décimation et LOD, ou version refaite avec Meshy |
| | | | | | | | | | |
| | | | | | | | | | |

## Hors assets

Ce qui n'est pas un asset suit les mêmes quatre statuts :

- **Lore et textes :** conservés comme référence, puis raccourcis pour les fenêtres narratives mobiles.
- **Données de jeu** (statistiques, coûts, rôles) : on peut s'en servir comme point de départ, mais l'équilibrage mobile reste à valider.
- **Code C++ de WOTOL :** à relire système par système. On recopie seulement ce qui ne dépend pas de la caméra libre, de l'interface PC ou de systèmes hors périmètre (économie à 8 ressources, couches de profondeur, etc.), et seulement après validation.
- **Sons :** garder ceux du gameplay et de l'ambiance. Le doublage est hors périmètre.
