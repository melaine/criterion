List_forest : liste générale
List_forest_position : maillon qui se déplace
Pour List_element : utiliser list_forest :
	value=attribut
	brother=suivant
	JAMAIS DE FILS (ou valeur spécial spécifiant qu'on est dans la liste d'élément)
	father : noeud relatif à la liste d'élément
Les typedef sont des pointeurs sur les structs