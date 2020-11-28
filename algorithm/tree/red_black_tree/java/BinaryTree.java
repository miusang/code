import java.util.Vector;

public class BinaryTree {
    public static void inorderVisit(Node root) {
        Vector list = new Vector(0);
        while (root != null || !list.isEmpty()) {
            while (root != null) {
                list.add(root);
                root = root.left;
            }
            root = (Node)list.remove(list.size() - 1);
            System.out.print(root.val + " ");
            root = root.right;
        }
        System.out.println();
    }

    public static void levelVisit(Node root) {
        if (root == null) {
            return;
        }
        Vector list = new Vector(0);
        list.add(root);
        while (!list.isEmpty()) {
            root = (Node)list.remove(0);
            int isBlack = root.color == Color.black ? 1 : 0;
            System.out.print(root.val + "(" + isBlack + ") ");
            if (root.left != null) {
                list.add(root.left);
            }
            if (root.right != null) {
                list.add(root.right);
            }
        }
        System.out.println();
    }
}
