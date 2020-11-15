import java.util.ArrayList;
import java.util.List;

public class BinaryTree {
    public static void inorderVisit(Node root) {
        ArrayList<Node> list = new ArrayList<Node>();
        while (root != null || !list.isEmpty()) {
            while (root != null) {
                list.add(root);
                root = root.left;
            }
            root = list.get(list.size() - 1);
            list.remove(list.size() -1);
            System.out.print(root.val + " ");
            root = root.right;
        }
        System.out.println("");
    }
}
