# =========================
# CONFIGURATION
# =========================

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = src/affichage.c \
      src/persistance.c \
      src/transport.c

TARGET = app

# =========================
# COMPILATION
# =========================

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# =========================
# EXECUTION
# =========================

run: all
	./$(TARGET)

# =========================
# INSTALLATION DEPENDANCES
# =========================

install:
	sudo apt update
	sudo apt install -y build-essential

# =========================
# NETTOYAGE
# =========================

clean:
	rm -f $(TARGET)

# =========================
# RECOMPILATION COMPLETE
# =========================

reset: clean all

# =========================
# AIDE
# =========================

help:
	@echo "Commandes disponibles :"
	@echo " make         -> Compiler le projet"
	@echo " make run     -> Compiler et lancer"
	@echo " make clean   -> Supprimer l'executable"
	@echo " make reset      -> Recompiler totalement"
	@echo " make install -> Installer les dependances"