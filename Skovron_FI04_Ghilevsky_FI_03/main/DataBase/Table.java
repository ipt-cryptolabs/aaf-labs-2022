package Skovron_FI04_Ghilevsky_FI_03.main.DataBase;

import java.util.ArrayList;

public class Table {

    private final String tableName;
    private String[] rowsName;
    private ArrayList<Row> rowArrayList = new ArrayList();

    public Table(String tableName, String... rowsName){
        this.tableName = tableName;
        this.rowsName = rowsName;
    }

    public Table createTable(){
        System.out.println(tableName + " has been created\n");
        return new Table(tableName, rowsName);
    }

    public void rowInsert(Row row){
        rowArrayList.add(row);
    }

    public void rowsInsert(int num, ArrayList<Row> rows){
        for(int i = 0; i < num; i++){
            rowInsert(rows.get(i));
        }

        String pl =  num > 1 ? "row" : "rows";
        String msg =  num + " " + pl + " has been inserted into " + tableName;
        System.out.println(msg);
    }

    private String[] fromIntToString(int[] intArray){
        String[] strArray = new String[intArray.length];

        for (int i = 0; i < intArray.length; i++) {
            strArray[i] = String.valueOf(intArray[i]);
        }

        return strArray;
    }

    public ArrayList<Row> getRowArrayList(){
        return rowArrayList;
    }

    public String getTableName() {
        return tableName;
    }

    @Deprecated
    public void selectAllAndPrint() { // demo
        String[][] arr = new String[rowArrayList.size() + 1][rowsName.length];
        String[] new_rowsName = new String[rowsName.length + 1];

        new_rowsName[0] = "sys_id";

        System.arraycopy(rowsName, 0, new_rowsName, 1, rowsName.length);

        arr[0] = new_rowsName;

        for (int i = 0; i < rowArrayList.size(); i++){
            arr[i + 1] = fromIntToString(rowArrayList.get(i).getRow());
        }

        printTable(arr);
    }

    @Deprecated
    private static void printTable(String[][] table) {
        int maxColumns = 0;
        for (String[] strings : table) {
            maxColumns = Math.max(strings.length, maxColumns);
        }

        int[] lengths = new int[maxColumns];
        for (String[] strings : table) {
            for (int j = 0; j < strings.length; j++) {
                lengths[j] = Math.max(strings[j].length(), lengths[j]);
            }
        }

        String[] formats = new String[lengths.length];
        for (int i = 0; i < lengths.length; i++) {
            formats[i] = "%1$" + lengths[i] + "s"
                    + (i + 1 == lengths.length ? "\n" : "   ");
        }

        for (String[] strings : table) {
            for (int j = 0; j < strings.length; j++) {
                System.out.printf(formats[j], strings[j]);
            }
        }
    }
}
