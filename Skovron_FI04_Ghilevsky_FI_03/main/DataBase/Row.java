package Skovron_FI04_Ghilevsky_FI_03.main.DataBase;

public class Row {

    private final int[] row;
    private static int staticID = 0;
    private int rowId;

    public Row(int... row){
        rowId = staticID;

        this.row = new int[row.length + 1];
        this.row[0] = rowId;

        System.arraycopy(row, 0, this.row, 1, row.length);

        staticID++;
    }

    public int[] getRow() {
        return row;
    }

    public Row createRow(int... cells){
        return new Row(cells);
    }
}