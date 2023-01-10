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
    private final static String AVG = "AVG";
    private final static String MAX = "MAX";

    public CreateSelectTable(Select select, Table table) {
        this.select = select;
        this.primeTable = table;
        this.outTable = new Table(table.getTableName(), table.getRowsName());
    }

    public void select() {
        if (select.isSelectAll()) {
            primeTable.selectAllAndPrint();
        } else if (select.isSelectGroupBy()) {
            Table tempTable = new Table(primeTable.getTableName(), primeTable.getRowsName());

            if (select.isSelectWhereValue()) {
                List<Row> rows = primeTable.getRowArrayList();

                String colName = select.selectWhereCol()[0];
                int value = Integer.parseInt(select.selectWhereValue()[0]);

                for (Row row : rows)
                    rowCompare(row, colName, value, tempTable);
            } else if (select.isSelectWhereColumn()) {
                List<Row> rows = primeTable.getRowArrayList();

                String colName1 = select.selectWhereCol()[0];
                String colName2 = select.selectWhereValue()[0];

                for (Row row : rows)
                    rowCompare(row, colName1, colName2, tempTable);
            } else
                tempTable = primeTable;

            String[] groupNames = select.getGroupNames();
            String[] aggMethods = select.getAggMethods();
            String[] aggFun = select.getAggFun();
            String[] aggCol = select.getAggCol();

            String[] rowsName = new String[groupNames.length + aggMethods.length];
            System.arraycopy(groupNames, 0, rowsName, 0, groupNames.length);
            System.arraycopy(aggMethods, 0, rowsName, groupNames.length, aggMethods.length);

            doGroupBY(tempTable.getRowArrayList(), rowsName, groupNames, aggCol, aggFun).selectAllAndPrint();
        } else if (select.isSelectWhereValue()) {
            List<Row> rows = primeTable.getRowArrayList();

            String colName = select.selectWhereCol()[0];
            int value = Integer.parseInt(select.selectWhereValue()[0]);

            for (Row row : rows)
                rowCompare(row, colName, value, outTable);

            outTable.selectAllAndPrint();
        } else if (select.isSelectWhereColumn()) {
            List<Row> rows = primeTable.getRowArrayList();

            String colName1 = select.selectWhereCol()[0];
            String colName2 = select.selectWhereValue()[0];

            for (Row row : rows)
                rowCompare(row, colName1, colName2, outTable);

            outTable.selectAllAndPrint();
        } else {
            throw new UnsupportedOperationException("Error: No such option (Create Select)");
        }
    }

    private boolean checkEquals(int[] comp, Set<int[]> set) {
        for (int[] ints : set)
            if (Arrays.equals(ints, comp))
                return false;

        return true;
    }

    public Table doGroupBY(
            ArrayList<Row> primeRow, String[] rowsName,
            String[] groupNames, String[] aggCol, String[] aggFun) {
        Table table = new Table("name", rowsName);

        ArrayList<List<Row>> groupRow = new ArrayList<>();
        Set<int[]> sets = new HashSet<>();

        // находим необхідні колонки
        int[] poss = new int[groupNames.length];
        for (int i = 0; i < groupNames.length; i++)
            poss[i] = findColName(groupNames[i]);

        // находим унікільні елементи по всім необхідним колонкам
        for (Row row : primeRow) {
            int[] integers = new int[groupNames.length];
            for (int i = 0; i < poss.length; i++)
                integers[i] = row.getRow()[poss[i]];

            if (checkEquals(integers, sets))
                sets.add(integers);
        }

        // робим по цим унікльним елементам групи
        int unique = sets.size();
        for (int i = 0; i < unique; i++) {
            ArrayList<Row> list = new ArrayList<>();
            groupRow.add(list);
        }

        // заповняєм групи
        int k = 0;
        for (int[] ints : sets) {
            for (Row row : primeRow)
                if (Arrays.equals(ints, getCell(row.getRow(), poss)))
                    groupRow.get(k).add(row);

            k++;
        }

        // рахуєм відповідні функції
        for (List<Row> rowList : groupRow) {
            int[] cells = new int[rowsName.length];
            int[] groupName = getCell(rowList.get(0).getRow(), poss); // temp
            int[] aggColumn = new int[aggFun.length];                 // temp

            int[] aggColPos = new int[aggFun.length];
            int[] aggFunPos = findFunName(aggFun);
            for (int i = 0; i < aggFun.length; i++)
                aggColPos[i] = findColName(aggCol[i]);

            boolean once = true;
            for (Row row : rowList) {
                prepare(row.getRow(), aggColPos, aggFunPos, aggColumn, once);
                once = false;
            }

            System.arraycopy(groupName, 0, cells, 0, groupName.length);
            System.arraycopy(aggColumn, 0, cells, groupName.length, aggColumn.length);

            table.rowInsert(new Row(cells));
        }

        return table;
    }

    private void prepare(int[] rowArr, int[] colPos, int[] funPos, int[] accum, boolean once) {
        for (int i = 0; i < accum.length; i++) {
            if (funPos[i] == 1)
                accum[i] += 1;
            if (funPos[i] == 2) {
                if (once)
                    accum[i] = rowArr[colPos[i]];
                accum[i] = (accum[i] + rowArr[colPos[i]]) / 2;
            }
            if (funPos[i] == 3)
                accum[i] = Math.max(accum[i], rowArr[colPos[i]]);
        }

    }

    @Deprecated
    private int[] after(int[] acc, int[] funPos, int count) {
        for (int i = 0; i < acc.length; i++)
            if (funPos[i] == 2)
                acc[i] = acc[i] / count;

        return acc;
    }

    public int findColName(String colName) {
        for (int i = 0; i < primeTable.getRowsName().length; i++)
            if (primeTable.getRowsName()[i].equals(colName))
                return i;

        throw new IllegalArgumentException(
                "Error: No such column \"" + colName + "\" in table " + primeTable.getTableName());
    }

    /**
     * 1 - COUNT
     * 2 - AVG
     * 3 - MAX
     */
    private int[] findFunName(String[] funNames) {
        int[] res = new int[funNames.length];
        for (int i = 0; i < funNames.length; i++) {
            if (funNames[i].equals(COUNT))
                res[i] = 1;
            if (funNames[i].equals(AVG))
                res[i] = 2;
            if (funNames[i].equals(MAX))
                res[i] = 3;
        }

        return res;
    }

    private int[] getCell(int[] rowArr, int[] poss) {
        int[] res = new int[poss.length];

        for (int i = 0; i < poss.length; i++)
            res[i] = rowArr[poss[i]];

        return res;
    }

    public Table getOutTable() {
        return outTable;
    }

    public void rowCompare(Row row, String colName, int value, Table outTable) {
        int pos = findColName(colName);

        if (row.getRow()[pos] == value)
            outTable.rowInsert(row);
    }

    public void rowCompare(Row row, String colName1, String colName2, Table outTable) {
        int pos1 = findColName(colName1);
        int pos2 = findColName(colName2);

        if (row.getRow()[pos1] == row.getRow()[pos2])
            outTable.rowInsert(row);
    }

}