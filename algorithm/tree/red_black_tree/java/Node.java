enum Color {
    black, red
}

public class Node {
    public int val;
    public Color color;
    public Node parent;
    public Node left;
    public Node right;

    public Node() {
        val = 0;
        color = Color.red;
        parent = null;
        left = null;
        right = null;
    }

    public Node(int val) {
        this.val = val;
        this.color = Color.red;
        this.parent = null;
        this.left = null;
        this.right = null;
    }

    public static Color getColor(Node node) {
        if (node == null) {
            return Color.black;
        }
        return node.color;
    }
}
