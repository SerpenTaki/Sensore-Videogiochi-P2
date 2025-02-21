# Sensore-Videogiochi-P2

## Disposizioni per compilare ed eseguire il programma
Per compilare il programma è necessario aprire il terminale in questa directory dove è contenuto questo file e digitare prima: `qmake` e dopo `make`.

---
### In caso di problemi
Se si hanno problemi con le librerie eseguire il comando `qmake -project` e aprire il file `.pro` 
Verificare che all'interno del file `.pro` siano presenti le seguenti librerie

````
QT += widgets
QT += charts
QT += xml
````

dopodichè rieseguire `qmake` e `make`.

## Per problemi con QtCharts
Per utenti **linux** decommentare la riga 14 di `content.h` su mac e su altri sistemi operativi non ne ho avuto bisogno ma se da problemi per le librerie **QtCharts** mettere il namespace aiuta e risolve il problema.

---

# Valutazione
````
Feedback Progetto di Programmazione ad Oggetti
Studente: Di Pietro Gabriele
Valutazione del progetto: Eccellente

Vincoli obbligatori
+ Soddisfatti


Orientamento ad oggetti
+ Incapsulamento
+ Modularità (modello logico e la GUI sono separati)
+ Estensibilità ed evolvibilità, polimorfismo
+ Efficienza e robustezza


Funzionalità
+ Funzionalità di ricerca e filtro
+ Ricerca in tempo reale
+ Ricerca case-insensitive
+ Ricerca parziale
+ Possibilità di modificare i parametri dei sensori


GUI
+ Visualizza i diversi tipi di dato in maniera opportuna
+ Usabile e intuitiva
+ Robusta, gestisce ridimensionamento
- Migliorabile utilizzando icone, immagini e stili grafici
- Migliorabile il modo in cui viene creato il widget in ContentVisitor:
  anziché creare una singola QLabel andrebbero costruiti widget appositi,
  in questo caso usando un QGridLayout (per mantenere l'impaginazione
  scelta) con dentro un'etichetta per ogni informazione


Relazione
+ Adeguata


Suggerimenti non collegati alla valutazione
Nessuno.
````

