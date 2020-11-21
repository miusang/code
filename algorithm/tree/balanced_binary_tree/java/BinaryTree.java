import java.util.Vector;

public class BinaryTree {
    public static void inorderVisit(Node root) {
        Vector list = new Vector(0);
        while (root != null || !list.isEmpty()) {
            while (root != null) {
                list.add(root);
                root = root.left;
            }
            root = (Node)(list.remove(list.size() - 1));
            System.out.print(root.val + " ");
            root = root.right;
        }
        System.out.println();
    }
}
