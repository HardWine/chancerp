## HOUSE API


Работа осуществляет с таблицой **house** в базе данных **chance**   
Методы, имеет одноименные процедуры в базе данных   


### forward bool: House.SetOwner(const arrayID, const accID, const name[]);
     * @param {int} const houseID [ID ячейки дома]
     * @param {int} const accID   [Номер аккаунта игрока]
     * @param {string} const name   [Ник владельца]

###  forward bool: House.UpRentDay(const arrayID);
     * @param {int} const houseID [ID ячейки дома]

###  forward bool: House.SwitchClossed(const arrayID);
     * @param {int} const houseID [ID ячейки дома]

###  forward bool: House.SellHouse(const arrayID, const percent);
     * @param {int} const houseID [ID ячейки дома]
     * @param {int} const percent [Процент который необходимо вернуть бывшему владельцу]

###  forward bool: House.SetRentDay(const arrayID, const day);
     * @param {int} const houseID [ID ячейки дома]
     * @param {int} const percent [Кол-во дней]

###  forward bool: House.DownRentDay(const arrayID);
     * @param {int} const houseID [ID ячейки дома]

###  forward bool: House.SetClass(const arrayID, const class);
     * @param {int} const houseID [ID ячейки дома]
     * @param {int} const percent [Новый класс]
   
   
   
   
>onlyhard @2018