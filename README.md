## K23α - Ανάπτυξη Λογισμικού Για Πληροφοριακά Συστήματα

### Part 1 - Αναζήτηση εγγύτερου γείτονα (Nearest Neighbor Search)

To compile type: ```make```  
To run type: ```./executable```   
To compile using Test Main type: ```make test=yes```    
To run with Test Main type: ```./executable```     
To clean all type: ```make clean```    

Κατασκευή ευρετηρίου-γράφου Vamana, υλοποίηση αλγορίθμων GreedySearch και RobustPrune, εύρεση του medoid με αλγόριθμο brute force.

### Part 2 - Προσεγγιστική Αναζήτηση Εγγύτερων Γειτόνων με Φίλτρα - Filtered ANNS

To compile type: ```make```  

To run using default arguments type: ```make run```  
To run and save output type: ```make save```  
To run using custom arguments type: ```make run ARGS="../yourdataset.bin ../yourqueries.bin <a> <t> <L> <R> <k>"```  
To run and save output using custom arguments type: ```make save ARGS="../yourdataset.bin ../yourqueries.bin <a> <t> <L> <R> <k>"```   

To run using Valgrind type: ```make val```  
 
To clean all type: ```make clean```  

To compile using Test Main type: ```make test=yes```    
To run with Test Main type: ```./executable```     


Κατασκευή ευρετηρίου γράφου με δύο τρόπους Filtered Vamana και Stitched Vamana, υλοποίηση αλγορίθμων FilteredGreedySearch και FilteredRobustPrune, 
εύρεση start node (medoid για κάθε φίλτρο) με την χρήση του αλγορίθμου FindMedoid.  
Χρησιμοποιούνται datasets που έχουν μόνο ένα φίλτρο σε κάθε στοιχείο-κόμβο
(τα datasets, πριν χρησιμοποιηθούν, "καθαρίζονται" και αφαιρούνται τα timestamps και τα queries που περιέχουν ερωτήματα που αφορούν timestamps).



**AUTHORS**  
[Χριστίνα Διαμαντή](https://github.com/ChristinaDiam) - 1115201800046  
[Μαριάννα Σταμάτη](https://github.com/mariannastamati) - 1115202000183  
[Αντρέας Γιέβτοβιτς](https://github.com/zodicx) - 1115202000033

