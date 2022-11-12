package Skovron_FI04_Ghilevsky_FI_03.test.ParserTest;

import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class SelectTest {
    @Test
    void regularSelectCase1Test(){
        Select select = new Select("SELECT FROM students");
        Assertions.assertEquals("students", select.getTableName());
    }

    @Test
    void regularSelectCase2Test(){
        Select select = new Select("SELECT FRO students");

        Exception exception = assertThrows(RuntimeException.class, select::getTableName);
        String expectedMessage = "Error: Invalid slq syntax (Select)";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void regularSelectCase3Test(){
        Select select = new Select("SELECT FROM ");

        Exception exception = assertThrows(RuntimeException.class, select::getTableName);
        String expectedMessage = "Error: Empty table name (Select)"; // or
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void regularSelectCase4Test(){
        Select select = new Select("select COUNT(id) from student where height = 170 group_by weight;");

        Assertions.assertEquals("student", select.getTableName());
        Assertions.assertEquals(Arrays.toString(new String[]{"COUNT"}), Arrays.toString(select.getAggFun()));
        Assertions.assertEquals(Arrays.toString(new String[]{"id"}), Arrays.toString(select.getAggCol()));
        Assertions.assertEquals(Arrays.toString(new String[]{"height"}), Arrays.toString(select.selectWhereCol()));
        Assertions.assertEquals(Arrays.toString(new String[]{"170"}), Arrays.toString(select.selectWhereValue()));
        Assertions.assertEquals(Arrays.toString(new String[]{"weight"}), Arrays.toString(select.getGroupNames()));
        Assertions.assertEquals(Arrays.toString(new String[]{"COUNT(id)"}), Arrays.toString(select.getAggMethods()));
        Assertions.assertTrue(select.isSelectGroupBy());
        Assertions.assertTrue(select.isSelectWhereValue());
        Assertions.assertFalse(select.isSelectAll());
        Assertions.assertFalse(select.isSelectWhereColumn());
    }

    @Test
    void regularSelectCase5Test(){
        Select select = new Select("select from student where age = 1;");

        Assertions.assertEquals("student", select.getTableName());
        Assertions.assertEquals(Arrays.toString(new String[]{"age"}), Arrays.toString(select.selectWhereCol()));
        Assertions.assertEquals(Arrays.toString(new String[]{"1"}), Arrays.toString(select.selectWhereValue()));
        Assertions.assertFalse(select.isSelectGroupBy());
        Assertions.assertTrue(select.isSelectWhereValue());
        Assertions.assertFalse(select.isSelectAll());
        Assertions.assertFalse(select.isSelectWhereColumn());
    }

    @Test
    void regularSelectCase6Test(){
        Select select = new Select("select COUNT(weight), AVG(height) from student group_by age;");

        Assertions.assertEquals("student", select.getTableName());
        Assertions.assertEquals(Arrays.toString(new String[]{"COUNT", "AVG"}), Arrays.toString(select.getAggFun()));
        Assertions.assertEquals(Arrays.toString(new String[]{"weight", "height"}), Arrays.toString(select.getAggCol()));
        Assertions.assertEquals(Arrays.toString(new String[]{"age"}), Arrays.toString(select.getGroupNames()));
        Assertions.assertEquals(Arrays.toString(new String[]{"COUNT(weight)", "AVG(height)"}), Arrays.toString(select.getAggMethods()));
        Assertions.assertTrue(select.isSelectGroupBy());
        Assertions.assertFalse(select.isSelectWhereValue());
        Assertions.assertFalse(select.isSelectAll());
        Assertions.assertFalse(select.isSelectWhereColumn());
    }

    @Test
    void regularSelectCase7Test(){
        Select select = new Select("select from student where weight = height;");

        Assertions.assertEquals("student", select.getTableName());
        Assertions.assertEquals(Arrays.toString(new String[]{"weight"}), Arrays.toString(select.selectWhereCol()));
        Assertions.assertEquals(Arrays.toString(new String[]{"height"}), Arrays.toString(select.selectWhereValue()));
        Assertions.assertFalse(select.isSelectGroupBy());
        Assertions.assertFalse(select.isSelectWhereValue());
        Assertions.assertFalse(select.isSelectAll());
        Assertions.assertTrue(select.isSelectWhereColumn());
    }

    @Test
    void isSelectAllTest(){
        Select select = new Select("SELECT FROM students");
        Assertions.assertTrue(select.isSelectAll());
    }

}
