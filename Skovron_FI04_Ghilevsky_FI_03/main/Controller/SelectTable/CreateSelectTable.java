package Skovron_FI04_Ghilevsky_FI_03.main.Controller.SelectTable;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Table;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;

public class CreateSelectTable {
    private Table table;
    private final Select select;
    public CreateSelectTable(Select select, Table table){
        this.select = select;
        this.table  = table;
    }

    public void select(){
        if (select.isSelectAll()){
            table.selectAllAndPrint();
        }else {
            throw new UnsupportedOperationException();
        }
    }


}