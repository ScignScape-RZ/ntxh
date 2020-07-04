
class ViewsListWidget //: QVBoxLayout
{
 QVBoxLayout* main_layout_;

 bool isUpdating_; //=false;

 QTableWidget* tableViews_; // =new QTableWidget(); 

 MainWindow* mw_;
 
public:
 
 ViewsListWidget(MainWindow* mw);
 
 void dothelayout();
 
 void actionSelectAllViews();

 // // Get selected views
 LinkedList<ViewSettings> getSelectedViews(); 
 
 // // Update list with views
 void updateViewsList();

 // // Action: Remove selected views
 void actionRemoveView();

 // // Action: Create a new view
 void actionNewView();
};


