# People-DB
 
This project allows to manage a SQLite database, specifically in this case, a database containing names of people. It provies such functions as adding, removing, printing, checking for existance and searching for certain names in the database. <br>
<br>
The window that opens after running the program has a title "Add People" and contains 3 buttons: "Add person", "Remove person" and "Show the database". Also it contains a line for text, where you can type a name of a person that you wish to add/remove. After clicking "Show the database" button, another window is opened. It has a title "People Database" and shows the list of names. It also has a line and "Find..." button. If we type a name and click this button, all the people with that name in the database will be displayed.

---

## Files 
- **People_DB.pro**<br>
A configuration file used to manage project settings, dependencies, and build configurations.
- **dbmanager.cpp** <br>
A "DbManager" class that provides main functionality of the database that was listed above (adding, removing etc.).
- **interface.cpp** <br>
An "Interface" class that contains all the code related to interface (visual parts like colors, geometry and also connections of all the buttons)<br>
- **dbmanager.h** <br>
A header file of the class DbManager.
- **interface.h**<br>
A header file of the class Interface.
- **main.cpp**
Main function that calls for the database widget.

## Code Explanation 
### In dbmanager.cpp file:
**DbManager Constructor (DbManager::DbManager(const QString& path))**:
```
DbManager::DbManager(const QString& path) {

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if (!m_db.open()){
        qDebug() << "Connection to database failed"; }
    else {
        qDebug() << "Connection to database ok";
    }

}
```
- Initializes a DbManager object with a path to a SQLite database file.<br>
- Adds a SQLite database connection using QSqlDatabase::addDatabase("QSQLITE").<br>
- Sets the database file name to the provided path.<br>
- Attempts to open the database connection and logs success or failure.<br>
<br>

**bool DbManager::addPerson(const QString& name)**:
  
  ```
  bool DbManager::addPerson(const QString& name) {
    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT INTO people (name) VALUES (:name)");
    query.bindValue(":name", name);

    if(query.exec()) {
        success = true;

    }
    else {
        qDebug() << "addPerson error: " << query.lastError().text();
    }

    return success;

}

  ```

- Adds a new person to the people table in the database.<br>
- Uses a prepared SQL statement to insert the person's name into the table.<br>
- Returns true if the insertion is successful, false otherwise.<br>
<br>

**bool DbManager::personExists(const QString& name)**:

 ```
bool DbManager::personExists(const QString& name){
    bool found = false;
    QSqlQuery query;
    query.prepare("SELECT name FROM people WHERE name = (:name)");
    query.bindValue(":name", name);
    if (query.exec()){
        if (query.next()) {
            found = true;
        }
    }
    else {
        qDebug() << "personExists error: " << query.lastError().text();
    }
    return found;
}
 ```

- Checks if a person with the given name exists in the people table.<br>
- Uses a prepared SQL statement to select the name from the table based on the input name.<br>
- Returns true if the person exists, false otherwise.<br>
<br>

**bool DbManager::removePerson(const QString& name)**:

  ```
bool DbManager::removePerson(const QString& name) {
    bool success = false;
    if (personExists(name)) {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM people WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        success = queryDelete.exec();
        if (!success) {
            qDebug() << "removePerson failed";
        }
    } else {
        qDebug() << "person doesn't exist";
    }
    return success;
}

  ```
- Removes a person with the given name from the people table if they exist.<br>
- Calls personExists to verify the person's existence before deletion.<br>
- Uses a prepared SQL statement to delete the person's entry from the table.<br>
- Returns true if the removal is successful, false otherwise.<br>
<br>


**void DbManager::printAll() const**:

 ```
void DbManager::printAll() const {
    qDebug() << "People in db:";
    QSqlQuery query ("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while (query.next()) {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}
 ```

- Prints all entries (names) in the people table of the database.<br>
- Executes a simple SQL query to select all records from the people table.<br>
- Iterates through the query result and prints each name.<br>
<br>

**bool DbManager::removeAll()**:

```
bool DbManager::removeAll() {
    bool success = false;
    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM PEOPLE");
    if (removeQuery.exec()) {
        success = true;
    } else {
        qDebug() << "remove failed: " << removeQuery.lastError();
    }
    return success;
}

```

- Removes all entries from the people table, effectively clearing the table.<br>
- Uses a prepared SQL statement to delete all records from the table.<br>
- Returns true if the removal of all entries is successful, false otherwise.<br>
<br>

**DbManager Destructor (DbManager::~DbManager())**:

```
DbManager::~DbManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

```

- Closes the database connection if it's open when the DbManager object is destroyed.

---

  ### In interface.cpp file:

**Constructor and Destructor**:

```
Interface::Interface(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

Interface::~Interface() {
    delete dbManager;
    delete model;
}

```

- The constructor initializes the interface's UI elements using setupUI() and sets up connections between UI elements and functions using setupConnections().<br>
- The destructor deallocates memory for dbManager and model objects.<br>
<br>


**setupUI() Function**:

```
void Interface::setupUI() {
    QFont font("Times New Roman");
    QApplication::setFont(font);

    setStyleSheet("background-color: lightBlue");
    setWindowIcon(QIcon(":/222.png"));
    setWindowTitle("Add People");
    setGeometry(100, 100, 350, 200);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setGeometry(20, 20, 280, 30);
    nameLineEdit->setStyleSheet("background-color: white");

    addButton = new QPushButton("Add person", this);
    addButton->setGeometry(20, 60, 130, 30);
    addButton->setIcon(QIcon(":/add.png"));
    addButton->setStyleSheet("background-color: white");

    removeButton = new QPushButton("Remove person", this);
    removeButton->setGeometry(170, 60, 130, 30);
    removeButton->setIcon(QIcon(":/remove.png"));
    removeButton->setStyleSheet("background-color: white");

    showDatabaseButton = new QPushButton("Show the database", this);
    showDatabaseButton->setGeometry(85, 100, 155, 30);
    showDatabaseButton->setIcon(QIcon(":/show.png"));
    showDatabaseButton->setStyleSheet("background-color: white");

    dbManager = new DbManager("D:/akhun/People_DB/people.db");

databaseWindow = new QWidget;

databaseWindow->setWindowTitle("People Database");
databaseWindow->setWindowIcon(QIcon(":/lens.png"));
databaseWindow->setGeometry(500, 100, 600, 400);

tableView = new QTableView(databaseWindow);
tableView->setGeometry(30, 30, 560, 360);

model = new QSqlQueryModel;
model->setQuery("SELECT * FROM people");
tableView->setModel(model);

tableView->resizeColumnsToContents();

findButton = new QPushButton("Find...", databaseWindow);
findButton->setGeometry(0, 3, 100, 25);

findLineEdit = new QLineEdit(databaseWindow);
findLineEdit->setGeometry(105, 3, 200, 25);
}
```

- Sets up the user interface with various widgets like QLineEdit, QPushButton, and QTableView.<br>
- Configures styles, icons, window title, geometry, and fonts for the widgets.<br>
- Creates an object of DbManager (dbManager) to manage the SQLite database.<br>
<br>

**setupConnections() Function**:

```
void Interface::setupConnections() {
        connect(addButton, &QPushButton::clicked, [this]() {
            QString name = nameLineEdit->text();
            if (!name.isEmpty()) {
                if (dbManager->addPerson(name)) {
                    qDebug() << "Person added successfully";
                } else {
                    qDebug() << "Failed to add person";
                }
            }
        });

        connect(removeButton, &QPushButton::clicked, [this]() {
            QString name = nameLineEdit->text();
            if (!name.isEmpty()) {
                if (dbManager->removePerson(name)) {
                    qDebug() << "Person removed successfully";
                } else {
                    qDebug() << "Failed to remove person";
                }
            }
        });

        connect(showDatabaseButton, &QPushButton::clicked, [this](){
databaseWindow->show();
        });

        connect(findButton, &QPushButton::clicked, [this]() {
            QString searchText = findLineEdit->text().trimmed();
            if (!searchText.isEmpty()) {
                QString queryStr = QString("SELECT * FROM people WHERE name LIKE '%%1%'").arg(searchText);
                model->setQuery(queryStr);
            } else {

                model->setQuery("SELECT * FROM people");
            }

        });


    }

```


- Establishes connections (signals and slots) between UI elements and corresponding functions using lambda expressions.<br>
- When the "Add person" button is clicked (addButton), it calls DbManager::addPerson to add a person to the database.<br>
- When the "Remove person" button is clicked (removeButton), it calls DbManager::removePerson to remove a person from the database.<br>
- When the "Show the database" button is clicked (showDatabaseButton), it displays the database window (databaseWindow) containing a QTableView to show database contents.<br>
- When the "Find..." button is clicked (findButton), it performs a search in the database based on the text entered in the findLineEdit.<br>
<br>

---

### In main.cpp file:

```
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Interface interface;
    interface.show();
    return app.exec();
}

```
- This main function sets up the Qt application, creates an object of the Interface class, displays the interface window, and runs the application.
---

## How to use
1. Copy all the header and cpp filed to your directory.
2. Download the database file and make sure that your code has a correct path to it.
3. Download png files for icons (or you could change them to whatever you want.
4. Run the program, add people to your database. 
