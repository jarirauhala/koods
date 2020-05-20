package fi.lut.shoppinglist;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    ListView itemsListView;
    Button addButton;
    DataBase db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        itemsListView = (ListView) findViewById(R.id.itemsListView);
        addButton = (Button) findViewById(R.id.addButton);

        db = new DataBase();
        final ItemAdapter itemAdapter = new ItemAdapter(this, db);

        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ListItem newItem = new ListItem("nTomatoo");
                db.addNewListItem(newItem);
                itemsListView.setAdapter(itemAdapter);

            }
        });

        itemsListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent showProductDetailsActivity =
                        new Intent (getApplicationContext(), ProductDetails.class);
                String productName = db.getItem(position).productName;
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_NAME", productName);
                showProductDetailsActivity.putExtra("fi.lut.OTHER_INFO", "INforillo");

                startActivity(showProductDetailsActivity);
            }
        });


    }
}
