using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;
using Calc;
using ICSharpCode.AvalonEdit.Highlighting;
using ICSharpCode.AvalonEdit.Highlighting.Xshd;


namespace LiteCalc
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Calc.Calc _calc = new Calc.Calc();
        public ObservableCollection<Memory> Variables { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            Variables = new ObservableCollection<Memory>(_calc.Variables);
            this.DataContext = this;
            TextInput.Focus();

            var myAssembly = Assembly.GetExecutingAssembly().GetManifestResourceNames();
            using (var s = Assembly.GetExecutingAssembly().GetManifestResourceStream("LiteCalc.highlight.xshd"))
            {
                using (var reader = new XmlTextReader(s))
                {
                    TextInput.SyntaxHighlighting = HighlightingLoader.Load(reader, HighlightingManager.Instance);

                    TextInput.SyntaxHighlighting = TextInput.SyntaxHighlighting;
                }
            }
        }

        private void Refresh()
        {
            Variables.Clear();
            foreach (var e in _calc.Variables)
            {
                Variables.Add(e);
            }
        }

        private void TextEditor_TextChanged(object sender, EventArgs e)
        {
            if (TextInput.Text.Length <= 0)
            {
                TextResult.Text = "";
                return;
            }
            var result = _calc.Eval(TextInput.Text);

            Refresh();

            if (result == null)
            {
                TextResult.Text = "";
                return;
            }
            TextResult.Text = result.ToString();
        }

    }
}
