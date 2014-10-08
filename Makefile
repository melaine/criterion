# Les modules
MODULE := list_forest ixemelle ixemelle_io ixemelle_criterion ixemelle_cut
# Fichiers entête
HEADERS := $(MODULE:%=%.h) 
# TEST_MODULE := test_ixemelle_criterion test_list_forest


# Compilteur 
CC  :=  gcc
# Options de compilation
CFLAGS :=  -ansi -Wall -Wextra -pedantic -ggdb -lm

.PHONY : all t_list_forest t_criterion compilation test memoire archive 

# construction par défaut : fait construire extraire
all : 
	@echo "Disponibles à la construction :"
	@echo "  compilation ==> compilation (ne doit produire ni erreur ni alerte)"
	@echo "  t_list_forest ==> petit test du module list_forest avec un test mémoire"
	@echo "  t_criterion ==> petit test du module ixemelle_criterion avec un test mémoire"
	@echo "  test ==> t_list_forest t_criterion et tests sur ixemelle"
	@echo "  memoire ==> test les fuites mémoire (il ne doit pas y en avoir)"
	@echo "  debug ==> lance un debugger "
	@echo "  archive => produit la fichier pour le rendu"
	@echo "(Dé-)commenter les lignes en focntion de l'avancement et de la partie en cours de mise au point"

# Compilation : faire engendrer le programme
compilation : 
	@make ./test_list_forest
#	@make ./test_ixemelle_criterion
#	@make ./ixemelle 

# Règles de compilation
./%.o : %.c $(HEADERS) 
	$(CC) -c $(CFLAGS) -o $@ $<

./% : %.c $(MODULE:%=%.o) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(MODULE:%=%.o) $*.c

# Compilation de l'exécutable ixemelle
./ixemelle : $(MODULE:%=%.o) $(HEADERS) ixemelle_main.c 
	$(CC) $(CFLAGS) -o $@ $(MODULE:%=%.o) ixemelle_main.c 


# Répertoire où sont rangés les données de test et les résultats
JEUX_TEST_DIR := Jeux_test/Basic

# Répertoire de données pour les tests
DONNES_DIR := $(JEUX_TEST_DIR)/Donnees

# Répertoire où mettre les résultats
RESULTATS_DIR := $(JEUX_TEST_DIR)/Resultats


# TESTS
T_LIST_FOREST_1 := ./test_list_forest 
T_CRITERION_1 := ./test_ixemelle_criterion
T_1 := ./ixemelle $(DONNES_DIR)/exemple_1.xmlight
T_2 := ./ixemelle $(DONNES_DIR)/exemple_2.xmlight
T_3 := ./ixemelle $(DONNES_DIR)/exemple_3.xmlight
T_4 := ./ixemelle $(DONNES_DIR)/exemple_4.xmlight
T_5 := ./ixemelle $(DONNES_DIR)/exemple_5.xmlight 
T_CUT_1 := ./ixemelle cut 'deux' $(DONNES_DIR)/exemple_4.xmlight
T_CUT_2 := ./ixemelle cut 'trois' $(DONNES_DIR)/exemple_4.xmlight
T_CUT_3 := ./ixemelle cut 'un[a="e"]' $(DONNES_DIR)/exemple_4.xmlight
T_CUT_4 := ./ixemelle cut 'un[a="abc"]' $(DONNES_DIR)/exemple_4.xmlight
T_CUT_5 := ./ixemelle cut ' <-- deux' $(DONNES_DIR)/exemple_4.xmlight
T_CUT_6 := ./ixemelle cut ' -> trois' $(DONNES_DIR)/exemple_4.xmlight
T_CUT_7 := ./ixemelle cut ' --> trois <--un[b="OBO"]' $(DONNES_DIR)/exemple_4.xmlight
T_CUT_8 := ./ixemelle cut 'deuxprime' cut "deuxseconde" $(DONNES_DIR)/exemple_4.xmlight
T_CUT_9 := ./ixemelle cut 'coissant' cut '[nombre="2"]' cut '-> brocoli'  $(DONNES_DIR)/exemple_5.xmlight 


VALGRIND := valgrind --leak-check=full >/dev/null

define TEST_F
	$($(1)) > $(RESULTATS_DIR)/$(2).output
	$(VALGRIND) $($(1))
	if ! diff $(RESULTATS_DIR)/$(2).output $(RESULTATS_DIR)/$(2).output_expected ; then echo "$(1): *** RÉSUTALT INCORRECT ***" ; false ; else echo "$(1): OK" ; fi
endef

define TEST_MEM_F
	$(VALGRIND) $($(1))
endef



# TESTE du modle FOREST_LIST avec un TEST MÉMOIRE
t_list_forest : compilation ./test_list_forest
	$(call TEST_F,T_LIST_FOREST_1,test_list_forest)


t_criterion : compilation ./test_ixemelle_criterion
	$(call TEST_F,T_CRITERION_1,test_criterion)


# TESTS de GESTION de la MÉMOIRE
memoire : compilation
	$(call TEST_MEM_F,T_LIST_FOREST_1,test_list_forest)
	$(call TEST_MEM_F,T_CRITERION_1,test_criterion)

test : compilation
#	@make t_list_forest
#	@make t_criterion
#	$(call TEST_F,T_1,t_1)
#	$(call TEST_F,T_2,t_2)
#	$(call TEST_F,T_3,t_3)
#	$(call TEST_F,T_4,t_4)
#	$(call TEST_F,T_5,t_5)
#	$(call TEST_F,T_CUT_1,t_cut_1)
#	$(call TEST_F,T_CUT_2,t_cut_2)
#	$(call TEST_F,T_CUT_3,t_cut_3)
#	$(call TEST_F,T_CUT_4,t_cut_4)
#	$(call TEST_F,T_CUT_5,t_cut_5)
#	$(call TEST_F,T_CUT_6,t_cut_6)
#	$(call TEST_F,T_CUT_7,t_cut_7)
#	$(call TEST_F,T_CUT_8,t_cut_8)
#	$(call TEST_F,T_CUT_9,t_cut_9)

debug : compilation 
#	make ./test_list_forest && nemiver $(T_LIST_FOREST_1)
#	make ./test_ixemelle_criterion && nemiver $(T_LIST_FOREST_1)
#	nemiver $(T_LIST_FOREST_1)
#	nemiver $(T_CRITERION_1)
#	nemiver $(T_1)
#	nemiver $(T_2)
#	nemiver $(T_3)
#	nemiver $(T_4)
#	nemiver $(T_5)
#	nemiver $(T_CUT_1)
#	nemiver $(T_CUT_2)
#	nemiver $(T_CUT_3)
#	nemiver $(T_CUT_4)
#	nemiver $(T_CUT_5)
#	nemiver $(T_CUT_6)
#	nemiver $(T_CUT_7)
#	nemiver $(T_CUT_8)
#	nemiver $(T_CUT_9)


# PRODUIT l'ARCHIVE à RENDRE par MAIL (depuis un compte étudiant)
archive :
	@tar czf PASD_mini-projet.tgz Makefile *.c *.h compte-rendu.pdf

