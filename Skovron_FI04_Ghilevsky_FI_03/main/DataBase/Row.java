package Skovron_FI04_Ghilevsky_FI_03.main.DataBase;

import java.util.Arrays;
import java.util.Objects;

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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Row row1 = (Row) o;
        return Arrays.equals(row, row1.row);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(rowId);
        result = 31 * result + Arrays.hashCode(row);
        return result;
    }
}