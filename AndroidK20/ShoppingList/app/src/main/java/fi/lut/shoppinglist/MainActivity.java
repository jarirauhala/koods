package fi.lut.shoppinglist;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ListView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    // to hold some data for displaying in ListView
    ArrayList<String> testList = new ArrayList<String>();

    ListView itemsListView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        itemsListView = (ListView) findViewById(R.id.itemsListView);

        testList.add("Eka");
        testList.add("Toka");
        testList.add("Vika");

        ItemAdapter itemAdapter = new ItemAdapter(this, testList);

        itemsListView.setAdapter(itemAdapter);


    }
}
