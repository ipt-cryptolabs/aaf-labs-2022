package Skovron_FI04_Ghilevsky_FI_03.test.ParserTest;

import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Create;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class CreateTest {

    @Test
    void regularCreateCase1Test(){
        Create create = new Create("create student (age, weight);");
        String[] colName = new String[]{"age", "weight"};

        assertEquals("student", create.getTableName());
        assertEquals(colName[0], create.getNameOfColum()[0]);
        assertEquals(colName[1], create.getNameOfColum()[1]);
    }

    @Test
    void regularCreateCase2Test(){
        Create create = new Create("create student (age, weight, height);");

        String[] colName = new String[]{"age", "weight", "height"};

        assertEquals("student", create.getTableName());
        assertEquals(colName[0], create.getNameOfColum()[0]);
        assertEquals(colName[1], create.getNameOfColum()[1]);
        assertEquals(colName[2], create.getNameOfColum()[2]);
    }

    @Test
    void regularCreateCase3Test(){
        Create create = new Create("create \"student id\" (age, weight, height);");

        String[] colName = new String[]{"age", "weight", "height"};

        assertEquals("\"student id\"", create.getTableName());
        assertEquals(colName[0], create.getNameOfColum()[0]);
        assertEquals(colName[1], create.getNameOfColum()[1]);
        assertEquals(colName[2], create.getNameOfColum()[2]);
    }

    @Test
    void regularCreateCase4Test(){
        Create create = new Create("create \"student id\" (\"student age\", weight, \"student height\");");

        String[] colName = new String[]{"\"student age\"", "weight", "\"student height\""};

        assertEquals("\"student id\"", create.getTableName());
        assertEquals(colName[0], create.getNameOfColum()[0]);
        assertEquals(colName[1], create.getNameOfColum()[1]);
        assertEquals(colName[2], create.getNameOfColum()[2]);
    }

    @Test
    void regularCreateCase5Test(){
        Create create = new Create("CreAtE student (age, weight, height);");

        String[] colName = new String[]{"age", "weight", "height"};

        assertEquals("student", create.getTableName());
        assertEquals(colName[0], create.getNameOfColum()[0]);
        assertEquals(colName[1], create.getNameOfColum()[1]);
        assertEquals(colName[2], create.getNameOfColum()[2]);
    }

    @Test
    void sameTableCreate(){
        Create create1 = new Create("create student (age, weight, height);");
        Create create2 = new Create("create \"student\" (age, weight, height);");
        String[] name = {"student"};

        assertEquals(name[0], create1.getTableName());
        assertEquals(name[0], create2.getTableName());
    }

    @Test
    void emptyNameCreateTest(){
        Exception exception = assertThrows(RuntimeException.class, () -> new Create("create (age, weight);"));
        String expectedMessage = "Error: Empty table name";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void emptyColumnNameCreateTest(){
        Exception exception = assertThrows(RuntimeException.class, () -> new Create("create student ();"));
        String expectedMessage = "Error: Empty Column name";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void wrongSqlQueryTest1(){
        Throwable exception = assertThrows(IllegalArgumentException.class, () -> new Create("create t(x;"));
        String expectedMessage = "Error: Invalid SQL syntax (Creation Error 1)";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void wrongSqlQueryTest2(){
        Exception exception = assertThrows(RuntimeException.class, () -> new Create("create x y(age, weight);"));
        String expectedMessage = "Error: Invalid SQL syntax (Creation Error 2)";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void wrongSqlQueryTest3(){
        Throwable exception = assertThrows(IllegalArgumentException.class, () -> new Create("create t(x)y;"));
        String expectedMessage = "Error: Invalid SQL syntax (Creation Error 3)";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }
}
