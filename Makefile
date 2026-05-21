# Makefile per il progetto Bar Abyssia

# Variabili
CC = gcc
CFLAGS = -Wall -g -I./include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# File sorgenti e oggetti
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = $(BINDIR)/abyssia

# Target di default
all: $(EXECUTABLE)

# Crea l'eseguibile
$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "✓ Compilazione completata: $(EXECUTABLE)"

# Crea i file oggetto
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "✓ Compilato: $<"

# Crea le directory se non esistono
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# Target per eseguire il programma
run: $(EXECUTABLE)
	@echo "Avvio del programma..."
	@./$(EXECUTABLE)

# Target per pulire i file compilati
clean:
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo "✓ Pulizia completata"

# Target per ricompilare tutto
rebuild: clean all

# Target per aiuto
help:
	@echo "Comandi disponibili:"
	@echo "  make              - Compila il progetto"
	@echo "  make run          - Compila ed esegue il programma"
	@echo "  make clean        - Rimuove i file compilati"
	@echo "  make rebuild      - Pulisce e ricompila tutto"
	@echo "  make help         - Mostra questo messaggio"

.PHONY: all run clean rebuild help
