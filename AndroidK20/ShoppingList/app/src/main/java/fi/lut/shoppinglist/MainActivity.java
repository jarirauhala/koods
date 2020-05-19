package fi.lut.shoppinglist;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    // to hold some data for displaying in ListView
    ArrayList<String> testList = new ArrayList<String>();

    ListView itemsListView;
    Button addButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        itemsListView = (ListView) findViewById(R.id.itemsListView);
        addButton = (Button) findViewById(R.id.addButton);

        testList.add("Eka");
        testList.add("Toka");
        testList.add("Vika");

        final ItemAdapter itemAdapter = new ItemAdapter(this, testList);

        itemsListView.setAdapter(itemAdapter);


        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testList.add("YEEEEEEEEEEEET9");
                itemsListView.setAdapter(itemAdapter);

            }
        });


    }
}
