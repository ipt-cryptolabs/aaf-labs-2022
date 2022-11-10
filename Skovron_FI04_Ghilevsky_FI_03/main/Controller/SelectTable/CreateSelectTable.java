package Skovron_FI04_Ghilevsky_FI_03.main.Controller.SelectTable;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Table;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;

import java.util.*;

public class CreateSelectTable {

    private final Table primeTable;
    private final Table outTable;
    private final Select select;

    private final static String COUNT = "COUNT";
    private final static String AVG   = "AVG";
    private final static String MAX   = "MAX";

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
        if (select.isSelectAll()) {
            primeTable.selectAllAndPrint();
        } else if(select.isSelectGroupBy()){ // TODO
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
            }else // suspicious?? work??
                tempTable = primeTable;

            String[] groupNames = select.getGroupNames();
            String[] aggMethods = select.getAggMethods();
            String[] aggFun = select.getAggFun();
            String[] aggCol = select.getAggCol();

            String[] rowsName = new String[groupNames.length + aggMethods.length];
            System.arraycopy(groupNames, 0, rowsName, 0 , groupNames.length);
            System.arraycopy(aggMethods, 0, rowsName, groupNames.length, aggMethods.length);

            // TODO
            doGroupBY(tempTable.getRowArrayList(), rowsName, groupNames, aggCol, aggFun).selectAllAndPrint();

        } else if (select.isSelectWhereValue()) {
            List<Row> rows =  primeTable.getRowArrayList();

            String colName = select.selectWhereValue()[0];
            int value = Integer.parseInt(select.selectWhereValue()[1]);

            for (Row row: rows)
                rowCompare(row, colName, value, outTable);

            outTable.selectAllAndPrint();
        } else if (select.isSelectWhereColumn()) {
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

    // TODO @DOING
    public Table doGroupBY(
            ArrayList<Row> primeRow, String[] rowsName,
            String[] groupNames, String[] aggCol, String[] aggFun) {
        Table table = new Table("name", rowsName);

        ArrayList<List<Row>> groupRow = new ArrayList<>();
        Set<Integer[]> sets = new HashSet<>();

        // находим необхідні колонки
        int[] poss = new int[rowsName.length];
        for (int i = 0; i < rowsName.length; i++)
            poss[i] = findColName(rowsName[i]);

        // находим унікільні елементи по всім необхідним колонкам
        for (Row row : primeRow) {
            Integer[] integers = new Integer[rowsName.length];
            for (int i = 0; i < poss.length; i++)
                integers[i] = row.getRow()[poss[i]];

            sets.add(integers); // працює?
        }

        // робим по цим унікльним елементам групи
        int unique = sets.size();
        for (int i = 0; i < unique; i++){
            ArrayList<Row> list = new ArrayList<>();
            groupRow.add(list);
        }

        // заносим в ці групи відповідні елементи
        int k = 0;
        for (Integer[] integer : sets) { // працює?
            for (Row row : primeRow) {
                Integer[] cell = getCell(row, integer, poss);
                if (Arrays.equals(cell, integer))
                    groupRow.get(k).add(row);
            }
                k++;
        }

        // TODO hard
        // рахуєм відповідні функції
        for (List<Row> rowList : groupRow) {
            int[] cells = new int[rowsName.length];

            int count = rowList.size();
            int max = 0;
            int avg = 0;

            for (Row row : rowList) {
                max = Math.max(row.getRow()[0], max);
                avg += row.getRow()[0];

                System.out.println(row);
            }

            cells[0] = rowList.get(0).getRow()[0];
            cells[1] = count;
            cells[2] = avg / count;
            cells[3] = max;

            table.rowInsert(new Row(cells));
            System.out.println();
        }

        return table;
    }

    private Integer[] getCell(Row row, Integer[] compArr, int[] poss){
        if(compArr.length != poss.length)
            throw new IllegalArgumentException("Wrong work GROUP_BY of something else wrong, ((VERY BAD ERROR!!))");

        Integer[] temp = new Integer[compArr.length];
        for(int i = 0; i < row.getRow().length; i++)
            temp[i] = row.getRow()[poss[i]];

        return temp;
    }

    public int findColName(String colName) {
        for (int i = 0; i < primeTable.getRowsName().length; i++)
            if (primeTable.getRowsName()[i].equals(colName))
                return i;

        throw new IllegalArgumentException(
                "Error: No such column " + colName + " in table " + primeTable.getTableName());
    }

    public Table getOutTable() {
        return outTable;
    }

    public void rowCompare(Row row, String colName, int value, Table outTable) {
        int pos = findColName(colName);

        if (row.getRow()[pos] == value)
            outTable.rowInsert(row);
    }

    public void rowCompare(Row row, String colName1, String colName2, Table outTable){
        int pos1 = findColName(colName1);
        int pos2 = findColName(colName2);

        if (row.getRow()[pos1] == row.getRow()[pos2])
            outTable.rowInsert(row);
    }

}