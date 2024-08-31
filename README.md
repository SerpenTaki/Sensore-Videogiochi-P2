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

dopodichè rieseguire `qmake` e `make`