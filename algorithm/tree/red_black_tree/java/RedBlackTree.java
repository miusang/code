import java.util.Arrays;
import java.util.Random;

public class RedBlackTree {
    public static void main(String[] args) {
        if (args.length < 1) {
            return;
        }
        int len = Integer.parseInt(args[0]);
        int[] nums = new int[len];
        Random rand = new Random();
        RedBlackTree tree = new RedBlackTree();
        for (int i = 0; i < len;) {
            int val = rand.nextInt(1000);
            if (tree.insert(val)) {
                nums[i++] = val;
            }
        }
        System.out.println(Arrays.toString(nums));
        BinaryTree.inorderVisit(tree.root);
        BinaryTree.levelVisit(tree.root);
        
        for (int i = 0; i < len; i++) {
            tree.remove(nums[i]);
            BinaryTree.inorderVisit(tree.root);
            BinaryTree.levelVisit(tree.root);
        }
    }

    public Node root;
    public boolean insert(int val) {
        Node cur = root;
        Node parent = null;
        while (cur != null) {
            if (cur.val == val) {
                return false;
            }
            parent = cur;
            if (cur.val > val) {
                cur = cur.left;
            } else {
                cur = cur.right;
            }
        }
        Node node = new Node(val);
        if (parent == null) {
            root = node;
        } else if (parent.val > val) {
            parent.left = node;
        } else {
            parent.right = node;
        }
        node.parent = parent;
        insertFix(node);
        return true;
    }
    public boolean remove(int val) {
        Node node = find(val);
        if (node == null) {
            return false;
        }
        boolean isLeft;
        Node replace = findMax(node.left);
        if (replace == null) {
            replace = findMin(node.right);
        }
        if (replace == null) { //叶子节点
            if (node.parent == null) {
                root = null;
                return true;
            } else if (node == node.parent.left) {
                node.parent.left = null;
                isLeft = true;
            } else {
                node.parent.right = null;
                isLeft = false;
            }
            removeFix(node, isLeft);
            return true;
        }
        if (replace.val > val) {
            if (replace == replace.parent.left) {
                replace.parent.left = replace.right;
                isLeft = true;
            } else {
                replace.parent.right = replace.right;
                isLeft = false;
            }
            if (replace.right != null) {
                replace.right.parent = replace.parent;
            }
        } else {
            if (replace == replace.parent.left) {
                replace.parent.left = replace.left;
                isLeft = true;
            } else {
                replace.parent.right = replace.left;
                isLeft = false;
            }
            if (replace.left != null) {
                replace.left.parent = replace.parent;
            }
        }
        node.val = replace.val;
        removeFix(replace, isLeft);
        return true;
    }

    private void insertFix(Node node) {
        while (node != null) {
            Node p = node.parent;
            if (Node.getColor(p) == Color.black) {
                if (p == null) {
                    node.color = Color.black;
                }
                return;
            }
            Node g = p.parent;
            Node u = null;
            if (p == g.left) {
                u = g.right;
            } else {
                u = g.left;
            }
            if (Node.getColor(u) == Color.red) {
                p.color = Color.black;
                u.color = Color.black;
                g.color = Color.red;
                node = g;
                continue;
            }
            g.color = Color.red;
            if (p == g.left) {
                if (node == p.right) {
                    leftRotate(p);
                    p = p.parent;
                }
                p.color = Color.black;
                rightRotate(g);
                return;
            }
            if (node == p.left) {
                rightRotate(p);
                p = p.parent;
            }
            p.color = Color.black;
            leftRotate(g);
            return;
        }
    }

    private void removeFix(Node node, boolean isLeft) {
        while (node != null && node.parent != null && 
                node.color == Color.black) {
            Node p = node.parent;
            Node w = null;
            if (isLeft) {
                w = p.right;
                if (Node.getColor(w) == Color.red) {
                    w.color = Color.black;
                    p.color = Color.red;
                    leftRotate(p);
                    w = p.right;
                }
                if (Node.getColor(w.left) == Color.black && 
                        Node.getColor(w.right) == Color.black) {
                    w.color = Color.red;
                    node = p;
                } else {
                    if (Node.getColor(w.right) == Color.black) {
                        w.left.color = Color.black;
                        w.color = Color.red;
                        rightRotate(w);
                        w = p.right;
                    }
                    w.color = p.color;
                    p.color = Color.black;
                    w.right.color = Color.black;
                    leftRotate(p);
                    node = root;
                    continue;
                }
                if (node.parent != null) {
                    isLeft = node == node.parent.left;
                }
                continue;
            }
            w = p.left;
            if (Node.getColor(w) == Color.red) {
                w.color = Color.black;
                p.color = Color.red;
                rightRotate(p);
                w = p.left;
            }
            if (Node.getColor(w.left) == Color.black &&
                    Node.getColor(w.right) == Color.black) {
                w.color = Color.red;
                node = p;
            } else {
                if (Node.getColor(w.left) == Color.black) {
                    w.right.color = Color.black;
                    w.color = Color.red;
                    leftRotate(w);
                    w = p.left;
                }
                w.color = p.color;
                p.color = Color.black;
                w.left.color = Color.black;
                rightRotate(p);
                node = root;
                continue;
            }
            if (node.parent != null) {
                isLeft = node == node.parent.left;
            }
        }
        node.color = Color.black;
    }

    private void leftRotate(Node node) {
        if (node == null || node.right == null) {
            return;
        }
        Node parent = node.parent;
        Node right = node.right;
        if (parent == null) {
            root = right;
        } else if (node == parent.left) {
            parent.left = right;
        } else {
            parent.right = right;
        }
        right.parent = parent;
        
        node.right = right.left;
        if (node.right != null) {
            node.right.parent = node;
        }

        right.left = node;
        node.parent = right;
    }

    private void rightRotate(Node node) {
        if (node == null || node.left == null) {
            return;
        }
        Node parent = node.parent;
        Node left = node.left;
        if (parent == null) {
            root = left;
        } else if (node == parent.left) {
            parent.left = left;
        } else {
            parent.right = left;
        }
        left.parent = parent;

        node.left = left.right;
        if (node.left != null) {
            node.left.parent = node;
        }

        left.right = node;
        node.parent = left;
    }

    private Node find(int val) {
        Node cur = root;
        while (cur != null) {
            if (cur.val == val) {
                return cur;
            }
            if (cur.val > val) {
                cur = cur.left;
            } else {
                cur = cur.right;
            }
        }
        return null;
    }

    private Node findMax(Node node) {
        while (node != null && node.right != null) {
            node = node.right;
        }
        return node;
    }

    private Node findMin(Node node) {
        while (node != null && node.left != null) {
            node = node.left;
        }
        return node;
    }
}
