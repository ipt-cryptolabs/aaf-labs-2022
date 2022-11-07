package Skovron_FI04_Ghilevsky_FI_03.main.Controller.SelectTable;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Table;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class CreateSelectTable {

    private final Table primeTable;
    private final Table outTable;
    private final Select select;

    public CreateSelectTable(Select select, Table table){
        this.select = select;
        this.primeTable = table;
        this.outTable = new Table(table.getTableName(), table.getRowsName());
    }

    public static void main(String[] args) {
        String[] groupNames = {"age", "weight"};
        String[] aggMethods = {"COUNT(age)", "AVG(weight)"};

        String[] rowsName = new String[groupNames.length + aggMethods.length];

        System.arraycopy(groupNames, 0, rowsName, 0 , groupNames.length);
        System.arraycopy(aggMethods, 0, rowsName, groupNames.length, aggMethods.length);

        System.out.println(Arrays.toString(rowsName));
    }

    public void select() {
        if (select.isSelectAll())
            primeTable.selectAllAndPrint();

        if(select.isSelectGroupBy()){ // TODO
            Table tempTable = new Table(primeTable.getTableName(), primeTable.getRowsName());

            if (select.isSelectWhereValue()){
                List<Row> rows =  primeTable.getRowArrayList();

                String colName = select.selectWhereValue()[0];
                int value = Integer.parseInt(select.selectWhereValue()[1]);

                for (Row row: rows)
                    rowCompare(row, colName, value, tempTable);
            }

            if(select.isSelectWhereColumn()){
                List<Row> rows =  primeTable.getRowArrayList();

                String colName1 = select.selectWhereCol()[0];
                String colName2 = select.selectWhereCol()[0];

                for (Row row: rows)
                    rowCompare(row, colName1, colName2, tempTable);
            }

            /**
             * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
             */ // будуть одні костилі напевно))

            // TODO GROUP_BY ??how??
            String[] groupNames = {""}; // some method from parser
            String[] aggMethods = {""}; // some method from parser
            String[] rowsName = new String[groupNames.length + aggMethods.length];

            System.arraycopy(groupNames, 0, rowsName, 0 , groupNames.length);
            System.arraycopy(aggMethods, 0, rowsName, groupNames.length, aggMethods.length);

            Table outTableGroup = new Table("outComeTable", rowsName);

            int[] cells = new int[rowsName.length];

            for (int i = 0; i < tempTable.getRowArrayList().size(); i++){ // eh не так треба
                System.arraycopy(
                        insertInCells(tempTable.getRowArrayList().get(i), groupNames),
                        0, cells, 0, groupNames.length);
                //System.arraycopy();

                outTableGroup.rowInsert(new Row(cells));
            }

            outTableGroup.selectAllAndPrint();
        }

        if (select.isSelectWhereValue()) {
            List<Row> rows =  primeTable.getRowArrayList();

            String colName = select.selectWhereValue()[0];
            int value = Integer.parseInt(select.selectWhereValue()[1]);

            for (Row row: rows)
                rowCompare(row, colName, value, outTable);

            outTable.selectAllAndPrint();
        }

        if (select.isSelectWhereColumn()) {
            List<Row> rows =  primeTable.getRowArrayList();

            String colName1 = select.selectWhereCol()[0];
            String colName2 = select.selectWhereCol()[0];

            for (Row row: rows)
                rowCompare(row, colName1, colName2, outTable);

            outTable.selectAllAndPrint();
        } else {
            throw new UnsupportedOperationException("Error: No such option (Create Select)");
        }
    }

    public int[] insertInCells(Row row, String[] groupNames){
        int[] res = new int[groupNames.length];

        for(int i = 0; i < groupNames.length; i++){
            res[i] = row.getRow()[findColName(groupNames[i])];
        }

        return res;
    }

    public int findColName(String colName) { // public for test
        for (int i = 0; i < primeTable.getRowsName().length; i++)
            if (primeTable.getRowsName()[i].equals(colName))
                return i;

        throw new IllegalArgumentException(
                "Error: No such column " + colName + " in table " + primeTable.getTableName());
    }

    public Table getOutTable() {
        return outTable;
    }

    public void rowCompare(Row row, String colName, int value, Table outTable) { // public for test
        int pos = findColName(colName);

        if (row.getRow()[pos] == value)
            outTable.rowInsert(row);

    }

    public void rowCompare(Row row, String colName1, String colName2, Table outTable){ // public for test
        int pos1 = findColName(colName1);
        int pos2 = findColName(colName2);

        if (row.getRow()[pos1] == row.getRow()[pos2])
            outTable.rowInsert(row);
    }

    private void COUNT(Row row, String colName){
        throw new UnsupportedOperationException();
    }

    private void MAX(Row row, String colName){
        throw new UnsupportedOperationException();
    }

    private void AVG(Row row, String colName){
        throw new UnsupportedOperationException();
    }

}