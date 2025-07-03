# Nimons Hospital: A Modular Hospital Management System in C

![C](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20WSL-orange.svg)
![Build](https://img.shields.io/badge/build-Makefile-brightgreen.svg)

**Nimons Hospital** is a comprehensive, command-line based information management system built entirely in C. Developed as a final project for the IF1210 Algorithm and Programming course, this application simulates the operational backend of a hospital. It features robust multi-user, role-based access control (Manager, Doctor, Patient) and handles complex data operations, from patient queues to data persistence, all while operating under strict constraints that required building fundamental components from the ground up.

---

### 🎥 Live Demo

*(It is highly recommended to record a short GIF of your program in action and place it here. It dramatically increases engagement.)*

![Demo GIF](https://placehold.co/800x400/2d3748/ffffff?text=Project+Demo+GIF)

---

### ✨ Core Features

This system is packed with features designed to manage hospital operations efficiently:

* **Role-Based Access Control:** A secure login system that provides different functionalities for three distinct user roles:
    * **Manager:** Oversees the entire system, with the ability to view all user data, add new doctors, and manage hospital layout and queues.
    * **Doctor:** Manages patient diagnosis, prescribes medication, and handles the patient queue for their assigned room.
    * **Patient:** Can register for an account, join a check-up queue, manage their medication, and consult with doctors.
* **Dynamic Patient Queuing:** A robust queuing system for patient check-ups, implemented with a custom-built linked list-based queue ADT.
* **Data Persistence:** Full capability to `save` the current state of the hospital (users, queues, rooms) to a set of `.csv` files and `load` it back upon startup.
* **Advanced User & Data Search:** Managers can search for users (doctors or patients) by ID or name using an efficient **binary search** algorithm.
* **Interactive Hospital Denah:** Users can view a 2D map of the hospital rooms and get detailed information about each room's occupants and queue status.
* **Comprehensive Command System:** An intuitive `HELP` command guides users based on their current role, ensuring a smooth user experience.

---

### 🛠️ Technical Deep Dive & Architecture

This project was built with a focus on fundamental computer science principles and low-level implementation.

* **Language:** **C (C99 Standard)**. All code is written to be compiled with `gcc`.
* **Abstract Data Types (ADTs) from Scratch:** A key requirement was to build our own data structures without relying on external libraries. We engineered:
    * **Linked List:** The foundation for our dynamic data structures.
    * **Queue:** Used for managing patient check-up lines.
    * **Stack:** Implemented for managing medication consumption history.
    * **Set & Map:** Used for ensuring data uniqueness (e.g., usernames) and creating efficient data relationships.
* **Custom CSV Parser:** Due to project constraints, standard library functions like `strtok` or `sscanf` were forbidden for parsing. We developed a **manual, from-scratch CSV parser** using only fundamental file I/O operations (`fgetc`, `fgets`). This parser is responsible for the critical `load` functionality, reading and interpreting data from `user.csv`, `penyakit.csv`, and other data files.
* **Algorithmic Implementation:** The system utilizes classic algorithms for efficiency, including **binary search** for user lookups and custom **sorting algorithms** for displaying lists of users.
* **Modular Architecture:** The codebase is organized into logical modules (`/src`), separating ADTs, feature logic, and the main driver program. This promotes code reusability and maintainability.
* **Build Automation:** A `Makefile` is provided for easy, one-command compilation in a Linux or WSL environment.

---

### 🚀 Getting Started

To get a local copy up and running, follow these simple steps.

#### Prerequisites

* A Linux or Unix-like environment (e.g., Ubuntu, macOS, or WSL on Windows).
* `gcc` compiler
* `make` build tool

```bash
# Check for installation
gcc --version
make --version
```

#### Installation & Execution

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/YavieAzka/nimons-hospital.git](https://github.com/YavieAzka/nimons-hospital.git)
    cd nimons-hospital
    ```

2.  **Compile the program:**
    Use the provided `Makefile` to compile all source files.
    ```sh
    make
    ```

3.  **Run the application:**
    The program requires a command-line argument specifying the folder containing the data files to load.
    ```sh
    ./bin/main data
    ```
    If the `data` folder does not exist, the program will notify you. You can then use the `SAVE` command within the application to create it.

---

### 📁 File Structure

```
.
├── bin/              # Compiled executable file
├── data/             # Default directory for .csv data files
├── doc/              # Project documentation and reports
├── src/              # Source code (.c and .h files)
│   ├── ADT/          # Abstract Data Type implementations
│   ├── modules/      # Feature-specific modules
│   └── main.c        # Main program driver
├── Makefile          # Build script
└── README.md         # You are here!
```

---

### 👤 My Key Contributions

As a core member of the development team, I was responsible for designing and implementing several critical components of the system:

* **User Authentication & Session (`F01 - Login`):** I engineered the primary login system that handles user authentication and establishes the role-based session for managers, doctors, and patients.
* **User Guidance (`F05 - Menu & Help`):** I developed the context-aware help menu, a crucial feature for user experience that displays available commands based on the logged-in user's role.
* **Data Retrieval (`F08 - Cari User` & `F09/D02 - Lihat Antrian`):** I implemented the functionality for managers to search for specific users using binary search and to view the status of all patient queues across the hospital.
* **System Expansion (`F10 - Tambah Dokter`):** I built the feature allowing managers to add new doctors to the system, expanding the hospital's operational capacity.
* **Core Data Loading (`D03 - Load`):** I took on the challenging task of writing the **manual CSV parser**. This involved low-level file and string manipulation to read and correctly interpret all initial data from the `.csv` files, forming the backbone of the program's data persistence.
* **Main Program Logic (`main.c`):** I was responsible for structuring and writing approximately **70% of the main program driver**, integrating all modules and managing the primary command loop and program flow.

---

### 👥 Authors

This project was a collaborative effort by:

* **Yavie Azka** - ([@YavieAzka](https://github.com/YavieAzka))
* *(Add other team members here)*

---

### 🙏 Acknowledgements

We would like to express our gratitude to the teaching assistants and lecturers of the **IF1210 Algorithm and Programming** course at Institut Teknologi Bandung for their guidance and for providing such a challenging and rewarding project specification.
