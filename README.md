# Crypto Portfolio Manager · CLI

**[English](#english) · [Català](#català)**

![C++](https://img.shields.io/badge/C++17-00599C?logo=cplusplus&logoColor=white)
![Tests](https://img.shields.io/badge/tests-make_test-2ea44f)

---

## English

A command-line application in C++ to manage cryptocurrency portfolios: assets with daily prices, users with a euro balance and wallet addresses, buying and selling, and a portfolio valuation with the average cost and the total gain of each user.

Pair project for **Programació 1 (PRO1)** at the **UPC – EPSEVG** (Q1 2025-2026), by **Magí Garcia Bedós** and **Sofía Peña Narváez**.

### Features
- **Assets** (`crearActiu`, `mostrarActius`) with a symbol, a name and a number of decimals, and **daily closing prices** (`crearPreu`, `mostrarPreusActiu`, `preuActualActiu`).
- **Users** (`crearUsuari`, `mostrarUsuaris`) with a euro balance (`afegirEuros`, `retirarEuros`) and **wallet addresses** per asset (`crearAdreca`, `mostrarAdrecesUsuari`).
- **Buying and selling** at the latest price (`comprar`, `vendre`), with checks for funds, existing assets and holdings.
- **Portfolio** (`carteraDeUsuari`): amount, **average cost** and current price of every holding, and the user's total cost, total value and **gain**.
- Every error (duplicates, unknown users or assets, missing prices, insufficient funds…) is reported with a message and the program keeps running.

### Design
Six classes (`Asset`, `Price`, `User`, `Address`, `Holding` and `CryptoApp`, which coordinates them), each method documented with a **precondition and a postcondition**, and errors handled with exceptions. The program reads commands from standard input and writes to standard output, so whole sessions can be scripted and tested.

### Build and run
```bash
make            # builds ./crypto
./crypto        # interactive session
./crypto < tests/02_cost_mitja_i_cartera.ent   # scripted session
```

Example:
```
crearActiu BTC Bitcoin 8
crearPreu BTC 2024-01-01 40000
crearUsuari Laia laia@upc.edu pwd123
afegirEuros Laia 100000
comprar Laia BTC 1
carteraDeUsuari Laia
acabar
```

### Tests
```bash
make test
```
Each test is a pair of files in `tests/`: an input (`.ent`) and its expected output (`.cor`), in the same format as the course's test data. `run_tests.sh` runs every input and compares the output line by line.
- **`01_enunciat_tasques_ABC`**: tasks A, B and C from the assignment, in order.
- **`02_cost_mitja_i_cartera`**: average cost after buying at different prices, gain as the price changes, partial sales and error cases.

The expected outputs record the program's **current behaviour**, checked by hand, so any change that breaks it is detected.

### Known differences and issues
The code is kept **exactly as it was delivered** (first commit). Compared with the assignment's expected output:
1. The command to show the latest price is `preuActualActiu` (the assignment uses `mostrarPreuActualActiu`).
2. Creating a user also prints the email: `Usuari Ana amb email ana@upc.edu creat correctament`.
3. Showing the prices of an existing asset with no prices prints `no te preus` instead of `no existeix`.
4. A wallet address can be created for an asset that does not exist.
5. Buying a negative amount is accepted, which gives money back and breaks the average cost.

---

## Català

Aplicació de línia d'ordres en C++ per gestionar carteres de criptomonedes: actius amb preus diaris, usuaris amb saldo en euros i adreces de wallet, compra i venda, i valoració de la cartera amb el cost mitjà i el guany total de cada usuari.

Pràctica en parella de **Programació 1 (PRO1)** a la **UPC – EPSEVG** (Q1 2025-2026), feta per **Magí Garcia Bedós** i **Sofía Peña Narváez**.

### Funcionalitats
- **Actius** (`crearActiu`, `mostrarActius`) amb símbol, nom i nombre de decimals, i **preus de tancament diaris** (`crearPreu`, `mostrarPreusActiu`, `preuActualActiu`).
- **Usuaris** (`crearUsuari`, `mostrarUsuaris`) amb saldo en euros (`afegirEuros`, `retirarEuros`) i **adreces de wallet** per actiu (`crearAdreca`, `mostrarAdrecesUsuari`).
- **Compra i venda** a l'últim preu (`comprar`, `vendre`), amb comprovació de fons, actius i tinences.
- **Cartera** (`carteraDeUsuari`): quantitat, **cost mitjà** i preu actual de cada tinença, i el cost total, el valor total i el **guany** de l'usuari.
- Tots els errors (duplicats, usuaris o actius inexistents, preus que falten, fons insuficients…) es notifiquen amb un missatge i el programa continua.

### Disseny
Sis classes (`Asset`, `Price`, `User`, `Address`, `Holding` i `CryptoApp`, que les coordina), cada mètode documentat amb **precondició i postcondició**, i gestió d'errors amb excepcions. El programa llegeix ordres per l'entrada estàndard i escriu per la sortida estàndard, de manera que es poden automatitzar i provar sessions senceres.

### Compilació i execució
```bash
make            # genera ./crypto
./crypto        # sessió interactiva
./crypto < tests/02_cost_mitja_i_cartera.ent   # sessió automatitzada
```

### Jocs de prova
```bash
make test
```
Cada prova és una parella de fitxers a `tests/`: una entrada (`.ent`) i la sortida esperada (`.cor`), amb el mateix format que les dades de prova de l'assignatura. `run_tests.sh` executa cada entrada i en compara la sortida línia a línia.
- **`01_enunciat_tasques_ABC`**: les tasques A, B i C de l'enunciat, en ordre.
- **`02_cost_mitja_i_cartera`**: cost mitjà després de comprar a preus diferents, guany segons evoluciona el preu, vendes parcials i casos d'error.

Les sortides esperades recullen el **comportament actual** del programa, revisat a mà, de manera que es detecta qualsevol canvi que el trenqui.

### Diferències i errors coneguts
El codi es manté **exactament tal com es va lliurar** (primer commit). Respecte a la sortida esperada de l'enunciat:
1. L'ordre per mostrar l'últim preu és `preuActualActiu` (l'enunciat fa servir `mostrarPreuActualActiu`).
2. En crear un usuari també es mostra el correu: `Usuari Ana amb email ana@upc.edu creat correctament`.
3. En mostrar els preus d'un actiu existent sense preus surt `no te preus` en lloc de `no existeix`.
4. Es pot crear una adreça per a un actiu que no existeix.
5. S'accepta comprar una quantitat negativa, cosa que retorna diners i desquadra el cost mitjà.
